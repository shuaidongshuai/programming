import pymysql
from Student import *

class DBUitl:
    conn = 0
    def __init__(self):
        if self.conn == 0:
            self.conn = pymysql.connect(host = "localhost", port = 3306, user = "root", password = "dong", db = "dong", charset = "utf8")

    def __del__(self):
        self.conn.close()

    def getAllStuByClazz(self, clazz):
        if self.conn == None:
            return
        sql = "SELECT student.`clazz`, student.`no`, student.`NAME`, winning.`winning` FROM student,winning WHERE student.no = winning.no AND student.`clazz` = %s"
        cursor = self.conn.cursor()
        cursor.execute(sql, (clazz, ))
        #获取查询结果
        rows = cursor.fetchall()
        list = []
        for item in rows:
            stu = Student(item[0], item[1], item[2], item[3])
            list.append(stu)

        self.conn.commit()
        cursor.close()

        return list

    def getStudentByNo(self, no):
        if self.conn == None:
            return
        sql = "SELECT * FROM student WHERE NO = %s"
        cursor = self.conn.cursor()
        cursor.execute(sql, (no, ))
        #获取查询结果
        rows = cursor.fetchall()
        stu = None
        for item in rows:
            stu = Student(item[1], item[2], item[3], '')
        self.conn.commit()
        cursor.close()
        return stu

    def getStudentByLike(self, student):
        if self.conn == None:
            return
        sql = "SELECT student.`clazz`, student.`no`, student.`NAME`, winning.`winning` FROM student,winning WHERE student.`no` = winning.`no` AND (student.no LIKE %s OR student.NAME LIKE %s OR winning.winning LIKE %s)"
        no = name = winning = ''
        if student.no:
            no = '%' + student.no + '%'
        if student.name:
            name = '%' + student.name + '%'
        if student.winning:
            winning = '%' + student.winning + '%'
        cursor = self.conn.cursor()
        cursor.execute(sql, (no, name, winning))
        #获取查询结果
        rows = cursor.fetchall()
        list = []
        for item in rows:
            stu = Student(item[0], item[1], item[2], item[3])
            list.append(stu)
        self.conn.commit()
        cursor.close()
        return list

    def insertStudent(self, student):
        if self.conn == None:
            return
        sql = "insert into student(clazz, no, name) values(%s, %s, %s)"
        cursor = self.conn.cursor()
        cursor.execute(sql, (student.clazz, student.no, student.name))
        self.conn.commit()

        cursor.close()

    def insertWinning(self, student):
        if self.conn == None:
            return
        sql = "insert into winning(no, winning) values(%s, %s)"
        cursor = self.conn.cursor()
        cursor.execute(sql, (student.no, student.winning))
        self.conn.commit()

        cursor.close()

    def delete(self, no, winning):
        if self.conn == None:
            return
        sql = "DELETE FROM winning WHERE NO = %s AND winning = %s"

        cursor = self.conn.cursor()
        cursor.execute(sql, (no, winning))
        self.conn.commit()
        cursor.close()

    def updateStudent(self, student, changeNo):
        if self.conn == None:
            return
        sql = "UPDATE student SET clazz = %s, NO = %s, NAME = %s WHERE NO = %s"
        cursor = self.conn.cursor()
        cursor.execute(sql, (student.clazz, student.no, student.name, changeNo))
        self.conn.commit()
        cursor.close()

    def updateWinning(self, student, changeNo, winning):
        if self.conn == None:
            return
        sql = "UPDATE winning SET NO = %s, winning = %s WHERE NO = %s AND winning = %s"
        cursor = self.conn.cursor()
        cursor.execute(sql, (student.no, student.winning, changeNo, winning))
        self.conn.commit()
        cursor.close()

