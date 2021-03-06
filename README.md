# Trikonasana - 3D renderer from scratch

A software CPU based 3D renderer made in pure C and SDL.

## Install

Install [SDL2 library](https://www.libsdl.org/). For ode completion, compile errors, go-to-definition, etc. install [clangd](https://clangd.llvm.org/installation.html).

## Configure && build

Create `build` directory in the root directory, `cd` to `build` directory and run

```
cmake ..
```

Staying in `build` directory, type

```
make
```

to compile and run the program.

## Run

Create `bin` directory in the root directory. `cd` to `bin/` and run

```
./main
```

If you have created `bin`, you can `cd` to `build` and type

```
make && cd ../bin && ./main
```

### Clangd

`compile_commands.json` will be created in `build` directory. Symlink it (or copy it) to the root directory. To symlink it, `cd` to the root and

```
ln -s build/compile_commands.json .
```


