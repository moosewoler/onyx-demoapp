#ifndef DS_APPLICATION_H_
#define DS_APPLICATION_H_

#include "onyx/base/base.h"
#include "onyx/ui/ui.h"
#include "onyx/base/dbus.h"

#include "demo_view.h"        // 布局


class DemoApplication : public QApplication
{
    Q_OBJECT;

public:
    DemoApplication(int &argc, char **argv);
    ~DemoApplication(void);

public Q_SLOTS:
    bool start();
    bool stop();
    bool execShellCommand(const QStringList & args);

private:
    DemoView main_window_;
    NO_COPY_AND_ASSIGN(DemoApplication);
};

#endif
