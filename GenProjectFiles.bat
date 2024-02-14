%ECHO OFF
SETLOCAL
CD /D %~dp0

SHARPMAKE\SHARPMAKE.APPLICATION.EXE "/sources(@'Oxygen.sharpmake.cs') /verbose"
if %ERRORLEVEL% NEQ 0 (
    PAUSE
)