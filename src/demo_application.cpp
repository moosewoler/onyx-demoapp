#include "onyx/data/configuration.h"
#include "onyx/ui/languages.h"
#include "demo_application.h"
#include "demo_logger.h"


DemoApplication::DemoApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    logger.log("ENTER DemoApplication:DemoApplication().");
    ui::loadTranslator(QLocale::system().name());
    QCoreApplication::setOrganizationName(QLatin1String("Onyx"));
    QCoreApplication::setApplicationName(QLatin1String("Demo Application"));
    logger.log("LEAVE DemoApplication:DemoApplication().");
}

DemoApplication::~DemoApplication(void)
{
    logger.log("ENTER DemoApplication:~DemoApplication().");
    logger.log("LEAVE DemoApplication:~DemoApplication().");
}

bool DemoApplication::start()
{
    logger.log("ENTER DemoApplication:start().");
    main_window_.showMaximized();
    main_window_.start();
    logger.log("LEAVE DemoApplication:start().");
    return true;
}

bool DemoApplication::stop()
{
    logger.log("ENTER DemoApplication:stop().");
    logger.log("LEAVE DemoApplication:stop().");
    return true;
}
