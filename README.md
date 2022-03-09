# Trikonasana - 3D renderer from scratch

A software CPU based 3D renderer made in pure C and SDL.

## Install

Install [SDL2 library](https://www.libsdl.org/). For ode completion, compile errors, go-to-definition, etc. install [clangd](https://clangd.llvm.org/installation.html).

## Configure & build

Create `build` directory in the root directory. 

### Linux & MinGW

To configure and generate, run

```
cd build/ && cmake -G"Unix Makefiles" ..
```

to compile and run the program on Linux

```
cd build/ && make && cd ../bin && ./main
```

to compile and run the program with MingW

```
cd build/ && make && cd ../bin && main.exe
```

### MSVC

To configure and generate, run

```
cd build/ && cmake ..
```

to compile and run the program 

```
cd build && MSBuild.exe -target:Build /property:Configuration=Release /m /noWarn:C4244;C4305 main.vcxproj && cd ../bin && main.exe
```

Warning C4244 is about possible loss of data due to conversion, e.g. from 'float' to 'int'. Warning C4305 is about possible loss of data due to truncation, e.g. from 'double' to 'float'.

### Clangd

If you are on Linux, `compile_commands.json` will be created in `build` directory. Symlink it (or copy it) to the root directory. To symlink it, `cd` to the root and

```
ln -s build/compile_commands.json .
```

On windows, you can generate or `compile_commands.json` using MinGW with

```
cd build/ && cmake -G"Unix Makefiles" .. && mv compile_commands.json ../
```

or using MSVC Ninja with

```
cd ninja && cmake -G"Ninja" .. && mv compile_commands.json ..
```



