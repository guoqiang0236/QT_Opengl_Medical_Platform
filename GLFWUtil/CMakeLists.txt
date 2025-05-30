#设置cmake的最低版本要求
cmake_minimum_required(VERSION 3.20)

#设置c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找所需要的库
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/Packages/glfw-3.4")
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Packages/glfw-3.4/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/Packages/glfw-3.4/lib")
set(GLFW_DLL "${CMAKE_SOURCE_DIR}/Packages/glfw-3.4/bin/glfw3.dll")
find_package(Qt6 COMPONENTS Core Gui REQUIRED)

# 启用 AUTOMOC（QT关键！）
set(CMAKE_AUTOMOC ON)   # 自动运行 moc，处理 Q_OBJECT 宏，生成元对象代码（信号槽机制依赖）
set(CMAKE_AUTOUIC ON)   # 自动处理 .ui 文件，生成对应的界面代码
set(CMAKE_AUTORCC ON)   # 自动处理 .qrc 资源文件，生成资源访问代码

# 收集源文件（显式列出头文件）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "source/*.cpp"
    "include/*.h"
    "${CMAKE_SOURCE_DIR}/Packages/glad/src/glad.c"
)

# 创建动态库目标（SHARED表示生成DLL）
add_library(GLFWUtil SHARED ${SRC_FILES})

# 添加预编译头支持
target_precompile_headers(GLFWUtil PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h")

# 添加预编译头支持（排除 glad.c）
set_source_files_properties(
    "${CMAKE_SOURCE_DIR}/Packages/glad/src/glad.c"
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

# 设置DLL导出宏（Windows下需要）
if(WIN32)
    target_compile_definitions(GLFWUtil PRIVATE GLFWUTIL_EXPORTS)
endif()


# 库头文件目录
target_include_directories(GLFWUtil
    PUBLIC
        ${GLFW_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Packages/glad/include
)

# 库lib目录
target_link_directories(GLFWUtil
    PRIVATE
        ${GLFW_LIB_DIR}
)


# 链接lib库
target_link_libraries(GLFWUtil
    PRIVATE
        Qt6::Core
        Qt6::Gui
        glfw3dll
)

# 复制 glfw*.dll 到可执行文件目录
add_custom_command(TARGET GLFWUtil POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${GLFW_DIR}/bin/glfw3.dll"
    "${GLFW_DIR}/lib/glfw3dll.lib"
    $<TARGET_FILE_DIR:GLFWUtil>
)

#使用 QT_NO_DEBUG_OUTPUT 宏禁止release模式下的调试输出
# if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_definitions(-DQT_NO_DEBUG_OUTPUT)
# endif()