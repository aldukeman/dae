# Install script for directory: /tools/eo/eo/src/utils

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/tools/eo/eo/build/lib/libeoutils.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eo/utils" TYPE FILE FILES
    "/tools/eo/eo/src/utils/eoUpdater.h"
    "/tools/eo/eo/src/utils/eoFDCStat.h"
    "/tools/eo/eo/src/utils/eoParserLogger.h"
    "/tools/eo/eo/src/utils/eoPopStat.h"
    "/tools/eo/eo/src/utils/eoUniformInit.h"
    "/tools/eo/eo/src/utils/eoRealVectorBounds.h"
    "/tools/eo/eo/src/utils/rnd_generators.h"
    "/tools/eo/eo/src/utils/pipecom.h"
    "/tools/eo/eo/src/utils/eoStat.h"
    "/tools/eo/eo/src/utils/eoRNG.h"
    "/tools/eo/eo/src/utils/eoScalarFitnessStat.h"
    "/tools/eo/eo/src/utils/eoGnuplot1DSnapshot.h"
    "/tools/eo/eo/src/utils/eoRealBounds.h"
    "/tools/eo/eo/src/utils/eoStdoutMonitor.h"
    "/tools/eo/eo/src/utils/eoHowMany.h"
    "/tools/eo/eo/src/utils/eoFuncPtrStat.h"
    "/tools/eo/eo/src/utils/eoIntBounds.h"
    "/tools/eo/eo/src/utils/eoFeasibleRatioStat.h"
    "/tools/eo/eo/src/utils/eoCheckPoint.h"
    "/tools/eo/eo/src/utils/eoMOFitnessStat.h"
    "/tools/eo/eo/src/utils/eoGnuplot1DMonitor.h"
    "/tools/eo/eo/src/utils/compatibility.h"
    "/tools/eo/eo/src/utils/eoUpdatable.h"
    "/tools/eo/eo/src/utils/selectors.h"
    "/tools/eo/eo/src/utils/eoLogger.h"
    "/tools/eo/eo/src/utils/eoFileSnapshot.h"
    "/tools/eo/eo/src/utils/eoData.h"
    "/tools/eo/eo/src/utils/eoDistance.h"
    "/tools/eo/eo/src/utils/eoMonitor.h"
    "/tools/eo/eo/src/utils/eoParam.h"
    "/tools/eo/eo/src/utils/eoRndGenerators.h"
    "/tools/eo/eo/src/utils/eoGnuplot.h"
    "/tools/eo/eo/src/utils/eoParser.h"
    "/tools/eo/eo/src/utils/eoTimedMonitor.h"
    "/tools/eo/eo/src/utils/eoFileMonitor.h"
    "/tools/eo/eo/src/utils/eoState.h"
    "/tools/eo/eo/src/utils/eoAssembledFitnessStat.h"
    "/tools/eo/eo/src/utils/eoTimeCounter.h"
    "/tools/eo/eo/src/utils/eoOStreamMonitor.h"
    "/tools/eo/eo/src/utils/checkpointing"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

