-- 第五周实验
-- (1) 建立计算机学院总评成绩不及格成绩学生的视图，包括学生学号、姓名、性别、手机、所选择课程和成绩

-- 首先先将相应的数据检索出来
select s.student_id,s.student_name,s.gender,s.phone_number, c.class_name, sc.score
from student s
join select_class sc on s.student_id = sc.student_id
join class c on sc.class_id = c.class_id
where s.yxh='01' and sc.score < 60;

-- 建立视图：
create view failed_01 as
select s.student_id,s.student_name,s.gender,s.phone_number, c.class_name, sc.score
from student s
join select_class sc on s.student_id = sc.student_id
join class c on sc.class_id = c.class_id
where s.yxh='01' and sc.score < 60;

-- (2) 在E表中插入记录，把每一个学生没有学过的课程全部插入到E表中，使得每个学生都选修每一门课程
-- 我们在插入数据之前先演练一番，防止差错数据
-- student_id, term, class_id, teacher_id, score

-- 先看下面所示代码，下面所示代码是将该名学生所有的开的课中他没有选修的可全部选择
-- 但是这样会出现一个问题，那就是开课表中我们是有着很多重复的课程的，只是由不同的老师进行教授
-- 如果我们这样筛选的话，就会导致该名学生一学期选择同样的课程很多次，不同老师教的，这样也太难为人家了
select s.student_id, os.term, os.class_id, os.teacher_id, NULL
from student s
join open_class os
where not exists(
        select * from select_class sc
        where sc.student_id=s.student_id and os.class_id=sc.class_id
    -- 注意我们这里仅仅对os表中的课号和sc表中的课号为关键条件进行检索，我们
    -- 这里不可以加上老师工号的条件，因为如果加上的话，有的课程是不同老师开设的
    -- 但是该名同学仅仅选择了一个老师，但是对于那些没有选择的老师，where条件就会不成立
    -- 就不会返回结果，where not exists就会返回真， 从而将那些选择过的课程号再次选择一遍
    )
group by s.student_id, os.class_id
-- 如果这里不以这样的条件进行分组的话
-- 就会导致不同的课程会重复选择
-- 此处的group by 的作用就是为了过滤重复
order by s.student_id asc ;

-- 答案：
# select s.student_id, sc.term, c.class_id, sc.teacher_id, NULL
# from student s
# join class c
# join select_class sc on s.student_id = sc.student_id
# where not exists(
#         select * from select_class
#         where select_class.student_id=s.student_id and select_class.class_id=c.class_id
#         -- 该行代码的意思是检索出所有的该学生学过的课但是他并没有选修的课程
#     )
# order by s.student_id asc ;

-- 参考李洪辰的答案：
select s.student_id, oc.term, oc.class_id, oc.term, oc.teacher_id
from student s
join open_class oc
where (s.student_id, oc.class_id) not in (select select_class.student_id, select_class.class_id from select_class)
group by s.student_id,oc.class_id;
-- 该行所做的事情就是将那些s表和oc表联结起来之后，此处联结起来之后就是笛卡尔积
-- 然后我们将笛卡尔积的结果去和选课表中的学生和选课课号这两个字段进行比较，如果不存在的话，说明该名学生没有选择该门课程
-- 我们就需要将该课程检索出来

-- group by
-- 使用group进行检索的时候会出现错误，原因是因为现在的MYSQL默认是不允许选择语句，HAVING条件中提及GROUP BY字句中没有命名的的属性
-- 具体的可以参考官方文档：https://dev.mysql.com/doc/refman/5.7/en/group-by-handling.html
-- 我们想要修改 ONLY_FULL_GROUP_BY SQL mode的话，我们可以先进行查看：
select @@global.sql_mode;

-- 然后我们可以将模式方面的字段设置为下面字段：
set @@global.sql_mode ='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';
-- 另一种方法：
SET GLOBAL sql_mode=(SELECT REPLACE(@@sql_mode,'ONLY_FULL_GROUP_BY',''));


-- 第二题的最终答案：

-- 我的答案：
insert into select_class(student_id, term, class_id, teacher_id, score)
select s.student_id, os.term, os.class_id, os.teacher_id, NULL
from student s
join open_class os
where not exists(
        select * from select_class sc
        where sc.student_id=s.student_id and os.class_id=sc.class_id)
group by s.student_id, os.class_id ;


-- 李洪辰的答案：
insert into select_class(student_id, term, class_id, teacher_id, score)
select s.student_id, oc.term, oc.class_id, oc.term, oc.teacher_id
from student s
join open_class oc
where (s.student_id, oc.class_id) not in (select select_class.student_id, select_class.class_id from select_class)
group by s.student_id,oc.class_id;

-- (3) 检索出年龄大于所有女同学年龄的男学生的姓名和年龄

-- 先将所有女同学的最大年龄检索出来
select min(birthday)
from student
where gender='女';

-- 检索出所有的年龄大于所有女同学年龄的男同学的姓名和年龄
select *
from student
where gender='男' and birthday < (select min(birthday)
from student
where gender='女');

-- 第三题答案
select *
from student
where gender='男' and birthday < (select min(birthday)
from student
where gender='女');


-- (4) 在E表中修改08305001课程的平时成绩，如果成绩小于等于75分时候提高5%，如果成绩大于75分的时候提高4%
select *
from select_class
where class_id='08305001';

-- 该题目应该就是考察我们对于update关键字的使用吧
-- 如果成绩小于等于75分的时候提高成绩5%
update select_class set score=score*105/100 where score <= 75 and class_id ='08305001';

-- 如果成绩大于75岁就提高4%
update select_class set score=score*104/100 where score > 75 and class_id = '08305001';


select *
from select_class
where score is not null;
-- (5) 删除没有开课的学院

-- 首先我们检索出所有开课的学院
select distinct class.yxh
from class
join open_class oc on class.class_id = oc.class_id
group by class.class_id;

-- 其次从学院中删除没有开课的学院
-- 如果我们直接删除该学院的话，由于别的表的外键约束，导致我们会删除失败
-- 所以我们应该使用级联删除
-- 下面代码是错误的
# delete from department
# where yxh not in (
#     select distinct class.yxh
#     from class
#     join open_class oc on class.class_id = oc.class_id
#     group by class.class_id);


-- 下面做的事情是创建一个数据库仅仅用来测试使用，创建了两个测试用表
-- 使用delete去联结删除多个表
CREATE TABLE test (
    id int primary key auto_increment
);

CREATE TABLE test0 (
    id varchar(20) primary key ,
    ref int not null
);


insert into test values (1),(2),(3);

insert into test0 (id, ref)
values ('A',1),('B',2),('C',3);

delete test, test0
from test
join test0 on test0.ref=test.id
where test.id=1;

select *
from test;

-- 以下部分讲述的是如何利用级联删除数据，即可以无视外键的约束进行删除操作
-- 我们如果想要使用级联删除或者级联更新的话，我们需要先对外键的属性进行设置
-- 将其设置为ON DELETE CASCADE 级联删除
-- 级联删除是指当主表的关联记录被删除的时候，从表会自动删除与主表删除记录相关行的记录
-- 或者设置为ON UPDATE CASCADE 级联更新
-- 级联更新是指当主表的主键发生更新的时候，从表关联的所有的数据都会自动更新

-- 以上最后一个单词的意思是级联
-- 这一般称为行为，常见的行为有：
-- NO ACTION, 如果行为设置为NO ACTION的话，当在父表中删除/更新对应记录的时候，会首先检查该记录是否有对应外键，如果有的话就不允许删除/更新
-- RESTRICT, 和NO ACTION是一样的属性
-- CASCADE, 如上面所示，即使父表中的记录具有对应的外键的话，仍旧更新或者删除在子表中的数据；
-- SET NULL, 如果我们删除的记录具有外键的话，我们就讲子表中对应的外键的值为NULL, 但是我们需要该键的属性不是NOT NULL,否则也会失败
alter table student drop foreign key fk_student_yxh;
alter table teacher drop foreign key fk_tearcher_yxh;
alter table class drop foreign key fk_class_yxh;
-- 此处我们对学生表中的外键属性进行修改，如果说主键删除数据的话，子表中对应的数据设置为NULL,因为我们将学院删除的话并不代表学生也得删除
-- 所以说我们将其设置为ON DELETE SET NULL
-- 对于更新的话，那很自然，我们将其属性设置为ON UPDATE CASCADE即可
ALTER TABLE student add constraint fk_student_yxh FOREIGN KEY (yxh) references department(yxh) on update cascade on delete set null ;
ALTER TABLE teacher add constraint fk_tearcher_yxh FOREIGN KEY (yxh) references department(yxh) on update cascade on delete set null ;
ALTER TABLE class add constraint fk_class_yxh FOREIGN KEY (yxh) references department(yxh) on update cascade on delete cascade ;

SHOW CREATE TABLE student;
show create table teacher;


ALTER TABLE student CHANGE yxh yxh char(10);
ALTER TABLE teacher change yxh yxh char(10);
ALTER TABLE class CHANGE yxh yxh char(10);

-- 好接下来我们再对其进行修改
-- 第5题最终答案：
delete from department
where yxh not in (
    select distinct class.yxh
    from class
    join open_class oc on class.class_id = oc.class_id
    group by class.class_id);


-- (6) 查询优、良、中、及格、不及格学生个数
-- 对于此种情况我们可以使用case关键字
6.
select score,
    case
        when score < 60 and score >= 0 then '不及格'
        when score >= 60 and score < 70 then '及格'
        when score >= 70 and score < 80 then '中'
        when score >= 80 and score < 90 then '良'
        when score >= 90 and score < 100 then '优'
    else '无成绩' end as Evaluation
from select_class;

-- 第六题答案
select Evaluation, count(*) as Total
from (
    select score,
    case
        when score < 60 and score >= 0 then '不及格'
        when score >= 60 and score < 70 then '及格'
        when score >= 70 and score < 80 then '中'
        when score >= 80 and score < 90 then '良'
        when score >= 90 and score < 100 then '优'
    else '无成绩' end as Evaluation
    from select_class
) TEMP_TABLE
group by Evaluation
ORDER BY FIELD(Evaluation,
    '优',
    '良',
    '中',
    '及格',
    '不及格',
    '无成绩');

-- 第二种方法
select
    (select count(*) from select_class where score >= 90) '优',
    (select count(*) from select_class where score < 90 and score >= 80) '良',
    (select count(*) from select_class where score < 80 and score >= 70) '中',
    (select count(*) from select_class where score < 70 and score >= 60) '及格',
    (select count(*) from select_class where score < 60 and score >= 0) '不及格',
    (select count(*) from select_class where score is null) '无成绩';


-- 研讨题目
-- (1) 关于删除具有外键约束的表来讲，更新或者删除数据的时候会出现什么问题？
-- (2) 如果学生在一学期当中不及格的课程学分之和达到该学期所修学分的二分之一，将进入试读期，请根据最近结束的学期获得试读的学生的状态改为试读。

