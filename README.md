# simple-multimedia-library
The library provides with the following functionality:
1. Creating and managing windows (see `Window`).
2. Simple primitives (like points, lines, rectangles, etc.), texture (see `Texture`) and text (see `Text`) rendering.
3. Basic 3D math library - vectors (see `Vec2<T>` and `Vec3<T>`), matrices (see `Mat4<T>`), etc.
4. Event system.

## Installation
The `install` script will create a directory `simple-multimedia-library/` with two subdirectories `include/` (this one will contain all header files) and `lib/` (this one will contain the static library `simple-multimedia-library.a`) in the directory specified by `OutputPrefix`.
```Shell
$ git clone https://github.com/tralf-strues/simple-multimedia-library.git
$ cd simple-multimedia-library
$ make install OutputPrefix=<YOUR DIRECTORY HERE>
```