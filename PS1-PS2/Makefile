vari = program.o read.o
compilation: $(vari)
	gcc -o out $(vari)
program.o: program.c read.h
	gcc -c program.c
read.o: read.h read.c
	gcc -c read.c
.PHONY: clean
clean:
	rm -f *.o out
