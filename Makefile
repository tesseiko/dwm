# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC_DIR := src
INC_DIR := include
OBJ_DIR := builds/obj
BIN_DIR := builds/bin

EXE := $(BIN_DIR)/dwm

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: options ${EXE} modes

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"


${OBJ}: include/config.h config.mk


${EXE}: ${OBJ} | $(BIN_DIR)
	${CC} -o $@ ${OBJ} ${LDFLAGS}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

${BIN_DIR} ${OBJ_DIR}: 
	mkdir -p $@

modes:
	cp -r share/dwmmodes ${HOME}/.local/share/

clean:
	rm -f ${OBJ} dwm-${VERSION}.tar.gz *.orig *.rej compile_commands.json
	rm -rf ${OBJ_DIR} ${BIN_DIR} builds
dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.mk\
		dwm.1 drw.h util.h ${SRC} transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN_DIR}/dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	# mkdir -p ${DESTDIR}${MANPREFIX}/man1
	# sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	# chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	mkdir -p ${DESTDIR}${PREFIX}/share/dwm
	# cp -f larbs.mom ${DESTDIR}${PREFIX}/share/dwm
	# chmod 644 ${DESTDIR}${PREFIX}/share/dwm/larbs.mom

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${PREFIX}/share/dwm/larbs.mom\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

-include $(OBJ:.o=.d)

.PHONY: all options clean dist install uninstall
