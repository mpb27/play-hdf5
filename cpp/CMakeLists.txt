cmake_minimum_required(VERSION 3.12)
project(H5PP_Examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(example1 example1.cpp)
target_link_libraries(example1 PRIVATE ${CONAN_LIBS})
target_compile_options(example1 PRIVATE
   -ffunction-sections
   -fdata-sections
   -flto
)
target_link_options(example1 PRIVATE
    -flto
    -Wl,--gc-sections
)

add_executable(example-02e-eigen-matrix example-02e-eigen-matrix.cpp)
target_link_libraries(example-02e-eigen-matrix PRIVATE ${CONAN_LIBS})

add_executable(example-02d-stdvector-struct example-02d-stdvector-struct.cpp)
target_link_libraries(example-02d-stdvector-struct PRIVATE ${CONAN_LIBS})

add_executable(example-04a-custom-struct-easy example-04a-custom-struct-easy.cpp)
target_link_libraries(example-04a-custom-struct-easy PRIVATE ${CONAN_LIBS})

add_executable(example-04c-tables example-04c-tables.cpp)
target_link_libraries(example-04c-tables PRIVATE ${CONAN_LIBS})

