#makefile 例子 #用来注释
hello:1.o 2.o 3.o
	gcc -o $@ $^
.c.o:
	gcc -c $<
.PHONY:clean				#使用说明  make clean 
clean:					#	  就可以执行下面语句
	rm -f *.o hello
