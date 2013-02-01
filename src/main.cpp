#include <QtCore>
#include <QtGui>
#include "onyx/sys/sys_status.h"
#include "demo_application.h"       // 本应用对象
#include "demo_logger.h"

int main(int argc, char * argv[])
{
    DemoApplication app(argc, argv);
    app.setApplicationName("DemoApplication");

    sys::SysStatus::instance().setSystemBusy(false);
    
    app.start();
    int ret = app.exec();

    logger.log("INFO  Hello world!");

    return ret;
}
