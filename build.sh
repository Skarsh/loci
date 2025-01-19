#!/bin/bash
set -eu
cd "$(dirname "$0")"

# --- Unpack Arguments --------------------------------------------------------
for arg in "$@"; do declare $arg='1'; done

# --- Compiler Setup --------------------------------------------------------
compiler="${CC:-cc}"
compile="$compiler -Wall -Wextra -g -I./src -I../src"
compile_link=""

# --- Prep Directories -------------------------------------------------------
mkdir -p build
mkdir -p build/obj
mkdir -p build/obj/base
mkdir -p build/obj/tests

# --- Generate compile_commands.json -----------------------------------------
if [ -v bear ]
then
    echo "Generating compile_commands.json..."
    bear -- make
    exit 0  # Exit after generating compile_commands.json
fi

# --- Build Everything ------------------------------------------------------
cd build

if [ -v test ]
then
    $compile ../tests/test_main.c $compile_link -o test_runner && ./test_runner
fi

if [ -v main ]
then
    $compile ../src/main.c $compile_link -o oci && ./oci
fi


# --- Warn On No Builds -----------------------------------------------------
if [ ! -v test ] && [ ! -v main ]
then
    echo "[WARNING] no valid build target specified; must use build target names as arguments"
    echo "Usage: ./build.sh main          (builds main executable)"
    echo "       ./build.sh test          (builds and runs tests)"
    echo "       ./build.sh main test     (builds both)"
    echo "       ./build.sh bear          (regenerate compile_commands.json)"
    exit 1
fi

cd ..
