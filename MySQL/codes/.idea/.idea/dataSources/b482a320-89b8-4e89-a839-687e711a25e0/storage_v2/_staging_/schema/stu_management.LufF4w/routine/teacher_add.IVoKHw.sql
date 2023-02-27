create
    definer = kirito@`%` procedure teacher_add(IN teacherid char(10), IN teachername char(10), IN sex char(2),
                                               IN birthday datetime(6), IN post char(10), IN department char(20),
                                               IN pwd varchar(13))
begin
    insert into tb_teacher
    values (teacherid, teachername, sex, birthday, post, department, pwd);

end;



