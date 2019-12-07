TARGET=bf

all: ${TARGET}

TOPDIR=${shell pwd}
SRCDIR=${TOPDIR}/src

CC=gcc
CFLAGS=-I. -O3 -Wall -Werror -std=c11

SRCS=
SRCS+=${SRCDIR}/main.c
SRCS+=${SRCDIR}/utils.c
SRCS+=${SRCDIR}/vm.c

OBJS=${SRCS:.c=.o}

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS}

clean:
	rm -f ${TARGET} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<
