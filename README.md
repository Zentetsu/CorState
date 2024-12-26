# CorState
Lightweight and versatile State Machine library

### Features
* State Machine implementation
* Load structure from JSON file
* GUI editor
* Include ``List`` and ``Dict``

### Ongoing
* Documentation

### Future improvement
* Petry Net implementation

### Building process

```console
> git clone -b C git@github.com:Zentetsu/CorState.git
> cd CorState
> mkdir build
> cd build
> cmake .. # CONDA ENV add: -DCMAKE_PREFIX_PATH="$CONDA_PREFIX;$CONDA_PREFIX/lib/cmake" -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
> make && make install
```

### Use case
#### Code generation from JSON file
```console
> generateStateMachine -f ./path/to/file.json
```

#### Build and call
Can be with CMake like a normal lib and can be include as follow:
```c
#include <CorState.h>
```

### More
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)