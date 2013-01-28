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
    onyx::screen::watcher().addWatcher(this);
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

bool DemoView::eventFilter(QObject *obj, QEvent *e)
{
    qDebug("Select event:%d", e->type());
    if (e->type() == QEvent::MouseButtonRelease && obj->isWidgetType())
    {
        onyx::screen::instance().updateWidget(0, onyx::screen::ScreenProxy::GU);
    }
    return QObject::eventFilter(obj, e);
}

void DemoView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    QFont font = QApplication::font();
    font.setPointSize(34);
    painter.setFont(font);
    QFontMetrics fm(font);

    painter.drawText(QRect(0, BUTTON_HEIGHT, width(), height() - BUTTON_HEIGHT), Qt::AlignHCenter | Qt::AlignTop, currentState());
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

QString DemoView::currentState()
{
    QString result(tr("DemoApplication.\nA blank application."));
    return result;
}

