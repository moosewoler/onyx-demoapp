#ifndef DEMO_VIEW_H_
#define DEMO_VIEW_H_

#include <QtGui/QtGui>
#include "onyx/ui/ui.h"
#include "onyx/ui/ui_utils.h"
#include "onyx/screen/screen_proxy.h"

using namespace ui;

class DemoView : public QWidget
{
    Q_OBJECT

public:
    DemoView(QWidget *parent = 0);
    ~DemoView();

public:
    bool start();
    bool stop();
    bool exec(const QStringList & args);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *ke);
    virtual void closeEvent(QCloseEvent * event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void paintEvent(QPaintEvent *);

private Q_SLOTS:
    void onStartClicked();
    void onCloseClicked();

private:
    QString currentState();

private:
    OnyxPushButton start_;
    OnyxPushButton close_;
};


#endif
