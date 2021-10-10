INCLUDE = -Wall -Wextra -std=c11 -O2

CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2
LDFLAGS  =

.PHONY: all clean

all: similar_lines

similar_lines: similar_lines.o check.o load.o processing_functions.o print.o
	gcc $(INCLUDE) -o similar_lines similar_lines.o check.o load.o processing_functions.o print.o
print.o: print.c print.h structures.h
	gcc $(INCLUDE) -c print.c
processing_functions.o: processing_functions.c processing_functions.h check.h structures.h
	gcc $(INCLUDE) -c processing_functions.c
load.o: load.c load.h load.h structures.h
	gcc $(INCLUDE) -c load.c
check.o: check.c check.h
	gcc $(INCLUDE) -c check.c
similar_lines.o: similar_lines.c check.h load.h processing_functions.h print.h structures.h
	gcc $(INCLUDE) -c similar_lines.c


clean:
	rm -f *.o similar_lines