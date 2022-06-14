# 将当前目录下所以cpp文件保存到一个变量 DIR_STRING_SRCS 中
aux_source_directory(. DIR_STRING_SRCS)
# 将这些源文件编译为 lib_myString.a
add_library(lib_myString ${DIR_STRING_SRCS})