ENABLE_QT()

# Add subdirs
# add_subdirectory(wpa)

# Source & Header files.
file(GLOB HDRS *.h)
file(GLOB SRCS *.cpp)
QT4_WRAP_CPP(MOC_SRCS ${HDRS})
set(SRCS ${HDRS} ${SRCS} ${MOC_SRCS})

# Resources.
#SET(RESOURCE_SRCS images.qrc)
#QT4_ADD_RESOURCES(IMAGES_RES ${RESOURCE_SRCS})

# Executable file.
ADD_EXECUTABLE(demoapp.oar ${SRCS} ${MOC_SRCS} )
TARGET_LINK_LIBRARIES(demoapp.oar
   onyx_data
   onyx_screen
   onyx_sys
   onyx_ui
   ${QT_LIBRARIES}
   ${ADD_LIB}
)

