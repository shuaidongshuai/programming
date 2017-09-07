#makefile 例子 #用来注释
hello:1.o 2.o 3.o
	gcc 1.o 2.o 3.o -o hello	# 格式是规定好的
1.o:1.c
	gcc -c 1.c
2.o:2.c
	gcc -c 2.c
3.o:3.c
	gcc -c 3.c
.PHONY:clean				#使用说明  make clean 
clean:					#	  就可以执行下面语句
	rm -f *.o hello
