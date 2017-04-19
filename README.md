# RAIDA
[![Build Status](https://travis-ci.org/iLCSoft/RAIDA.svg?branch=master)](https://travis-ci.org/iLCSoft/RAIDA)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12491/badge.svg)](https://scan.coverity.com/projects/ilcsoft-raida)

RAIDA [Root](http://root.cern.ch) implementation of [AIDA](http://aida.freehep.org)(Abstract Interfaces for Data Analysis). The motivation for the development of RAIDA was to offer the possibility to create and fill n-tuple or histograms using standard ROOT objects with AIDA. All ROOT objects created with AIDA are stored in a ROOT file. Since our main application of RAIDA is to create ROOT output to be analysed using the ROOT program, the current version can not read in the root files created. Furthermore only objects, which exist within ROOT can be created. 

This version of RAIDA supports the following AIDA objects:

ITREE (create output-file, create and change directories) IHistogram1D, IHistogram2D, IHistogram3D (1D, 2D, and 3D binned histograms) ICloud1D, ICloud2D, ICloud3D (1D, 2D, and 3D unbinned histograms) IProfile1D, IProfile2D (1D and 2D profile histogram) IAxis (get information about axis of IHistogram, ICloud, and IProfile) ITuple (creating and filling of n-tuples with different data types: int, short, long, float, double)

RAIDA is distributed under the [GPLv3 License](http://www.gnu.org/licenses/gpl-3.0.en.html)

[![License](https://www.gnu.org/graphics/gplv3-127x51.png)](https://www.gnu.org/licenses/gpl-3.0.en.html)


## Additional Information:

The AIDA histograms hold more information about the data than those from ROOT. RAIDA can write out these additional information by including additional  histograms in the output file. By default the additional histograms are omitted. To tell RAIDA to write out these histograms, the environment variable `AIDA_HISTOGRAMS_IN_ROOT` has to be set to `1`:
```
export AIDA_HISTOGRAMS_IN_ROOT=1
```
### Debug Information:
To supporting the usage of a debugger like GDB (DDD), the object file has to have some additional information. By default these information is not  written to the object file. This can be changed by setting an environment variable:
```
export RAIDADEBUG=1
```
### Verbose Mode:
To get additional information written to the screen during the operation of RAIDA, set the following environment variable:
```
export RAIDA_DEBUG_VERBOSE=1
```

### Installation (with cmake):
In order to build RAIDA you need ILCUTIL, ROOT and CMake if you have access to `/cvmfs/ilc.desy.de/` then you will find all this packages under:
```
/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/
```
Checkout the package and issue the following commands:
```
mkdir build
cd build
cmake -C $ILCSOFT/ILCSoft.cmake ..
make install
```

### Installation (with cmake) standalone (no ilcinstall, no afs):
In order to build RAIDA you need ILCUTIL, ROOT and CMake

1. install ROOT >= 6.0
2. install ILCUTIL
3. install RAIDA
```
git clone git@github.com:iLCSoft/RAIDA.git

mkdir RAIDA/build
cd RAIDA/build
cmake -DILCUTIL_DIR=/path/to/ILCUTIL -DROOT_DIR=/path/to/ROOT ..
make install
```

### Linking against RAIDA:
In order to build your program with RAIDA you need to use the proper include files and libraries, e.g. in your Makefile add:
```
CPPFLAGS += `aida-config --include`
LIBS += `aida-config --lib`

LIBS += `root-config --libs`
```

and before calling 'make' set the proper environment, e.g.:
```
export ROOTSYS=/path/to/ROOT

export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
export PATH=$ROOTSYS/bin:$PATH

export RAIDA_HOME=/path/to/RAIDA

. $RAIDA_HOME/bin/aida-setup.sh
```

## License and Copyright
Copyright (C), RAIDA Authors

RAIDA is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License long with this program.  If not, see <http://www.gnu.org/licenses/>.
