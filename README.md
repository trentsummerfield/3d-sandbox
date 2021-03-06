# 3d-sandbox

A simple sandbox to view models and play with shaders. Written in modern C++.

![](https://raw.githubusercontent.com/trentsummerfield/3d-sandbox/master/examples/3d-viewer-bunny.gif)

Dependencies
------------
 - [CMAKE](https://cmake.org/)
 - [SDL2](https://libsdl.org)
 - [GLEW](http://glew.sourceforge.net/)

On windows cmake will install and compile the dependencies. On OSX and Linux you should use your favourite package manager to install these dependencies first.

Installation
------------

The code has been tested on Windows and Linux. 

Assuming cmake is installed. The code can be compiled as follows:
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Usage
-----


```
$ ./build/bin/3d-sandbox OBJ_FILE SHADER_NAME
```
Note: The binary needs to be executed in the working directory containing the directory called `shaders`.

For example the gif above is the output of: 
```
$ ./build/bin/3d-sandbox assets/bunny.obj oren-nayar
```

Shaders
-------

| shader name | description |
--------------|--------------
| gooch       | A simple shader derived from one presented in Real-Time Rendering, Fourth Edition, Akenine-Moller, Haines, Hoffman |
| oren-nayar | A diffuse shader with more physically correct properties |
| disolve | A shader which causes the object to disolve over time |

License
-------

SDL2 is licensed under the [zlib license](https://www.libsdl.org/license.php)  
GLEW is licensed under the [MIT license](https://github.com/nigels-com/glew#copyright-and-licensing)

This project is available under the UNLICENSE.
```
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
```
