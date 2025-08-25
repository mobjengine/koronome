CC	=	gcc
CFLAGS	=	-std=c99 $(shell pkg-config --cflags sdl2)
LIBS	=	-lzip -lm $(shell pkg-config --libs sdl2)
EXE	=	koronome
OBJS	=	\
	rxi_map.o	\
	rxi_vec.o	\
	k_main.o	\
	k_world.o	\
	k_lump.o	\
	k_playpal.o

all:	$(EXE)

clean:
	rm -f $(OBJS)

koronome.zkd:
	cd koronome.zkd.dir && zip -9 ../koronome.zkd *

$(EXE):	$(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
