#ifndef REMOTEDISPLAYWIDGET_P_H
#define REMOTEDISPLAYWIDGET_P_H

#include <QWidget>
#include <QPointer>
#include <freerdp/freerdp.h>

class RemoteDisplayWidget;
class QThread;
class EventProcessor;
namespace { struct MyContext; }


class RemoteDisplayWidgetPrivate : public QObject {
    Q_OBJECT
public:
    RemoteDisplayWidgetPrivate(RemoteDisplayWidget *q);

    void initFreeRDP();

    void setSettingServerHostName(const QString &host);
    void setSettingServerPort(quint16 port);
    static MyContext* getMyContext(freerdp* instance);
    static MyContext* getMyContext(rdpContext* context);
    static BOOL PreConnectCallback(freerdp* instance);
    static BOOL PostConnectCallback(freerdp* instance);
    static void PostDisconnectCallback(freerdp* instance);
    static void BeginPaintCallback(rdpContext* context);

    freerdp* freeRdpInstance;
    QPointer<QThread> processorThread;
    QPointer<EventProcessor> eventProcessor;

    Q_DECLARE_PUBLIC(RemoteDisplayWidget)
    RemoteDisplayWidget* const q_ptr;

private slots:
    void onAboutToConnect();
    void onConnected();
    void onDisconnected();
    void onBeginPaint();
};

#endif // REMOTEDISPLAYWIDGET_P_H