cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

enable_testing()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Matrix lib/Matrix/Matrix.h lib/Matrix/Matrix.cc)

include_directories(include)
include_directories(lib/Matrix)

add_subdirectory(lib/Catch2)
include_directories(lib/Catch2/single_include)
add_executable(tests tests/TestsMain.cc tests/TestMatrix.cc)
target_link_libraries(tests PRIVATE
        Matrix
        Catch2::Catch2
        )

set(LIBRARIES_TO_LINK)

message(CHECK_START "Looking for Eigen")
set(EIGEN_DIR ${CMAKE_SOURCE_DIR}/lib/eigen/)
if(EXISTS ${EIGEN_DIR})
    list(APPEND CMAKE_MESSAGE_INDENT "    ")
    add_subdirectory(${EIGEN_DIR})
    include_directories(${EIGEN_DIR})
    add_compile_definitions(MK_WITH_EIGEN)
    list(POP_BACK CMAKE_MESSAGE_INDENT)
    message(CHECK_PASS "found")
else()
    message(CHECK_FAIL "not found")
endif()

message(CHECK_START "Looking for ROOT")
# Full list of avaliable ROOT libraries
# https://cliutils.gitlab.io/modern-cmake/chapters/packages/ROOT.html
find_package(ROOT CONFIG)
if(${ROOT_FOUND})
    include(${ROOT_USE_FILE})
    include_directories(${ROOT_INCLUDE_DIRS})
    list(APPEND LIBRARIES_TO_LINK ROOT::Core ROOT::Gui)
    add_compile_definitions(MK_WITH_ROOT)
    message(CHECK_PASS "found")
else()
    message(CHECK_FAIL "not found")
endif()


message(CHECK_START "Looking for Sciplot")
set(SCIPLOT_DIR ${CMAKE_SOURCE_DIR}/lib/sciplot/)
if(EXISTS ${SCIPLOT_DIR})
    include_directories(${SCIPLOT_DIR})
    add_compile_definitions(MK_WITH_PLOT)
    message(CHECK_PASS "found")
else()
    message(CHECK_FAIL "not found")
endif()

add_executable(network src/Network.cpp src/main.cpp include/LettersDataset.h)
target_link_libraries(network ${LIBRARIES_TO_LINK}  ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_test(NAME Catch2 COMMAND ./tests)