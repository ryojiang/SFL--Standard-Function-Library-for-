Folder content
--------------
issue    - Contents all issues found when using Microsfot C 5.0
           (small memory model) makefiles to compile original SFL source code
makefile - Contents 5 sets of makefile for Microsfot C 5.0 with MAKE.EXE
           Version 4.06
original - Contents original source codes from SFL 1.4 that will be replaced
           by modified codes in patch folder.
patch    - Contents code must be modified in order to eliminate those errors
           when using Microsfot C 5.0 to compile origianal SFL 1.4 source code


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

4. Miscrosoft C 5.0 compiler have 5 memory models for user to choose. 
------------------------------------------------------------------------------
Base on above status, I do some modification to make SFL v1.4 alive 

1. A modified version of 'Build.BAT' for Miscrosoft C 5.0 which I named it
   'MSCbuild.BAT'

2 'MSCbuild.bat' still not contains any code to create Test????.exe

3. For speed up to create standard library 'LIBSFL.LIB', I create makefiles
   for Miscrosoft C 5.0. and these makefiles are not only can create
   'LIBSFL.LIB', but also can create all test files. Furthermore, I add some
   features on this makefile that able to delet all test files' .obj, .exe,
   even 'LIBSFL.LIB'. For detail please refer to makefile source.

4. I created 5 sets of makefile for 5 different momory models.
   When use these 5 set of makefile to build SFL, Each set of makefiles will
   keep a copy of 'LIBSFL.LIB' named such as LIBMSCah.LIB, SFLMSCal.LIB,
   SFLMSCam.LIB, SFLMSCas.LIB, SFLMSCac.LIB that for later on use by user 

------------------------------------------------------------------------------
Q&A
---
1. 
  Q: Why using Miscrosoft C 5.0 Optimizing compiler ?
  A: 1) Because it is close to Unix System V C standard library
     2) Miscrosoft C 4.0 Optimizing compiler may be to old, and it is not work
        well within my environment.
        
Last modified date on 2024/02/13