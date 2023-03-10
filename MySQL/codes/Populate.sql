-- define foreign keys --
ALTER TABLE student ADD CONSTRAINT fk_student_yxh FOREIGN KEY (yxh) REFERENCES department (yxh);
ALTER TABLE teacher ADD CONSTRAINT fk_tearcher_yxh FOREIGN KEY (yxh) REFERENCES department (yxh);

ALTER TABLE class ADD CONSTRAINT fk_class_yxh FOREIGN KEY (yxh) REFERENCES department (yxh);

ALTER TABLE open_class ADD CONSTRAINT fk_open_class FOREIGN KEY (class_id) REFERENCES class (class_id);
ALTER TABLE open_class ADD CONSTRAINT fk_open_tercher FOREIGN KEY (teacher_id) REFERENCES teacher (teacher_id);

ALTER TABLE select_class ADD CONSTRAINT fk_select_student FOREIGN KEY (student_id) REFERENCES student (student_id);
ALTER TABLE select_class ADD CONSTRAINT fk_select_class FOREIGN KEY (class_id) REFERENCES class (class_id);
ALTER TABLE select_class ADD CONSTRAINT fk_select_teacher FOREIGN KEY (teacher_id) REFERENCES teacher (teacher_id);


alter table open_class drop foreign key fk_open_class;
alter table open_class drop foreign key fk_open_tercher;

drop table open_class;


drop table select_class;
# show create table select_class;
# show create table open_class;
# alter table open_class modify column term varchar(30);
# alter table open_class modify column class_id char(15);
# alter table open_class drop foreign key fk_open_class;




-- Populate student table --
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1101,'李明','男','1993-03-06','上海','13613005486','02');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1102,'刘晓明','男','1992-12-08','安徽','18913457890','01');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1103,'张颖','女','1993-01-05','江苏','18826490423','01');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1104,'刘晶晶','女','1994-11-06','上海','13331934111','01');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1105,'刘成刚','男','1991-06-07','上海','18015872567','01');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1106,'李二丽','女','1993-05-04','江苏','18107620945','01');
INSERT INTO student(student_id, student_name, gender, birthday, native_place, phone_number, yxh)
VALUES (1107,'张晓峰','男','1992-08-16','浙江','13912341078','01');

-- Populate department table --
INSERT INTO department(yxh, depart_name, depart_place, depart_phone)
VALUES ('01','计算机学院','上大东校区三号楼','65347567');
INSERT INTO department(yxh, depart_name, depart_place, depart_phone)
VALUES ('02','通讯学院','上大东校区二号楼','65341234');
INSERT INTO department(yxh, depart_name, depart_place, depart_phone)
VALUES ('03','材料学院','上大东校区四号楼','65347890');

-- Populate teacher table --
INSERT INTO teacher(teacher_id, teacher_name, gender, birthday, job_title, yxh)
VALUES ('0101','陈迪茂','男','1973-03-06','副教授','01');
INSERT INTO teacher(teacher_id, teacher_name, gender, birthday, job_title, yxh)
VALUES ('0102','马小红','女','1972-12-08','讲师','01');
INSERT INTO teacher(teacher_id, teacher_name, gender, birthday, job_title, yxh)
VALUES ('0201','张心颖','女','1960-01-05','教授','02');
INSERT INTO teacher(teacher_id, teacher_name, gender, birthday, job_title, yxh)
VALUES ('0103','吴宝钢','男','1980-11-06','讲师','01');

-- Populate open_class table --
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201201','08305001','0103','星期三5-8');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201202','08305002','0101','星期三1-4');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201202','08305002','0102','星期三1-4');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201202','08305002','0103','星期三1-4');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201202','08305003','0102','星期五5-8');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201301','08305004','0101','星期二1-4');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201301','08305001','0102','星期三5-8');
INSERT INTO open_class(term, class_id, teacher_id, schooltime)
VALUES ('201302','08302001','0201','星期三5-8');
-- change the primary key of table --
-- alter table open_class drop primary key ;
-- alter table open_class add primary key (term,class_id,teacher_id);


-- Populate class table --
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08305001','离散数学',4,40,'01');
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08305002','数据库原理',4,50,'01');
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08305003','数据结构',4,50,'01');
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08305004','系统结构',6,60,'01');
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08301001','分子物理学',4,40,'03');
INSERT INTO class(class_id, class_name, class_score, class_time, yxh)
VALUES ('08302001','通信学',3,30,'02');
-- show create table class;

-- Populate class table --
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1101,'201201','08305001','0103',60);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1102,'201201','08305001','0103',87);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1102,'201202','08305002','0103',82);
INSERT INTO select_class(student_id, term, class_id, teacher_id)
VALUES (1102,'201301','08305004','0101');
INSERT INTO select_class(student_id, term, class_id, teacher_id,score)
VALUES (1103,'201201','08305001','0103',56);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1103,'201202','08305002','0102',75);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1103,'201202','08305003','0102',84);
INSERT INTO select_class(student_id, term, class_id, teacher_id)
VALUES (1103,'201301','08305001','0102');
INSERT INTO select_class(student_id, term, class_id, teacher_id)
VALUES (1103,'201301','08305004','0101');
INSERT INTO select_class(student_id, term, class_id, teacher_id,score)
VALUES (1104,'201201','08305001','0103',74);
INSERT INTO select_class(student_id, term, class_id, teacher_id)
VALUES (1104,'201302','08302001','0201');
INSERT INTO select_class(student_id, term, class_id, teacher_id,score)
VALUES (1106,'201201','08305001','0103',85);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1106,'201202','08305002','0103',66);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1107,'201201','08305001','0103',90);
INSERT INTO select_class(student_id, term, class_id, teacher_id, score)
VALUES (1107,'201202','08305003','0102',79);
INSERT INTO select_class(student_id, term, class_id, teacher_id)
VALUES (1107,'2013-2014秋季','08305004','0101');

-- alter table select_class modify column term varchar(30);