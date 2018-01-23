!#/bin/bash

echo "rm cmake cache begin..."
rm ./cmake_install.cmake
rm -r ./CMakeFiles
rm ./Makefile
rm ./CMakeCache.txt
rm getopt_custom
echo "rm cmake cache end..."
