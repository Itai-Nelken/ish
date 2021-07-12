# ish - a simple shell written in C

## Installing

### To install for Debian/Ubuntu based distributions:

To download for Debian/Ubuntu based distributions, simply go to Github [releases](https://github.com/Itai-Nelken/ish/releases/latest) and install the package through dpkg or apt.

### To compile from source:

Compile from source when the `.deb` isn't useful for your distribution.

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

To install to /usr/local/bin, run the command `sudo make install`.

### Optional - Packaging:

While inside the `build` folder of `ish`, run: 

- Debian package: `cpack -G DEB`
