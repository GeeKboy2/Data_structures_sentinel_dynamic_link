SET_DIR = set
SEN_DIR = sentinel
DYN_DIR = dynamic
LNK_DIR=link

BIN = sentinel_struc dynamic_struc link_struc test_link sentinel_func dynamic_func link_func

CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} -I ${DYN_DIR} -I ${LNK_DIR}
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =

.PHONY: all test build clean

all: build test

build: ${BIN}

test: build
	@echo "-- run tests:"
	@for e in ${BIN}; do \
	echo -n "-- $${e} -> "; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN} *~ */*~

#for sentinel implentation
set_sentinel.o: ${SEN_DIR}/set_sentinel.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/set_sentinel.c -c

test_sentinel_struc.o: ${SEN_DIR}/test_sentinel_struc.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/test_sentinel_struc.c -c

sentinel_struc: test_sentinel_struc.o set_sentinel.o
	${CC} test_sentinel_struc.o set_sentinel.o -o $@ ${LDFLAGS}

#for dynamic implementation
set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

test_dynamic_struc.o: ${DYN_DIR}/test_dynamic_struc.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc.c -c

dynamic_struc: test_dynamic_struc.o set_dynamic.o
	${CC} test_dynamic_struc.o set_dynamic.o -o $@

#for link
link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

test_link.o : ${LNK_DIR}/test_link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link.c -c

test_link: test_link.o link.o
	${CC} test_link.o link.o -o $@ ${LDFLAGS}

#for set link
set_link.o: ${LNK_DIR}/set_link.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/set_link.c -c

test_link_struc.o : ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/set_link.h ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o set_link.o link.o
	${CC} test_link_struc.o set_link.o link.o -o $@ ${LDFLAGS}

test_set_func.o: ${SET_DIR}/test_set_func.c ${SET_DIR}/set.h 
	${CC} ${CPPFLAGS} ${CFLAGS} ${SET_DIR}/test_set_func.c -c -o $@

sentinel_func: test_set_func.o set_sentinel.o
	${CC} test_set_func.o set_sentinel.o -o $@ ${LDFLAGS}

dynamic_func: test_set_func.o set_dynamic.o
	${CC} test_set_func.o set_dynamic.o -o $@ ${LDFLAGS}

link_func: test_set_func.o set_link.o link.o
	${CC} test_set_func.o set_link.o link.o -o $@ ${LDFLAGS}