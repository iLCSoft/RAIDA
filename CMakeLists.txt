########################################################
# cmake file for building RAIDA
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################


# project name
PROJECT( RAIDA )

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 5 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )
SET( ${PROJECT_NAME}_VERSION_TWEAK 0 )



### SETTINGS ################################################################

# ilcsoft_default_settings.cmake needs to be in CMAKE_MODULE_PATH
INCLUDE( ilcsoft_default_settings )


### DEPENDENCIES ############################################################

# at least version 5.0 of ROOT is required
SET( ROOT_VERSION_CHECK_MINIMUM_REQUIRED TRUE )
FIND_PACKAGE( ROOT 5.0 REQUIRED )



### DOCUMENTATION ###########################################################

#OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" ON )
#
#IF( INSTALL_DOC )
#
#    FIND_PACKAGE( Doxygen )
#    FIND_PACKAGE( LATEX )
#
#    IF( DOXYGEN_FOUND AND LATEX_COMPILER AND MAKEINDEX_COMPILER )
#        ADD_SUBDIRECTORY( ./doc )
#    ELSE()
#        IF( NOT DOXYGEN_FOUND )
#            MESSAGE( STATUS "Doxygen not found in your system!!" )
#        ENDIF()
#        IF( NOT LATEX_COMPILER OR NOT MAKEINDEX_COMPILER )
#            MESSAGE( STATUS "Latex not found in your system!!" )
#        ENDIF()
#        IF( INSTALL_DOC )
#            MESSAGE( STATUS "INSTALL_DOC set to OFF" )
#            SET( INSTALL_DOC OFF )
#        ENDIF()
#    ENDIF()
#ENDIF()
#MESSAGE( STATUS "INSTALL_DOC = ${INSTALL_DOC}" )



#############################################################################


# -------- generate RAIDAConfig.h ----------------------------------------------
#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/cmake/RAIDAConfig.h.cmake.in"
#    "${PROJECT_BINARY_DIR}/RAIDA/RAIDAConfig.h" @ONLY )
#
#INSTALL( FILES "${PROJECT_BINARY_DIR}/RAIDA/RAIDAConfig.h" DESTINATION "include/RAIDA/" )
# -----------------------------------------------------------------------------



INCLUDE_DIRECTORIES( ./include )
INCLUDE_DIRECTORIES( ${ROOT_INCLUDE_DIRS} )
INSTALL_DIRECTORY( ./include DESTINATION . FILES_MATCHING PATTERN "*.h" )



ADD_DEFINITIONS( "-Wall -ansi" ) # FIXME -pedantic
ADD_DEFINITIONS( "-Wno-long-long" )



# verbose debug mode
OPTION( RAIDA_DEBUG_VERBOSE_FACTORY "Set to ON to additional verbosity" OFF )
IF( RAIDA_DEBUG_VERBOSE_FACTORY )
    ADD_DEFINITIONS( "-DUSE_RAIDA_DEBUG_VERBOSE_FACTORY" )
ENDIF()



# RAIDA library
AUX_SOURCE_DIRECTORY( ./src library_sources )
ADD_SHARED_LIBRARY( RAIDA ${library_sources} )
INSTALL_SHARED_LIBRARY( RAIDA DESTINATION lib )
TARGET_LINK_LIBRARIES( RAIDA ${ROOT_LIBRARIES} )


# RAIDA example
OPTION( BUILD_RAIDA_EXAMPLE "Set to ON to build RAIDA example" OFF )
IF( BUILD_RAIDA_EXAMPLE )
    ADD_EXECUTABLE( RAIDA_EXAMPLE ./example/example.cc )
    TARGET_LINK_LIBRARIES( RAIDA_EXAMPLE RAIDA )
    INSTALL( TARGETS RAIDA_EXAMPLE DESTINATION bin )
ENDIF()



# install aida configuration scripts
INSTALL( FILES "./bin/aida-config" "./bin/aida-setup.sh"
    DESTINATION bin PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)



# display some variables and write them to cache
DISPLAY_STD_VARIABLES()

MESSAGE( STATUS "BUILD_RAIDA_EXAMPLE = ${BUILD_RAIDA_EXAMPLE}" )
MESSAGE( STATUS "RAIDA_DEBUG_VERBOSE_FACTORY = ${RAIDA_DEBUG_VERBOSE_FACTORY}" )
MESSAGE( STATUS )


# export library dependencies (keep this as the last line in the file)
EXPORT_LIBRARY_DEPENDENCIES( "${PROJECT_NAME}LibDeps.cmake" )
INSTALL( FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}LibDeps.cmake" DESTINATION lib/cmake )

