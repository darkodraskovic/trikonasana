#!/bin/bash

ROOT_DIR=~/Development/trikonasana
EXE_NAME=main
CONFIGURE=false
COMPILE_CMD="make"

while getopts ":c" option; do
    case $option in
        c)
            CONFIGURE=true
            ;;
    esac
done

if [ "$OSTYPE" = "msys" ]; then
    EXE_NAME=${EXE_NAME}.exe
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release main.vcxproj"
else
    EXE_NAME=./${EXE_NAME}
fi

if [ $CONFIGURE == true ]; then
    cd $ROOT_DIR/build/
    cmake ..
fi


cd $ROOT_DIR/build/
echo "COMPILE_CMD: $COMPILE_CMD"
$COMPILE_CMD
cd $ROOT_DIR/bin/
echo "EXE_NAME: $EXE_NAME"
$EXE_NAME
