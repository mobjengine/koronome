CC	=	gcc
CFLAGS	=	-std=gnu89 -Wall -Werror $(shell pkg-config --cflags sdl2)
LIBS	=	$(shell pkg-config --libs sdl2)
EXE	=	koronome
OBJS	=	\
	koronome.o	\
	player.o

all:	$(EXE)

clean:
	rm -f $(OBJS)

run:
	./$(EXE)

$(EXE):	$(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o:	%.c
	$(CC) $(CFLAGS) -MD -MF $@.d -c $< -o $@

-include $(wildcard *.d)
