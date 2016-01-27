# Install script for directory: /tools/eo/eo/src/es

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/tools/eo/eo/build/lib/libes.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/tools/eo/eo/build/lib/libcma.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eo/es" TYPE FILE FILES
    "/tools/eo/eo/src/es/CMAState.h"
    "/tools/eo/eo/src/es/eoEsStdev.h"
    "/tools/eo/eo/src/es/eoEsMutationInit.h"
    "/tools/eo/eo/src/es/eoEsMutate.h"
    "/tools/eo/eo/src/es/make_op.h"
    "/tools/eo/eo/src/es/eoCMAInit.h"
    "/tools/eo/eo/src/es/matrices.h"
    "/tools/eo/eo/src/es/make_real.h"
    "/tools/eo/eo/src/es/eoRealAtomXover.h"
    "/tools/eo/eo/src/es/make_op_es.h"
    "/tools/eo/eo/src/es/eoNormalMutation.h"
    "/tools/eo/eo/src/es/eoReal.h"
    "/tools/eo/eo/src/es/eoEsFull.h"
    "/tools/eo/eo/src/es/eoRealOp.h"
    "/tools/eo/eo/src/es/eoEsSimple.h"
    "/tools/eo/eo/src/es/CMAParams.h"
    "/tools/eo/eo/src/es/make_op_real.h"
    "/tools/eo/eo/src/es/make_es.h"
    "/tools/eo/eo/src/es/eig.h"
    "/tools/eo/eo/src/es/eoEsChromInit.h"
    "/tools/eo/eo/src/es/eoEsGlobalXover.h"
    "/tools/eo/eo/src/es/make_genotype_real.h"
    "/tools/eo/eo/src/es/eoRealInitBounded.h"
    "/tools/eo/eo/src/es/eoCMABreed.h"
    "/tools/eo/eo/src/es/eoEsStandardXover.h"
    "/tools/eo/eo/src/es/eoSBXcross.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

