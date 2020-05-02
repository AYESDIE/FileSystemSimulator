# fsx

## File System Simulator in C++

![](https://cdn.discordapp.com/attachments/617951895386062868/706221001297625158/fsx.png)

**fsx** is a File System Simulator written in C++. It includes a library with functions used to perform basic file system operations and also includes an executable ready to be tested and used out of the box.

### Dependencies

fsx has the following dependency:

```
CMake       >= 3.1
```

### Building fsx from source:

fsx uses CMake as a build system. One can consult any CMake tutorials for further documentation, but this tutorial should be enough to get fsx built and installed.

First, unpack the fsx source and change into the unpacked directory. Then, make a build directory. The directory can have any name, not just `build`, but `build` is sufficient.

```
$ mkdir build
$ cd build
```

The next step is to run CMake to configure the project.  Running CMake is the
equivalent to running `./configure` with autotools.

```
$ cmake ../
```

Once CMake is configured, building the library is as simple as typing `make`.

```
$ make
```

To run the project, just run the binary produced.

```
$ ./output/bin/FileSystemSimulator 
```