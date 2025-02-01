# See LICENSE for details
# configuration for the compilation
VERSION = 0.4.0
CC = gcc
CFLAGS = -W -Wall -pedantic -std=c99 -g
CPPFLAGS =\
	-DVERSION=\"${VERSION}\"\
	-D_BSD_SOURCE\
	-D_DEFAULT_SOURCE\
	-D_POSIX_C_SOURCE=200809L
LDFLAGS = -static
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< $(LDFLAGS)
