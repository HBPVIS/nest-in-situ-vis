# nest in situ vis

*nest in situ vis* is Copyright (c) 2017-2018 RWTH Aachen University, Germany,
Virtual Reality & Immersive Visualization Group.


## Overview

*nest in situ vis* (`niv`) is (the yet prototypical implementation of) a library facilitating in situ visualization for the [nest simulator](http://www.nest-simulator.org).

With `niv` data can be collected in nest's recording backends and transported to a visualization process. Currently, only on-node transport to a separate visualization process is provided using shared memory.


## Building


### Requirements

* a customized nest simulator with nestio and a conduit recording backend
* [conduit 0.2.1](https://github.com/LLNL/conduit/tree/v0.2.1)
* Boost python and boost interprocess v1.64.0
* Python 2.7.13
* CMake 3.8.2 (or above)
* gcc 5.3 (or above)


### Compiling the Library

* In a teminal, `cd to `niv`'s root directory

```
mkdir build
cd build
cmake .. \
  -DCONDUIT_DIR=<conduit install dir> \
  -DBOOST_ROOT=<boost install dir> \
  -DPYTHON_INCLUDE_DIR=<python include directory> \
  -DPYTHON_LIBRARY=<absolute path to python library>
make
```

### Compiling the Custom Nest Simulator

These are hints for compiling nest (not included in this repository).

* In a terminal, `cd` to nest's root directory

```
mkdir build
cd build
cmake ../.. \
  -Dwith-conduit=<conduit install dir> \
  -Dniv_DIR=<niv's build directory> \
  -DPYTHON_INCLUDE_DIR=<python include directory> \
  -DPYTHON_LIBRARY=<absolute path to python library> \
  -DCMAKE_INSTALL_PREFIX:PATH=<path to nest's install directory>
make
make install
```


### Generating the Demo Runners

* In a teminal, `cd to `niv`'s root directory

```
cd build
cmake . -DNEST_DIR=<path to nest's install directory>
chmod +x chmod +x demo/nest_python_vis/*.sh
```


## Running the Demo

You'll need two terminals.

* in both, `cd` to `<niv's build directory>/demo/nest_python_vis`

* in the first

```
./run_vis.sh
```

* in the second

```
./run_sim.sh
```

* in the visualization app press "Start"
* in the simulation app press "nest.Simulate(20)"


## Releasing Shared Memory if Something Breaks

If one of the two apps crashes, shared memory might still exist. Consequently, the visualization will throw an exception. In order to manually release the shared memory:

* in a terminal `cd` to `niv`s build directory

```
niv/helper_apps/niv-shared-memory destroy
```

## License

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


## Acknowledgements

`niv` is developed in the Human Brain Project. This project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement No 720270 (HBP SGA1).
