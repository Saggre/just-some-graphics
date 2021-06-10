# Just some graphics

![Build Status](https://github.com/Saggre/just-some-graphics/workflows/Build%20release/badge.svg?style=flat-square)

## Building a new release with GitHub Actions

- `git tag <tag>`
- `git push origin <tag>`

## Building manually

Supports building for Linux and Windows, but binaries can only be built on Linux.

### Build requirements

```bash
sudo apt-get update
sudo apt-get -y install cmake python
sudo apt-get -y install build-essential libxmu-dev libxi-dev libgl-dev libglu1-mesa-dev
```

Additional requirements for Windows:

```bash
sudo apt-get -y install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64
```

### Building for Linux

#### With a build script

```bash
cd <root-dir> # Run in project root dir
./scripts/build.sh --linux --dependencies -v
cd <root-dir>/build/bin # Binary will be located here
```

Flag `--dependencies` builds all dependencies. Subsequent builds can omit this flag to speed up the build process
significantly.

### Building for Windows

#### With a build script

```bash
cd <root-dir> # Run in project root dir
./scripts/build.sh --windows --dependencies -v
cd <root-dir>/build/bin # Binary will be located here
```

Flag `--dependencies` builds all dependencies. Subsequent builds can omit this flag to speed up the build process
significantly.
