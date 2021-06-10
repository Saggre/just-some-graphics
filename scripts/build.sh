#!/bin/bash

# Build GLEW dependency for target platform
function GLEW() {
  dir="$(pwd)/lib/GLEW"

  rm -rf "$dir"
  cd libsrc/GLEW || exit

  if [ "$1" == "win32" ]; then
    make SYSTEM=linux-mingw64 \
      CC=x86_64-w64-mingw32-gcc LD=x86_64-w64-mingw32-ld \
      LDFLAGS.EXTRA=-L"${dir}"/lib \
      GLEW_PREFIX="${dir}" \
      GLEW_DEST="${dir}"

    make SYSTEM=linux-mingw64 \
      CC=x86_64-w64-mingw32-gcc LD=x86_64-w64-mingw32-ld \
      LDFLAGS.EXTRA=-L"${dir}"/lib \
      GLEW_PREFIX="${dir}" \
      GLEW_DEST="${dir}" install
  else
    make LDFLAGS.EXTRA=-L"${dir}"/lib \
      GLEW_DEST="${dir}"

    make LDFLAGS.EXTRA=-L"${dir}"/lib \
      GLEW_DEST="${dir}" install
  fi

}

# Build SDL dependency for target platform
function SDL() {
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
    (verb GLEW "$build_target")
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

if [ $build_target == "win32" ]; then
  echo "Building for Windows"
else
  echo "Building for Linux"
fi

if $build_deps; then
  # Build all dependencies
  (verb SDL "$build_target")
  (verb GLEW "$build_target")
fi

# Build binary
if [ $build_target == "win32" ]; then
  build_windows
else
  build_linux
fi
