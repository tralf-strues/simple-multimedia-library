# simple-multimedia-library
The library provides with the following functionality:
1. Creating and managing windows (see `Window`).
2. Simple primitives (like points, lines, rectangles, etc.), texture (see `Texture`) and text (see `Text`) rendering.
3. Basic 3D math library - vectors (see `Vec2<T>` and `Vec3<T>`), matrices (see `Mat4<T>`), etc.
4. Event system.

## Installation
The `install` script will create a directory `sml/`, which will contain all header files and the static library `sml.a`, in the directory specified by `OutputPrefix`.
```Shell
$ git clone https://github.com/tralf-strues/simple-multimedia-library.git
$ cd simple-multimedia-library
$ make install OutputPrefix=<YOUR DIRECTORY HERE>
```