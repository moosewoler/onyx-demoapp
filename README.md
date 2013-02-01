ONYX-DemoApplication
====================

1. Introduction
---------------
This is (not exactly now) a empty application can be run on onyx boox i62/m92/a62(only tested on i62, maybe work on others). 

What i have tested:
* QWidget                         main form
* QWidget::mousePressEvent        
* QWidget::keyReleaseEvent
* QTimer & SLOT & SIGNAL          to repeat screen update
* gettimeofday()                  
* onyx::screen::UpdateWidget()    test all 7 waveforms of EPD controller.
* QFile & QTextStream             to log program information to text file on external sdcard.

2. Installation & Usage
-----------------------
Copy binary(onyx-demoapp.oar) on your device's Flash (both internal and external is OK), click on the icon to run the application.

3. Development & Compilation
----------------------------
This application requires onyx toolchain & SDK which can be obtained from github.com/onyxintl.
Fllows the instructions of onyx how to build the development environment of your own. Then ./build.sh to build binary.
