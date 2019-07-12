#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QNetworkInterface>
#include <QtNetwork>
#include <QTimer>
#include <QList>
#include "ui_mainwindow.h"
#include "tcpudpcombase.h"

namespace Ui {
    class TCPServer;
}

class TCPServer : public QDialog,public TcpUdpComBase
{
    Q_OBJECT

public:
    explicit TCPServer(QWidget *parent = 0);
    ~TCPServer();
    void sendmessage();//��������
    void serverlisten();//����
    void serverStoplisten();//ֹͣ����
    void setDisplayFlag(bool flag){showbox = flag;}
    void setMainUiPoint(Ui::MainWindow *ui){main_ui=ui;}
    bool WorkOpen();//����
    void WorkClose();//ֹͣ����
    void WorkSendMessage();//��������
    void WorkSetDisplayFlag(bool flag){showbox = flag;}

signals:
    void formSmit();

private slots:
    void updateserver();
    void updateSendStatus();//������
    void serverReadMessage();
    void on_OKpushButton_clicked();

private:
    Ui::TCPServer *ui;
    Ui::MainWindow *main_ui;
    void updataWidgetList();
    void cleaerWidgetList();
    void initListen();


    QTcpServer *tcpserver;
    QString serverPort;
    QTimer* _time;
    QList<QTcpSocket* > linkList;
    bool showbox;

};

#endif // TCPSERVER_H
