#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "udp.h"
#include "com.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "tcpudpcombase.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_OpenpushButton_clicked();//�򿪰�ť
    void on_ClosepushButton_clicked();//�رհ�ť
    void on_PeizhipushButton_clicked();//���ð�ť
    void on_DisplaypushButton_clicked(bool checked);//ֹͣ��ʾ
    void on_ClearpushButton_clicked();
    void on_SendpushButton_clicked();
    void on_AutoSendcheckBox_toggled(bool checked);//�Զ����Ͳۺ���
    void SlectAutoSend();
    void HandleText();//�������룬16����
    void HandleStyle();//��������

private:
    Ui::MainWindow *ui;
    QTimer* _time;
    int style;
    int laststyle;
    UDP* P_udp;
    COM* P_com;
    TcpClient* P_tcpclient;
    TCPServer* p_tcpserver;
    TcpUdpComBase* p_base;

    void OpenCreateUdp();//����UDP
    void OpenCreateCOM();//��������
    void OpenCreateTcpClient();//����TCP�ͻ���
    void OpenCreateTcpServer();//����TCP������
    void WorkCreate();//����
    void DeleteCreation(int);
    void WorkDeleteCreation();

    bool HexDisplayFlag;
    bool HexSendFlag;
    bool DisplayFlag;
};

#endif // MAINWINDOW_H
