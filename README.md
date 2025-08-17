-- Native

Glad
  https://glad.dav1d.de/
  Choose: 
    language: C++
    GL Api: 3.3
    profile: Core
    Generate a loader: option ticked

  Unzip GLAD package into deps/usr/local/ structure:

  Prepare GLAD static lib:
    cd /home/jurmc/learn_opengl/deps/usr/local/src
    g++ -I ../include/ -c glad.c -o glad.o
    ar rcs glad.a glad.o 
    rm glad.o 
    mkdir ../lib
    mv glad.a ../lib

GLFW, GLM
  Use library from Arch repository

-- Cross compiling (host Archlinux, target Windows):

GLFW
install mingw-w64 from Arch repository

GLFW
  wget https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
  unzip glfw-3.4.zip
  cd glfw-3.4
  mkdir build
  cd build
  cmake -S ../ -B ./ -DCMAKE_TOOLCHAIN_FILE=<learn_opengl_repo>/tools/TC-mingw.cmake
  make
  make DESTDIR=<learn_opengl_repo>/deps install

