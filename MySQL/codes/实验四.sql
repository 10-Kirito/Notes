-- 第四次实验
-- 日期: 2022年12月21日
-- 作者: Kirito

-- (1) 查询每一个学生选课情况(包括没有选修课程的学生)
-- 以下查询语句查询了所有学生的选课情况，包括那些没有选课的同学
-- 因为使用的是左联结，左表的所有的记录全部会被查询显示
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
select student.student_id, student.student_name, count(distinct sc.class_id) select_num
from student inner join select_class sc on student.student_id = sc.student_id
group by student_id
having select_num >= 4;

-- (3) 检索选修课程包含  1106同学所学全部课程  的学生学号和姓名
select class_id
from select_class
where student_id = 1106;

select s.student_id, s.student_name
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join open_class oc on sc.class_id = oc.class_id
where s.student_id = 1106;




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

-- 内联结学生表来查询最后高分数对应的姓名
select sc.class_id, s.student_id, s.student_name
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


-- 检索所有课程的平均成绩
select class_id, avg(score) avg_score
from select_class
group by class_id;

-- 创建视图，给选课表添加一列属性为平均成绩的一列
create view advance_select as
select class_id, avg(score)
from select_class
group by class_id;

drop view advance_select;


select *
from advance_select;


-- 检索所有学生的成绩，形成一个成绩表，我们也可以将其创建成一个视图来看
select s.student_id, s.student_name, sc.class_id, sc.score
from student s
inner join select_class sc on s.student_id = sc.student_id;


select s.student_id, s.student_name, sc.class_id, sc.score, avg(score)
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join advance_select `as` on sc.class_id = `as`.class_id;


select s.student_id, s.student_name, avg(sc.score) as avg_grade
from student s
inner join select_class sc on s.student_id = sc.student_id
inner join class c on sc.class_id = c.class_id
where s.birthday > (select avg(birthday) from student where yxh = s.yxh);

































