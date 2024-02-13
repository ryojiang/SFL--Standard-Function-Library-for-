set HDD=e:
SET PATH=.;\.;%HDD%\tc;%HDD%\tc\bin;%HDD%\tools;%HDD%\sflsrc14\script

@echo off
echo.
echo For any one who would like to use Turbo C 2.01 to compile Standard
echo Functional library, must initial compiler and its head files and library
echo path first.
echo.
echo In SFL 2.1 the c.bat file assumes all Turbo C execution file is located at
echo "bin" directory; therefore, there are 2 options to solve this issue
echo.
echo    1) Create "bin" directory first, and then either copy or move all
echo       Turbo C 2.01 execution files to "bin" directory
echo    2) Modify content of c.bat to let all execution file point to Turbo
echo       C 2.0 root directory
echo.
echo I chose the first way because Turbo C 3.0 already put all execution files
echo in the "bin" directory. This will make Turbo C 2.01 and 3.0 compatible.
echo.
echo Writen by Jau-Bing Lin on 2023/10/02
echo.

set CCNAME=tc
set CCDIR=\tc
set INCDEF=%CCDIR%\include
set LIBDIR=%CCDIR%\lib
echo ----- Initial compiler and its include file and library path -----
echo CCNAME=%CCNAME
echo CCDIR=%CCDIR
echo INCDEF=%INCDEF
echo LIBDIR=%LIBDIR
echo ----- End of initialization -----