A simple paint program using raylib. 

## Dependencies

[Raylib](https://www.raylib.com/)

## Building for linux

```console
gcc -o paint main.c -Wall -Wextra -Wwrite-strings -Wno-unused-result -march=native -O2 -ftree-vectorize -fno-semantic-interposition -fno-plt -pipe -s -flto -D_FORTIFY_SOURCE=2 -lraylib
```

## Building for windows

Install [MSYS2](https://www.msys2.org/), then install the gcc compiler along with the raylib library using this command `pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-x86_64-raylib`.

```console
gcc -o paint.exe main.c -Wall -Wextra -Wwrite-strings -Wno-unused-result -march=native -O2 -ftree-vectorize -fno-semantic-interposition -fno-plt -pipe -s -flto -D_FORTIFY_SOURCE=2 -lraylib
```
