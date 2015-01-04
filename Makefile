# MPATE-GE 2618
# Problem Set 4 
# Makefile for audio extraction program

CC		= gcc

CFLAGS		= -g -std=c99 -Wall


audio: audio.c audio.h
	$(CC) $(CFLAGS) -o audio audio.c

clean:		
	rm -f *~ *.o a.out core audio

