#ifndef UDP_H
#define UDP_H

#include <QDialog>
#include <QtNetwork>
#include "ui_mainwindow.h"
#include "tcpudpcombase.h"

namespace Ui {
    class UDP;
}

class UDP : public QDialog,public TcpUdpComBase
{
    Q_OBJECT

public:
    explicit UDP(QWidget *parent = 0);
    ~UDP();
    void sendmessage();//��������
    void setMainUiPoint(Ui::MainWindow *ui){main_ui=ui;}
    void DisBindUDPSocket();//�Ͽ�����
    void setDisplayFlag(bool flag){DisplayFlag = flag;}
    void BindUDPSocket();//������
    bool WorkOpen();//������
    void WorkClose();//�Ͽ�����
    void WorkSendMessage();//��������
    void WorkSetDisplayFlag(bool flag){DisplayFlag = flag;}

private:
    Ui::UDP *ui;
    Ui::MainWindow *main_ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    QList<QHostAddress> IPlist;
    void getLocalIP();

    bool HexDisplayFlag;
    bool HexSendFlag;
    bool DisplayFlag;

private slots:
    void sendmessageslot();
    void ReadAndDisplayMessage();//���ݽ��ռ���ʾ�ۺ���
    //void on_OKpushButton_clicked();//ȷ����ť�ۺ���
    void on_OKpushButton_clicked();
};

#endif // UDP_H
