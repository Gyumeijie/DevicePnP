.phony: all clean

SRCDIR     = ../src ../test
INCLUDE    = ../include
OBJDIR     = .
TARGET     = ../test/test_device_open

CC         = gcc
CFLAGS     = -m32 
CPPFLAGS   = -W --std=c99 -Os -I ../include/ -I ../include/utility -I ../include/drivers \
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
