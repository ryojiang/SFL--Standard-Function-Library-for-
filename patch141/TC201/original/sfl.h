/*  ----------------------------------------------------------------<Prolog>-
    Name:       prelude.h
    Title:      Universal Header File for C programming
    Package:    Standard Function Library (SFL)

    Written:    93/03/29    Pieter Hintjens <ph@imatix.com>
    Revised:    97/01/02    Ewen McNeill <ewen@naos.co.nz>

    Version:    1.4
    <TABLE>
    1.4_PH      Released with SFL 1.4
    </TABLE>

    Synopsis:   This header file encapsulates many generally-useful include
                files and defines lots of good stuff.  The intention of this
                header file is to hide the messy #ifdef's that you typically
                need to make real programs compile & run.  To use, specify
                as the first include file in your program.

                The main contributors to this file were:
                <Table>
                PH   Pieter Hintjens    <ph@imatix.com>
                PA   Pascal Antonnaux   <pascal@imatix.com>
                EDM  Ewen McNeill       <ewen@naos.co.nz>
                PS   Peter Seebach      <seebs@solon.com>
                GG   Gary M. Greenberg  <garyg@southeast.net>
                </Table>

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _PRELUDE_INCLUDED               /*  Allow multiple inclusions        */
#define _PRELUDE_INCLUDED


/*- Establish the compiler and computer system ------------------------------*/
/*
 *  Defines zero or more of these symbols, for use in any non-portable
 *  code:
 *
 *  __WINDOWS__         Microsoft C/C++ with Windows calls
 *  __MSDOS__           System is MS-DOS (set if __WINDOWS__ set)
 *  __VMS__             System is VAX/VMS or Alpha/OpenVMS
 *  __UNIX__            System is UNIX
 *  __OS2__             System is OS/2
 *  __MAC__             System is Mac/OS          GG  96/07/04
 *  __AMIGA__           System is AmigaDOS        PS  96/06/17
 *
 *  __IS_32BIT__        OS/compiler is 32 bits    EDM 96/05/30
 *  __IS_64BIT__        OS/compiler is 64 bits
 *
 *  When __UNIX__ is defined, we also define exactly one of these:
 *
 *  __UTYPE_AUX         Apple AUX
 *  __UTYPE_DECALPHA    Digital UNIX (Alpha)
 *  __UTYPE_HPUX        HP/UX
 *  __UTYPE_IBMAIX      IBM RS/6000 AIX
 *  __UTYPE_LINUX       Linux
 *  __UTYPE_MIPS        MIPS (BSD 4.3/System V mixture)
 *  __UTYPE_NETBSD      NetBSD
 *  __UTYPE_NEXT        NeXT
 *  __UTYPE_SCO         SCO Unix
 *  __UTYPE_SUNOS       SunOS
 *  __UTYPE_SUNSOLARIS  Sun Solaris
 *                      ... these are the ones I know about so far.
 *  __UTYPE_GENERIC     Any other UNIX
 *
 *  When __VMS__ is defined, we may define one or more of these:
 *
 *  __VMS_XOPEN         Supports XOPEN functions
 */

#if (defined (__64BIT__))               /*  EDM 96/05/30                     */
#    define __IS_64BIT__                /*  May have 64-bit OS/compiler      */
#else
#    define __IS_32BIT__                /*  Else assume 32-bit OS/compiler   */
#endif

#if (defined WIN32 || defined (_WIN32))
#   undef __WINDOWS__
#   define __WINDOWS__
#   undef __MSDOS__
#   define __MSDOS__
#endif

#if (defined WINDOWS || defined (_WINDOWS))
#   undef __WINDOWS__
#   define __WINDOWS__
#   undef __MSDOS__
#   define __MSDOS__
#endif

/*  MSDOS               Microsoft C                                          */
/*  _MSC_VER            Microsoft C                                          */
/*  __TURBOC__          Borland Turbo C                                      */
#if (defined (MSDOS) || defined (_MSC_VER) || defined (__TURBOC__))
#   undef __MSDOS__
#   define __MSDOS__
#endif

/*  EDM 96/05/28                                                             */
/*  __OS2__    Triggered by __EMX__ define and __i386__ define to avoid      */
/*             manual definition (eg, makefile) even though __EMX__ and      */
/*             __i386__ can be used on a MSDOS machine as well.  Here        */
/*             the same work is required at present.                         */
#if (defined (__EMX__) && defined (__i386__))
#   undef __OS2__
#   define __OS2__
#endif

/*  VMS                 VAX C (VAX/VMS)                                      */
/*  __VMS               Dec C (Alpha/OpenVMS)                                */
/*  __vax__             gcc                                                  */
#if (defined (VMS) || defined (__VMS) || defined (__vax__))
#   undef __VMS__
#   define __VMS__
#   if (__VMS_VER >= 70000000)
#       define __VMS_XOPEN
#   endif
#endif

/*  Untested                                                                 */
/*  GG  96/07/04                                                             */
#if (defined (_MAC) || defined (MAC_OS) || defined (THINK_C))
#   undef __MAC__
#   define __MAC__
#endif

/*  Untested                                                                 */
/*  PS  96/06/17                                                             */
#if (defined (_AMIGA_))
#   undef __AMIGA__
#   define __AMIGA__
#endif

/*  Try to define a __UTYPE_xxx symbol...                                    */
/*  unix                SunOS at least                                       */
/*  __unix__            gcc                                                  */
/*  _POSIX_SOURCE is various UNIX systems, maybe also VAX/VMS                */
#if (defined (unix) || defined (__unix__) || defined (_POSIX_SOURCE))
#   if (!defined (__VMS__))
#       undef __UNIX__
#       define __UNIX__
#       if (defined (__alpha))          /*  Digital UNIX is 64-bit           */
#           undef  __IS_32BIT__
#           define __IS_64BIT__
#           define __UTYPE_DECALPHA
#       endif
#   endif
#endif

#if (defined (_AUX))
#   define __UTYPE_AUX
#   define __UNIX__
#elif (defined (__hpux))
#   define __UTYPE_HPUX
#   define __UNIX__
#   define _INCLUDE_HPUX_SOURCE
#   define _INCLUDE_XOPEN_SOURCE
#   define _INCLUDE_POSIX_SOURCE
#elif (defined (_AIX) || defined (AIX))
#   define __UTYPE_IBMAIX
#   define __UNIX__
#elif (defined (linux))
#   define __UTYPE_LINUX
#   define __UNIX__
#elif (defined (Mips))
#   define __UTYPE_MIPS
#   define __UNIX__
#elif (defined (NetBSD))
#   define __UTYPE_NETBSD
#   define __UNIX__
#elif (defined (NeXT))
#   define __UTYPE_NEXT
#   define __UNIX__
#elif (defined (sco))
#   define __UTYPE_SCO
#   define __UNIX__
#elif (defined (SUNOS) || defined (SUN) || defined (sun))
#   define __UTYPE_SUNOS
#   define __UNIX__
#elif (defined (SOLARIS))
#   define __UTYPE_SUNSOLARIS
#   define __UNIX__
#elif (defined __UNIX__)
#   define __UTYPE_GENERIC
#endif


/*- Standard ANSI include files ---------------------------------------------*/

#ifdef __cplusplus                      /*  PA 96/05/29                      */
#include <iostream.h>                   /*  A bit of support for C++         */
#endif

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <signal.h>
#include <setjmp.h>


/*- System-specific include files -------------------------------------------*/

#if (defined (__MSDOS__))
#   if (defined (__WINDOWS__))          /*  When __WINDOWS__ is defined,     */
#       include <windows.h>             /*    so is __MSDOS__                */
#       include <winsock.h>             /*  May cause trouble on VC 1.x      */
#   endif
#   if (defined (__TURBOC__))
#       include <dir.h>
#   endif
#   include <dos.h>
#   include <io.h>
#   include <fcntl.h>
#   include <malloc.h>
#   include <sys\types.h>
#   include <sys\stat.h>
#endif

#if (defined (__UNIX__))
#   include <fcntl.h>
#   include <netdb.h>
#   include <unistd.h>
#   include <dirent.h>
#   include <pwd.h>
#   include <grp.h>
#   include <sys/types.h>
#   include <sys/param.h>
#   include <sys/socket.h>
#   include <sys/time.h>
#   include <sys/stat.h>
#   include <sys/ioctl.h>
#   include <sys/file.h>
#   include <sys/wait.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
/*  Specific #include's for UNIX varieties                                   */
#   if (defined (__UTYPE_IBMAIX))
#       include <sys/select.h>
#   endif
#endif

#if (defined (__VMS__))
#   if (!defined (vaxc))
#       include <fcntl.h>               /*  Not provided by Vax C            */
#   endif
#   include <netdb.h>
#   include <unixio.h>
#   include <types.h>
#   include <socket.h>
#   include <dirent.h>
#   include <time.h>
#   include <pwd.h>
#   include <stat.h>
#   include <in.h>
#endif

#if (defined (__OS2__))
/*  Include list for OS/2 updated by EDM 96/12/31
 *  NOTE: sys/types.h must go near the top of the list because some of the
 *        definitions in other include files rely on types defined there.
 */
#   include <sys/types.h>
#   include <fcntl.h>
#   include <malloc.h>
#   include <netdb.h>
#   include <unistd.h>
#   include <dirent.h>
#   include <pwd.h>
#   include <grp.h>
#   include <sys/param.h>
#   include <sys/socket.h>
#   include <sys/time.h>
#   include <sys/stat.h>
#   include <sys/ioctl.h>
#   include <sys/file.h>
#   include <sys/wait.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#endif

/*  GG  96/07/04                                                             */
#if (defined (__MAC__))
#   include <console.h>
#endif


/*- Data types --------------------------------------------------------------*/

typedef int             Bool;           /*  Boolean TRUE / FALSE value       */
typedef unsigned char   byte;           /*  Single unsigned byte = 8 bits    */
typedef unsigned short  dbyte;          /*  Double byte = 16 bits            */
typedef unsigned short  word;           /*  Alternative for double-byte      */
typedef unsigned long   dword;          /*  Double word >= 32 bits           */
#if (defined (__IS_32BIT__))
typedef unsigned long   qbyte;          /*  Quad byte = 32 bits              */
#else
typedef unsigned int    qbyte;          /*  Quad byte = 32 bits              */
#endif
typedef void (*function) (void);        /*  Address of simple function       */
#define local static void               /*  Shorthand for local functions    */

typedef struct {                        /*  Memory descriptor                */
    size_t size;                        /*    Size of data part              */
    byte  *data;                        /*    Data part follows here         */
} DESCR;


/*- Check compiler data type sizes ------------------------------------------*/

#if (UCHAR_MAX != 0xFF)
#   error "Cannot compile: must change definition of 'byte'."
#endif
#if (USHRT_MAX != 0xFFFFU)
#   error "Cannot compile: must change definition of 'dbyte'."
#endif
#if (defined (__IS_32BIT__))
#   if (ULONG_MAX != 0xFFFFFFFFUL)
#       error "Cannot compile: must change definition of 'qbyte'."
#   endif
#else
#   if (UINT_MAX != 0xFFFFFFFFU)
#       error "Cannot compile: must change definition of 'qbyte'."
#   endif
#endif


/*- Pseudo-functions --------------------------------------------------------*/

#define FOREVER         for (;;)            /*  FOREVER { ... }              */
#define until(expr)     while (!(expr))     /*  do { ... } until (expr)      */
#define streq(s1,s2)    (!strcmp ((s1), (s2)))
#define strneq(s1,s2)   (strcmp ((s1), (s2)))
#define strused(s)      (*(s) != 0)
#define strnull(s)      (*(s) == 0)
#define strclr(s)       (*(s) = 0)
#define strlast(s)      (s [strlen (s) - 1])
#define strterm(s)      (s [strlen (s)])

#define bit_msk(bit)    (1 << (bit))
#define bit_set(x,bit)  ((x) |=  bit_msk (bit))
#define bit_clr(x,bit)  ((x) &= ~bit_msk (bit))
#define bit_tst(x,bit)  ((x) &   bit_msk (bit))

#define tblsize(x)      (sizeof (x) / sizeof ((x) [0]))
#define tbllast(x)      (x [tblsize (x) - 1])

#if (defined (random))
#   undef random
#   undef randomize
#endif
#if (defined (min))
#   undef min
#   undef max
#endif

#if (defined (__IS_32BIT__))
#define random(num)     (int) ((long) rand () % (num))
#else
#define random(num)     (int) ((int)  rand () % (num))
#endif
#define randomize()     srand ((unsigned) time (NULL))
#define min(a,b)        (((a) < (b))? (a): (b))
#define max(a,b)        (((a) > (b))? (a): (b))


/*- ASSERT ------------------------------------------------------------------*/

#if (defined (DEBUG))
    /*  Define _Assert function here locally                                 */
    local _Assert (char *File, unsigned Line)
    {
        fflush  (stdout);
        fprintf (stderr, "\nAssertion failed: %s, line %u\n", File, Line);
        fflush  (stderr);
        abort   ();
    }
#   define ASSERT(f)    \
        if (f)          \
            ;           \
        else            \
            _Assert (__FILE__, __LINE__)
#else
#   define ASSERT(f)
#endif


/*- Boolean operators and constants -----------------------------------------*/

#if (!defined (TRUE))
#    define TRUE        1               /*  ANSI standard                    */
#    define FALSE       0
#endif


/*- Symbolic constants ------------------------------------------------------*/

#define FORK_ERROR      -1              /*  Return codes from fork()         */
#define FORK_CHILD      0

#if (!defined (LINE_MAX))               /*  Length of line from text file    */
#   define LINE_MAX     255             /*    if not previously #define'd    */
#endif
#if (!defined (PATH_MAX))               /*  Length of path variable          */
#   define PATH_MAX     2048            /*    if not previously #define'd    */
#endif                                  /*  EDM 96/05/28                     */


/*- System-specific definitions ---------------------------------------------*/

/*  We define the STARTUP macro: this performs any initialisation for the
 *  main function that is system-dependent.  In theory a portable main
 *  program should do this...                                                */

#if (defined (__MAC__))
#define STARTUP         argc = ccommand (&argv);
#else
#define STARTUP
#endif

/*  MSVC 1.x does not define standard signals if doing a Windows program     */

#if (defined (_MSC_VER) && !defined (SIGINT))
#    define SIGINT      2               /*  Ctrl-C sequence                  */
#    define SIGILL      4               /*  Illegal instruction              */
#    define SIGSEGV     11              /*  Segment violation                */
#    define SIGTERM     15              /*  Kill signal                      */
#    define SIGABRT     22              /*  Termination by abort()           */
#endif

/*  UNIX defines sleep() in terms of second; Win32 defines Sleep() in
 *  terms of milliseconds.  We want to be able to use sleep() anywhere.      */

#if (defined (__WINDOWS__))
#   if (defined (WIN32))
#       define sleep(a) Sleep(a*1000)   /*  UNIX sleep() is seconds          */
#   else
#       define sleep(a)                 /*  Do nothing?                      */
#   endif
#endif

/*  On SunOs, the ANSI C compiler costs extra, so many people install gcc
 *  but using the standard non-ANSI C library.  We have to make a few extra
 *  definitions for this case.  (Here we defined just what we needed for
 *  Libero -- we'll add code as required.)                                   */

#if (defined (__UTYPE_SUNOS))
#   if (!defined (_SIZE_T))             /*  Non-ANSI headers/libraries       */
#       define strerror(n)      sys_errlist [n]
#       define memmove(d,s,l)   bcopy (s,d,l)
        extern char *sys_errlist [];
#   endif
#endif

/*  We define constants for the way the current system formats filenames;
 *  we assume that the system has some type of path concept.                 */

#if (defined (WIN32))                   /*  Windows 95/NT                    */
#   define PATHSEP      ";"             /*  Separates path components        */
#   define PATHEND      '\\'            /*  Delimits directory and filename  */
#   define PATHFOLD     FALSE           /*  Convert pathvalue to uppercase?  */
#   define NAMEFOLD     FALSE           /*  Convert filenames to uppercase?  */
#elif (defined (__MSDOS__))             /*  16-bit Windows, MS-DOS           */
#   define PATHSEP      ";"
#   define PATHEND      '\\'
#   define PATHFOLD     TRUE
#   define NAMEFOLD     TRUE
#elif (defined (__VMS__))               /*  Digital VMS, OpenVMS             */
#   define PATHSEP      ","
#   define PATHEND      ':'
#   define PATHFOLD     TRUE
#   define NAMEFOLD     TRUE
#elif (defined (__UNIX__))              /*  All UNIXes                       */
#   define PATHSEP      ":"
#   define PATHEND      '/'
#   define PATHFOLD     FALSE
#   define NAMEFOLD     FALSE
#elif (defined (__OS2__))               /*  OS/2 using EMX/GCC               */
#   define PATHSEP      ";"             /*  EDM 96/05/28                     */
#   define PATHEND      '\\'
#   define PATHFOLD     FALSE
#   define NAMEFOLD     FALSE
#elif (defined (__MAC__))               /*  GG  96/07/04                     */
#   define PATHSEP      " "
#   define PATHEND      ':'
#   define PATHFOLD     FALSE
#   define NAMEFOLD     FALSE
#else
#   error "No definitions for PATH constants"
#endif


/*- Capability definitions --------------------------------------------------*/
/*
 *  Defines zero or more of these symbols, for use in any non-portable
 *  code:
 *
 *  DOES_SOCKETS        We can use (at least some) BSD socket functions
 *  DOES_UID            We can use (at least some) uid access functions
 *  DOES_TIMERS         We can use the BSD setitimer functions
 */

#if (defined (AF_INET))
#   define DOES_SOCKETS                 /*  System supports BSD sockets      */
#else
#   undef  DOES_SOCKETS
#   define ntohs(x)     (x)             /*  Needs to be correct for the      */
#   define ntohl(x)     (x)             /*    platform as far as possible    */
#   define htons(x)     (x)
#   define htonl(x)     (x)
#endif

#if (defined (__UNIX__) || defined (__VMS__) || defined (__OS2__))
#   define DOES_UID                     /*  System supports uid functions    */
#else
#   undef  DOES_UID
    typedef int gid_t;                  /*  Group id type                    */
    typedef int uid_t;                  /*  User id type                     */
#endif

#if (defined (ITIMER_REAL))
#   define DOES_TIMERS                  /*  Supports BSD setitimer calls     */
#else
#   undef  DOES_TIMERS
#   if (!defined (SIGALRM))             /*  We can use SIGALRM in code       */
#       define SIGALRM  1               /*    though it may never happen     */
#   endif
#endif


#endif                                  /*  Include PRELUDE.H                */
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflvers.h
    Title:      Define SFL version
    Package:    Standard Function Library (SFL)

    Written:    96/11/21  Pieter Hintjens <ph@imatix.com>
    Revised:    96/11/21  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Defines the SFL_VERSION constant.
    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLVERS_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLVERS_INCLUDED

#define SFL_VERSION     "1.41"          /*  Main SFL version                 */

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflbits.h
    Title:      Large bitstring manipulation functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/14  Pieter Hintjens <ph@imatix.com>
    Revised:    96/06/08  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides operations to manipulate large bitstrings.  The
                bitstrings are compressed.  Intended for bit-based index
                techniques, where bitstrings can be millions of bits long.
                These functions are still in development; this is an early
                version that provides basic functionality.  Simple tests
                on large bitmaps with random filling show a cost of about
                3 bytes per bit, after compression.  This includes all the
                indexing information.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLBITS_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLBITS_INCLUDED

/*  Definitions                                                              */

#define BIT_DATASIZE    500             /*  Size of block data part          */
#define BIT_INDEXSIZE   BIT_DATASIZE/2  /*  Size of block index part         */
#define BIT_SECTSIZE    8192            /*  Size of one bitstring section    */
#define BIT_MAXBLOCKS   1024            /*  Max. size of bitstring           */
#define BIT_MAXBITS     16384000L       /*  Max. possible bit number         */

typedef struct {                        /*  Bitstring block                  */
    union {
        byte  data  [BIT_DATASIZE];     /*    Data record part               */
        dbyte index [BIT_INDEXSIZE];    /*    Index record part              */
    } block;
    dbyte left,                         /*    Pointer to left (index only)   */
          right;                        /*    Pointer to right (data too)    */
    int   size;                         /*    Size of data part              */
} BITBLOCK;

typedef struct {                        /*  Bitstring object                 */
    BITBLOCK
       *block [BIT_MAXBLOCKS];          /*  Table of allocated blocks        */
    int
        block_count;                    /*  How many allocated blocks        */
    dbyte
        free_list;                      /*  Block free list                  */
} BITS;

extern long bits_free_count;            /*  We count free() and malloc()     */
extern long bits_alloc_count;

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

int   bits_init    (void);
int   bits_term    (void);
BITS *bits_create  (void);
void  bits_destroy (BITS *bits);
int   bits_set     (BITS *bits, long bit);
int   bits_clear   (BITS *bits, long bit);
int   bits_test    (BITS *bits, long bit);
int   bits_fput    (FILE *file, BITS *bits);
BITS *bits_fget    (FILE *file);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflcomp.h
    Title:      Compression functions
    Package:    Standard Function Library (SFL)

    Written:    91/05/20  Pieter Hintjens <ph@imatix.com>
    Revised:    96/05/24  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Various compression/decompression functions.  The LZ-type
                algorith (LZRW1/KH) was originally written by Kurt Haenen
                <ghgaea8@blekul11> and made portable by P. Hintjens. This
                is a reasonable LZ/RLE algorithm, very fast, but about 30%
                less efficient than a ZIP-type algorithm in terms of space.
                The RLE algorithms are better suited to compressing sparse
                data.  The nulls variant is specifically tuned to data that
                consists mostly of binary zeroes.  The bits variant is
                tuned for compressing sparse bitmaps.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLCOMP_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLCOMP_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

word compress_block (byte *source, byte *dest, word source_size);
word expand_block   (byte *source, byte *dest, word source_size);
word compress_rle   (byte *source, byte *dest, word source_size);
word expand_rle     (byte *source, byte *dest, word source_size);
word compress_nulls (byte *source, byte *dest, word source_size);
word expand_nulls   (byte *source, byte *dest, word source_size);
word compress_bits  (byte *source, byte *dest, word source_size);
word expand_bits    (byte *source, byte *dest, word source_size);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflconv.h
    Title:      Conversion functions
    Package:    Standard Function Library (SFL)

    Written:    95/12/17  Pieter Hintjens <ph@imatix.com>
    Revised:    96/09/30  Pieter Hintjens <ph@imatix.com>

    Synopsis:   These functions provide conversion between a set of datatypes
                (dates, times, numbers, Booleans) and external strings that
                represent the values.  The objective is to format datatypes
                for display or printing, and to validate and convert strings
                supplied by the user.  Conversion is controlled by a set of
                options specific to each datatype.  Additionally, dates and
                times may be formatted using picture strings.  The functions
                were written for use in an interactive 'forms' environment.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLCONV_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLCONV_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

char  *conv_number_str  (char *number, word flags, char point, int decimals,
                         int decimal_format, int width, int sign_format);
char  *conv_str_number  (char *string, word flags, char point,
                         int decimals, int decimal_format, int width);

char  *conv_date_str    (long date, word flags, int format, int order,
                         char datesep, int width);
long   conv_str_date    (char *string, word flags, int format, int order);
int    conv_str_day     (char *day_name);

char  *conv_time_str    (long time, word flags, char timesep, int width);
long   conv_str_time    (char *string);

char  *conv_bool_str    (Bool bool, int format);
int    conv_str_bool    (char *string);

char  *conv_time_pict   (long time, char *picture);
char  *conv_date_pict   (long date, char *picture);

/** Not Yet Implemented **/
char  *conv_float_str   (double number, word flags, int sign_format, char
                         point, int decimals, int decimal_format, int width
                        /*  Srcdoc does not find prototypes like this        */
                        );
/** Not Yet Implemented **/
double conv_str_float   (char *string, word flags, int sign_format,
                         char point, int decimals, int decimal_format
                        /*  Srcdoc does not find prototypes like this        */
                        );

#ifdef __cplusplus
}
#endif

#define FORMAT_MAX             80       /*  Max. size of formatted field     */

/*  Global variables for error reporting                                     */

extern int   conv_reason;               /*  Reason for last conversion error */
                                        /*  0 = okay; >0 = error             */
extern char *conv_reason_text [];       /*  Array of error messages 1..n     */
                                        /*  Index using conv_reason          */

/*  Possible values for conv_reason                                          */

#define CONV_NO_ERRORS             0    /*  No errors                        */

#define CONV_ERR_INVALID_INPUT     1    /*  Unrecognised char in input       */
#define CONV_ERR_OUT_OF_RANGE      2    /*  Value out of valid range         */

/*  conv_str_bool ()                                                         */

#define CONV_ERR_NOT_BOOLEAN       3    /*  Not a yes/no or true/false value */

/*  conv_str_time ()                                                         */

#define CONV_ERR_MULTIPLE_AM       4    /*  More than one 'am' or 'pm'       */

/*  conv_date_str ()                                                         */

#define CONV_ERR_DATE_OVERFLOW     5    /*  Result too large for output      */

/*  conv_str_date ()                                                         */

#define CONV_ERR_DATE_SIZE         6    /*  Too few or too many digits       */
#define CONV_ERR_MULTIPLE_DELIM    7    /*  Too many delimiters              */
#define CONV_ERR_BAD_MONTH         8    /*  Unknown month name               */
#define CONV_ERR_REJECT_3_5        9    /*  3/5 digits in a row not allowed  */
#define CONV_ERR_MULTIPLE_MONTH   10    /*  More than one month name         */

/*  conv_number_str ()                                                       */

#define CONV_ERR_DECS_MISSING     11    /*  Not enough decimals supplied     */
#define CONV_ERR_NUM_OVERFLOW     12    /*  Result too large for output      */

/*  conv_str_number ()                                                       */

#define CONV_ERR_MULTIPLE_SIGN    13    /*  More than one sign character     */
#define CONV_ERR_SIGN_REJECTED    14    /*  Sign not allowed if unsigned     */
#define CONV_ERR_SIGN_BAD_FIN     15    /*  Malformed financial negative     */
#define CONV_ERR_MULTIPLE_POINT   16    /*  More than one decimal point      */
#define CONV_ERR_DECS_REJECTED    17    /*  Decimals not allowed if integer  */
#define CONV_ERR_DECS_HIDDEN      18    /*  Decimals not allowed if hidden   */
#define CONV_ERR_DECS_OVERFLOW    19    /*  Too many decimal positions       */
#define CONV_ERR_TOO_MANY_DIGITS  20    /*  Too many digits for number       */


/*  Constants used for dedicated formatting functions                        */

#define _DATE_ORDER_FIRST       1       /*  Values for date_order            */
#define DATE_ORDER_YMD          1
#define DATE_ORDER_DMY          2
#define DATE_ORDER_MDY          3
#define _DATE_ORDER_LAST        3

#define FLAG_N_SIGNED           1       /*  Number field flags               */
#define FLAG_N_DECIMALS         2
#define FLAG_N_LEFT             4
#define FLAG_N_ZERO_FILL        8
#define FLAG_N_ZERO_BLANK      16
#define FLAG_N_THOUSANDS       32

#define SIGN_NEG_TRAIL          1       /*  Number field formatting          */
#define SIGN_ALL_TRAIL          2
#define SIGN_NEG_LEAD           3
#define SIGN_ALL_LEAD           4
#define SIGN_FINANCIAL          5

#define DECS_SHOW_ALL           1
#define DECS_DROP_ZEROS         2
#define DECS_HIDE_ALL           3
#define DECS_SCIENTIFIC         4

#define _DATE_FORMAT_FIRST      0       /*  Date field formatting            */
#define DATE_YMD_COMPACT        0
#define DATE_YMD_DELIM          1
#define DATE_YMD_SPACE          2
#define DATE_YMD_COMMA          3
#define _DATE_YMD_LAST          3
#define DATE_YM_COMPACT         4
#define DATE_YM_DELIM           5
#define DATE_YM_SPACE           6
#define _DATE_YM_LAST           6
#define DATE_MD_COMPACT         7
#define DATE_MD_DELIM           8
#define DATE_MD_SPACE           9
#define _DATE_MD_LAST           9
#define _DATE_FORMAT_LAST       9

#define FLAG_D_DD_AS_D          1       /*  Date field flags                 */
#define FLAG_D_MM_AS_M          2
#define FLAG_D_MONTH_ABC        4
#define FLAG_D_CENTURY          8
#define FLAG_D_UPPER           16
#define FLAG_D_ORDER_YMD       32
#define FLAG_D_ORDER_DMY       64
#define FLAG_D_ORDER_MDY      128

#define FLAG_T_HH_AS_H          1       /*  Time field flags                 */
#define FLAG_T_MM_AS_M          2
#define FLAG_T_SS_AS_S          4
#define FLAG_T_CC_AS_C          8
#define FLAG_T_COMPACT         16
#define FLAG_T_12_HOUR         32

#define BOOL_YES_NO             0       /*  Boolean field formatting         */
#define BOOL_Y_N                1
#define BOOL_TRUE_FALSE         2
#define BOOL_T_F                3
#define BOOL_1_0                4

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflcryp.h
    Title:      Encryption and decryption functions
    Package:    Standard Function Library (SFL)

    Written:    96/01/23  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/04  Pieter Hintjens <ph@imatix.com>

    Copyright:  Copyright (c) 1991-1996 iMatix except as noted.

    Synopsis:   The encryption/decryption functions were based on the
                cryptosystem library by Andrew Brown <asb@cs.nott.ac.uk>,
                cleaned-up for portability.  Thanks for a great package.

                IDEA is registered as the international patent WO 91/18459
                "Device for Converting a Digital Block and the Use thereof".
                For commercial use of IDEA, you should contact:
                  ASCOM TECH AG
                  Freiburgstrasse 370
                  CH-3018 Bern, Switzerland

    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.

    Notes:
    Description of IDEA cipher
    --------------------------
    The IDEA cipher operates on 64 bit (8 byte) blocks, using a 128 bit (16
    byte) key. IDEA has found itself famous through its inclusion in the
    well-known PGP package. The following is from the introduction to chapter
    3 of the thesis that presented the cipher.

    The block cipher IDEA (International Data Encryption Algorithm) is based
    on the new design concept of "mixing operations from different algebraic
    groups". The required "confusion" was achieved by successively using three
    "incompatible" group operations on pairs of 16-bit subblocks and the cipher
    structure was chosen to provide the necessary "diffusion". The cipher
    structure was further chosen to facilitate both hardware and software
    implementations. The IDEA cipher is an improved version of PES and was
    developed to increase security against differential cryptanalysis.

    Description of MDC cipher
    -------------------------
    This is a method for turning a hash function, here MD5, into a fast
    secret-key encryption. Based on a suggestion by Phil Karn in sci.crypt, 13
    Feb 1992. See also his comments from sci.crypt, 23 Mar 1992. The method is
    a variant of that described in Zheng, Matsumoto and Imai, Crypto 89. See
    also, "A New Class of Cryptosystems Based on Interconnection Networks" by
    michaelp@terpsichore.informatic.rwth-aachen.de

    Description of DES cipher
    -------------------------
    DES is the well known U.S. Data Encryption Standard cipher.
    DES encrypts data in 64 bit blocks, using a 64 bit key -- of which
    56 bits are used in the encipherment process.
------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLCRYP_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLCRYP_INCLUDED


/*  Definitions of the encryption algorithms we support                      */

#define CRYPT_IDEA      0               /*  IDEA algorithm                   */
#define CRYPT_MDC       1               /*  MDC algorithm                    */
#define CRYPT_DES       2               /*  DES algorithm                    */
#define CRYPT_XOR       3               /*  A basic XOR algorithm            */
#define CRYPT_TOP       4               /*  We support 4 algorithms          */

/*  We define some tables that key off the encryption algorithm              */

#if (defined (DEFINE_CRYPT_TABLES))
static int
    crypt_block_size [] = {             /*  Block size for each algorithm    */
       8, 32, 8, 16
    };
#define CRYPT_MAX_BLOCK_SIZE  32        /*  Largest block size, in bytes     */
#endif

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

Bool  crypt_encode  (byte *buffer, word buffer_size, int algorithm, byte *key);
Bool  crypt_decode  (byte *buffer, word buffer_size, int algorithm, byte *key);
qbyte calculate_crc (byte *block, size_t length);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfldate.h
    Title:      Date and time functions
    Package:    Standard Function Library (SFL)

    Written:    96/01/05  Pieter Hintjens <ph@imatix.com>
    Revised:    96/09/30  Jonathan Schultz <jonathan@imatix.com>

    Synopsis:   Includes functions to get the current date/time, calculate
                the day or week, week of year and leap year.  Dates and times
                are each stored in a 32-bit long value of 8 digits: dates are
                CCYYMMDD; times are HHMMSSCC.  You can compare dates and times
                directly - e.g. if (date_wanted >= date_now).

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLDATE_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLDATE_INCLUDED

/*  Macros                                                                   */

#define GET_CENTURY(d)      (int) ( (d) / 1000000L)
#define GET_CCYEAR(d)       (int) ( (d) / 10000L)
#define GET_YEAR(d)         (int) (((d) % 1000000L) / 10000L)
#define GET_MONTH(d)        (int) (((d) % 10000L) / 100)
#define GET_DAY(d)          (int) ( (d) % 100)

#define GET_HOUR(t)         (int) ( (t) / 1000000L)
#define GET_MINUTE(t)       (int) (((t) % 1000000L) / 10000L)
#define GET_SECOND(t)       (int) (((t) % 10000L) / 100)
#define GET_CENTI(t)        (int) ( (t) % 100)

#define MAKE_DATE(c,y,m,d)  (long) (c) * 1000000L +                          \
                            (long) (y) * 10000L +                            \
                            (long) (m) * 100 + (d)
#define MAKE_TIME(h,m,s,c)  (long) (h) * 1000000L +                          \
                            (long) (m) * 10000L +                            \
                            (long) (s) * 100 + (c)

#define timeeq(d1,t1,d2,t2)  ((d1) == (d2) && (t1) == (t2))
#define timeneq(d1,t1,d2,t2) ((d1) != (d2) || (t1) != (t2))
#define timelt(d1,t1,d2,t2)  ((d1) < (d2) || ((d1) == (d2) && (t1) <  (t2)))
#define timele(d1,t1,d2,t2)  ((d1) < (d2) || ((d1) == (d2) && (t1) <= (t2)))
#define timegt(d1,t1,d2,t2)  ((d1) > (d2) || ((d1) == (d2) && (t1) >  (t2)))
#define timege(d1,t1,d2,t2)  ((d1) > (d2) || ((d1) == (d2) && (t1) >= (t2)))

/*  Interval values, specified in centiseconds                               */

#define INTERVAL_CENTI      1
#define INTERVAL_SEC        100
#define INTERVAL_MIN        6000
#define INTERVAL_HOUR       360000L
#define INTERVAL_DAY        8640000L


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

long   date_now           (void);
long   time_now           (void);
Bool   leap_year          (int year);
int    julian_date        (long date);
int    day_of_week        (long date);
int    week_of_year       (long date);
int    year_quarter       (long date);
word   pack_date          (long date);
word   pack_time          (long time);
long   unpack_date        (word packdate);
long   unpack_time        (word packtime);
long   default_century    (long *date);
long   date_to_days       (long date);
long   days_to_date       (long days);
time_t date_to_timer      (long date, long time);
long   timer_to_date      (time_t time_secs);
long   timer_to_time      (time_t time_secs);
long   timer_to_gmdate    (time_t time_secs);
long   timer_to_gmtime    (time_t time_secs);
long   time_to_csecs      (long time);
long   csecs_to_time      (long csecs);
void   future_date        (long *date, long *time, long days, long csecs);
void   past_date          (long *date, long *time, long days, long csecs);
void   date_diff          (long date1, long time1, long date2, long time2,
                           long *days, long *csecs);
#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflexdr.h
    Title:      External data representation functions
    Package:    Standard Function Library (SFL)

    Written:    96/06/25  Pieter Hintjens <ph@imatix.com>
    Revised:    96/10/25  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to read and write data in a portable
                format that is suitable for transmission to other systems.
                The principle is similar to the ONC XDR standard used in
                RPC, but somewhat simpler.  The streams produced by these
                functions are not compatible with ONC XDR.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLEXDR_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLEXDR_INCLUDED


/*---------------------------------------------------------------------------
 *  Function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

int    exdr_write   (byte  *buffer, char *format, ...);
int    exdr_writed  (DESCR *buffer, char *format, ...);
void   exdr_read    (byte  *buffer, char *format, ...);

#ifdef __cplusplus
}
#endif


#endif                                  /*  Include sflexdr.h                */
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflfind.h
    Title:      Fast string searching functions
    Package:    Standard Function Library (SFL)

    Written:    96/04/24  Pieter Hintjens <ph@imatix.com>
    Revised:    96/05/25  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Searches for a pattern within a string or block of memory
                using a variant of the Boyer-Moore algorithm (improved by
                Horspool and Sunday). As fast or faster than the normal
                Boyer-Moore algorithm for most search strings, and much
                simpler.  Includes a basic function for searching blocks of
                memory with known sizes, plus an envelope that searches
                null-delimited strings.  Provides the option of repeatedly
                searching for the same pattern without re-parsing the pattern
                each time.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLFIND_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLFIND_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

char *strfind (char *string, char *pattern, Bool repeat_find);
byte *memfind (byte *block, size_t block_size,
               byte *pattern, size_t pattern_size, Bool repeat_find);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflfile.h
    Title:      File-access functions
    Package:    Standard Function Library (SFL)

    Written:    92/10/25  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/13  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to read and write files with explicit
                new-line/carriage-return control; to find files on a path;
                to copy files, check files' protection, etc.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLFILE_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLFILE_INCLUDED


/*  System-specific definitions                                              */

#if (defined (__MSDOS__))
#   define FOPEN_READ_TEXT      "rt"    /*  Under DOS we can be explict      */
#   define FOPEN_READ_BINARY    "rb"    /*    and use 't' or 'b' in fopen    */
#   define FOPEN_WRITE_TEXT     "wt"
#   define FOPEN_WRITE_BINARY   "wb"
#   define FOPEN_APPEND_TEXT    "at"
#   define FOPEN_APPEND_BINARY  "ab"
#elif (defined (__VMS__))
#   define FOPEN_READ_TEXT      "r"     /*  Dec C does not like 't' or 'b'   */
#   define FOPEN_READ_BINARY    "r"
#   define FOPEN_WRITE_TEXT     "w"
#   define FOPEN_WRITE_BINARY   "w"
#   define FOPEN_APPEND_TEXT    "a"
#   define FOPEN_APPEND_BINARY  "a"
#elif (defined (__UNIX__))
#   define FOPEN_READ_TEXT      "rt"    /*  Under UNIX we can be explict     */
#   define FOPEN_READ_BINARY    "rb"    /*    and use 't' or 'b' in fopen    */
#   define FOPEN_WRITE_TEXT     "wt"
#   define FOPEN_WRITE_BINARY   "wb"
#   define FOPEN_APPEND_TEXT    "at"
#   define FOPEN_APPEND_BINARY  "ab"
#elif (defined (__OS2__))
#   define FOPEN_READ_TEXT      "rt"    /*  Under OS/2 we can be explict     */
#   define FOPEN_READ_BINARY    "rb"    /*    and use 't' or 'b' in fopen    */
#   define FOPEN_WRITE_TEXT     "wt"
#   define FOPEN_WRITE_BINARY   "wb"
#   define FOPEN_APPEND_TEXT    "at"
#   define FOPEN_APPEND_BINARY  "ab"
#else
#   error "No definitions for FOPEN constants"
#endif


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

FILE  *file_open           (char *filename, char mode);
FILE  *file_locate         (char *path, char *name, char *ext);
Bool   file_close          (FILE *stream);
Bool   file_read           (FILE *stream, char *string);
char  *file_write          (FILE *stream, char *string);
int    file_copy           (char *dest, char *src, char mode);
char  *file_where          (char mode, char *path, char *name, char *ext);
Bool   file_exists         (char *filename);
Bool   file_cycle          (char *filename);
Bool   safe_to_extend      (char *filename);
int    default_extension   (char *dest, char *src, char *ext);
int    fixed_extension     (char *dest, char *src, char *ext);
char  *strip_extension     (char *filename);
char  *strip_file_path     (char *filename);
Bool   file_is_readable    (char *filename);
Bool   file_is_writeable   (char *filename);
Bool   file_is_executable  (char *filename);
Bool   file_is_directory   (char *filename);
long   get_file_size       (char *filename);
time_t get_file_time       (char *filename);

#ifdef __cplusplus
}
#endif


/*  Symbols, macros                                                          */

#define FILE_NAME_MAX   160             /*  Max size of filename             */
#define FILE_DIR_MAX    64              /*  Max size of directory name       */


/*  External variables                                                       */

extern Bool  file_crlf;                 /*  TRUE or FALSE                    */

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflini.h
    Title:      Initialisation file access functions
    Package:    Standard Function Library (SFL)

    Written:    94/01/08  Pieter Hintjens <ph@imatix.com>
    Revised:    96/05/25  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to read an initialisation file that follows
                the MS-Windows style, i.e. consists of [Sections] followed by
                keyword = value lines.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SLFINI_INCLUDED                /*  Allow multiple inclusions        */
#define _SLFINI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

Bool ini_find_section    (FILE *inifile, char *section, Bool top);
Bool ini_scan_section    (FILE *inifile, char **keyword, char **value);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflmath.h
    Title:      Mathematic functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/12  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/04  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides miscellaneous mathematical functions, including
                calculation of points within areas.

    Copyright:  Copyright (c) 1991-1996 iMatix  Adapted from NCSA HTTPd.
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLMATH_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLMATH_INCLUDED

/*  Structure declaration                                                    */

typedef struct
  {
    double x;
    double y;
  } FPOINT;

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

int  point_in_rect   (FPOINT *point, FPOINT *coords);
int  point_in_circle (FPOINT *point, FPOINT *coords);
int  point_in_poly   (FPOINT *point, FPOINT *coords, int nb_point);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflmesg.h
    Title:      Message-file access functions
    Package:    Standard Function Library (SFL)

    Written:    92/10/25  Pieter Hintjens <ph@imatix.com>
    Revised:    96/05/25  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to read and format messages from a message
                file.  The intention of such a file is to provide a single
                location for all error messages: you can easier translate
                these into foreign languages, and you can control the
                consistency of an application's error messages.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLMESG_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLMESG_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

int    open_message_file   (char *filename);
void   close_message_file  (void);
void   print_message       (int msgid, ...);
char  *message_text        (int msgid);

#ifdef __cplusplus
}
#endif

/*  Symbols, macros                                                          */

#define ERROR_ANY       0000            /*  Generic error message            */

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflmem.h
    Title:      Memory allocation functions
    Package:    Standard Function Library (SFL)

    Written:    96/06/08  Pieter Hintjens <ph@imatix.com>
    Revised:    96/06/19  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Encapsulated memory allocation functions.  Based on an
                article by Jim Schimandle in DDJ August 1990.  Provides
                'safe' versions of malloc(), realloc(), free(), and strdup().
                These functions protect the programmer from errors in calling
                memory allocation/free routines.   When these calls are used,
                the allocation routines in this module add a data structure
                to the top of allocated memory blocks which tags them as legal
                memory blocks.  When the free routine is called, the memory
                block to be freed is checked for legality tag.  If the block
                is not legal, the memory list is dumped to stderr and the
                program is terminated.  Some of these functions are called
                through macros, which add the filename and line number of the
                call, for tracing.

    Copyright:  Copyright (c) 1991-96 iMatix, parts copyright (c) DDJ 1990.
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLMEM_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLMEM_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

void  *_mem_alloc   (size_t size, char *file, word line);
void  *_mem_realloc (void *block, size_t size, char *file, word line);
void   _mem_free    (void *block, char *file, word line);
char  *_mem_strdup  (char *string, char *file, word line);
char **_mem_strfree (char **string, char *file, word line);
void   _mem_assert  (char *file, word line);
long    mem_used    (void);
long    mem_allocs  (void);
long    mem_frees   (void);
void    mem_display (FILE *save_to);

#ifdef __cplusplus
}
#endif

/*  Define macros to simplify calls to these functions                      */

#define mem_alloc(size)        _mem_alloc   ((size), __FILE__, __LINE__)
#define mem_realloc(ptr,size)  _mem_realloc ((ptr), (size), __FILE__, __LINE__)
#define mem_free(ptr)          _mem_free    ((ptr), __FILE__, __LINE__)
#define mem_strdup(str)        _mem_strdup  ((str), __FILE__, __LINE__)
#define mem_strfree(pstr)      _mem_strfree ((pstr), __FILE__, __LINE__)
#define mem_assert()           _mem_assert  (__FILE__, __LINE__)

/*  Global variables                                                         */

extern int mem_trace;

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflmime.h
    Title:      MIME support functions
    Package:    Standard Function Library (SFL)

    Written:    96/03/28  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/04  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides various functions that support MIME encoding and
                decoding.  See RFC 1521 for details.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.

    Notes:
    Extract from RFC1521 for Base64 Content-Transfer-Encoding
    ---------------------------------------------------------

    The Base64 Content-Transfer-Encoding is designed to represent
    arbitrary sequences of octets in a form that need not be humanly
    readable.  The encoding and decoding algorithms are simple, but the
    encoded data are consistently only about 33 percent larger than the
    unencoded data.  This encoding is virtually identical to the one used
    in Privacy Enhanced Mail (PEM) applications, as defined in RFC 1421.
    The base64 encoding is adapted from RFC 1421, with one change: base64
    eliminates the "*" mechanism for embedded clear text.

    A 65-character subset of US-ASCII is used, enabling 6 bits to be
    represented per printable character. (The extra 65th character, "=",
    is used to signify a special processing function.)

    \NOTE: This subset has the important property that it is
    represented identically in all versions of ISO 646, including US
    ASCII, and all characters in the subset are also represented
    identically in all versions of EBCDIC.  Other popular encodings,
    such as the encoding used by the uuencode utility and the base85
    encoding specified as part of Level 2 PostScript, do not share
    these properties, and thus do not fulfill the portability
    requirements a binary transport encoding for mail must meet.

    The encoding process represents 24-bit groups of input bits as output
    strings of 4 encoded characters. Proceeding from left to right, a
    24-bit input group is formed by concatenating 3 8-bit input groups.
    These 24 bits are then treated as 4 concatenated 6-bit groups, each
    of which is translated into a single digit in the base64 alphabet.
    When encoding a bit stream via the base64 encoding, the bit stream
    must be presumed to be ordered with the most-significant-bit first.

    That is, the first bit in the stream will be the high-order bit in
    the first byte, and the eighth bit will be the low-order bit in the
    first byte, and so on.

    Each 6-bit group is used as an index into an array of 64 printable
    characters. The character referenced by the index is placed in the
    output string. These characters, identified in Table 1, below, are
    selected so as to be universally representable, and the set excludes
    characters with particular significance to SMTP (e.g., ".", CR, LF)
    and to the encapsulation boundaries defined in this document (e.g.,
    "-").

                      Table 1: The Base64 Alphabet

      Value Encoding  Value Encoding  Value Encoding  Value Encoding
           0 A            17 R            34 i            51 z
           1 B            18 S            35 j            52 0
           2 C            19 T            36 k            53 1
           3 D            20 U            37 l            54 2
           4 E            21 V            38 m            55 3
           5 F            22 W            39 n            56 4
           6 G            23 X            40 o            57 5
           7 H            24 Y            41 p            58 6
           8 I            25 Z            42 q            59 7
           9 J            26 a            43 r            60 8
          10 K            27 b            44 s            61 9
          11 L            28 c            45 t            62 +
          12 M            29 d            46 u            63 /
          13 N            30 e            47 v
          14 O            31 f            48 w         (pad) =
          15 P            32 g            49 x
          16 Q            33 h            50 y

    The output stream (encoded bytes) must be represented in lines of no
    more than 76 characters each.  All line breaks or other characters
    not found in Table 1 must be ignored by decoding software.  In base64
    data, characters other than those in Table 1, line breaks, and other
    white space probably indicate a transmission error, about which a
    warning message or even a message rejection might be appropriate
    under some circumstances.

    Special processing is performed if fewer than 24 bits are available
    at the end of the data being encoded.  A full encoding quantum is
    always completed at the end of a body.  When fewer than 24 input bits
    are available in an input group, zero bits are added (on the right)
    to form an integral number of 6-bit groups.  Padding at the end of
    the data is performed using the '=' character.  Since all base64
    input is an integral number of octets, only the following cases can
    \arise: (1) the final quantum of encoding input is an integral
    multiple of 24 bits; here, the final unit of encoded output will be
    an integral multiple of 4 characters with no "=" padding, (2) the
    final quantum of encoding input is exactly 8 bits; here, the final
    unit of encoded output will be two characters followed by two "="
    padding characters, or (3) the final quantum of encoding input is
    exactly 16 bits; here, the final unit of encoded output will be three
    characters followed by one "=" padding character.

    Because it is used only for padding at the end of the data, the
    occurrence of any '=' characters may be taken as evidence that the
    end of the data has been reached (without truncation in transit).  No
    such assurance is possible, however, when the number of octets
    transmitted was a multiple of three.

    Any characters outside of the base64 alphabet are to be ignored in
    base64-encoded data.  The same applies to any illegal sequence of
    characters in the base64 encoding, such as "====="

    Care must be taken to use the proper octets for line breaks if base64
    encoding is applied directly to text material that has not been
    converted to canonical form.  In particular, text line breaks must be
    converted into CRLF sequences prior to base64 encoding. The important
    thing to note is that this may be done directly by the encoder rather
    than in a prior canonicalization step in some implementations.

    \NOTE: There is no need to worry about quoting apparent
    encapsulation boundaries within base64-encoded parts of multipart
    entities because no hyphen characters are used in the base64
    encoding.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLMIME_INCLUDED                /*  Allow multiple inclusions       */
#define _SFLMIME_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

size_t  encode_base64    (char *source, byte *target, size_t source_size);
size_t  decode_base64    (byte *source, char *target, size_t source_size);
Bool    decode_mime_time (char *mime_date, long *date, long *time);
char   *encode_mime_time (long date, long time);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflnode.h
    Title:      Linked-list functions
    Package:    Standard Function Library (SFL)

    Written:    96/06/03  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12083  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to maintain doubly-linked lists.  You can
                use these functions to work with lists of any structure.  To
                make this work, all structures must start with two pointers,
                "void *next, *prev;".  When you want to attach a linked-list
                to another structure, declare the list head as a NODE.  You
                can then refer to this variable when you attach items to the
                list head.  The code sets the global node_unsafe to TRUE
                whenever it is changing a list.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLNODE_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLNODE_INCLUDED


/*  The node descriptor simply contains two pointers.  All blocks that are   */
/*  descriptors that are held in lists.  We can (a) allocate a dummy node    */
/*  instead of a complete block for a list head, and (b) use the same list   */
/*  handling functions for all descriptors.                                  */

typedef struct {                        /*  Node descriptor                  */
    void *next, *prev;                  /*    for a doubly-linked list       */
} NODE;

/*  Global variables                                                         */

extern Bool
    node_unsafe;                        /*  TRUE if we're changing a list    */

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

void *node_create        (void *after, size_t size);
void  node_destroy       (void *node);
void *node_unlink        (void *node);
void *node_relink        (void *left, void *node, void *right);
void *node_relink_after  (void *node, void *after);
void *node_relink_before (void *node, void *before);

#ifdef __cplusplus
}
#endif

/*  Macros                                                                   */

#define node_reset(node)          (node)-> prev = (node)-> next = (node)

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfldir.h
    Title:      Directory access functions
    Package:    Standard Function Library (SFL)

    Written:    96/04/02  Pieter Hintjens <ph@imatix.com>
    Revised:    97/01/02  Pieter Hintjens <ph@imatix.com>

    Synopsis:   The directory access functions provide a portable interface
                to the system's file directory structure.   In general these
                functions are modelled around the UNIX opendir and readdir
                functions, but they are also similar to the DOS interface.
                These functions can fail on SVr4 if the <dirent.h> file
                does not match the C library.  Recompile with the switch
                -D _USE_BSD_DIRENT and they should work a bit better.
                Tested on: MS-DOS (Turbo-C), Windows (MSVC 4.0), UNIX
                (Linux, IBM AIX, SunOS).  OS/2 port was done by Ewen McNeill
                <ewen@naos.co.nz>.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLDIR_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLDIR_INCLUDED

#if !(defined (NAME_MAX))               /*  Posix uses NAME_MAX              */
#   if !(defined (MAXNAMLEN))           /*  BSD uses MAXNAMLEN               */
#       if (defined (__WINDOWS__))
#           define MAXNAMLEN 259        /*  MS VC uses 259                   */
#       elif (defined (__MS_DOS__))
#           define MAXNAMLEN 12         /*  DOS uses 8.3                     */
#       else
#           define MAXNAMLEN 255        /*  And for everyone else, 255       */
#       endif
#   endif
#   define NAME_MAX         MAXNAMLEN
#endif

#define UID_CACHE_MAX       10          /*  Max. different uid's we cache    */
#define GID_CACHE_MAX       10          /*  Max. different gid's we cache    */

/*  DOS-ish file attributes, provided as an alternative to the UNIX-ish      */
/*  file mode bits.  Both fields are always filled-out as far as possible.   */
/*  These bits correspond to the normal DOS values.                          */

#define ATTR_RDONLY         0x01        /*  Read only file                   */
#define ATTR_HIDDEN         0x02        /*  Hidden file                      */
#define ATTR_SYSTEM         0x04        /*  System file                      */
#define ATTR_SUBDIR         0x10        /*  Subdirectory                     */
#define ATTR_MASK           0x17        /*  All bits together                */

/*  For portability we need to define types for the various fields that      */
/*  stat() returns.  If the compiler complains about these definitions,      */
/*  you need to add conditional definitions accordingly.  SMOP.              */
/*  For now, I assume that DOES_UID defines the stat types correctly.        */
/*  Note that prelude.h already defines uid_t and gid_t.                     */

#if (!defined (DOES_UID))
typedef unsigned short      mode_t;
typedef unsigned short      nlink_t;
typedef long                off_t;
#endif

/*  Microsoft tends to use _stat instead of stat.                            */

#if (defined (_MSC_VER))
#   define stat _stat
#endif

/*  We define DEFAULT_DIR as the default current directory, so that we       */
/*  can call open_dir() with a null or empty directory argument.  On most    */
/*  systems this is ".".                                                     */

#if (defined (__VMS__))
#   define DEFAULT_DIR      " "
#else
#   define DEFAULT_DIR      "."
#endif

/*  Under SVr4 it can happen that the <dirent.h> file does not match the     */
/*  C library.  Typically the library readdir() function returns the BSD     */
/*  structure while the <dirent.h> file defines dirent using the System V    */
/*  standards.  This is weird but apparently quite common.  Solution: at     */
/*  compile-time, force the switch -D _USE_BSD_DIRENT, and we define our     */
/*  own BSD-like structure.  Hey, I hate second-guessing the include files   */
/*  but if it's broke, you gotta fix it.  This problem appears at least on   */
/*  SunOS, to our knowledge.                                                 */

#if (defined (_USE_BSD_DIRENT))
struct Dirent
  {
    unsigned long   d_fileno;           /*  File number of entry             */
    unsigned short  d_reclen;           /*  Length of this record            */
    unsigned short  d_namlen;           /*  Length of string in d_name       */
    char            d_name [255 + 1];   /*  Maximum name length              */
  };
#else
#   define Dirent   dirent              /*  We'll always refer to Dirent     */
#endif

/*  Directory stream structure - this contains private fields starting       */
/*  with '_' and public fields.  If you use the private fields, be warned    */
/*  that these may change as we see fit.  If you add strings to this block,  */
/*  be sure to check fix_dir() and free_dir().                               */

typedef struct
{
    Bool    _fixed;                     /*  TRUE if processed by fix_dir()   */
#if (defined (__UNIX__) || defined (__VMS_XOPEN) || defined (__OS2__))
    DIR    *_dir_handle;                /*    a directory handle             */
    struct Dirent                       /*    and a file desc. structure,    */
           *_dir_entry;                 /*    both transient blocks          */

#elif (defined (_MSC_VER))              /*  MSC returns:                     */
    long    _dir_handle;                /*    a directory handle             */
#   if defined (WIN32)                  /*    and a file desc. structure     */
    struct _finddata_t                  /*    defined differently for Win32  */
            _dir_entry;
#   else
    struct _find_t                      /*    and poor old Win16 (VC++ 1.x)  */
            _dir_entry;
#   endif
#elif (defined (__TURBOC__))            /*  Borland C returns:               */
    struct ffblk                        /*    a file desc. structure         */
            _dir_entry;
#endif

    /*  Public fields                                                        */
    char   *dir_name;                   /*  Directory name + sep             */
    char   *owner;                      /*  File owner name                  */
    char   *group;                      /*  File owner group name            */
    char   *file_name;                  /*  Name of the file                 */
    time_t  file_time;                  /*  Time of modification for file    */
    off_t   file_size;                  /*  Size of the file                 */
    mode_t  file_mode;                  /*  UNIX-ish permission bits         */
    byte    file_attrs;                 /*  MS-DOS-ish permission bits       */
    nlink_t file_nlink;                 /*  Number of links to file          */
} DIRST;


typedef struct _FILEINFO
{
    struct _FILEINFO                    /*  Pointer for the linked list      */
        *next,
        *prev;
    DIRST
        dir;                            /*  File information                 */
    Bool
        directory;                      /*  TRUE if file is directory        */
} FILEINFO;

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

Bool   open_dir      (DIRST *dir, char *dir_name);
Bool   read_dir      (DIRST *dir);
Bool   close_dir     (DIRST *dir);
char  *format_dir    (DIRST *dir, Bool full);
int    fix_dir       (DIRST *dir);
int    free_dir      (DIRST *dir);
NODE  *load_dir_list (char  *dir_name, char *sort);
Bool   free_dir_list (NODE  *filelist);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflproc.h
    Title:      Process control functions
    Package:    Standard Function Library (SFL)

    Written:    96/09/09  Pieter Hintjens <ph@imatix.com>
    Revised:    96/11/23  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to create and manage processes.  The main
                set of functions lets you create, monitor, and end processes.
                A secondary function lets you run the current process as a
                background process.  Some of the code in process_server()
                came from the book "Internetworking With TCP/IP Volume III:
                Client-Server Programming And Applications, BSD Socket
                Version" by Douglas E. Comer and David L. Stevens, published
                1993 by Prentice-Hall Inc.  ISBN 0-13-020272-X.  Changes for
                OS/2 were made by Ewen McNeill <ewen@naos.co.nz>.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLPROC_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLPROC_INCLUDED

/*  Type definitions                                                         */

#if (defined (WIN32))
typedef struct _PROC_HANDLE
{
    HANDLE process;
    HANDLE in;
    HANDLE out;
    HANDLE err;
    DESCR  *envd;                       /*  Environment data                 */
} PROC_HANDLE;
typedef PROC_HANDLE *PROCESS;           /*  Process ID type                  */
#define NULL_PROCESS NULL               /*    and null process               */
#else
typedef qbyte        PROCESS;           /*  Process ID type                  */
#define NULL_PROCESS 0                  /*    and null process               */
#endif

/*  Global variables                                                         */

extern int process_errno;               /*  Last process exit code           */
extern int process_delay;               /*  Wait for child to start          */

#ifdef __cplusplus
extern "C" {
#endif

PROCESS process_create  (char *file, char *argv [], char *workdir,
                         char *std_in, char *std_out, char *std_err,
                         char *envv [], Bool wait);
int     process_status  (PROCESS process_id);
int     process_kill    (PROCESS process_id);
void    process_close   (PROCESS process_id);
int     process_server  (char *workdir, char *lockfile);

#ifdef __cplusplus
}
#endif

/*  Return values from process_status()                                      */

#define PROCESS_RUNNING         0
#define PROCESS_ENDED_OK        1
#define PROCESS_ENDED_ERROR     2
#define PROCESS_INTERRUPTED     3

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflslot.h
    Title:      Time-slot functions
    Package:    Standard Function Library (SFL)

    Written:    96/01/01  Pieter Hintjens <ph@imatix.com>
    Revised:    96/09/30  Pieter Hintjens <ph@imatix.com>

    Synopsis:   The time-slot functions provide long-running programs with
                a means to 'switch-on' and 'switch-off' depending on the time
                of day, and day of year.  The intention is that the user can
                configure such programs to be active only between certain
                hours, on certain days, etc.  The time-slot functions work
                with 'range' bitmaps for a day (in seconds) and a year (in
                days), and provide functions to set, clear, and test these
                ranges.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLSLOT_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLSLOT_INCLUDED

#define MAX_DAY          366            /*  Max. days in a normal year       */
#define MAX_MIN         1440            /*  Max. minutes in a normal day     */
typedef byte year_range [46];           /*  366 bits (1 per day)             */
typedef byte day_range  [180];          /*  1440 bits (1 per minute)         */

#ifdef __cplusplus
extern "C" {
#endif

void  year_range_empty      (byte *range);
void  year_range_fill       (byte *range);
int   year_slot_set         (byte *range, int day_from, int day_to);
int   year_slot_clear       (byte *range, int day_from, int day_to);
Bool  year_slot_filled      (byte *range, int day);

void  day_range_empty       (byte *range);
void  day_range_fill        (byte *range);
int   day_slot_set          (byte *range, int min_from, int min_to);
int   day_slot_clear        (byte *range, int min_from, int min_to);
Bool  day_slot_filled       (byte *range, int minute);

int   date_to_day           (long date);
int   time_to_min           (long time);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflsrt.h
    Title:      String-handling functions
    Package:    Standard Function Library (SFL)

    Written:    92/10/25  Pieter Hintjens <ph@imatix.com>
    Revised:    96/10/28  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides various string-handling functions.  Some of these
                functions are available on some but not all platforms; others
                are useful tools for string handling.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLSTR_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLSTR_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

char   *strdupl            (char *string);
char  **strfree            (char **string);
char   *strskp             (char *string);
char   *strcset            (char *string, char ch);
char   *strpad             (char *string, char ch, int length);
char   *strlwc             (char *string);
char   *strupc             (char *string);
char   *strcrop            (char *string);
char   *stropen            (char *string, Bool align);
char   *strclose           (char *string, Bool align);
int     strmatch           (char *string1, char *string2);
qbyte   strhash            (char *string);
char   *xstrcat            (char *dest, char *src, ...);
char   *xstrcpy            (char *dest, char *src, ...);
int     lexcmp             (char *string1, char *string2);
char   *soundex            (char *string);
DESCR  *strt2descr         (char **strings);
char  **descr2strt         (DESCR *descr);
void    strtfree           (char **strings);
Bool    strescape          (char *string);
Bool    strunescape        (char *string);
char   *strconvch          (char *string, char from, char to);

#ifdef __cplusplus
}
#endif


#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflsock.h
    Title:      TCP/IP, UDP/IP socket functions
    Package:    Standard Function Library (SFL)

    Written:    96/02/03  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/21  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to create, read, and write TCP and UDP
                sockets.  Encapsulates system dependencies.  Tested under
                MS Winsock, UNIX (Linux, AIX, SunOs), OpenVMS.  Some of the
                code in this module was based on the book "Internetworking
                With TCP/IP Volume III: Client-Server Programming And
                Applications BSD Socket Version" by Douglas E. Comer and
                David L. Stevens, published 1993 by Prentice-Hall Inc.
                ISBN 0-13-020272-X.  Defines sock_t which you should use
                for all sockets.  If you need to call a native socket
                function, use an (SOCKET) cast on the sock_t handle.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLSOCK_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLSOCK_INCLUDED


/*---------------------------------------------------------------------------
 *  Non-portable definitions - currently for Winsocks
 *  winsock.h is included in the prelude.h file.
 */

#if (defined (__WINDOWS__))
#   define sockerrno        winsock_last_error ()
#   undef INVALID_SOCKET                /*  MSVC defines these constants     */
#   undef SOCKET_ERROR                  /*    in winsock.h                   */
#else
#   define sockerrno        errno       /*  Use sockerrno for error number   */
    typedef int SOCKET;                 /*  Use (SOCKET) for system calls    */
#endif

/*---------------------------------------------------------------------------
 *  Define the socket type 'sock_t'.
 */

typedef qbyte sock_t;                   /*  Use t_sock for all sockets       */
#define INVALID_SOCKET   (sock_t) -1    /*  Invalid socket handle            */
#define SOCKET_ERROR     (sock_t) -1    /*  Error on socket function         */


/*---------------------------------------------------------------------------
 *  Fake socket definitions
 *
 *  If the system does not support sockets, we'll fake it so that the code
 *  still works.  Under crippleware OS's this will work so that all devices
 *  are always ready for I/O.  Most of this code is adapted from the Linux
 *  time.h file.  We also define some useful structures.
 */

#if (!defined (DOES_SOCKETS))
    /*  Number of descriptors that can fit in an `fd_set'.                   */
#   define FD_SETSIZE       256

    /*  It's easier to assume 8-bit bytes than to get CHAR_BIT.              */
#   define NFDBITS          (sizeof (unsigned long int) * 8)
#   define __FDELT(d)       ((d) / NFDBITS)
#   define __FDMASK(d)      (1 << ((d) % NFDBITS))
#   define FD_ZERO(set)     ((void) memset((void *) (set), 0, sizeof(fd_set)))
#   define FD_SET(d,set)    ((set)->__bits[__FDELT(d)] |=  __FDMASK(d))
#   define FD_CLR(d,set)    ((set)->__bits[__FDELT(d)] &= ~__FDMASK(d))
#   define FD_ISSET(d,set)  ((set)->__bits[__FDELT(d)] &   __FDMASK(d))

    /*  Fake a select() function that just returns 1                         */
#   define select(n,rf,wf,xf,t)         1

    /*  Define the fd_set structure for select()                             */
    typedef struct {
        qbyte __bits [(FD_SETSIZE + (NFDBITS - 1)) / NFDBITS];
    } fd_set;

    /*  Define the timeval structure for select()                            */
    struct timeval {
        long  tv_sec;                   /*  Seconds                          */
        long  tv_usec;                  /*  Microseconds                     */
    };

    /*  Define the generic socket address structure                          */
    struct sockaddr {
        dbyte sa_family;                /*  Type of address                  */
        char  sa_data [14];             /*  Value of address (filename)      */
    };

    /*  Define the internet socket address structure                         */
    struct in_addr {
        qbyte s_addr;
    };
    struct sockaddr_in {
        dbyte          sin_family;      /*  Type of address                  */
        dbyte          sin_port;        /*  Protocol port number             */
        struct in_addr sin_addr;        /*  IP address                       */
        char           sin_zero [8];    /*  Unused - should be zero          */
    };
#   define AF_INET          0

#endif                                  /*  Define FD_xxx                    */


/*---------------------------------------------------------------------------
 *  Required definitions
 *
 *  These are symbols used by calling programs: if the compiler does not
 *  define them, we do it.
 */

#if (!defined (O_NONBLOCK))             /*  open() flag for asynch I/O       */
#   define O_NONBLOCK       0
#endif

#if (!defined (EWOULDBLOCK))            /*  BSD tends to use EWOULDBLOCK     */
#   if (defined (__WINDOWS__))
#       define EWOULDBLOCK  WSAEWOULDBLOCK
#   else
#       define EWOULDBLOCK  -1
#   endif
#endif

#if (!defined (EINPROGRESS))            /*  Return code for asynch I/O       */
#   if (defined (__WINDOWS__))
#       define EINPROGRESS  WSAEINPROGRESS
#   else
#       define EINPROGRESS  EWOULDBLOCK
#   endif
#endif

#if (!defined (EAGAIN))                 /*  Return code for asynch I/O       */
#   define EAGAIN           EWOULDBLOCK
#endif

#if (!defined (EPIPE))                  /*  Return code for closed socket    */
#   define EPIPE            -1
#endif

#if (!defined (ECONNRESET))             /*  Return code for closed socket    */
#   if (defined (__WINDOWS__))
#       define ECONNRESET   WSAECONNRESET
#   else
#       define ECONNRESET   EPIPE
#   endif
#endif

#if (defined (__UTYPE_HPUX) || defined (__VMS__))
#   define FD_SETTYPE (int *)           /*  Some systems use the older       */
#else                                   /*    select() format                */
#   define FD_SETTYPE                   /*  Most use fd_set's                */
#endif

#if (!defined (MAXHOSTNAMELEN))         /*  Some guys don't define this      */
#   define MAXHOSTNAMELEN   256         /*    constant                       */
#endif
#if (!defined (INADDR_NONE))            /*  Some guys don't define this      */
#   define INADDR_NONE      -1          /*    constant                       */
#endif


/*---------------------------------------------------------------------------
 *  Error values returned by socket_error().  These reflect the last problem
 *  detected by one of the passive/connect connection functions.
 */

#define IP_NOERROR          0           /*  No errors                        */
#define IP_NOSOCKETS        1           /*  Sockets not supported            */
#define IP_BADHOST          2           /*  Host not known                   */
#define IP_BADSERVICE       3           /*  Service or port not known        */
#define IP_BADPROTOCOL      4           /*  Invalid protocol specified       */
#define IP_SOCKETERROR      5           /*  Error creating socket            */
#define IP_CONNECTERROR     6           /*  Error making connection          */
#define IP_BINDERROR        7           /*  Error binding socket             */
#define IP_LISTENERROR      8           /*  Error preparing to listen        */


/*---------------------------------------------------------------------------
 *  The ip_portbase is added to the port number when creating a service;
 *  you can set this variable before calling passive_TCP or passive_UDP.
 */

extern int
    ip_portbase;

/*---------------------------------------------------------------------------
 *  The ip_nonblock flag determines whether sockets are blocking or not.
 *  Under Windows sockets are never blocking.  Under UNIX they may be, or
 *  not.  For portability to Windows, this flag is set to TRUE by default.
 *  The main consequence of this is that after a connect_xxx() call you may
 *  need to perform a select() on the socket for writing to determine when
 *  the connection has suceeded.
 */

extern Bool
    ip_nonblock;

/*---------------------------------------------------------------------------
 *  The connect_errlist table provides messages for the connect_error()
 *  values.
 */

extern char
    *connect_errlist [];


/*---------------------------------------------------------------------------
 *  Function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

int    sock_init            (void);
int    sock_term            (void);
sock_t passive_TCP          (char *service, int queue_length);
sock_t passive_UDP          (char *service);
sock_t passive_socket       (char *service, char *protocol, int queue_length);
sock_t connect_TCP          (char *host, char *service);
sock_t connect_UDP          (char *host, char *service);
sock_t connect_TCP_fast     (struct sockaddr_in *sin);
sock_t connect_UDP_fast     (struct sockaddr_in *sin);
sock_t connect_socket       (char *host, char *service, char *protocol,
                             struct sockaddr_in *sin, int retry_max,
                             int retry_delay);
int    connect_to_peer      (sock_t handle, struct sockaddr_in *sin);
int    connect_error        (void);
sock_t accept_socket        (sock_t master);
sock_t create_socket        (char *protocol);
int    address_end_point    (char *host, char *service, char *protocol,
                             struct sockaddr_in *sin);
int    get_peer_addr        (sock_t handle, struct sockaddr_in *sin,
                             char *name, int namesize);
void   build_sockaddr       (struct sockaddr_in *sin, qbyte host, dbyte port);
char  *socket_hostaddr      (sock_t handle);
int    read_TCP             (sock_t handle, void *buffer, size_t length);
int    write_TCP            (sock_t handle, void *buffer, size_t length);
int    read_UDP             (sock_t handle, void *buffer, size_t length,
                             struct sockaddr_in *sin);
int    write_UDP            (sock_t handle, void *buffer, size_t length,
                             struct sockaddr_in *sin);
int    close_socket         (sock_t handle);
char  *get_host_name        (void);
Bool   socket_is_alive      (sock_t handle);
int    socket_error         (sock_t handle);
char  *sockmsg              (void);

#if (defined (__WINDOWS__))
int    winsock_last_error   (void);
#endif

#ifdef __cplusplus
}
#endif

/*  For backwards compatability with previous releases of sflsock            */

#define init_sockets        sock_init
#define term_sockets        sock_term

#endif                                  /*  Include sflsock.h                */
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflsymb.h
    Title:      Symbol-table functions
    Package:    Standard Function Library (SFL)

    Written:    93/12/27  Pieter Hintjens <ph@imatix.com>
    Revised:    96/10/26  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Symbol lookup is by name.  Symbols contain a string value
                and a pointer to an caller-defined memory block.

                The symbol-table functions let you create and manage symbol
                tables.  The functions are designed to be as general as
                possible (to support a wide variety of applications), but at
                the same time fast.  The symbol table data structure is based
                on a combined linked list & hash table representation.  The
                file sflsymb.h contains definitions for the various structures
                and external functions used in the sflsymb.c.  Both the
                linked-list and hash-table representations have a guaranteed
                order.  In the linked-list, new symbols are pushed on to the
                head of the list.  In the hash table each bucket just contains
                a pointer to a linked-list of symbols.  When a new symbol is
                created, it is pushed onto the front of this list.  The reason
                that both data structures are used is to make the algorithm
                faster.  Each representation has its stengths and weaknesses.
                For instance, if you wanted to lookup a symbol table entry
                for a given name using the hash table you could find it
                immediately, whereas with the linked-list, you would need to
                traverse most of the table to find the symbol.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLSYMB_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLSYMB_INCLUDED

/*  Structure of a symbol                                                    */

typedef struct _SYMBOL {
    struct _SYMBOL
         *next,                         /*  Next symbol in table             */
         *prev,                         /*  Previous symbol in table         */
         *h_next,                       /*  Next symbol in bucket            */
         *h_prev;                       /*  Previous symbol in bucket        */
    char *name;                         /*  Copy of name                     */
    char *value;                        /*  String value, or null            */
    void *data;                         /*  Caller data, or null             */
    byte  hash;                         /*  Hash bucket #                    */
} SYMBOL;

#define SYM_HASH_SIZE   256             /*  Assumed by sym_hash ()           */

/*  Structure of a symbol table                                              */

typedef struct {
    SYMBOL *symbols;                    /*  Pointer to list of symbols       */
    SYMBOL *hash [SYM_HASH_SIZE];       /*  Table of hash buckets            */
    int     size;                       /*  Number of symbols defined        */
} SYMTAB;

/*  Function that handles a symbol                                           */

typedef Bool (*symfunc) (SYMBOL *, ...);


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

SYMTAB *sym_create_table   (void);
void    sym_delete_table   (SYMTAB *symtab);
int     sym_merge_tables   (SYMTAB *symtab, SYMTAB *import);
SYMBOL *sym_lookup_symbol  (SYMTAB *symtab, char *name);
SYMBOL *sym_create_symbol  (SYMTAB *symtab, char *name, char *value);
SYMBOL *sym_assume_symbol  (SYMTAB *symtab, char *name, char *value);
SYMBOL *sym_delete_symbol  (SYMTAB *symtab, SYMBOL *symbol);
char   *sym_get_value      (SYMTAB *symtab, char *name, char *default_value);
long    sym_get_number     (SYMTAB *symtab, char *key, long default_value);
Bool    sym_get_boolean    (SYMTAB *symtab, char *key, Bool default_value);
void    sym_set_value      (SYMBOL *symbol, char *value);
int     sym_exec_all       (SYMTAB *symtab, symfunc handler, ...);
int     sym_hash           (char *name);
char  **symb2strt          (SYMTAB *symtab);
SYMTAB *strt2symb          (char **strings);
DESCR  *symb2descr         (SYMTAB *symtab);
SYMTAB *descr2symb         (DESCR *descr);

#ifdef __cplusplus
}
#endif


#endif                                  /*  Include SFLSYMB.H                */
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflcgi.h
    Title:      Common Gateway Interface functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/31  Pieter Hintjens <ph@imatix.com>
    Revised:    96/12/04  Pieter Hintjens <ph@imatix.com>

    Copyright:  Copyright (c) 1991-1996 iMatix

    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLCGI_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLCGI_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

int cgi_query_to_sym      (char *buffer, SYMTAB *table);
int file_cgi_query_to_sym (FILE *file,   SYMTAB *table);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sflenv.h
    Title:      Environment variable functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/14  Pieter Hintjens <ph@imatix.com>
    Revised:    96/10/26  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to read environment variables (also called
                shell variables or logical variables.)  Provides translation
                into numeric and Boolean values.  Provides functions to work
                with the environment block.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLENV_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLENV_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

char    *env_get_string   (char *name, char *default_value);
long     env_get_number   (char *name, long default_value);
Bool     env_get_boolean  (char *name, Bool default_value);
DESCR   *env2descr        (void);
char   **descr2env        (DESCR *descr);
SYMTAB  *env2symb         (void);
char   **symb2env         (SYMTAB *symtab);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfltok.h
    Title:      String token manipulation functions.
    Package:    Standard Function Library (SFL)

    Written:    96/09/10  Pieter Hintjens <ph@imatix.com>
    Revised:    96/09/10  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to break strings into tokens.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLTOK_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLTOK_INCLUDED


/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

char **tok_split    (char *string);
void   tok_free     (char **token_list);

#ifdef __cplusplus
}
#endif

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfltron.h
    Title:      Tracing functions
    Package:    Standard Function Library (SFL)

    Written:    92/10/25  Pieter Hintjens <ph@imatix.com>
    Revised:    96/08/06  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions for a programmer who needs to insert
                long-term tracing code in software.  The tracing code is
                activated and disactivated at run-time, for instance when
                problems are suspected.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLTRON_INCLUDED               /*  Allow multiple inclusions        */
#define _SFLTRON_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

void  enable_trace        (void);
void  disable_trace       (void);
void  push_trace          (Bool new_state);
void  pop_trace           (void);
void  set_trace_file      (char *filename, char mode);
void  trace               (char *format, ...);

#ifdef __cplusplus
}
#endif


/*  External variables                                                       */

extern Bool  TraceState;                /*  TRUE or FALSE                    */
extern FILE *TraceFile;                 /*  Current trace output file        */

#endif
/*  ----------------------------------------------------------------<Prolog>-
    Name:       sfluid.h
    Title:      Process user id (uid) and group id (gid) functions
    Package:    Standard Function Library (SFL)

    Written:    96/05/03  Pieter Hintjens <ph@imatix.com>
    Revised:    96/06/08  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Provides functions to access user and group id names and
                manage the current real/effective uid's and gid's for a
                process.  These functions are only meaningful on UNIX
                systems, and partially on VMS systems, but may be used by
                portable programs that must operate under UNIX as well as
                other environments.  Some uid functions are non-portable
                between UNIX systems; this package provides a single API.
                Changes for OS/2 were done by Ewen McNeill <ewen@naos.co.nz>.

    Copyright:  Copyright (c) 1991-1996 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the SFL License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#ifndef _SFLUID_INCLUDED                /*  Allow multiple inclusions        */
#define _SFLUID_INCLUDED

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif

char *get_uid_name  (uid_t uid);
char *get_gid_name  (gid_t gid);
int   set_uid_user  (void);
int   set_uid_root  (void);
int   set_gid_user  (void);
int   set_gid_root  (void);

#ifdef __cplusplus
}
#endif

#endif
