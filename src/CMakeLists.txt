ENABLE_QT()

# Header files.
SET(DEMO_HDRS demo_view.h demo_application.h demo_logger.h)

# Srouce files.
SET(DEMO_SRCS ${DEMO_HDRS} demo_application.cpp demo_view.cpp demo_logger.cpp main.cpp)

# Moc files.
SET(MOC_DEMO_HDRS demo_application.h demo_view.h)
QT4_WRAP_CPP(MOC_DEMO_SRCS ${MOC_DEMO_HDRS})

# Executable file.
ADD_EXECUTABLE(demoapp.oar ${DEMO_SRCS} ${MOC_DEMO_SRCS} )
TARGET_LINK_LIBRARIES(demoapp.oar
   onyx_data
   onyx_screen
   onyx_sys
   onyx_ui
   ${QT_LIBRARIES}
   ${ADD_LIB}
)

