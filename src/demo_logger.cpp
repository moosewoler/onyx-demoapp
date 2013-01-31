#define  DEMO_LOGGER_IMPLEMENTATION
#include "demo_logger.h"

DemoLogger logger("/media/sd/log.txt");

DemoLogger::DemoLogger(const QString & filename)
{
    file_.setFileName(filename);
    if (!file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {        
        // logger error
    }
    out_.setDevice(&file_);
    log(QString("Log file opens at ")+filename+QString("."));
    loglevel_=0;
}

DemoLogger::~DemoLogger(void)
{
    // reset loglevel no matter what it is.
    loglevel_=0;
    log("Log file Closed.");
    file_.close();
}

void DemoLogger::log(const QString & message)
{
    if (message.left(5) == QString("ENTER"))
    {
        loglevel_++;
    }

    for (int i=0;i<loglevel_;i++)
    {
        out_<<"  ";
    }
    out_ << message << "\n";

    if (message.left(5) == QString("LEAVE"))
    {
        loglevel_--;
    }
}
