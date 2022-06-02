#!/bin/bash

ROOT_DIR=~/Development/trikonasana
EXE_NAME=main
CONFIGURE=false
COMPILE_CMD="make"
WIN=false

while getopts ":c" option; do
    case $option in
        c)
            CONFIGURE=true
            ;;
    esac
done

if [ "$OSTYPE" = "msys" ]; then
    WIN=true
    
    COMPILE_CMD="MSBuild.exe -target:Build /property:Configuration=Release main.vcxproj"
    ROOT_DIR="c:/Users/darko/Development/trikonasana/"
fi

# configure
if [ $CONFIGURE == true ]; then
    cd $ROOT_DIR/build/
    cmake ..

    if  [ $WIN == true ]; then
        cd $ROOT_DIR/ninja/
        cmake -G"Ninja" ..
        mv compile_commands.json ..
    fi
fi


# build
cd $ROOT_DIR/build/
echo "COMPILE_CMD: $COMPILE_CMD"
$COMPILE_CMD

# run
cd $ROOT_DIR/bin/
echo "EXE_NAME: $EXE_NAME"
./${EXE_NAME}
