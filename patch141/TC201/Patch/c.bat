:-  compile
echo Compiling %1...
\tc\bin\tcc -c -f -O -Z -w -C -I%INCDEF% -L%LIBDIR% -DDEBUG %1 > %1.err
if errorlevel 1 goto error
goto ok
:error
	echo.
    type %1.err
    echo Compile errors in %1
    goto exit
:ok

:exit