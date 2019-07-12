#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QNetworkInterface>
#include <QtNetwork>
#include "ui_mainwindow.h"
#include "tcpudpcombase.h"

namespace Ui {
    class TcpClient;
}

class TcpClient : public QDialog,public TcpUdpComBase
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();
    void sendmessage();//��������
    void setMainUiPoint(Ui::MainWindow *ui){main_ui=ui;}
    void setDisplayFlag(bool flag){showbox = flag;}
    void ClientDisconnect();//�Ͽ�����
    void ClientConnect();//����
    bool WorkOpen();//����
    void WorkClose();//�Ͽ�����
    void WorkSendMessage();//��������
    void WorkSetDisplayFlag(bool flag){showbox = flag;}
private slots:
    void displayError(QAbstractSocket::SocketError);
    void updateclient();
    void clientReadMessage();//��ȡ��Ϣ

    void on_OKpushButton_clicked();

private:
    Ui::TcpClient *ui;
    Ui::MainWindow *main_ui;
    QTcpSocket *tcplink;
    QString serverIP;
    QString serverPort;
    QTimer* _time;
    bool showbox;

};

#endif // TCPCLIENT_H
