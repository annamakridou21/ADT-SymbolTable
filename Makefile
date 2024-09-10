###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2022
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################

CFLAGS = -ansi -pedantic -Wall

all: list.exe hash.exe

list: symtablelist.o testsymtab.o
	gcc $(CFLAGS) -o symlist testsymtab.o symtablelist.o;
hash: symtablehash.o testsymtab.o
	gcc $(CFLAGS) -o symhash testsymtab.o symtablehash.o;
symtablelist.o: src/symtable.h src/symtablelist.c
	gcc $(CFLAGS) -c src/symtablelist.c;
symtablehash.o: src/symtable.h src/symtablehash.c
	gcc $(CFLAGS) -c src/symtablehash.c;
testsymtab.o: src/symtable.h src/testsymtab.c
	gcc $(CFLAGS) -c src/testsymtab.c;
clean:
	rm -rf *.o;
	rm -rf symlist;
	rm -rf symhash;
