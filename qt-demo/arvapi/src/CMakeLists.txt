
# 设置变量，给LIB_NAME赋值为staticLib
set(LIB_NAME arv)

project(${LIB_NAME})

# 设置编译源文件。
file(GLOB_RECURSE c_files RELATIVE ${PROJECT_SOURCE_DIR}  *.cpp)
# 设置编译头文件
file(GLOB_RECURSE h_files RELATIVE ${PROJECT_SOURCE_DIR}  *.h)

# 将源文件和头文件编译成共享库文件。${LIB_NAME}为库文件的文件名。
add_library(${LIB_NAME} SHARED ${h_files} ${c_files})

