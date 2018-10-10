ls:ls.o ls_func.o libdbll.a
	gcc ls.o ls_func.o -o ls libdbll.a
ls.o:ls.c ls.h
	gcc -I/home/zhouli/dblllib -c ls.c
ls_func.o:ls_func.c ls.h
	gcc -I/home/zhouli/dblllib -c ls_func.c
clean:
	rm -f *.o
