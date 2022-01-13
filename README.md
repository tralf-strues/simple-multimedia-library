# simple-multimedia-library
The library provides the following cross-platform functionality:
1. **Graphics wrapper (⚙️ work-in-progress).**
   * Creating and managing windows (see `Window`).
   * Rendering textures, text and primitives (lines, rectangles, circles, etc.) in a state-machine kind of way (see `Renderer`).
   * Loading and writing images.
2. **Basic 3D template-based math library (⚙️ work-in-progress).**
   * Vectors (see `Vec2<T>` and `Vec3<T>`) and matrices (see `Mat4<T>`).
   * Image kernels, gaussian blur and sharpening.
   * Equation solving.
3. **Event system.**
   * Listener pattern interface.
   * Abstract `Event` class.
   * Event dispatching interfaces (see `EventDispatcher`, `EventDispatchChain` and `EventTarget`).
   * System events (window, input events, etc.).
4. **Application abstraction.**
5. **Logging system (⚙️ work-in-progress).**

## Installation
The `install` script will create a directory `sml/`, which will contain all header files and the static library `sml.a`, in the directory specified by `OutputPrefix`.
```Shell
$ git clone https://github.com/tralf-strues/simple-multimedia-library.git
$ cd simple-multimedia-library
$ make install OutputPrefix=<YOUR DIRECTORY HERE>
```