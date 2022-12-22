-- 第四次实验
-- 日期: 2022年12月21日
-- 作者: Kirito

-- (1) 查询每一个学生选课情况(包括没有选修课程的学生)
-- 以下查询语句查询了所有学生的选课情况，包括那些没有选课的同学
-- 因为使用的是左联结，左表的所有的记录全部会被查询显示
-- 试题1的答案:
select student.student_id, student.student_name, sc.term, sc.class_id, c.class_name as num
from student
    left join select_class sc
        on student.student_id = sc.student_id
    left join class c
        on sc.class_id = c.class_id;

-- 以下查询语句目的是为了从所有的学生中筛选出选择的课超过5门的同学，包括5门
select student.student_id, student.student_name, count(distinct concat(sc.term, sc.class_id, c.class_name)) as select_num
from student, select_class sc, class c
where student.student_id = sc.student_id
    and sc.class_id = c.class_id
group by student.student_id
having select_num >= 5;

-- 以下查询语句目的是为了统计所有选课的学生选择的不同课(以课的名字不同为比较基准)的数目
select student.student_id, student.student_name, count(distinct  c.class_name) as select_num
from student, select_class sc, class c
where student.student_id = sc.student_id
    and sc.class_id = c.class_id
group by student.student_id;

-- (2) 检索所有课程都选修的学生的学号与姓名
-- 以下查询语句目的是为了检索所有已经开设课程的学生与姓名
-- 试题2答案1:
select student.student_id, student.student_name, count(distinct sc.class_id) select_num
from student inner join select_class sc on student.student_id = sc.student_id
group by student_id
having select_num >= 4;

-- 试题2答案2:
-- 换一种思考角度就是没有一门课程是我不选修的
select *
from student s
where not exists(-- 该条语句注意，当下面的返回结果为空的时候才为真
    -- 下面的语句的目的是为了寻找一门该名同学没有选择过的课程
    select * from open_class c
    where not exists(
            -- 如果说该名同学选择了所有的选修课程，那么每一次返回都不为空
            -- 那么我们就找不到一门课程是该同学没有选修过的,那么就会返回空
            select * from select_class sc
            where s.student_id=sc.student_id and sc.class_id=c.class_id
        )
    );


-- (3) 检索选修课程包含  1106同学所学全部课程  的学生学号和姓名
select class_id
from select_class
where student_id = 1106;

-- 我们检索的是检索出  选修了 学号为1106的学生所选全部课程 的学生姓名
-- 我们可以转换为: 检索没有一门课(该课是什么课，被学号为1106的学生选择的课)没有被该学生选择的学生的姓名
-- 首先，题目要求的是一名学生的学号，但是这个学生X必须至少选修了学号为1106学生Y的全部课程
-- 当然学生X也可以选择学生Y没有选修的课程。因为SQL里面没有全程量词，所以说，这里需要我们使用
-- 否定的否定来实现


-- 试题3答案:
-- 参考老师PPT
-- 关键在于不存在这样的课程，学生1106选择了，而检索的学生没有选择
select distinct scx.student_id, s.student_name
from select_class scx
join student s on scx.student_id = s.student_id
where not exists(
    select *
    from select_class scy
    where scy.student_id=1106 and not exists(
        select *
        from select_class scz
        where scz.student_id=scx.student_id and scz.class_id=scy.class_id
        )
    );


-- 继续上面的检索，本次检索加入对应学生的姓名
select distinct scx.student_id, s.student_name
from select_class scx
join student s on scx.student_id = s.student_id
where not exists(
    -- 不存在下面不存在的情况
    select *
    from select_class scy
    where scy.student_id=1106 and not exists(
        -- 不存在下面的情况
        -- 下面的情况是学生
        select *
        from select_class scz
        where scz.student_id=scx.student_id and scz.class_id=scy.class_id and scx.student_id!=1106
        )
    );


-- 拓展理解，为了理解上面的例子
-- SQL语言查询选修了全部课程的


select *
from select_class x, select_class y, select_class z
where x.student_id=z.student_id and y.class_id=z.class_id;



-- (4) 查询每门课程中分数最高的学生学号和学生姓名

-- 查询选修每一门课程的学生总数，除去重复的
select sc.class_id, count(distinct sc.student_id) as stu_num
from select_class sc
group by sc.class_id;

-- 查询每一门课程中最高的分数
select sc.class_id, max( sc.score) as max_score
from select_class sc
group by sc.class_id
having max_score >= 0;

-- 利用每一门课程中的最高的分数来检索相对应的学生的学号
select sc.class_id, sc.student_id, sc.score
from select_class sc
where sc.score in (select max( sc.score) as max_score
                from select_class sc
                group by sc.class_id
                having max_score >= 0);

-- 试题4答案:
-- 内联结学生表来查询最后高分数对应的姓名
select sc.class_id, s.student_id, s.student_name, sc.score
from select_class sc
inner join student s on sc.student_id = s.student_id
where sc.score in (select max( sc.score) as max_score
                from select_class sc
                group by sc.class_id
                having max_score >= 0);


-- (5) 查询年龄小于本学院平均年龄，所有课程总评成绩都高于所选课程平均总评成绩的学生学号、姓名和平均总评成绩，按年龄排序。

-- 利用函数得到所有学生的年龄

select *, (year(now()) - year(birthday)) age
from student;

-- 计算所有学生的年龄的平均值

-- 这里我们可以使用视图来解决一些问题
-- 我们可以为学生表创建一个临时的视图，该视图相对于原来的学生表添加了年龄这一列
create view advance_student as
    select *, (year(now()) - year(birthday)) age
    from student;

-- 创建好之后，我们可以检索一下所有的年龄来试一试
select age
from advance_student;

-- 这里是求出所有人年龄的平均值，并且利用函数ceil来向上取整
select ceil(avg(age))
from advance_student;

-- 查询年龄低于平均年龄的人
select *
from advance_student
where age < (select ceil(avg(age))
            from advance_student);


select *
from student
limit 0,7;



-- 检索所有课程的平均成绩
select class_id, avg(score) avg_score
from select_class
group by class_id;

-- 创建视图，给选课表添加一列属性为平均成绩的一列
create view advance_select as
select class_id, avg(score) avg_score
from select_class
group by class_id;

drop view advance_select;


select *
from advance_select;


-- 检索所有学生的成绩，形成一个成绩表，我们也可以将其创建成一个视图来看
select s.student_id, s.student_name, sc.class_id, sc.score
from student s
inner join select_class sc on s.student_id = sc.student_id;



-- 检索所有的学生在各科的成绩，并且在最后一列检索出对应科目的平均成绩
select s.student_id stu_id, s.student_name stu_name, sc.class_id cla_id, sc.score sco, `as`.avg_score avg_sco
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join advance_select `as` on sc.class_id = `as`.class_id;



create view useful_select as
select s.student_id stu_id, s.student_name stu_name, sc.class_id cla_id, sc.score sco, `as`.avg_score avg_sco
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join advance_select `as` on sc.class_id = `as`.class_id;



-- 进行筛选，筛选出成绩大于平均成绩的
select s.student_id, s.student_name, sc.class_id, sc.score, `as`.avg_score
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join advance_select `as` on sc.class_id = `as`.class_id
where sc.score >= `as`.avg_score;



-- 进一步计数，计算出每一位学生大于平均成绩的课程数
select s.student_id, s.student_name, count(sc.class_id), sc.score, `as`.avg_score
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join advance_select `as` on sc.class_id = `as`.class_id
where sc.score >= `as`.avg_score
group by s.student_id, s.student_name
having count(sc.class_id) in (select count(*)
                             from select_class
                             group by select_class.student_id);

show tables ;

select *
from student
where birthday > (select avg(birthday) from student);

-- 该临时视图中添加了每一个人的年龄
select *
from advance_student;

-- 该临时视图中添加了额外的各个课程的平均成绩
select *
from advance_select;
drop view advance_select;





-- 所有课程总评成绩都高于所选课程平均总成绩的学生的学号、姓名和平均总成据
-- 我们可以转换为没有一门课程比所选修的课程的平均总成绩低
select distinct s.student_id, s.student_name
from student s
join select_class sc on s.student_id = sc.student_id
join advance_select `as` on sc.class_id = `as`.class_id
where not exists(
    select *
    from select_class scx
    where s.student_id=scx.student_id and not exists(
        select *
        from select_class scy
        where s.student_id=scy.student_id and scy.score < `as`.avg_score
        )
    );


select *
from useful_select usx
where not exists(
        select *
        from useful_select usy
        where not exists(
            select *
            from useful_select usz
            where usx.stu_id=usz.stu_id and usz.sco >= usz.avg_sco and usy.stu_id=usz.stu_id
            )
    );



select *
from useful_select
where sco > avg_sco;



-- 翻阅《数据库系统概论》上面的习题
-- 多表连接问题
-- 关系型数据库在执行多表连接的时候，通常是先进行两个表的连接操作，再将其连接结果与第三个表进行连接

-- 1. 先将student和select_class两个表建立连接
select s.student_id, student_name
from student s, select_class sc
where s.student_id=sc.student_id;

-- 2. 在将连接之后的表与class表建立连接
select s.student_id, student_name, class_name, class_score
from student s, select_class sc, class c
where s.student_id=sc.student_id and c.class_id=sc.class_id;


-- (1) 一个很简单的题目，与上面所讲述知识点无关┗|｀O′|┛ 嗷~~  查询与“张颖”在同一个系的同学
-- 第一步:找到张颖所在的系
select yxh
from student
where student_name='张颖';
-- 第二步:进行嵌套查询
select student_id, student_name, yxh
from student
where yxh in
    (select yxh
     from student
     where student_name='张颖');

-- 还有就是以上查询过程也可以使用下面的查询方式完成
select s1.student_id, s1.student_name
from student s1, student s2
where s1.yxh=s2.yxh and s2.student_name='张颖';
-- 该种方法中，我们可以这样去理解，我们需要检索出表1中与表2中yxh字段相同的元组(就是每一行为一个元组),
-- 但是嘞，后面又加上了另一个条件，另一个条件就是s2表中的检索出来的元组需要满足条件s2.student_name='张颖'.
-- 这样一来的话，现在表2可以说就是只有张颖的那一个元组


-- 带有EXISTS谓词的子查询
-- EXISTS代表存在量词，带有EXISTS谓词的子查询不返回任何数据，只产生逻辑值’true‘或者’false‘
-- (2) 举例，查询所有选修了’08305001‘课程的同学姓名
-- 我们可以不适用谓词EXISTS来解决这个问题:
select sc.student_id, s.student_name
from select_class sc
join student s on sc.student_id = s.student_id
where sc.class_id='08305001';
-- 可能你会想这个不简单吗？是挺简单的，但是有的时候，有的地方使用存在量词的确更加方便
-- 所以说还是得好好学习以下这个存在量词
select *
from student s
where exists
    (select *
     from select_class sc
    where s.student_id=sc.student_id and sc.class_id='08305001'
    );
-- 我们可以这样去理解，我们在s表中拿出每一个元组的student_id去检查select_class表
-- 如果说存在这样元组说s.student_id=sc.student_id and sc.class_id='08305001'
-- 那么我们就将s表中的所有字段都送到结果表当中
-- (3) 如果你仍旧嘴硬呢，你觉得存在量词不好用，那么请你看这一道题:
-- 请你检索出所有没有选修了'08305001'课程的同学姓名
select *
from student s
where not exists(
    select *
     from select_class sc
    where s.student_id=sc.student_id and sc.class_id='08305001'
    );
-- 你也可能会说，直接在最开始那里加一个！不就可以解决这个问题吗？
select sc.student_id, s.student_name
from select_class sc
join student s on sc.student_id = s.student_id
where sc.class_id!='08305001';
-- yes, you are right.But I just want to introduce this to you!
-- 好回到正题，这里not exists意思指的是，如果你从select_class中取出来的元组
-- 不可以满足下面的条件，那么你就去将s表中的所有字段取出来
-- 另外提一下，在这个例子中，你可以切身的体会到我们好像是在写while循环，而where和exists后面的则是条件
-- 至于每一次运算那就是其中的元组啦

-- (4) 检索出选修了所有课程的学生的姓名
-- 如果你讨厌存在两次的话，你肯定首先往其他方向想，也可以解决问题
-- 你可以先检索出所有学生选修的课程的数量，然后去比较该数量与课程总数量的大小，如果相等，那么就说明该学生选修了所有的课程
-- 下面的部分，我们来查看，如何利用存在量词来解决这个问题
-- 首先，我们都知道SQL中没有全称量词(for all), 所以说我们需要将所有的涉及到全称量词的题目全部转换一下:
-- 就一个任意可以使用否定的否定的来替换，这里需要自行去脑补啊，我打字打不出来的
-- 所以说我们将题目转换为:
-- 没有一门课程是他不选修的。
-- ┗|｀O′|┛ 嗷~~
-- 然后下面的语句需要自己去顿悟:
-- 注意使用了not exist存在量词之后呢，如果内层查询结果为空的话，则外层的where字句就会返回真，否则就会返回假
select *
from student
where not exists(-- 1
        select *
        from class c
        where not exists(-- 2
            -- 该处的not exists意思是筛选出那些该名同学不选修的课程
            -- 如果针对每一个元组来讲，下面的where语句成立的话，也就是该同学选修该课
            -- 那么就会返回假，这样的话，如果该名同学每一个课程都有选择的话，那么这里你想一想
            -- 那不就是全部返回假吗，对的，就是全部返回假
            -- 所以导致最外面的因为2处的where条件为假，所以也不会返回一个元组
            -- 也就是说1处由于内层返回结果为空，所以说返回真，就会返回当前满足条件的同学的所有信息
            -- ┗|｀O′|┛ 嗷~~
                select *
                from select_class sc
                where student.student_id=sc.student_id
                and c.class_id=sc.class_id
            )
    );

-- 继续上面的例子讨论
-- (5) 检索出至少选修了学生1106选修的全部课程的学生号码
-- 这里可能要和离散数学挂钩
-- 哎，和离散数学挂钩的部分先去掉
-- 我们可以这样理解，不存在一个课程，学号为1106的学生选修了，但是该同学没有选修，我们检索的就是这样的同学

select student_id
from select_class scx
where not exists(-- 1
        select * from select_class scy
        where scy.student_id='1006'
        and not exists(-- 2
            select *
            from select_class scz
            where scz.student_id=scx.student_id and scy.class_id=scz.class_id
            -- 关键在于scy.class_id=scz.class_id，这里是一个一个对于学生1006所选修的课程作比较
            -- 很遗憾，该名同学全部选修，所以说这里不会返回空，导致2处的not exists为假，所以会导致1处返回为空
            -- 刚好此时该名同学满足条件，所以将该同学筛选出来
            )
    );




















