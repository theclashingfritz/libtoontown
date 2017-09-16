cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
project(libtoontown)

find_package(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
    message(FATAL_ERROR "Python libs not found.")
endif()

find_package(PythonInterp)
if(NOT PYTHONINTERP_FOUND)
    message(FATAL_ERROR "Python interpreter not found.")
endif()

if(PYTHON_VERSION_MAJOR EQUAL 2)
    set(PYTHON2_EXECUTABLE "${PYTHON_EXECUTABLE}")
else()
    set(PYTHON2_EXECUTABLE python2)
endif()

### Panda3D dir ###
SET(PANDA_DIR "C:\\Panda3D-1.10.0" CACHE STRING "Panda3D directory.")

### OpenSSL dir ###
SET(OPEN_SSL_DIR "C:\\openssl" CACHE STRING "OpenSSL directory.")

# Toggle when Panda3D is Opt 3 or above.
option(PANDA_OPTIMIZED "Set this to true if NDEBUG was not defined when Panda was compiled! (NDEBUG will not be defined on high optimization levels.)")

### libotp dir ###
SET(LIBOTP_DIR "C:\\libotp" CACHE STRING "libotp directory.")
execute_process(COMMAND ${PYTHON2_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/run_interrogate.py" "${PANDA_DIR}" "${LIBOTP_DIR}/src")

### Define core components ###
set(BASE_FILES
    src/base/DNALoader.h
    src/base/DNALoader.cxx
    src/base/DNAStorage.h
    src/base/DNAStorage.cxx
    src/base/DNAUtil.h
    src/base/DNAUtil.cxx
    src/base/DNAData.h
    src/base/DNAData.cxx
    src/base/dnabase.h
    src/base/util.h
    src/base/config_libtoontown.h
    src/base/config_libtoontown.cxx
)

set(SUIT_FILES
    src/suit/DNASuitPath.h
    src/suit/DNASuitPath.cxx
    src/suit/DNASuitEdge.h
    src/suit/DNASuitEdge.cxx
    src/suit/DNASuitPoint.h
    src/suit/DNASuitPoint.cxx
    src/suit/SuitLeg.h
    src/suit/SuitLeg.cxx
    src/suit/SuitLegList.h
    src/suit/SuitLegList.cxx
)

set(COMPONENTS_FILES
    src/components/DNAAnimBuilding.cxx
    src/components/DNAAnimBuilding.h
    src/components/DNAAnimProp.cxx
    src/components/DNAAnimProp.h
    src/components/DNABattleCell.cxx
    src/components/DNABattleCell.h
    src/components/DNACornice.cxx
    src/components/DNACornice.h
    src/components/DNADoor.cxx
    src/components/DNADoor.h
    src/components/DNAFlatBuilding.cxx
    src/components/DNAFlatBuilding.h
    src/components/DNAFlatDoor.cxx
    src/components/DNAFlatDoor.h
    src/components/DNAGroup.cxx
    src/components/DNAGroup.h
    src/components/DNAInteractiveProp.cxx
    src/components/DNAInteractiveProp.h
    src/components/DNALandmarkBuilding.cxx
    src/components/DNALandmarkBuilding.h
    src/components/DNANode.cxx
    src/components/DNANode.h
    src/components/DNAProp.cxx
    src/components/DNAProp.h
    src/components/DNASign.cxx
    src/components/DNASign.h
    src/components/DNASignBaseline.cxx
    src/components/DNASignBaseline.h
    src/components/DNASignGraphic.cxx
    src/components/DNASignGraphic.h
    src/components/DNAStreet.cxx
    src/components/DNAStreet.h
    src/components/DNAVisGroup.cxx
    src/components/DNAVisGroup.h
    src/components/DNAWall.cxx
    src/components/DNAWall.h
    src/components/DNAWindows.cxx
    src/components/DNAWindows.h
)

set(PET_FILES
    src/pet/CPetChase.h
    src/pet/CPetChase.cxx
    src/pet/CPetFlee.h
    src/pet/CPetFlee.cxx
    src/pet/CPetBrain.h
    src/pet/CPetBrain.cxx
    src/pet/CPetLeash.h
    src/pet/CPetLeash.cxx
)

set(IGATE_FILES
    src/base_igate.cxx
    src/suit_igate.cxx
    src/components_igate.cxx
    src/pet_igate.cxx
    src/libtoontown_module.cxx
)


include_directories(${LIBOTP_DIR}/src)
include_directories(${LIBOTP_DIR}/src/components)
include_directories(${LIBOTP_DIR}/src/nametag)
include_directories(${LIBOTP_DIR}/src/margins)
include_directories(${LIBOTP_DIR}/src/settings)
include_directories(src/base)
include_directories(src/suit)
include_directories(src/components)
include_directories(src/pet)
include_directories(${PANDA_DIR}/include)
include_directories(${OPEN_SSL_DIR}/include)
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(/usr/include/eigen3)
link_directories(${LIBOTP_DIR}/build/)
link_directories(${PANDA_DIR}/lib)
link_directories(${OPEN_SSL_DIR}/lib)

set(LIBPFX "")
if(WIN32)
    set(LIBPFX "lib")
    add_definitions(/wd4275)
    add_definitions(/EHa)
    add_definitions(/GF)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    execute_process(COMMAND "${CMAKE_C_COMPILER}" -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    message(STATUS "GCC Version: ${GCC_VERSION}")
    if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        add_definitions(-std=c++11) # Enable the new C++ standard
    else()
        add_definitions(-std=c++0x) # Enable the new C++ standard
    endif()
endif()

if (PANDA_OPTIMIZED)
    add_definitions(-DPANDA_OPTIMIZED)
    add_definitions(-DNDEBUG)
    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /GL")
    string(REGEX REPLACE "[-/]INCREMENTAL" "/INCREMENTAL:NO" CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO} /LTCG")
    string(REGEX REPLACE "[-/]INCREMENTAL" "/INCREMENTAL:NO" CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /LTCG")
    string(REGEX REPLACE "[-/]INCREMENTAL" "/INCREMENTAL:NO" CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /LTCG")
    
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /GL")
    set(CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL "${CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL} /LTCG")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL} /LTCG")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} /LTCG")
else()
    add_definitions(-D_DEBUG)
endif()

add_definitions(-DBUILDING_TOONTOWN)
add_definitions(-DBUILDING_DNA)
add_definitions(/O2)
add_definitions(/Ob1)

set(PANDA_LIBS
    ${LIBPFX}p3framework
    ${LIBPFX}panda
    ${LIBPFX}pandafx
    ${LIBPFX}pandaexpress
    ${LIBPFX}p3dtool
    ${LIBPFX}p3dtoolconfig
    ${LIBPFX}p3direct
    ${LIBPFX}p3pandatoolbase
)

set(LIBOTP_LIBS
    ${LIBPFX}otp
)

# Add p3interrogatedb, if it exists
find_library(HAVE_P3INTERROGATEDB
             ${LIBPFX}p3interrogatedb
             HINTS ${PANDA_DIR}/lib)
             
if (HAVE_P3INTERROGATEDB)
    message(STATUS "libp3interrogatedb found")
    LIST(APPEND PANDA_LIBS ${LIBPFX}p3interrogatedb)
else()
    message(STATUS "libp3interrogatedb not found")
endif()

if(WIN32)
    add_library(libtoontown SHARED
        ${BASE_FILES}
        ${SUIT_FILES}
        ${COMPONENTS_FILES}
        ${PET_FILES}
        ${IGATE_FILES}
    )
    SET_TARGET_PROPERTIES(libtoontown PROPERTIES SUFFIX ".pyd")
else()
    add_library(libtoontown MODULE
        ${BASE_FILES}
        ${SUIT_FILES}
        ${COMPONENTS_FILES}
        ${PET_FILES}
        ${IGATE_FILES}
    )
endif()

target_link_libraries(libtoontown ${PANDA_LIBS} ${LIBOTP_LIBS} ${PYTHON_LIBRARY})

add_custom_command(TARGET libtoontown
                   PRE_BUILD
                   COMMAND ${PYTHON2_EXECUTABLE} "${CMAKE_SOURCE_DIR}/src/run_interrogate.py" "${PANDA_DIR}" "${LIBOTP_DIR}/src"
                   COMMENT "Interrogate")

### Setup source groups and defines for configurables ###
source_group("base" FILES ${BASE_FILES})
source_group("suit" FILES ${SUIT_FILES})
source_group("components" FILES ${COMPONENTS_FILES})
source_group("pet" FILES ${PET_FILES})
source_group("interrogate_files" FILES ${IGATE_FILES})