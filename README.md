# ish - a simple shell written in C

## Installing

### To install for Debian/Ubuntu based distributions:

To download for Debian/Ubuntu based distributions, simply go to Github [releases](https://github.com/Itai-Nelken/ish/releases) and install the package through dpkg or apt.

### To compile from source:

This also works with Debian/Ubuntu based distributions however will work for distributions which don't use dpkg or apt.

## Building:

**Dependencies:**

- Readline - Install `libreadline-dev`
- A C compiler like `gcc`
- `make`
- `Cmake` version 3.16 and later

While inside the root of the `ish` folder, run:

```sh
mkdir build
cd build
cmake ..
make
```

### Installing:

To install to /usr/loca/bin, run the command `sudo make install`.

### Optional - Packaging:

While inside the `build` folder of `ish`, run: 

- Debian package: `cpack -G DEB`
