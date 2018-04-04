CC = g++
CFLAGS = -std=gnu++11 -lstdc++ -Wall -Wextra -Werror -O2 -I.
LFLAGS = -lm

DEPS = receiver.h sender.h utils.h
OBJ = main.o receiver.o sender.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

talking-dockers: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm $(OBJ)

distclean:
	rm router $(OBJ)
