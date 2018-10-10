wordfre:wordfre.o wordfre_func.o libdbll.a
	gcc wordfre.o wordfre_func.o -o wordfre libdbll.a
wordfre.o:wordfre.c wordfre.h
	gcc -I/home/zhouli/dblllib -c wordfre.c
wordfre_func.o:wordfre_func.c wordfre.h
	gcc -I/home/zhouli/dblllib -c wordfre_func.c
clean:
	rm -f *.o
