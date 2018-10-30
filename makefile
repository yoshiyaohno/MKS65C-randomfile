all : randomfile.o
	gcc -o randomfile randomfile.o

randomfile.o : randomfile.c randomfile.h
	gcc -c randomfile.c

run : randomfile
	./randomfile

clean : 
	rm file randomfile *.o

bug : randomfile.c randomfile.h
	gcc -g -c randomfile.c
	gcc -g -o randomfile_debug randomfile.o

debug :
	gdb randomfile_debug 
