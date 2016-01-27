# Install script for directory: /tools/eo/eo/src

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/tools/eo/eo/build/lib/libeo.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "libraries")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eo" TYPE FILE FILES
    "/tools/eo/eo/src/eoOp.h"
    "/tools/eo/eo/src/eoLinearTopology.h"
    "/tools/eo/eo/src/eoGaussRealWeightUp.h"
    "/tools/eo/eo/src/eoEvalFuncPtr.h"
    "/tools/eo/eo/src/eoReplacement.h"
    "/tools/eo/eo/src/eoStarTopology.h"
    "/tools/eo/eo/src/eoProportionalCombinedOp.h"
    "/tools/eo/eo/src/eoObject.h"
    "/tools/eo/eo/src/eoTimeContinue.h"
    "/tools/eo/eo/src/EO.h"
    "/tools/eo/eo/src/eoInit.h"
    "/tools/eo/eo/src/eoMGGReplacement.h"
    "/tools/eo/eo/src/eoSharingSelect.h"
    "/tools/eo/eo/src/eoInitializer.h"
    "/tools/eo/eo/src/eoEvalFuncCounterBounder.h"
    "/tools/eo/eo/src/eoOneToOneBreeder.h"
    "/tools/eo/eo/src/eoMerge.h"
    "/tools/eo/eo/src/eoTopology.h"
    "/tools/eo/eo/src/eoVectorParticle.h"
    "/tools/eo/eo/src/eoScalarFitness.h"
    "/tools/eo/eo/src/eoSequentialSelect.h"
    "/tools/eo/eo/src/eoParticleFullInitializer.h"
    "/tools/eo/eo/src/eoConstrictedVariableWeightVelocity.h"
    "/tools/eo/eo/src/eoMergeReduce.h"
    "/tools/eo/eo/src/eoEvalFuncCounter.h"
    "/tools/eo/eo/src/eoCellularEasyEA.h"
    "/tools/eo/eo/src/eoStandardVelocity.h"
    "/tools/eo/eo/src/eoOrderXover.h"
    "/tools/eo/eo/src/eoRanking.h"
    "/tools/eo/eo/src/eoPop.h"
    "/tools/eo/eo/src/PO.h"
    "/tools/eo/eo/src/eoSimpleEDA.h"
    "/tools/eo/eo/src/eoEasyEA.h"
    "/tools/eo/eo/src/eoCounter.h"
    "/tools/eo/eo/src/eoBreed.h"
    "/tools/eo/eo/src/eoDistribUpdater.h"
    "/tools/eo/eo/src/eoFlOrQuadOp.h"
    "/tools/eo/eo/src/eoRankingSelect.h"
    "/tools/eo/eo/src/eoPSO.h"
    "/tools/eo/eo/src/eoSecondsElapsedContinue.h"
    "/tools/eo/eo/src/eoSelectNumber.h"
    "/tools/eo/eo/src/eoPersistent.h"
    "/tools/eo/eo/src/eoSTLFunctor.h"
    "/tools/eo/eo/src/eoOpSelMason.h"
    "/tools/eo/eo/src/eoScalarFitnessAssembled.h"
    "/tools/eo/eo/src/eoFlOrBinOp.h"
    "/tools/eo/eo/src/eoVariableLengthMutation.h"
    "/tools/eo/eo/src/eoFitnessScalingSelect.h"
    "/tools/eo/eo/src/eoSelect.h"
    "/tools/eo/eo/src/eoRandomSelect.h"
    "/tools/eo/eo/src/eoParticleBestInit.h"
    "/tools/eo/eo/src/eoContinue.h"
    "/tools/eo/eo/src/eoNeighborhood.h"
    "/tools/eo/eo/src/eoTwoOptMutation.h"
    "/tools/eo/eo/src/eoEvalFunc.h"
    "/tools/eo/eo/src/eoExtendedVelocity.h"
    "/tools/eo/eo/src/eoG3Replacement.h"
    "/tools/eo/eo/src/eoSharing.h"
    "/tools/eo/eo/src/ga.h"
    "/tools/eo/eo/src/eoBinaryFlight.h"
    "/tools/eo/eo/src/eoFixedInertiaWeightedVelocity.h"
    "/tools/eo/eo/src/eoOpContainer.h"
    "/tools/eo/eo/src/eoTruncSelect.h"
    "/tools/eo/eo/src/eoPerf2Worth.h"
    "/tools/eo/eo/src/eoFactory.h"
    "/tools/eo/eo/src/eoSocialNeighborhood.h"
    "/tools/eo/eo/src/eoVariableLengthCrossover.h"
    "/tools/eo/eo/src/eoInt.h"
    "/tools/eo/eo/src/eoPeriodicContinue.h"
    "/tools/eo/eo/src/eoSGA.h"
    "/tools/eo/eo/src/eoSurviveAndDie.h"
    "/tools/eo/eo/src/eoRandomRealWeightUp.h"
    "/tools/eo/eo/src/eoEvalContinue.h"
    "/tools/eo/eo/src/eoInvalidateOps.h"
    "/tools/eo/eo/src/eoSelectPerc.h"
    "/tools/eo/eo/src/eoPopulator.h"
    "/tools/eo/eo/src/eoSGAGenOp.h"
    "/tools/eo/eo/src/eoPropGAGenOp.h"
    "/tools/eo/eo/src/eoReduceMerge.h"
    "/tools/eo/eo/src/eoCombinedInit.h"
    "/tools/eo/eo/src/eoCtrlCContinue.h"
    "/tools/eo/eo/src/eoSelectMany.h"
    "/tools/eo/eo/src/eoSteadyFitContinue.h"
    "/tools/eo/eo/src/eoVelocityInit.h"
    "/tools/eo/eo/src/eoFunctorStore.h"
    "/tools/eo/eo/src/eoBitParticle.h"
    "/tools/eo/eo/src/eoSigBinaryFlight.h"
    "/tools/eo/eo/src/eoTruncatedSelectMany.h"
    "/tools/eo/eo/src/eoPrintable.h"
    "/tools/eo/eo/src/eoFitContinue.h"
    "/tools/eo/eo/src/eoTransform.h"
    "/tools/eo/eo/src/eoSyncEasyPSO.h"
    "/tools/eo/eo/src/eoTruncatedSelectOne.h"
    "/tools/eo/eo/src/eoReduceSplit.h"
    "/tools/eo/eo/src/eoCombinedContinue.h"
    "/tools/eo/eo/src/eoSelectOne.h"
    "/tools/eo/eo/src/eoEDA.h"
    "/tools/eo/eo/src/eoVelocity.h"
    "/tools/eo/eo/src/eoSwapMutation.h"
    "/tools/eo/eo/src/eoGenOp.h"
    "/tools/eo/eo/src/eoGenContinue.h"
    "/tools/eo/eo/src/eoSelectFactory.h"
    "/tools/eo/eo/src/eoStochasticUniversalSelect.h"
    "/tools/eo/eo/src/eoStochTournamentSelect.h"
    "/tools/eo/eo/src/eoVector.h"
    "/tools/eo/eo/src/eoDetTournamentSelect.h"
    "/tools/eo/eo/src/eoVariableInertiaWeightedVelocity.h"
    "/tools/eo/eo/src/eoSIGContinue.h"
    "/tools/eo/eo/src/eoExceptions.h"
    "/tools/eo/eo/src/eoFunctor.h"
    "/tools/eo/eo/src/eoGeneralBreeder.h"
    "/tools/eo/eo/src/eoDualFitness.h"
    "/tools/eo/eo/src/eoSelectFromWorth.h"
    "/tools/eo/eo/src/eoPopEvalFunc.h"
    "/tools/eo/eo/src/eoShiftMutation.h"
    "/tools/eo/eo/src/apply.h"
    "/tools/eo/eo/src/eoFlight.h"
    "/tools/eo/eo/src/eoRingTopology.h"
    "/tools/eo/eo/src/eoIntegerVelocity.h"
    "/tools/eo/eo/src/eoLinearDecreasingWeightUp.h"
    "/tools/eo/eo/src/eoEvalUserTimeThrowException.h"
    "/tools/eo/eo/src/eoStandardFlight.h"
    "/tools/eo/eo/src/eoAlgo.h"
    "/tools/eo/eo/src/eoEasyPSO.h"
    "/tools/eo/eo/src/eoRealParticle.h"
    "/tools/eo/eo/src/eoReduce.h"
    "/tools/eo/eo/src/eoCloneOps.h"
    "/tools/eo/eo/src/eoReduceMergeReduce.h"
    "/tools/eo/eo/src/eoRealBoundModifier.h"
    "/tools/eo/eo/src/eoWeightUpdater.h"
    "/tools/eo/eo/src/eoConstrictedVelocity.h"
    "/tools/eo/eo/src/eoEvalCounterThrowException.h"
    "/tools/eo/eo/src/eoLinearFitScaling.h"
    "/tools/eo/eo/src/eoFlOrMonOp.h"
    "/tools/eo/eo/src/es.h"
    "/tools/eo/eo/src/eoSGATransform.h"
    "/tools/eo/eo/src/eoNDSorting.h"
    "/tools/eo/eo/src/eoDistribution.h"
    "/tools/eo/eo/src/eoEvalTimeThrowException.h"
    "/tools/eo/eo/src/eoDetSelect.h"
    "/tools/eo/eo/src/eoProportionalSelect.h"
    "/tools/eo/eo/src/eo"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/tools/eo/eo/build/src/do/cmake_install.cmake")
  INCLUDE("/tools/eo/eo/build/src/es/cmake_install.cmake")
  INCLUDE("/tools/eo/eo/build/src/ga/cmake_install.cmake")
  INCLUDE("/tools/eo/eo/build/src/gp/cmake_install.cmake")
  INCLUDE("/tools/eo/eo/build/src/other/cmake_install.cmake")
  INCLUDE("/tools/eo/eo/build/src/utils/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

