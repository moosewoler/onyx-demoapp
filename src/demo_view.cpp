#include <QtGui/QtGui>
#include "demo_view.h"
#include "onyx/screen/screen_update_watcher.h"
#include "onyx/sys/sys_status.h"
#include "onyx/sys/platform.h"
#include "onyx/data/configuration.h"
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

    freq_=1;
    timer_.setInterval(int(1/freq_)); // 10Hz
    logger.log(QString("INFO  set freq_ to ")+QString::number(freq_));
    counter_=10;
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
        if (freq_ > 1)
        {
            freq_--;
            timer_.stop();
            counter_=10;
            timer_.setInterval(int(1/freq_));
            timer_.start();
        }
        logger.log(QString("INFO  Key_PageDown pressed."));
        break;
    case Qt::Key_Down:
        logger.log(QString("INFO  Key_Down pressed."));
        break;
    case Qt::Key_PageUp:
        freq_++;
        timer_.stop();
        counter_=10;
        timer_.setInterval(int(1/freq_));
        timer_.start();
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
    logger.log("ENTER DemoView:paintEvent().");

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    QFont font = QApplication::font();
    font.setPointSize(24);
    painter.setFont(font);
    QFontMetrics fm(font);

    painter.drawText(QRect(point_.x(),point_.y(), width(), 200), Qt::AlignLeft, msg_);
    onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::A2, false);

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
    update();

    counter_--;
    if (counter_ == 0)
    {
        timer_.stop();
    }
    logger.log(QString("INFO  counter = ") + QString::number(counter_));
    logger.log("LEAVE DemoView:OnTimer().");
}
