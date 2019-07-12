#ifndef COM_H
#define COM_H

#include <QDialog>
#include "win_qextserialport.h"
#include "ui_mainwindow.h"
#include "tcpudpcombase.h"

namespace Ui {
    class COM;
}

class COM : public QDialog,public TcpUdpComBase
{
    Q_OBJECT

public:
    explicit COM(QWidget *parent = 0);
    ~COM();

    void setMainUiPoint(Ui::MainWindow *ui){main_ui=ui;}
    bool OpenSerialCom();//�򿪴���
    bool WorkOpen();//�򿪴���
    void CloseSerialCom();//�رմ���
    void WorkClose();//�رմ���
    void SendMessage();//��������
    void WorkSendMessage();//��������
    void setDisplayFlag(bool flag){DisplayFlag = flag;}
    void WorkSetDisplayFlag(bool flag){DisplayFlag = flag;}

private:
    Ui::COM *ui;
    Ui::MainWindow *main_ui;
    bool DisplayFlag;
    Win_QextSerialPort *myCom; //��������//����

private slots:
    void  readMyCom();//��ȡ���ڣ������ڵ�������ʾ
//    void on_openMyComBtn_clicked();//����
//    void on_closeMyComBtn_clicked();//����
//    void on_sendMsgBtn_clicked();
//    void on_ComClearBtn_clicked();
//    void on_ComDisplayBtn_clicked(bool checked);
//    void on_ComSendAutocheckBox_toggled(bool checked);
//    void AutoSendMessage();
    void on_OKpushButton_clicked();
};

#endif // COM_H
