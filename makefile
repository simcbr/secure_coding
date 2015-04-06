SOURCES = sanit.c sanit_str.c sanit_num.c sanit_email.c sanit_err.c
OBJECTS = $(SOURCES:.c=.o)
#OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

CC = gcc

CFLAGS = -g -Wall

PROG=sanit

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)

depend:
	makedepend -Y $(SOURCES)

clean:
	rm -f *.o 

