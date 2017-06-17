#########################################################################
# vim: ts=8 sw=8
#########################################################################
# Author:   tf135c (James Reynolds)
# Filename: Makefile
# Date:     2007-01-16 13:41:28
#########################################################################
# Note that we use '::' rules to allow multiple rule sets for the same
# target.  Read that as "modularity exemplarized".
#########################################################################

PREFIX	:=${HOME}/opt/$(shell uname -m)
BINDIR	=${PREFIX}/bin

TARGETS	=all clean distclean clobber check install uninstall tags
TARGET	=all

.SUFFIXES: .lst

%.lst: %.o
	objdump -dS $< >$@.tmp && move-if-change $@.tmp $@

SUBDIRS	=

.PHONY:	${TARGETS} ${SUBDIRS}

CC	=ccache gcc4 -march=i686 -std=gnu99
DEFS	=-D_FORTIFY_SOURCE=2
OPT	=-Os
# OPT	=-O6
INCS	=-I.
CFLAGS	=${OPT} -Wall -Wextra -Werror -pedantic -pipe -g ${DEFS} ${INCS}
LDFLAGS	=-g
LDLIBS	=-lSegFault

all::	carebear carebear.lst

${TARGETS}::

clean::
	${RM} a.out *.o core.* lint tags

distclean clobber:: clean
	${RM} carebear carebear.lst

check::	carebear
	./carebear ${ARGS}

install:: carebear
	install -d ${BINDIR}
	install -c -s carebear ${BINDIR}/

uninstall::
	${RM} ${BINDIR}/carebear

tags::
	ctags -R .

# ${TARGETS}::
# 	${MAKE} TARGET=$@ ${SUBDIRS}

# ${SUBDIRS}::
# 	${MAKE} -C $@ ${TARGET}
