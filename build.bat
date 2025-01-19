@echo off
setlocal enabledelayedexpansion

:: Change to script directory
cd /d "%~dp0"

:: Initialize VS Developer Environment
if not defined VSCMD_ARG_TGT_ARCH (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    if errorlevel 1 (
        echo Error: Could not initialize Visual Studio environment.
        exit /b 1
    )
)

:: --- Unpack Arguments ---------------------------------------------------
set test=
set main=
for %%a in (%*) do (
    set %%a=1
)

:: --- Compiler Setup ----------------------------------------------------
set "compile=cl /nologo /W4 /EHsc /Zi /I.\src /I..\src"
set "compile_link=/link /DEBUG"

:: --- Prep Directories -------------------------------------------------
if not exist build mkdir build
if not exist build\obj mkdir build\obj
if not exist build\obj\base mkdir build\obj\base
if not exist build\obj\tests mkdir build\obj\tests

:: --- Build Everything ------------------------------------------------
cd build

if defined test (
    echo Building tests...
    %compile% ..\tests\test_main.c /Fe:test_runner.exe %compile_link%
    if !errorlevel! equ 0 (
        echo Running tests...
        .\test_runner.exe
    )
)

if defined main (
    echo Building main executable...
    %compile% ..\src\main.c /Fe:oci.exe %compile_link%
    if !errorlevel! equ 0 (
        echo Running main executable...
        .\oci.exe
    )
)

:: --- Warn On No Builds -----------------------------------------------
if not defined test if not defined main (
    echo [WARNING] no valid build target specified; must use build target names as arguments
    echo Usage: build.bat main          (builds main executable^)
    echo        build.bat test          (builds and runs tests^)
    echo        build.bat main test     (builds both^)
    exit /b 1
)

cd ..
endlocal
