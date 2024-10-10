# opengltf
This is a small 3D glTF viewer.

## Compiling opengltf
This project can be built using CMake. On Unix systems, just recursively clone
the directory and `cd` into it. Then, make a build directory, `cd` into it,
then call CMake. Build the project with Make, and a bin folder will be created
with the executable.

```
git clone --recurse-submodules -j8 git@github.com:gequalspisquared/opengltf.git
cd opengltf
mkdir build
cd build
cmake ..
make
./../bin/opengltf
```

[//]: # (TODO: add directions for building on windows)
