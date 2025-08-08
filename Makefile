CC	=	gcc
CFLAGS	=	-std=gnu99 $(shell pkg-config --cflags sdl2)
LIBS	=	$(shell pkg-config --libs sdl2)
EXE	=	koronome
OBJS	=	\
	koronome.o	\
	player.o	\
	world.o	\
	ray.o	\
	vec.o	\
	map.o	\
	wad.o

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
