#include "onyx/data/configuration.h"
#include "onyx/ui/languages.h"
#include "demo_application.h"


DemoApplication::DemoApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    ui::loadTranslator(QLocale::system().name());
    QCoreApplication::setOrganizationName(QLatin1String("Onyx"));
    QCoreApplication::setApplicationName(QLatin1String("Demo Application"));
}

DemoApplication::~DemoApplication(void)
{
}

bool DemoApplication::start()
{
    main_window_.showMaximized();
    main_window_.start();
    return true;
}

bool DemoApplication::stop()
{
    return true;
}

bool DemoApplication::execShellCommand(const QStringList &args)
{
    return true;
}


