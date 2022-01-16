# Trikonasana - 3D renderer from scratch

A software CPU based 3D renderer made in pure C and SDL.

## Install

Install [SDL2 library](https://www.libsdl.org/). For ode completion, compile errors, go-to-definition, etc. install [clangd](https://clangd.llvm.org/installation.html).

## Configure && build

Create `build` directory in the root directory. 

To configure and generate, run

```
cd build/ && cmake -G"Unix Makefiles" ..
```

to compile and run the program on Linux

```
cd build/ && make && cd ../bin && ./main
```

to compile and run the program on Windows (with MingW)

```
cd build/ && make && cd ../bin && main.exe
```

### Clangd

`compile_commands.json` will be created in `build` directory. Symlink it (or copy it) to the root directory. To symlink it, `cd` to the root and

```
ln -s build/compile_commands.json .
```

or

```
cd build/ && cmake -G"Unix Makefiles" .. && mv compile_commands.json ../
```



