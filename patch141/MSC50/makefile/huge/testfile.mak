
#  --------------------------------------------------------------------------
#       File name:  testfile.mak
#
#       Purpose:    Use Microsoft C 5.0 MAKE, LINK, LIB on DOS to build
#                   Standard Function Library version 1.4 source code.
#
#       Syntax:		MAKE filename
#
#                   filename			Description
#                  -------------    -----------------------------------------
#                   headfile.mak	Create SFL.H
#                   MSC50-AH.mak	Create standard function library
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
MEMORYMODEL=/AH
LIBFILE=SFLMSCah.LIB
#CFLAGS=/c /FPi /O /Ol /W1 /I$(INCDEF)
CFLAGS=/c
#OBJFLAGS=/c /FPi /O /Ol /W1 $(MEMORYMODEL) /I$(INCDEF)
OBJFLAGS=/c $(MEMORYMODEL)
#EXEFLAGS=/FPi /O /Ol /W1 $(MEMORYMODEL) /I$(INCDEF)
EXEFLAGS=$(MEMORYMODEL)
LINK=$(CCDIR)\bin\link
LIB=$(CCDIR)\bin\lib


EXES1=\
testbits.exe testcgi.exe testcomp.exe testconv.exe testcryp.exe
EXES2=\
testdate.exe testdes.exe testdir.exe testexdr.exe testfind.exe
EXES3=\
testit.exe testmime.exe teststr.exe testsym.exe testuid.exe

EXES=$(EXES1) $(EXES2) $(EXES3) 


# Test file dependency

#testfile:	$(EXES)

testbits.exe:	LIBSFL.LIB testbits.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testcgi.exe:	LIBSFL.LIB testcgi.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testcomp.exe:	LIBSFL.LIB testcomp.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testconv.exe:	LIBSFL.LIB testconv.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB 

#testcryp.exe:	LIBSFL.LIB testcryp.c
#	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testdate.exe:	LIBSFL.LIB testdate.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB 

#testdes.exe:	LIBSFL.LIB testdes.c
#	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testdir.exe:	LIBSFL.LIB testdir.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB 

testexdr.exe:	LIBSFL.LIB testexdr.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB 

testfind.exe:	LIBSFL.LIB testfind.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testit.exe:	LIBSFL.LIB testit.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testmime.exe:	LIBSFL.LIB testmime.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB 

teststr.exe:	LIBSFL.LIB teststr.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testsym.exe:	LIBSFL.LIB testsym.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

testuid.exe:	LIBSFL.LIB testuid.c
	$(CC) $(EXEFLAGS) $*.c LIBSFL.LIB

