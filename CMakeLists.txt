########################################################
# cmake file for building RAIDA
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################


# project name
PROJECT( RAIDA )

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 11 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

cmake_policy(SET CMP0008 NEW)

### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )


# at least version 5.0 of ROOT is required
FIND_PACKAGE( ROOT 5.0 REQUIRED )



### DOCUMENTATION ###########################################################

OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" OFF )

IF( INSTALL_DOC )

    FIND_PACKAGE( Doxygen )

    IF( DOXYGEN_EXECUTABLE )
        ADD_SUBDIRECTORY( ./doc )
    ELSE()
        MESSAGE( SEND_ERROR "Could not find doxygen required to build documentation" )
        MESSAGE( "Please install doxygen or set INSTALL_DOC to OFF" )
        MESSAGE( "" )
    ENDIF()

ENDIF()


#############################################################################


INCLUDE_DIRECTORIES( BEFORE ./include )
INSTALL_DIRECTORY( ./include DESTINATION . FILES_MATCHING PATTERN "*.h" )



#FIXME: silence the eccessive warnings for now
#       should be addressed later - if needed
ADD_DEFINITIONS( "-Wno-effc++ -Wno-unused-parameter -Wno-vla" )


# verbose debug mode
OPTION( RAIDA_DEBUG_VERBOSE_FACTORY "Set to ON to additional verbosity" OFF )
MESSAGE( STATUS "RAIDA_DEBUG_VERBOSE_FACTORY: ${RAIDA_DEBUG_VERBOSE_FACTORY}" )
IF( RAIDA_DEBUG_VERBOSE_FACTORY )
    ADD_DEFINITIONS( "-DUSE_RAIDA_DEBUG_VERBOSE_FACTORY" )
ENDIF()



# RAIDA library
AUX_SOURCE_DIRECTORY( ./src library_sources )
ADD_SHARED_LIBRARY( RAIDA ${library_sources} )
INSTALL_SHARED_LIBRARY( RAIDA DESTINATION lib )
TARGET_LINK_LIBRARIES( RAIDA ROOT::Tree ROOT::Graf)


# RAIDA example
IF( BUILD_TESTING )
    ADD_EXECUTABLE( RAIDA_EXAMPLE ./example/example.cc )
    TARGET_LINK_LIBRARIES( RAIDA_EXAMPLE RAIDA )
    #INSTALL( TARGETS RAIDA_EXAMPLE DESTINATION bin )
ENDIF()


# install aida configuration scripts
INSTALL( PROGRAMS "./bin/aida-config" "./bin/aida-setup.sh" DESTINATION bin )


# display some variables and write them to cache
DISPLAY_STD_VARIABLES()

# generate and install following configuration files
GENERATE_PACKAGE_CONFIGURATION_FILES( RAIDAConfig.cmake RAIDAConfigVersion.cmake AIDAConfig.cmake AIDAConfigVersion.cmake RAIDALibDeps.cmake )

