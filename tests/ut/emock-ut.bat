@echo off
copy /y ..\3rdparty\testngpp\src\runner\Debug\testngpp-runner.exe .
copy /y ..\3rdparty\testngpp\src\listeners\Debug\*.dll .
setlocal enabledelayedexpansion
set cases=
for /r %%i in (Debug\emock-ut-*.dll) do (
   set cases=!cases! %%~pni
)
@echo !cases!
testngpp-runner.exe -L. -l"testngppxmllistener result.xml" -l"testngppstdoutlistener -c " -c100 !cases!
