@echo off

rem Only run this script inside the project folder
rem where .vcxproj file is located, NOT the solution folder, or else it will horribly break!
rem Visual Studio's working directory for post-build scripts by default is the project directory.
rem so setting this script as Post-Build in VS should be fine.

echo Copying files...
copy /Y ..\Release\libmulti.dll ..\libmulti.gmx\extensions\libmulti\libmulti.dll
rem copy /Y ..\Release\libmulti.dll ..\libmulti.gms2\extensions\libmulti\libmulti.dll
copy /Y ..\Release\libmulti.dll ..\libmulti.gms23\extensions\libmulti\libmulti.dll
copy /Y ..\x64\Release\libmulti_x64.dll ..\libmulti.gms23\extensions\libmulti\libmulti_x64.dll
copy /Y libmulti.h ..\libmulti.gmx\extensions\libmulti\libmulti.cpp
rem copy /Y libmulti.h ..\libmulti.gms2\extensions\libmulti\libmulti.cpp
copy /Y libmulti.h ..\libmulti.gms23\extensions\libmulti\libmulti.cpp

echo Running GmxGen...

rem 1.4.
GmxGen ..\libmulti.gmx\extensions\libmulti.extension.gmx

rem 2.1 - 2.2.5.
rem GmxGen ..\libmulti.gms2\extensions\libmulti\libmulti.yy

rem 2.3.1+, x86 and x64.
GmxGen ..\libmulti.gms23\extensions\libmulti\libmulti.yy

echo Cleanup...
del /Q /F ..\libmulti.gmx\extensions\libmulti\libmulti.cpp
rem del /Q /F ..\libmulti.gms2\extensions\libmulti\libmulti.cpp
del /Q /F ..\libmulti.gms23\extensions\libmulti\libmulti.cpp

