CC	=	gcc
CFLAGS	=	-std=gnu99 -Wall $(shell pkg-config --cflags sdl2)
LIBS	=	$(shell pkg-config --libs sdl2)
EXE	=	koronome
OBJS	=	\
	k_main.o	\
	k_world.o

all:	$(EXE)

clean:
	rm -f $(OBJS)

$(EXE):	$(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
