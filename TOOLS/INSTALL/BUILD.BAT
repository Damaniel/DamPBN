@ECHO OFF
REM set the build memory model (currently large)
SET MEMMODEL=/ml
REM delete any existing executable
DEL *.EXE
REM change to the source directory
ECHO ********************* Building installer *************************
CD SRC
WCL INSTALL.C INPUT.C RENDER.C UTIL.C /zq /i..\INCLUDE %MEMMODEL% /fe=INSTALL.EXE ..\LIBS\TEXTDRAW.LIB
DEL *.OBJ
MOVE INSTALL.EXE .. >NUL
cd ..

