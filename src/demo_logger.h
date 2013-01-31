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
        DemoLogger & operator << (const QString & message);
    private:
        QFile       file_;
        QTextStream out_;
        int         loglevel_;
};

#ifndef DEMO_LOGGER_IMPLEMENTATION
extern DemoLogger logger;
#endif

#endif
