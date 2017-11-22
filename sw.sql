select * from matricula;
begin transaction;
update matricula set id_alumno = 3 where id_curso = 11;
--rollback;
commit;
select * from matricula;