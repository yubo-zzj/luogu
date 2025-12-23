@echo off
rem run_current.bat
rem Usage: run_current.bat [exeName] [inputFile]

setlocal enabledelayedexpansion

if "%~1"=="" (
  rem pick the first .exe in the current directory
  for %%f in ("%CD%\*.exe") do (
    set "EXE=%%~nxf"
    goto :found
  )
) else (
  set "EXE=%~1"
)

:found
if not defined EXE (
  echo No .exe found in %CD%
  pause
  exit /b 1
)

if "%~2"=="" (
  echo Running "%EXE%" (no input redirection)
  "%CD%\%EXE%"
) else (
  echo Running "%EXE%" with input file "%~2"
  cmd /c "%CD%\%EXE% < %~2"
)

echo Exit code: %ERRORLEVEL%
pause
