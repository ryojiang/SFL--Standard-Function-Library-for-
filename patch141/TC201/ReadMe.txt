Folder content
--------------
issue    - Contents all issues found when using Turbo C 2.01
           (small memory model) makefiles to compile original SFL source code
makefile - Contents 5 sets of makefile for Turbo C 2.01 with MAKE.EXE
original - Contents original source codes from SFL 1.4 that will be replaced
           by modified codes in patch folder.
patch    - Contents code must be modified in order to eliminate those errors
           when using Turbo C 2.01 to compile origianal SFL 1.4 source code


Note
----
1. SFL 1.4 source file included 'Build.BAT' is not working

2. 'Build.BAT' not contains any code to create any Test????.exe file

3. Each time using batch file to create standard library 'LIBSFL.LIB' is very
   slow if only modify one single file, it will need to build all objiect 
   files, and link all files again

4. One by one manully to compile all test file, there are many problems
   occurred. And after create execution files, many cannot run.

5. Turbo C 2.01 lacks some features than Mircrosoft C 5.0 and Quick C 2.01 
   compiler. Such as
   1) Lacks of 'MALLOC.H' head file which is consistency with Unix system V 
      C compiler head file
   2) Head file 'TIME.H' lack of definition of  'CLOCKS_PER_SEC' and 'mktime()'
   3) All memory model library files lack of 'mktime()' function 

6. Turbo C 2.01 compiler have 6 memory models for user to choose. 
--------------------------------------------------------------------------
Base on above status, I do some modification to make SFL v1.4 alive
 
1. A modified version of 'Build.BAT' for Turbo C 2.01 which I named it
   'TCbuild.BAT'

2 'TCbuild.bat' still not contains any code to create Test????.exe

3. For speed up to create standard library 'LIBSFL.LIB', I create makefile
   for Turbo C 2.01. and these makefiles not only can create 'LIBSFL.LIB', but
   also can create all test files. Furthermore, I add some features on these
   makefiles so that they are able to delet all test files' .obj, .exe, even
   'LIBSFL.LIB'. For detail please refer to makefile source before use them.

4. 
  1) The easy way is just copy Turbo C 2.01 'ALLOC.H' to 'MALLOC.H'
  2) Modify head file 'TIME.H' to add definition of  'CLOCKS_PER_SEC' and
     'mktime()'

5. I created 6 makefiles for different momory models. After using each makefile
   to build SFL, they will keep a copy of 'LIBSFL.LIB' named such as
   LIBTC-mh.LIB, SFLTC-ml.LIB, SFLTC-mm.LIB, SFLTC-ms.LIB, SFLTC-mt.LIB,
   SFLTC-mc.LIB that for later on use by user 

------------------------------------------------------------------------------
Q&A
1. 
  Q: Why using Turbo C 2.01 ?
  A: 1) Because it is Free, quick, and small; also it is easy to use in DOS
     2) Easy to find document e.g. user's guide, and reference book for
        Turbo C 2.01
     3) Because I have software and manuals (books) on my hand
     
Last modified date on 2024/02/13