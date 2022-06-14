cmake_minimum_required(VERSION 3.22)
project(json-demo)

set(CMAKE_CXX_STANDARD 14)


# 将当前目录下所以cpp文件保存到一个变量 DIR_SRCS 中
aux_source_directory(. DIR_SRCS)


# 添加 test 目录
include_directories(./test)  # 添加 .h   文件目录
add_subdirectory(./test)     # 添加 .cpp 文件目录

# 添加 string 目录
include_directories(./myString)  # 添加 .h   文件目录
add_subdirectory(./myString)     # 添加 .cpp 文件目录

# 添加 JsonNode 目录
include_directories(./JsonNode)  # 添加 .h   文件目录
add_subdirectory(./JsonNode)     # 添加 .cpp 文件目录

# 添加 JsonParser 目录
include_directories(./JsonParser)  # 添加 .h   文件目录
add_subdirectory(./JsonParser)     # 添加 .cpp 文件目录

# 生成可执行文件
add_executable(json-demo ${DIR_SRCS})
target_link_libraries(json-demo lib_test lib_myString lib_JsonNode lib_JsonParser)

