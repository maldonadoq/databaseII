/*with tab as(
	select
		alumnos.id_alumno as alumno_id,
		alumnos.name as alumno_na,
		curso.id_curso as curso_id,
		curso.name as curso_na
	from alumnos, curso
)
select
	tab.alumno_id as "Id A",
	tab.alumno_na as "Alumno",
	tab.curso_id as "Id C",
	tab.curso_na as "Curso",
	case
		coalesce(mat.id_alumno,'0')
		when '0' then 'no'
		else 'si'
	end as "Status"
from tab
left join matricula as mat on mat.id_alumno = tab.alumno_id and mat.id_curso = tab.curso_id
order by tab.alumno_id;*/

--select *from tmp;

/*
create materialized view tmp as
select
	al.id_alumno,
	al.name as aname,
	cur.id_curso,
	cur.name as cname
from alumnos as al
inner join matricula as mat on mat.id_alumno = al.id_alumno
inner join curso as cur on cur.id_curso = mat.id_curso


create temp table tab as(
	select
		al.id_alumno,
		al.name as aname,
		cur.id_curso,
		cur.name as cname
	from alumnos as al
	inner join matricula as mat on mat.id_alumno = al.id_alumno
	inner join curso as cur on cur.id_curso = mat.id_curso
);



--insert into alumnos(id_alumno, name) values(6,'Gerard');
--insert into matricula(id_alumno, id_curso) values(6,11);
select * from alumnos;
select * from curso;

select * from tab;
select * from tmp;*/

create temp table tab as(
	select
		v.producto,
		v.fecha,
		sum(v.monto) as monto
	from venta as v
	group by v.fecha, v.producto
);


with tab1 as(
	select 
		*
	from aux, fecha
)
select
	tab1.producto,
	tab1.fecha,
	--tab.monto
	coalesce(tab.monto,'0')
from tab1
full outer join tab on tab.fecha = tab1.fecha and tab.producto = tab1.producto
order by tab1.producto;