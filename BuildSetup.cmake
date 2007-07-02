#############################################################################
# cmake build setup for RAIDA
#
# For building lcio with cmake type:
# (1) $ mkdir build
# (2) $ cd build
# (3) $ cmake -C ../BuildSetup.cmake ..
# (4) $ make install
#
# @author Jan Engels, DESY
#############################################################################


#############################################################################
# Setup path variables
#############################################################################

# ILC_HOME
SET( ILC_HOME "/afs/desy.de/group/it/ilcsoft/v01-01_beta"
    CACHE PATH "Path to ILC Software" FORCE )

# Path to ROOT
SET( ROOT_HOME "${ILC_HOME}/root/5.08.00"
    CACHE PATH "Path to ROOT" FORCE )

# CMake Modules Path
SET( CMAKE_MODULE_PATH "${ILC_HOME}/CMakeModules/v01-00"
    CACHE PATH "Path to CMake Modules" FORCE )

###############################################
# Project options
###############################################

#SET( BUILD_SHARED_LIBS OFF CACHE BOOL "Set to OFF to build static libraries" FORCE )
#SET( BUILD_RAIDA_EXAMPLE ON CACHE BOOL "Set to ON to build RAIDA example" FORCE )
#SET( RAIDA_DEBUG_VERBOSE_FACTORY ON CACHE BOOL "Set to ON to additional verbosity" FORCE )

# set cmake build type, default value is: RelWithDebInfo
# possible options are: None Debug Release RelWithDebInfo MinSizeRel
#SET( CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE )

###############################################
# Advanced options
###############################################

# installation path for RAIDA
#SET( CMAKE_INSTALL_PREFIX "/foo/bar" CACHE STRING "Where to install RAIDA" FORCE )
