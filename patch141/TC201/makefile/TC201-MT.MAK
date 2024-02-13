
#  --------------------------------------------------------------------------
#      File name:  tc201-mt.mak
#                  (created by MAKEF4TC.BAS program)
#      Purpose:    Use Turbo C 2.01 MAKE, TLINK, TLIB on DOS to build
#                  Standard Function Library version 1.4.
#
#      Syntax:     MAKE -ftc201-mt.mak target
#
#                  Target      Description
#                 ---------    ---------------------------------------------
#                  library     Create standard function library
#                  testfile    Create all test files
#                  clobber     Delete LIBSFL-xx.LIB, SFL.H, *.obj *.exe
#                  clean       Delete *.obj *.exe
#                  deltest     Delete test*.obj test*.exe
#
#      Makefile notice:
#
#         1) Below variables should be carefully modified base on system setup
#            CCNAME, CCDIR, INCDEF, LIBDIR, CC, MEMORYMODEL, LIBFILE, CFLAGS,
#            OBJFLAGS, EXEFLAGES, LINK, LIB
#         2) Defined Macros list of HEADERS, OBJS, LIBS, EXES should NOT be
#            modified if you are not very sure what they are doing.
#         3) Turbo C 2.01 lacks of mktime() in library; therefore, must modify
#            TIME.H and copy MKTIME.C to SFL source directory.
#
#      Created by Jau-Bing Lin on 2023-12-25 in Taiwan.
#  --------------------------------------------------------------------------

CCNAME=tcc
CCDIR=\tc
INCDEF=$(CCDIR)\include
LIBDIR=$(CCDIR)\lib
CC=$(CCDIR)\bin\tcc
MEMORYMODEL=-mt
LIBFILE=SFLTC-mt.LIB
CFLAGS=-c -f -O -Z -w -C -I$(INCDEF) -L$(LIBDIR)
OBJFLAGS=-c -f -O -Z -w -C $(MEMORYMODEL) -I$(INCDEF) -L$(LIBDIR)
EXEFLAGS=-f -O -Z -w -C $(MEMORYMODEL) -I$(INCDEF) -L$(LIBDIR)
LINK=$(CCDIR)\bin\tlink
LIB=$(CCDIR)\bin\tlib

#               *Headfile should NOT include sfl.h*

HEADERS=\
prelude.h     sflbits.h     sflcgi.h      sflcomp.h	\
sflconv.h     sflcryp.h     sfldate.h     sfldir.h      sflenv.h	\
sflexdr.h     sflfile.h     sflfind.h     sflini.h      sflmath.h	\
sflmem.h      sflmesg.h     sflmime.h     sflnode.h     sflproc.h	\
sflslot.h     sflsock.h     sflstr.h      sflsymb.h     sfltok.h	\
sfltron.h     sfluid.h      sflvers.h     

#
# *List Macros*
#
# Only 5 files per definition. This is limitation of DOS batch files
# only 9 directly accessible parameters.
# This is a very ugly way of linking the LIBSFL.LIB, forced upon us by
# the inability of Turbo `make' 2.0 to perform command line redirection.

OBJS1=\
sflbits.obj sflcgi.obj sflcomp.obj sflconv.obj sflcryp.obj
OBJS2=\
sflcvbs.obj sflcvdp.obj sflcvds.obj sflcvns.obj sflcvsb.obj
OBJS3=\
sflcvsd.obj sflcvsn.obj sflcvst.obj sflcvtp.obj sflcvts.obj
OBJS4=\
sfldate.obj sfldir.obj sflenv.obj sflexdr.obj sflfile.obj
OBJS5=\
sflfind.obj sflini.obj sflmath.obj sflmem.obj sflmesg.obj
OBJS6=\
sflmime.obj sflnode.obj sflproc.obj sflslot.obj sflsock.obj
OBJS7=\
sflstr.obj sflsymb.obj sfltok.obj sfltron.obj sfluid.obj

OBJGROUP1=$(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) 
OBJGROUP2=$(OBJS6) $(OBJS7) 

LIBS1=\
-+sflbits.obj -+sflcgi.obj -+sflcomp.obj -+sflconv.obj -+sflcryp.obj
LIBS2=\
-+sflcvbs.obj -+sflcvdp.obj -+sflcvds.obj -+sflcvns.obj -+sflcvsb.obj
LIBS3=\
-+sflcvsd.obj -+sflcvsn.obj -+sflcvst.obj -+sflcvtp.obj -+sflcvts.obj
LIBS4=\
-+sfldate.obj -+sfldir.obj -+sflenv.obj -+sflexdr.obj -+sflfile.obj
LIBS5=\
-+sflfind.obj -+sflini.obj -+sflmath.obj -+sflmem.obj -+sflmesg.obj
LIBS6=\
-+sflmime.obj -+sflnode.obj -+sflproc.obj -+sflslot.obj -+sflsock.obj
LIBS7=\
-+sflstr.obj -+sflsymb.obj -+sfltok.obj -+sfltron.obj -+sfluid.obj

EXES1=\
testbits.exe testcgi.exe testcomp.exe testconv.exe testcryp.exe
EXES2=\
testdate.exe testdes.exe testdir.exe testexdr.exe testfind.exe
EXES3=\
testit.exe testmime.exe teststr.exe testsym.exe testuid.exe

EXES=$(EXES1) $(EXES2) $(EXES3) 

#
#               *Explicit Rules*
#
# Put SFL.h before LIBSFL.LIB, because need to create sfl.h first
# since compiler testXXX.c will include "libsfl.h"

library:	SFL.H LIBSFL.LIB

LIBSFL.LIB: $(HEADERS) $(OBJGROUP1) $(OBJGROUP2) 
            del LIBSFL.LIB
            $(LIB) LIBSFL.LIB
            $(LIB) LIBSFL.LIB $(LIBS1)
            $(LIB) LIBSFL.LIB $(LIBS2)
            $(LIB) LIBSFL.LIB $(LIBS3)
            $(LIB) LIBSFL.LIB $(LIBS4)
            $(LIB) LIBSFL.LIB $(LIBS5)
            $(LIB) LIBSFL.LIB $(LIBS6)
            $(LIB) LIBSFL.LIB $(LIBS7)
            del $(LIBFILE)
            copy LIBSFL.LIB $(LIBFILE)

SFL.H:	$(HEADERS)
	buildh              # Call buildh.bat to create sfl.h which size 109 KB
#	cpp -P- sfl.h       # Using CPP to reduce sfl.h size down to 42 kB
#	del sfl.h           # Replace sfl.h by sfl.i which is created by CPP
#	ren sfl.i sfl.h     #

clobber:	clean
	del LIBSFL.LIB
	del $(LIBFILE)
	del SFL.H

clean:
	del *.obj
	del *.exe

deltest:
	del test*.obj
	del test*.exe

#
#               *Individual File Dependencies*
#

# SFL Library file dependency

sflbits.obj:	$(HEADERS) sflbits.c
	$(CC) $(OBJFLAGS) $*.c

sflcgi.obj:	$(HEADERS) sflcgi.c
	$(CC) $(OBJFLAGS) $*.c

sflcomp.obj:	$(HEADERS) sflcomp.c
	$(CC) $(OBJFLAGS) $*.c

sflconv.obj:	$(HEADERS) sflconv.c
	$(CC) $(OBJFLAGS) $*.c

sflcryp.obj:	$(HEADERS) sflcryp.c
	$(CC) $(OBJFLAGS) $*.c

sflcvbs.obj:	$(HEADERS) sflcvbs.c
	$(CC) $(OBJFLAGS) $*.c

sflcvdp.obj:	$(HEADERS) sflcvdp.c
	$(CC) $(OBJFLAGS) $*.c

sflcvds.obj:	$(HEADERS) sflcvds.c
	$(CC) $(OBJFLAGS) $*.c

sflcvns.obj:	$(HEADERS) sflcvns.c
	$(CC) $(OBJFLAGS) $*.c

sflcvsb.obj:	$(HEADERS) sflcvsb.c
	$(CC) $(OBJFLAGS) $*.c

sflcvsd.obj:	$(HEADERS) sflcvsd.c
	$(CC) $(OBJFLAGS) $*.c

sflcvsn.obj:	$(HEADERS) sflcvsn.c
	$(CC) $(OBJFLAGS) $*.c

sflcvst.obj:	$(HEADERS) sflcvst.c
	$(CC) $(OBJFLAGS) $*.c

sflcvtp.obj:	$(HEADERS) sflcvtp.c
	$(CC) $(OBJFLAGS) $*.c

sflcvts.obj:	$(HEADERS) sflcvts.c
	$(CC) $(OBJFLAGS) $*.c

sfldate.obj:	$(HEADERS) sfldate.c mktime.c
	$(CC) $(OBJFLAGS) $*.c mktime.c

sfldir.obj:	$(HEADERS) sfldir.c
	$(CC) $(OBJFLAGS) $*.c

sflenv.obj:	$(HEADERS) sflenv.c
	$(CC) $(OBJFLAGS) $*.c

sflexdr.obj:	$(HEADERS) sflexdr.c
	$(CC) $(OBJFLAGS) $*.c

sflfile.obj:	$(HEADERS) sflfile.c
	$(CC) $(OBJFLAGS) $*.c

sflfind.obj:	$(HEADERS) sflfind.c
	$(CC) $(OBJFLAGS) $*.c

sflini.obj:	$(HEADERS) sflini.c
	$(CC) $(OBJFLAGS) $*.c

sflmath.obj:	$(HEADERS) sflmath.c
	$(CC) $(OBJFLAGS) $*.c

sflmem.obj:	$(HEADERS) sflmem.c
	$(CC) $(OBJFLAGS) $*.c

sflmesg.obj:	$(HEADERS) sflmesg.c
	$(CC) $(OBJFLAGS) $*.c

sflmime.obj:	$(HEADERS) sflmime.c
	$(CC) $(OBJFLAGS) $*.c

sflnode.obj:	$(HEADERS) sflnode.c
	$(CC) $(OBJFLAGS) $*.c

sflproc.obj:	$(HEADERS) sflproc.c
	$(CC) $(OBJFLAGS) $*.c

sflslot.obj:	$(HEADERS) sflslot.c
	$(CC) $(OBJFLAGS) $*.c

sflsock.obj:	$(HEADERS) sflsock.c
	$(CC) $(OBJFLAGS) $*.c

sflstr.obj:	$(HEADERS) sflstr.c
	$(CC) $(OBJFLAGS) $*.c

sflsymb.obj:	$(HEADERS) sflsymb.c
	$(CC) $(OBJFLAGS) $*.c

sfltok.obj:	$(HEADERS) sfltok.c
	$(CC) $(OBJFLAGS) $*.c

sfltron.obj:	$(HEADERS) sfltron.c
	$(CC) $(OBJFLAGS) $*.c

sfluid.obj:	$(HEADERS) sfluid.c
	$(CC) $(OBJFLAGS) $*.c


# Test file dependency

testfile:	$(EXES)

testbits.exe:	LIBSFL.LIB testbits.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testcgi.exe:	LIBSFL.LIB testcgi.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testcomp.exe:	LIBSFL.LIB testcomp.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testconv.exe:	LIBSFL.LIB mktime.obj testconv.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB mktime.obj

testcryp.exe:	LIBSFL.LIB testcryp.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testdate.exe:	LIBSFL.LIB mktime.obj testdate.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB mktime.obj

testdes.exe:	LIBSFL.LIB testdes.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testdir.exe:	LIBSFL.LIB mktime.obj testdir.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB mktime.obj

testexdr.exe:	LIBSFL.LIB mktime.obj testexdr.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB mktime.obj

testfind.exe:	LIBSFL.LIB testfind.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testit.exe:	LIBSFL.LIB testit.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testmime.exe:	LIBSFL.LIB mktime.obj testmime.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB mktime.obj

teststr.exe:	LIBSFL.LIB teststr.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testsym.exe:	LIBSFL.LIB testsym.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testuid.exe:	LIBSFL.LIB testuid.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

