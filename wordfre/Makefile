wordfre:wordfre.o wordfre_func.o libdbll.a
	gcc wordfre.o wordfre_func.o -o  wordfre libdbll.a
wordfre.o:wordfre.c wordfre.h
	gcc -I../dblllib -c -Wall wordfre.c
wordfre_func.o:wordfre_func.c wordfre.h
	gcc -I../dblllib -c -Wall wordfre_func.c
clean:
	rm -f *.o
