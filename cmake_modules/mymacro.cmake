# select the proper toolchain
if (BUILD_FOR_X86)
    include(x86_toolchain)
elseif (BUILD_FOR_ARM)
    include(arm_toolchain)
elseif (BUILD_FOR_MIPS)
    include(mips_toolchain)
endif(BUILD_FOR_X86)

# cmake modules
include (FindThreads)
include (enable_qt)
#include (qt4_wrap_ts)
#include (onyx_test)
#include (misc)
#include (tc)
#include (strict_warning)

# some other staffs
if(UNIX)
    add_definitions(-DSHARE_ROOT="/usr/share")
else (UNIX)
    add_definitions(-DSHARE_ROOT="")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif (UNIX)

add_definitions(-DCONFIG_CTRL_IFACE)
add_definitions(-DCONFIG_CTRL_IFACE_UNIX)

# Project include directories.
message             (STATUS "by MWO: QT_LIBRARY_DIR is set to ${QT_LIBRARY_DIR}")
include_directories (BEFORE ${CMAKE_SOURCE_DIR}/src/include ${CMAKE_FIND_ROOT_PATH}/include ~/Code/freescale/linux-2.6.35.3/include)
link_directories    (${QT_LIBRARY_DIR})
