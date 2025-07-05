Cross compiling GLFW (host Archlinux, target Windows):

install mingw-w64
wget https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
unzip glfw-3.4.zip
cd glfw-3.4
mkdir build
cd build
cmake -S ../ -B ./ -DCMAKE_TOOLCHAIN_FILE=<learn_opengl_repo>/tools/TC-mingw.cmake
make
make DESTDIR=<learn_opengl_repo>/deps install

