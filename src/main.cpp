#include <QtGui>
#include "onyx/sys/sys_status.h"    // 状态条
#include "demo_application.h"    // 本应用对象

int main(int argc, char * argv[])
{
    DemoApplication app(argc, argv);
    app.setApplicationName("DemoApplication");

    sys::SysStatus::instance().setSystemBusy(false);
    
    app.start();

    int ret = app.exec();
    return ret;
}
