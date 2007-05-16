######################################
# cmake file for building RAIDA
# @author Jan Engels, DESY
######################################

####################################################################################################
### INCLUDES
####################################################################################################

# include directories
INCLUDE_DIRECTORIES( "${${PROJECT_NAME}_SOURCE_DIR}/include" )

# install include files
INSTALL( DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/include"
		DESTINATION .
		PATTERN "*~" EXCLUDE
		PATTERN "*CVS*" EXCLUDE )


####################################################################################################
### SOURCES
####################################################################################################

# require proper c++
ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

# need long long for int64 for now
#FIXME: should establish wether we are on a 32bit or 64 bit machine ...
ADD_DEFINITIONS( "-Wno-long-long" )

#IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
IF( RAIDA_DEBUG_VERBOSE_FACTORY )
	MESSAGE( STATUS "RAIDA_DEBUG_VERBOSE_FACTORY flag activated..." )
	ADD_DEFINITIONS( "-DUSE_RAIDA_DEBUG_VERBOSE_FACTORY" )
ENDIF()

# binary sources: list of all sources from which you want to create a binary
#SET( bin_srcs example.cc )

# get list of all source files in this directory
AUX_SOURCE_DIRECTORY( . lib_srcs )

####################################################################################################
### DEPENDENCIES
####################################################################################################

# load macro
IF( DEFINED ${PROJECT_NAME}_DEPENDS OR DEFINED BUILD_WITH OR DEFINED LINK_WITH )
    # load macro
    IF( NOT EXISTS "${CMAKE_MODULE_PATH}/MacroCheckDeps.cmake" )
        MESSAGE( FATAL_ERROR "\nSorry, could not find MacroCheckDeps.cmake...\n"
            "Please set CMAKE_MODULE_PATH correctly with: "
            "cmake -DCMAKE_MODULE_PATH=<path_to_cmake_modules>" )
    ENDIF()
    INCLUDE( "${CMAKE_MODULE_PATH}/MacroCheckDeps.cmake" )
    CHECK_DEPS()
ENDIF()


####################################################################################################
### LIBRARY
####################################################################################################

# create library
ADD_LIBRARY( lib_${PROJECT_NAME} ${lib_srcs} )

# create symbolic lib target for calling target lib_XXX
ADD_CUSTOM_TARGET( lib DEPENDS lib_${PROJECT_NAME} )

# change lib_target properties
SET_TARGET_PROPERTIES( lib_${PROJECT_NAME} PROPERTIES
	# create *nix style library versions + symbolic links
	VERSION ${${PROJECT_NAME}_VERSION}
	SOVERSION ${${PROJECT_NAME}_SOVERSION}
	# allow creating static and shared libs without conflicts
	CLEAN_DIRECT_OUTPUT 1
	# avoid conflicts between library and binary target names
	OUTPUT_NAME ${PROJECT_NAME}	)

# install library
INSTALL( TARGETS lib_${PROJECT_NAME} DESTINATION lib PERMISSIONS
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_EXECUTE
		WORLD_READ WORLD_EXECUTE )


####################################################################################################
### BINS
####################################################################################################

IF( BUILD_RAIDA_EXAMPLE )

	ADD_EXECUTABLE( bin ../example.cc )
	SET_TARGET_PROPERTIES( bin PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
	TARGET_LINK_LIBRARIES( bin lib_${PROJECT_NAME} )
	# install binary commando
	INSTALL( TARGETS bin DESTINATION bin )

ENDIF()

