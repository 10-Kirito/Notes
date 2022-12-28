-- create the student table --
CREATE TABLE Student
(
    student_id      int         NOT NULL AUTO_INCREMENT ,
    student_name            char(50)    NOT NULL ,
    gender          char(5)     NOT NULL ,
    birthday        datetime    NOT NULL ,
    native_place    char(50)    NOT NULL ,
    phone_number    char(50)    NOT NULL ,
    yxh             char(10)    NOT NULL ,
    state           char(20)    NULL ,

    PRIMARY KEY (student_id)
) ENGINE=InnoDB;
alter table Student change birthday birthday date not null ;

-- create table of departments --
CREATE TABLE department
(
    yxh             char(10)    NOT NULL ,
    depart_name     char(50)    NOT NULL ,
    depart_place    char(100)   NOT NULL ,
    depart_phone    char(50)    NOT NULL ,

    PRIMARY KEY (yxh)
) ENGINE = InnoDB;

drop table department;

-- create table of teachers --
CREATE TABLE teacher
(
    teacher_id      char(10)    NOT NULL ,
    teacher_name    char(20)    NOT NULL ,
    gender          char(2)     NOT NULL ,
    birthday        datetime    NOT NULL ,
    job_title       char(10)    NOT NULL ,
    yxh             char(10)    NOT NULL ,

    PRIMARY KEY (teacher_id)
) ENGINE = InnoDB;

alter table teacher change birthday birthday date not null ;

-- create the table of class --
CREATE TABLE class
(
    class_id        char(15)    NOT NULL ,
    class_name      char(20)    NOT NULL ,
    class_score     int         NOT NULL ,
    class_time      int         NOT NULL ,
    yxh             char(10)    NOT NULL ,

    PRIMARY KEY (class_id)
) ENGINE = InnoDB;

drop table class;

-- create the table of open_class --
CREATE TABLE open_class
(
    term            char(10)    NOT NULL ,
    class_id        char(10)    NOT NULL ,
    teacher_id      char(10)    NOT NULL ,
    schooltime      char(20)    NOT NULL ,

    PRIMARY KEY (term,class_id,teacher_id)
) ENGINE = InnoDB;


alter table open_class change term term varchar(30) not null ;

drop table open_class;
-- create the table of select_class
CREATE TABLE select_class
(
    student_id      int         NOT NULL ,
    term            varchar(30)    NOT NULL ,
    class_id        char(15)    NOT NULL ,
    teacher_id      char(10)    NOT NULL ,
    score           int         NULL ,

    PRIMARY KEY (student_id,term,class_id,teacher_id)
) ENGINE = InnoDB;

alter table select_class change term term varchar(30) not null ;

drop table select_class;