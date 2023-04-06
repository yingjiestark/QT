#定义cmake版本
cmake_minimum_required(VERSION 3.9.5)

#设置项目名称
set(EXE_NAME Minesweeper)
project(${EXE_NAME})

if (NOT DEFINED VERSION)
    set(VERSION 1.0)
endif ()

# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--as-needed -fPIE -fPIC") #-Wl,--as-needed 减少无效的库链接，用不到的库需要清理

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON) #要显示执行构建过程中详细的信息(比如为了得到更详细的出错信息)
set(CMAKE_AUTOMOC ON) #打开全局moc
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_TYPE "Debug")

#对DApplication 进行加速
set(CMAKE_EXE_LINKER_FLAGS "-pie")

#龙芯特有编译参数 -start
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips64")
    message(STATUS "this system is mips64=========")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ftree-vectorize -march=loongson3a -mhard-float -mno-micromips -mno-mips16 -flax-vector-conversions -mloongson-ext2 -mloongson-mmi -Wl,--as-needed")
endif()
#龙芯特有编译参数 -end

find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

file(GLOB_RECURSE c_files RELATIVE ${PROJECT_SOURCE_DIR} main.cpp ui/*.cpp db/*.cpp)
file(GLOB_RECURSE h_files RELATIVE ${PROJECT_SOURCE_DIR} ui/*.h db/*.h)

qt5_add_resources(qrc_FILES resources/resource.qrc)

add_executable(${EXE_NAME}  ${c_files} ${h_files} ${qrc_FILES})

# 应用程序安装
install(TARGETS ${EXE_NAME} DESTINATION bin)

# desktop文件安装
install(FILES  desktop/minesweeper.desktop
        DESTINATION share/applications/
        PERMISSIONS OWNER_READ OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE)

# 应用程序图标安装
install(FILES resources/lei.png DESTINATION share/icons/hicolor/scalable/apps/)

target_link_libraries(${EXE_NAME}
    Qt5::Widgets
    Qt5::Sql
)

