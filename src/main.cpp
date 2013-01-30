#include <QtCore>
#include <QtGui>
#include "onyx/sys/sys_status.h"    // 状态条
#include "demo_application.h"    // 本应用对象
#include "demo_logger.h"

int main(int argc, char * argv[])
{
    DemoApplication app(argc, argv);
    app.setApplicationName("DemoApplication");

    sys::SysStatus::instance().setSystemBusy(false);
    
    app.start();
    int ret = app.exec();

    QFile file("/media/sd/log.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return ret;
    }

    DemoLogger logger("/media/sd/log.txt");
    logger.log("Hello world");

    return ret;
}
