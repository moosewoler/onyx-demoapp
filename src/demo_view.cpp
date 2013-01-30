#include <QtGui/QtGui>
#include "demo_view.h"
#include "onyx/screen/screen_update_watcher.h"
#include "onyx/sys/sys_status.h"
#include "onyx/sys/platform.h"
#include "onyx/data/configuration.h"

static const int BUTTON_HEIGHT = 100;

DemoView::DemoView(QWidget *parent)
    : QWidget(0, Qt::FramelessWindowHint)
    , start_(tr("Start"), 0)
    , close_(tr("Close"), 0)
{
    msg_="Demo Application\nA blank application.";
    point_=QPoint(0,0);
    onyx::screen::watcher().addWatcher(this);
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

DemoView::~DemoView()
{
}

void DemoView::keyPressEvent(QKeyEvent *e)
{
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
}

void DemoView::keyReleaseEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
    case ui::Device_Menu_Key:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_PageDown:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_PageUp:
        break;
    case Qt::Key_Up:
        break;
    case Qt::Key_C:
        break;
    case Qt::Key_Escape:
    case Qt::Key_Home:
        onCloseClicked();
    default:
        QWidget::keyReleaseEvent(ke);
        break;
    }
    ke->ignore();
}

void DemoView::closeEvent(QCloseEvent * event)
{
    QWidget::closeEvent(event);
}

/// Ignore the double click event.
void DemoView::mouseDoubleClickEvent(QMouseEvent*me)
{
    me->accept();
}

//void DemoView::mousePressEvent(QMouseEvent*me)
//{
//    QString str = QString("(,)");
//    str.insert(1,QString::number(me->x()));
//    str.insert(str.indexOf(QChar(',')), QString::number(me->y()));
//    currentState(str);
//    point_ = me->pos();
//
//    update();
//    onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU);
//
//    me->accept();
//}

bool DemoView::eventFilter(QObject *obj, QEvent *e)
{
    qDebug("Select event:%d", e->type());
    if (e->type() == QEvent::MouseButtonRelease && obj->isWidgetType())
    {
        onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU);
    }
    return QObject::eventFilter(obj, e);
}

void DemoView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    QFont font = QApplication::font();
    font.setPointSize(16);
    painter.setFont(font);
    QFontMetrics fm(font);

    painter.drawText(QRect(point_.x(),point_.y(), 200, 200), Qt::AlignLeft, msg_);
}

void DemoView::onStartClicked()
{
    update();
    onyx::screen::watcher().enqueue(this, onyx::screen::ScreenProxy::GC);
}

void DemoView::onCloseClicked()
{
//    sys::SysStatus::instance().stopWpaSupplicant();
    qApp->exit();
}


bool DemoView::start()
{
    onStartClicked();
    return true;
}

bool DemoView::stop()
{
    onCloseClicked();
    return true;
}

bool DemoView::exec(const QStringList & args)
{
    return true;
}

void DemoView::currentState(const QString & str)
{
    msg_ = str;
}

