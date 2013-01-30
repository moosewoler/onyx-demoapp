#include "demo_logger.h"


DemoLogger::DemoLogger(const QString & filename)
{
    file_.setFileName(filename);
    if (!file_.open(QIODevice::WriteOnly | QIODevice::Text))
    {        
        // logger error
    }
    out_.setDevice(&file_);
    log(QString("Log file opens at ")+filename);
}

DemoLogger::~DemoLogger(void)
{
    log("Log file Closed.");
    file_.close();
}

void DemoLogger::log(const QString & message)
{
    out_ << message << "\n";
}
