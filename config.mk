# See LICENSE for details
# configuration for the compilation
VERSION = 0.1.0
CC = gcc
CFLAGS = -W -Wall -pedantic -std=c99 -g
CPPFLAGS = -DVERSION=\"$(VERSION)\"
HELP2MAN=help2man
LDFLAGS = -static
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< $(LDFLAGS)
