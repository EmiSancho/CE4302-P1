@echo off 

set /p prot=Protocolo 1 o 2: 

g++ -o main.exe main.cpp
main.exe %prot%

REM timeout /t 2
REM python "gui/gui.py"

pause