CC=gcc

SRCS=main.c

OBJS=$(SRCS:.c=.o)

EXEC=myapp

start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -L. -lmylib
.c.o:
	$(CC) -o $@ -c $<  #生成位置无关的代码

clean:
	rm -rf $(OBJS)
