#include <QtGui/QtGui>
#include "demo_view.h"
#include "onyx/screen/screen_update_watcher.h"
#include "onyx/sys/sys_status.h"
#include "onyx/sys/platform.h"
#include "onyx/data/configuration.h"
#include <sys/time.h>
#include "demo_logger.h"

static const int BUTTON_HEIGHT = 100;

DemoView::DemoView(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint)
    , start_(tr("Start"), 0)
    , close_(tr("Close"), 0)
{
    logger.log("ENTER DemoView:DemoView().");

    msg_="Demo Application\nA blank application.";
    point_=QPoint(0,0);
    onyx::screen::watcher().addWatcher(this);
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);

    wftype_=1;  // waveform type from 1 to 7
    freq_=1;
    timer_.setInterval(int(1/freq_*1000)); // 1Hz
    logger.log(QString("INFO  set freq_ to ")+QString::number(freq_));
    counter_=2;
    connect(&timer_, SIGNAL(timeout()), this, SLOT(OnTimer()));
    timer_.start();

    logger.log("LEAVE DemoView:DemoView().");
}

DemoView::~DemoView()
{
    logger.log("ENTER DemoView:~DemoView().");
    logger.log("LEAVE DemoView:~DemoView().");
}

void DemoView::keyPressEvent(QKeyEvent *e)
{
    logger.log("ENTER DemoView:keyPressEvent().");
    switch (e->key())
    {
    case Qt::Key_Down:
    case Qt::Key_Up:
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
    e->accept();
    logger.log("LEAVE DemoView:keyPressEvent().");
}

void DemoView::keyReleaseEvent(QKeyEvent *ke)
{
    logger.log("ENTER DemoView:keyReleaseEvent().");
    switch (ke->key())
    {
    case ui::Device_Menu_Key:
        logger.log(QString("INFO  Device_Menu_Key pressed."));
        break;
    case Qt::Key_Left:
        logger.log(QString("INFO  Key_Left pressed."));
        break;
    case Qt::Key_Right:
        logger.log(QString("INFO  Key_Right pressed."));
        break;
    case Qt::Key_PageDown:
        timer_.stop();
        counter_=2;
        timer_.start();

        wftype_++;
        if (wftype_>=7)
        {
            wftype_=7;
        }

        logger.log(QString("INFO  Key_PageDown pressed."));
        break;
    case Qt::Key_Down:
        logger.log(QString("INFO  Key_Down pressed."));
        break;
    case Qt::Key_PageUp:
        timer_.stop();
        counter_=2;
        timer_.start();

        wftype_--;
        if (wftype_<=1)
        {
            wftype_=1;
        }
        logger.log(QString("INFO  Key_PageUp pressed."));
        break;
    case Qt::Key_Up:
        logger.log(QString("INFO  Key_Up pressed."));
        break;
    case Qt::Key_C:
        logger.log(QString("INFO  Key_C pressed."));
        break;
    case Qt::Key_Escape:
    case Qt::Key_Home:
        logger.log(QString("INFO  Key_Home pressed."));
        onCloseClicked();
    default:
        logger.log(QString("INFO  unknown key pressed."));
        QWidget::keyReleaseEvent(ke);
        break;
    }
    ke->ignore();
    logger.log("LEAVE DemoView:keyReleaseEvent().");
}

void DemoView::closeEvent(QCloseEvent * event)
{
    logger.log("ENTER DemoView:closeEvent().");
    QWidget::closeEvent(event);
    logger.log("LEAVE DemoView:closeEvent().");
}

/// Ignore the double click event.
//void DemoView::mouseDoubleClickEvent(QMouseEvent*me)
//{
//    logger.log("ENTER DemoView:mouseDoubleClickEvent().");
//    me->accept();
//    logger.log("LEAVE DemoView:mouseDoubleClickEvent().");
//}

void DemoView::mousePressEvent(QMouseEvent*me)
{
    logger.log("ENTER DemoView:mousePressEvent().");
    QString str = QString("(,)");
    str.insert(1,QString::number(me->x()));
    str.insert(str.indexOf(QChar(')')), QString::number(me->y()));
    currentState(str);
    point_ = me->pos();

    update();

    //me->accept();
    logger.log("LEAVE DemoView:mousePressEvent().");
}

bool DemoView::eventFilter(QObject *obj, QEvent *e)
{
    logger.log("ENTER DemoView:eventFilter().");

    qDebug("Select event:%d", e->type());
    if (e->type() == QEvent::MouseButtonRelease && obj->isWidgetType())
    {
        onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU);
    }

    logger.log("LEAVE DemoView:eventFilter().");
    return QObject::eventFilter(obj, e);
}

void DemoView::paintEvent(QPaintEvent *e)
{
    struct  timeval start;
    struct  timeval end;
    unsigned  long elapsed;

    QString wftype;

    logger.log("ENTER DemoView:paintEvent().");

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    QFont font = QApplication::font();
    font.setPointSize(24);
    painter.setFont(font);
    QFontMetrics fm(font);


    painter.drawText(QRect(point_.x(),point_.y(), width(), 200), Qt::AlignLeft, msg_);

    //gettimeofday(&start,NULL);
    //onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::A2, true, onyx::screen::ScreenCommand::WAIT_ALL);
    //gettimeofday(&end,NULL);
    //wftype="A2";

    // i prefer to use switch rather than pass wftype_ directly as a enumeration value
    switch(wftype_)
    {
        case 1:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::DW, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="DW";
            break;
        case 2:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::A2, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="A2";
            break;
        case 3:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="GU";
            break;
        case 4:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GC, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="GC";
            break;
        case 5:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GC4, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="GC4";
            break;
        case 6:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GC8, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="GC8";
            break;
        case 7:
            gettimeofday(&start,NULL);
            onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GC16, true, onyx::screen::ScreenCommand::WAIT_ALL);
            gettimeofday(&end,NULL);
            wftype="GC16";
            break;
        default:
            break;
    }

    elapsed = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    logger.log(QString("INFO  paintEvent use waveform ")+wftype+QString(", elapsed ")+QString::number(elapsed)+QString(" usec.")); 

    logger.log("LEAVE DemoView:paintEvent().");
}

void DemoView::onStartClicked()
{
    logger.log("ENTER DemoView:onStartClicked().");
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
    logger.log("LEAVE DemoView:onStartClicked().");
}

void DemoView::onCloseClicked()
{
    logger.log("ENTER DemoView:onCloseClicked().");
//    sys::SysStatus::instance().stopWpaSupplicant();
    qApp->exit();
    logger.log("LEAVE DemoView:onCloseClicked().");
}


bool DemoView::start()
{
    logger.log("ENTER DemoView:start().");
    onStartClicked();
    logger.log("LEAVE DemoView:start().");
    return true;
}

bool DemoView::stop()
{
    logger.log("ENTER DemoView:stop().");
    onCloseClicked();
    logger.log("LEAVE DemoView:stop().");
    return true;
}

bool DemoView::exec(const QStringList & args)
{
    logger.log("ENTER DemoView:exec().");
    logger.log("LEAVE DemoView:exec().");
    return true;
}

void DemoView::currentState(const QString & str)
{
    logger.log("ENTER DemoView:currentState().");
    msg_ = str;
    logger.log("LEAVE DemoView:currentState().");
}

void DemoView::OnTimer()
{
    logger.log("ENTER DemoView:OnTimer().");

    currentState(QString("counter = ")+QString::number(counter_)+QString(" freq = ")+QString::number(freq_));
    point_.setX(point_.x()+1);
    repaint();

    counter_--;
    if (counter_ == 0)
    {
        timer_.stop();
    }
    logger.log(QString("INFO  counter = ") + QString::number(counter_));
    logger.log("LEAVE DemoView:OnTimer().");
}
