
#  --------------------------------------------------------------------------
#       File name:  deltest.mak
#
#       Purpose:    Use Microsoft C 5.0 MAKE, LINK, LIB on DOS to build
#                   Standard Function Library version 1.4 source code.
#
#       Syntax:		MAKE filename
#
#                   filename			Description
#                  -------------    -----------------------------------------
#                   headfile.mak	Create SFL.H
#                   MSC50-AM.mak	Create standard function library
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

deltest:
	del test*.obj
	del test*.exe