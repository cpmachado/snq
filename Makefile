# See LICENSE for details
# Makefile for snq

include config.mk

SRC = snq.c
OBJ = ${SRC:.c=.o}

PKGFILES= ${SRC}\
	LICENSE\
	Makefile\
	README.md\
	snq.1

all: snq

snq: ${OBJ}
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ ${OBJ} $(LDFLAGS)

clean:
	@echo cleaning
	$(RM) snq ${OBJ} snq-${VERSION}.tar.gz

dist: clean
	mkdir snq-${VERSION}
	cp ${PKGFILES} snq-${VERSION}
	tar -cf snq-${VERSION}.tar snq-${VERSION}
	gzip snq-${VERSION}.tar
	$(RM) -r snq-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f snq ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/snq
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@cp snq.1 ${DESTDIR}${MANPREFIX}/man1/snq.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/snq.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/snq

.PHONY: all clean dist install uninstall
