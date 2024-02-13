
#  --------------------------------------------------------------------------
#       File name:  library.mak
#
#       Purpose:    Use Microsoft C 5.0 MAKE, LINK, LIB on DOS to build
#                   Standard Function Library version 1.4 source code.
#
#       Syntax:		MAKE filename
#
#                   filename			Description
#                  -------------    -----------------------------------------
#                   headfile.mak	Create SFL.H
#                   MSC50-AL.mak	Create standard function library
#                   testfile.mak	Create all test files
#                   clobber.mak		Delete LIBSFL.LIB, SFL.H, *.obj *.exe
#                   clean.mak		Delete *.obj *.exe
#                   deltest.mak		Delete test*.obj test*.exe
#
#       Makefile notice:
#
#          1) Below variables should be carefully modified base on system setup
#             CCNAME, CCDIR, INCDEF, LIBDIR, CC, MEMORYMODEL, LIBFILE, CFLAGS,
#             OBJFLAGS, EXEFLAGES, LINK, LIB
#          2) Defined Macros list of HEADERS, OBJS, LIBS, EXES should NOT be
#             modified if you are not very sure what they are doing.
#          3) Microsoft C 5.0 and QuickC 2.01 cannot handle macro definition in
#             'sflcryp.c'; therfore, need to remove all encrypt related
#             programs, e.g. 'sflcryp' 'testcryp' 'testdes' with sub file name
#             .h .obj .c in makefile
#
# 	    Created by Jau-Bing Lin on 2023-11-24 in Taiwan.
#  --------------------------------------------------------------------------

CCNAME=MSC50
CCDIR=\msc50
INCDEF=$(CCDIR)\include
LIBDIR=$(CCDIR)\lib
CC=$(CCDIR)\bin\cl
MEMORYMODEL=/AL
LIBFILE=SFLMSCal.LIB
#CFLAGS=/c /FPi /O /Ol /W1 /I$(INCDEF)
CFLAGS=/c
#OBJFLAGS=/c /FPi /O /Ol /W1 $(MEMORYMODEL) /I$(INCDEF)
OBJFLAGS=/c $(MEMORYMODEL)
#EXEFLAGS=/FPi /O /Ol /W1 $(MEMORYMODEL) /I$(INCDEF)
EXEFLAGS=$(MEMORYMODEL)
LINK=$(CCDIR)\bin\link
LIB=$(CCDIR)\bin\lib

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
sflbits.obj sflcgi.obj sflcomp.obj sflconv.obj 
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
-+sflbits.obj -+sflcgi.obj -+sflcomp.obj -+sflconv.obj 
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

#library:	SFL.H LIBSFL.LIB

LIBSFL.LIB: $(HEADERS) $(OBJGROUP1) $(OBJGROUP2) 
			echo $(HEADERS) 
			echo $(OBJGROUP1) 
			echo $(OBJGROUP2)
            del LIBSFL.LIB
            $(LIB) LIBSFL.LIB;
            $(LIB) LIBSFL.LIB $(LIBS1);
            $(LIB) LIBSFL.LIB $(LIBS2);
            $(LIB) LIBSFL.LIB $(LIBS3);
            $(LIB) LIBSFL.LIB $(LIBS4);
            $(LIB) LIBSFL.LIB $(LIBS5);
            $(LIB) LIBSFL.LIB $(LIBS6);
            $(LIB) LIBSFL.LIB $(LIBS7);
            del $(LIBFILE)
            copy LIBSFL.LIB $(LIBFILE)

