#!/bin/bash

ROOT_DIR=~/Development/trikonasana

TARGET=main
EXECUTABLE=main

CONFIGURE=false
COMPILE_CMD="make"
WIN=false

while getopts "t:c" option; do
    case $option in
        c)
            CONFIGURE=true
            ;;
        t)
            TARGET=$OPTARG
            EXECUTABLE=$OPTARG
            ;;
    esac
done


if [ "$OSTYPE" = "msys" ]; then
    WIN=true
    
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Debug"
    ROOT_DIR="c:/Users/darko/Development/trikonasana/"

    TARGET=${TARGET}.vcxproj
    EXECUTABLE=${EXECUTABLE}.exe
fi

# configure
if [ $CONFIGURE == true ]; then
    cd $ROOT_DIR/build/
    cmake ..
    
    if [ $? != 0 ]; then
        exit 1
    fi
    
    if  [ $WIN == true ]; then
        cd $ROOT_DIR/ninja/
        cmake -G"Ninja" ..
        mv compile_commands.json ..
    fi

    exit 0
fi


# build
cd $ROOT_DIR/build/
echo "COMPILE_CMD: $COMPILE_CMD ${TARGET}"
$COMPILE_CMD ${TARGET}

# run
cd $ROOT_DIR/bin/
echo "EXECUTABLE: $EXECUTABLE"
./${EXECUTABLE}
