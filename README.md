# simple-http-server
A simple lightweight HTTP server in C

## Building

#### Requirements

* CMake 3.10 or higher
* GNU Make or another CMake compatible build tool 
* C11 or higher compiler
* Doxygen

#### Steps

##### Building the Project
First, clone the repository.

```
git clone https://github.com/bama4/simple-http-server.git
cd simple-http-server/
```

Create a _build/_ directory to store the contents of the build process.

```
mkdir build/
cd build/
```

Then run CMake to generate the Makefile

```
cmake ../
```

Finally, run GNU make to compile the program.

```
make
```

The executable should be in the folder ``bin/`` and should be called simple_http_server

##### Building the Tests

Create a _build/_ directory to store the contents of the build process.

```
mkdir build/
cd build/
```

Then run CMake to generate the Makefile for the tests

```
cmake -DCMAKE_BUILD_TYPE=Debug -DTEST=ON ../
```

Run the tests associated with the package

```
ctest --verbose
```

