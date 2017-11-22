#!/usr/bin/python
# coding=utf-8
import psycopg2

try:
    conn = psycopg2.connect("dbname='join' user='maldonado' host='localhost' password='maldonado'")
    print "I am connecting"
except:
    print "I am unable to connect to the database"

cur = conn.cursor()
#query = "DELETE FROM matricula WHERE id_curso='%s';"%(11)
query = "INSERT INTO matricula(id_alumno, id_curso) VALUES('%s','%s');"%(2,11)
cur.execute(query)
conn.commit()
conn.close()