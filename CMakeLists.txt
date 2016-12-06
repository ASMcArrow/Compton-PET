CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

PROJECT(Compton-PET)

FIND_PACKAGE(Geant4 REQUIRED ui_all vis_all)
IF(NOT Geant4_FOUND)
MESSAGE(FATAL_ERROR "Geant4 not found!")
ENDIF(NOT Geant4_FOUND)

INCLUDE(${Geant4_USE_FILE})

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/GateFunc/include)

FILE(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
FILE(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

FILE(GLOB GATEsources ${PROJECT_SOURCE_DIR}/GateFunc/src/*.cc)
FILE(GLOB GATEheaders ${PROJECT_SOURCE_DIR}/GateFunc/include/*.hh)

ADD_EXECUTABLE(Compton-PET PET.cc ${sources} ${headers} ${GATEsources} ${GATEheaders})
TARGET_LINK_LIBRARIES(Compton-PET ${Geant4_LIBRARIES})

set(PET_SCRIPTS
    init_vis.mac)

foreach(_script ${PET_SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${PROJECT_BINARY_DIR}/${_script}
        COPYONLY)
endforeach()




