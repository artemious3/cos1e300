cmake_minimum_required(VERSION 3.26)
project(bignum)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")


add_executable(bignum main.cpp)


find_package(Boost REQUIRED)
find_package(MPFR REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
TARGET_LINK_LIBRARIES( bignum LINK_PUBLIC Boost::boost ${MPFR_LIBRARY})

