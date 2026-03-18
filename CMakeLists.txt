cmake_minimum_required(VERSION 3.20)
project(DataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_STRUCT_TESTS "Build executables in Structures/Tests" ON)
option(BUILD_EXERCISES "Build executables in Exercises" ON)

# 头文件搜索路径（容器与工具）
set(PROJECT_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/Structures
    ${CMAKE_SOURCE_DIR}/Utils
)

# 收集 Structures 下的实现文件（排除 Tests）
file(GLOB_RECURSE STRUCTURE_IMPL CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/Structures/*.cpp
)
list(FILTER STRUCTURE_IMPL EXCLUDE REGEX ".*/Tests/.*")

# 可复用容器库：有 cpp 则做 STATIC，无 cpp 则做 INTERFACE
if(STRUCTURE_IMPL)
    add_library(ds_structures STATIC ${STRUCTURE_IMPL})
    target_include_directories(ds_structures PUBLIC ${PROJECT_INCLUDE_DIRS})
else()
    add_library(ds_structures INTERFACE)
    target_include_directories(ds_structures INTERFACE ${PROJECT_INCLUDE_DIRS})
endif()

# 给某个目录下所有 .cpp（每个都含 main）自动建可执行目标
function(add_mains_from_dir prefix base_dir folder_name)
    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${base_dir}/*.cpp)
    foreach(src IN LISTS SRCS)
        file(RELATIVE_PATH rel ${base_dir} ${src})
        get_filename_component(name_we ${rel} NAME_WE)
        get_filename_component(rel_dir ${rel} DIRECTORY)

        if(rel_dir STREQUAL "")
            set(target "${prefix}_${name_we}")
        else()
            string(REPLACE "/" "_" rel_dir_norm "${rel_dir}")
            string(REPLACE "\\" "_" rel_dir_norm "${rel_dir_norm}")
            set(target "${prefix}_${rel_dir_norm}_${name_we}")
        endif()

        add_executable(${target} ${src})
        target_link_libraries(${target} PRIVATE ds_structures)
        set_target_properties(${target} PROPERTIES FOLDER ${folder_name})
    endforeach()
endfunction()

if(BUILD_STRUCT_TESTS)
    add_mains_from_dir(test ${CMAKE_SOURCE_DIR}/Structures/Tests Tests)
endif()

if(BUILD_EXERCISES)
    add_mains_from_dir(ex ${CMAKE_SOURCE_DIR}/Exercises Exercises)
endif()