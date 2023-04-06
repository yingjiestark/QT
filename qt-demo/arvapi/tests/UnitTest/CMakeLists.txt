
# 设置变量，给LIB_NAME赋值为staticLib
set(EXE_NAME arv-test)

project(${EXE_NAME})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fprofile-arcs -ftest-coverage -lgcov")

set(SRCELATIVEPATH ../../)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/${SRCELATIVEPATH}/src)


# 设置编译源文件。
file(GLOB_RECURSE c_files RELATIVE ${PROJECT_SOURCE_DIR}  main.cpp src/*.cpp ${SRCELATIVEPATH}/src/*.cpp)
# 设置编译头文件
file(GLOB_RECURSE h_files RELATIVE ${PROJECT_SOURCE_DIR}  ${SRCELATIVEPATH}/src/*.h)


add_executable(${EXE_NAME} ${h_files} ${c_files})
target_link_libraries(
    ${EXE_NAME}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
)
