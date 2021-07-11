# ish - a simple shell written in C

## Installing
### Debian
check the latest release for debs
### Other Linux
compile yourself for now
## compiling
**Dependencies:**
- readline (debian & pacman package `libreadline-dev`)
- A C compiler like `gcc`.
- `make`
- `Cmake` version 3.16 and later

In the root of the `ish` folder, run:
```
mkdir build
cd build
cmake ..
make
```
### Installing
in the build folder run `sudo make install`
### Packaging
run the following in the `build` folder:
- Debian package: `cpack -G DEB`

