#ifndef _DEMO_LOGGER_H_
#define _DEMO_LOGGER_H_
#include <QtCore>

class DemoLogger 
{
    public:
        DemoLogger(const QString & filename);
        ~DemoLogger(void);
    public:
        void log(const QString & message);
    private:
        QFile file_;
        QTextStream out_;
};

#endif
