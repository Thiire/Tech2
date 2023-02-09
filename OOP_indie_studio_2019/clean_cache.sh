#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
ORANGE="\033[0;33m"
ENDCOLOR="\033[0m"
check=0;

echo -e "${BLUE}         _                               
     | |                (_)            
  ___| | ___  __ _ _ __  _ _ __   __ _ 
 / __| |/ _ \/ _  |  _ \| |  _ \ / _  |
| (__| |  __/ (_| | | | | | | | | (_| |
 \___|_|\___|\__ _|_| |_|_|_| |_|\__, |
                                  __/ |
                                 |___/ \n${ENDCOLOR}"


if [ -f cmake_install.cmake ]; then
    echo -e "${GREEN}Removing file 'cmake_install.cmake'${ENDCOLOR}";
    rm cmake_install.cmake;
    ((++check));
fi;

if [ -f CMakeCache.txt ]; then
    echo -e "${GREEN}Removing file 'CMakeCache.txt'${ENDCOLOR}";
    rm CMakeCache.txt;
    ((++check));
fi;

if [ -f Makefile ]; then
    echo -e "${GREEN}Removing file 'Makefile'${ENDCOLOR}";
    rm Makefile;
    ((++check));
fi;

if [ -d CMakeFiles ]; then
    echo -e "${GREEN}Removing directory 'CMakeFiles'${ENDCOLOR}";
    rm -r CMakeFiles;
    ((++check));
fi;

if [ ${check} == 0 ]; then
    echo -e "${ORANGE}Nothing to clean";
fi