#!/bin/bash

# Build GLEW dependency for target platform
function GLEW() {
  echo "Building GLEW"

  dir="$(pwd)/lib/GLEW"

  rm -rf "$dir"
  cd libsrc/GLEW || exit

  # https://github.com/nigels-com/glew/issues/31
  make extensions

  if [ "$1" == "win32" ]; then
    make SYSTEM=linux-mingw64 \
      CC=x86_64-w64-mingw32-gcc LD=x86_64-w64-mingw32-ld \
      LDFLAGS.EXTRA=-L"${dir}/lib" \
      GLEW_PREFIX="${dir}" \
      GLEW_DEST="${dir}"

    make SYSTEM=linux-mingw64 \
      CC=x86_64-w64-mingw32-gcc LD=x86_64-w64-mingw32-ld \
      LDFLAGS.EXTRA=-L"${dir}/lib" \
      GLEW_PREFIX="${dir}" \
      GLEW_DEST="${dir}" install
  else
    make LDFLAGS.EXTRA=-L"${dir}/lib" \
      GLEW_DEST="${dir}"

    make LDFLAGS.EXTRA=-L"${dir}/lib" \
      GLEW_DEST="${dir}" install
  fi
}

# Build SDL2 dependency for target platform
function SDL() {
  echo "Building SDL2"

  dir="$(pwd)/lib/SDL"
  rm -rf "$dir"

  [ -d libsrc/SDL/build ] && rm -rf libsrc/SDL/build
  mkdir -p libsrc/SDL/build
  cd libsrc/SDL/build || exit

  if [ "$1" == "win32" ]; then
    ../configure --prefix="$dir" --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --build=x86_64-linux --enable-static --disable-shared
  else
    ../configure --prefix="$dir"
  fi

  make && make install
}

# Build SDL_image dependency for target platform
function SDL_image() {
  echo "Building SDL_image"

  config_dir="$(pwd)/lib/SDL/bin/sdl2-config"
  dest_dir="$(pwd)/lib/SDL_image"
  rm -rf "$dest_dir"

  [ -d libsrc/SDL_image/build ] && rm -rf libsrc/SDL_image/build
  mkdir -p libsrc/SDL_image/build
  cd libsrc/SDL_image/build || exit

  ../autogen.sh

  if [ "$1" == "win32" ]; then
    export CC="x86_64-w64-mingw32-gcc -static-libgcc"
    export SDL2_CONFIG="$config_dir"
    ../configure --prefix="$dest_dir" --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --build=x86_64-linux --disable-webp
  else
    export CC="gcc -static-libgcc"
    export SDL2_CONFIG="$config_dir"
    ../configure --prefix="$dest_dir" --build=x86_64-linux --disable-webp
  fi

  make && make install
}

# Build soil dependency for target platform
function soil() {
  echo "Building soil"

  dir="$(pwd)/lib/soil"
  rm -rf "$dir"
  mkdir -p -- "$dir" "$dir/lib"

  [ -d libsrc/soil/build ] && rm -rf libsrc/soil/build && rm -f libsrc/soil/Makefile
  cd libsrc/soil || exit

  if [ "$1" == "win32" ]; then
    export CC="x86_64-w64-mingw32" && ./configure --prefix="$dir"
  else
    ./configure --prefix="$dir"
  fi

  make && make install
}

function zlib() {
  echo "Building zlib"

  dest="$(pwd)/lib/zlib"

  prepare_build_dirs libsrc/zlib "$dest"

  if [ "$1" == "win32" ]; then
    export CC="x86_64-w64-mingw32" && ../configure --prefix="$dest"
  else
    ../configure --prefix="$dest"
  fi

  make && make install
}

function libpng() {
  echo "Building libpng"

  dest="$(pwd)/lib/libpng"

  prepare_build_dirs libsrc/libpng "$dest"

  if [ "$1" == "win32" ]; then
    export CC="x86_64-w64-mingw32" && ../configure --prefix="$dest"
  else
    ../configure --prefix="$dest"
  fi

  make && make install
}

function libjpeg() {
  echo "Building libjpeg"

  dest="$(pwd)/lib/libjpeg"

  prepare_build_dirs libsrc/libjpeg-turbo "$dest"

  cmake ..
  make
}

# Clears, creates and enters build and destination dirs
function prepare_build_dirs() {
  lib_src=$1
  lib_dest=$2

  rm -rf "$lib_dest"
  mkdir -p -- "$lib_dest" "$lib_dest/lib"

  [ -d "$lib_src/build" ] && rm -rf "$lib_src/build"
  mkdir -p "$lib_src/build"
  cd "$lib_src/build" || exit
}

# Build Linux binary
function build_linux() {
  rm -rf build
  mkdir -p build
  cd build || exit
  export CC="gcc" && export CXX="g++" && cmake ..
  make
}

# Build Windows binary
function build_windows() {
  rm -rf build
  mkdir -p build
  cd build || exit
  export CC="x86_64-w64-mingw32-gcc" && export CXX="x86_64-w64-mingw32-g++" && cmake .. -DWIN32=1 -DGLEW_STATIC=1
  make
}

# Conditional verbose output
verb() {
  if ((verbose == 0)); then
    "$@" >/dev/null
  else
    "$@"
  fi
}

if [ ! -f "CMakeLists.txt" ]; then
  echo "Invalid directory. Script must be run from project root directory."
  exit
fi

build_target='linux'
build_deps=false
verbose=0

while test $# -gt 0; do
  case "$1" in
  -h | --help)
    echo "TODO help"
    exit 0
    ;;
  -t | --test)
    (verb libjpeg "$build_target")
    exit 0
    ;;
  -v | --verbose)
    verbose=1
    shift
    ;;
  -w | --windows)
    build_target="win32"
    shift
    ;;
  -l | --linux)
    build_target="linux"
    shift
    ;;
  -d | --dependencies)
    build_deps=true
    shift
    ;;
  *)
    break
    ;;
  esac
done

if $build_deps; then
  # Build all dependencies
  (verb SDL "$build_target")
  (verb GLEW "$build_target")
  (verb soil "$build_target")
  (verb libpng "$build_target")
  (verb zlib "$build_target")
  (verb SDL_image "$build_target")
fi

if [ $build_target == "win32" ]; then
  echo "Building for Windows"
else
  echo "Building for Linux"
fi

# Build binary
if [ $build_target == "win32" ]; then
  build_windows
else
  build_linux
fi
