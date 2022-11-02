# Sorting-Visualization-Algorithm
 
 C++ Program that visualizes Bubble sort algorithm.

Install required tools
You need a GCC (or alternative C99 compiler), make and git (to download raylib repo).

    sudo apt install build-essential git

Optionally, you could use CMake building system.

    sudo apt install cmake

Install required libraries
You need to install some required libraries; ALSA for audio, Mesa for OpenGL accelerated graphics and X11 for windowing system.

    sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

Download the raylib repository from Github, then compile it with:

    git clone https://github.com/raysan5/raylib.git raylib
    cd raylib/src/
    make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED # To make the dynamic shared version.

Install the library to the standard directories, usr/local/lib and /usr/local/include, or remove it:

    sudo make install RAYLIB_LIBTYPE=SHARED # Dynamic shared version.



