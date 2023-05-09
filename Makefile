CC=gcc
CFLAGS=-O2 -Wall -fgnu89-inline
DEPS=include/dampbn.h include/palette.h include/uiconsts.h include/render.h include/input.h include/util.h include/globals.h include/audio.h
LIBS=-lalleg -lemu

all: dampbn

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dampbn: src/dampbn.o src/input.o src/render.o src/palette.o src/util.o src/audio.o
	$(CC) -o dampbn.exe src/dampbn.o src/input.o src/render.o src/palette.o src/util.o src/audio.o $(LIBS)

convert: tools/convert.o src/palette.o
	$(CC) -o tools/convert.exe tools/convert.o src/palette.o $(LIBS)

expand : tools/expand.o
	$(CC) -o tools/expand.exe tools/expand.o

prod: dampbn
	strip dampbn.exe
	upx dampbn.exe

tools: convert expand 

clean: 
	rm -f *.exe src/*.o tools/*.o tools/*.exe
