Folder content
--------------
issue    - Contents all issues found when using Quick C 2.01
           (small memory model) makefiles to compile original SFL source code
makefile - Contents 5 sets of makefile for Quick C 2.01 with NMAKE.EXE
           Version 1.00
original - Contents original source codes from SFL 1.4 that will be replaced
           by modified codes in patch folder.
patch    - Contents code must be modified in order to eliminate those errors
           when using Quick C 2.01 to compile origianal SFL 1.4 source code


important note
--------------
When use Miscrosoft C 5.0 Optimizing compiler and link in vDOS emulator
that vDOS will report the "Packed file is corrupt"

In order to solve this issue, go to vDOS setup directory, Edit 'config.txt'
file in ====== Memory ====== section, remove 'REM' keyword from below
line. After that need to reopen vDOS window before it affect.

REM LOW = OFF


Note
----
1. SFL 1.4 source file included 'Build.BAT' is not working

2. 'Build.BAT' not contains any code to create any Test????.exe file

3. Each time using batch file to create standard library 'LIBSFL.LIB' is very
   slow if only modify one single file, it will need to build all objiect 
   files, and link all files again

3. One by one manully to compile all test file, there are many problems
   occurred. And after create execution files, many cannot run.

4. Microsoft C 5.0 has 5 memory models, but Quick C 2.01 compiler only have
   4 memory models for user to choose;
   
   --------------------------------
   Memory Model   Data Pointer Size
   --------------------------------
   small          16 bits
   medium         16 bits
   compact        32 bits
   large          32 bits

5. Quick C 2.01 install packag contains with NMAKE.EXE which is more
   consistency with Unix make utility than Microsoft C 5.0 MAKE.EXE

------------------------------------------------------------------------------
Base on above status, I do some modification to make SFL v1.4 alive 

1. A modified version of 'Build.BAT' for Quick C 2.01 which I named it
   'MSCbuild.BAT'

2 'MSCbuild.bat' still not contains any code to create Test????.exe

3. For speed up to create standard library 'LIBSFL.LIB', I create makefiles
   for Quick C 2.01. and these makefiles are not only can create
   'LIBSFL.LIB', but also can create all test files. Furthermore, I add some
   features on this makefile that able to delet all test files' .obj, .exe,
   even 'LIBSFL.LIB'. For detail please refer to makefile source.

4. I created 4 makefiles for 4 different momory models.
   When use these 4 makefiles to build SFL, Each makefile will keep a copy of
   'LIBSFL.LIB' named such as 'SFLQC-al.LIB', 'SFLQC-am.LIB', 'SFLQC-as.LIB',
   'SFLQC-ac.LIB' that for later on use by user

5. Must use NMAKE.EXE Version 1.00 with these makefiles intead. Microsoft C 5.0
   MAKE.EXE Version 4.06 won't work with these makefiles.

------------------------------------------------------------------------------
Q&A
1. 
  Q: Why using Quick C 2.01 Optimizing compiler ?
  A: 1) Because it is close to Unix System V C standard library
     2) Miscrosoft C 4.0 Optimizing compiler may be to old, and it is not work
        well within my environment.
        
Last modified date on 2024/02/13