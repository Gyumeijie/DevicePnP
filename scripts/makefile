#
# Copyright 2004 P&P Software GmbH (Konstanz, Germany) - All Rights Reserved
#
# Makefile
#
# Version      1.5
# Date         22.12.03
# Author       R. Totaro / A. Pasetti
#
# Makefile to build the RegressionTest for the OBS Framework, the test coverage files, and some test programs
# useful as references for memory occupation tests.

.phony: all clean

SRCDIR     = ../src ../test
INCLUDE    = ../include
OBJDIR     = .
TARGET     = ../test/test_device_open

CC         = sparc-elf-gcc
CFLAGS     = 
CPPFLAGS   = -W --std=c99 -I ../include/ -I ../include/utility -I ../include/drivers \
			 -I ../include/interpreter -I ../include/mxml -I ../test  
LDFLAGS    = 

VPATH      = ${shell for dir in `find ${SRCDIR} -type d`;do echo -n $$dir:;done}

HFILES     = ${shell find ${SRCDIR} -name \*.h}
CPPSOURCES = ${shell find ${SRCDIR} -name \*.cpp}
CSOURCES   = ${shell find  ${SRCDIR} -name \*.c}
SOURCES    = ${CPPSOURCES} ${CSOURCES}
OBJECTS    = ${shell for obj in ${CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

${OBJDIR}/%.o: %.c
	${CC} -c ${CFLAGS} ${CPPFLAGS} $< -o $@

all: ${TARGET}

ifeq (.depend,${wildcard .depend})
include .depend
endif

${OBJECTS}: .depend

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} ${OBJECTS} -o $@

.depend: ${SOURCES} ${HFILES}
	@echo -n > .depend.tmp
	/usr/bin/makedepend -f.depend.tmp -- ${CPPFLAGS} -- ${SOURCES} 2>/dev/null
	@sed -e "s@^[^:]*/@${OBJDIR}/@" < .depend.tmp > .depend

clean:
	rm -f  .depend *~ *.html *.txt 
	cd ${OBJDIR}; rm -f *.o 

cleanObj:
	cd ${OBJDIR}; rm -f *.o
