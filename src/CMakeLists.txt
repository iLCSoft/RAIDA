######################################
# cmake file for building RAIDA
# @author Jan Engels, DESY
######################################

####################################################################################################
### INCLUDES
####################################################################################################

# include directories
INCLUDE_DIRECTORIES( "${RAIDA_SOURCE_DIR}/include" )

# install include files
INSTALL( DIRECTORY "${RAIDA_SOURCE_DIR}/include"
        DESTINATION .
        PATTERN "*~" EXCLUDE
        PATTERN "*CVS*" EXCLUDE
        PATTERN "*/.svn*" EXCLUDE
        )


####################################################################################################
### SOURCES
####################################################################################################

# require proper c++
# FIXME under sl4 -pedantic flag throws C++ ISO error
ADD_DEFINITIONS( "-Wall -ansi" )

# need long long for int64 for now
#FIXME: should establish wether we are on a 32bit or 64 bit machine ...
ADD_DEFINITIONS( "-Wno-long-long" )

#IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
IF( RAIDA_DEBUG_VERBOSE_FACTORY )
    MESSAGE( STATUS "RAIDA_DEBUG_VERBOSE_FACTORY flag activated..." )
    ADD_DEFINITIONS( "-DUSE_RAIDA_DEBUG_VERBOSE_FACTORY" )
ENDIF()

# get list of all source files in this directory
AUX_SOURCE_DIRECTORY( . lib_srcs )


####################################################################################################
### LIBRARY
####################################################################################################

# create library
ADD_LIBRARY( lib_RAIDA ${lib_srcs} )

# create symbolic lib target for calling target lib_XXX
ADD_CUSTOM_TARGET( lib DEPENDS lib_RAIDA )

# change lib_target properties
SET_TARGET_PROPERTIES( lib_RAIDA PROPERTIES
    # create *nix style library versions + symbolic links
    VERSION ${RAIDA_VERSION}
    SOVERSION ${RAIDA_SOVERSION}
    # allow creating static and shared libs without conflicts
    CLEAN_DIRECT_OUTPUT 1
    # avoid conflicts between library and binary target names
    OUTPUT_NAME RAIDA )

# install library
INSTALL( TARGETS lib_RAIDA DESTINATION lib PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE )


####################################################################################################
### BINS
####################################################################################################

IF( BUILD_RAIDA_EXAMPLE )

    ADD_EXECUTABLE( bin ../example.cc )
    SET_TARGET_PROPERTIES( bin PROPERTIES OUTPUT_NAME RAIDA )
    TARGET_LINK_LIBRARIES( bin lib_RAIDA )
    # install binary commando
    INSTALL( TARGETS bin DESTINATION bin )

ENDIF()

