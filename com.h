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
    bool OpenSerialCom();//打开串口
    bool WorkOpen();//打开串口
    void CloseSerialCom();//关闭串口
    void WorkClose();//关闭串口
    void SendMessage();//发送数据
    void WorkSendMessage();//发送数据
    void setDisplayFlag(bool flag){DisplayFlag = flag;}
    void WorkSetDisplayFlag(bool flag){DisplayFlag = flag;}

private:
    Ui::COM *ui;
    Ui::MainWindow *main_ui;
    bool DisplayFlag;
    Win_QextSerialPort *myCom; //声明对象//串口

private slots:
    void  readMyCom();//读取串口，将串口的数据显示
//    void on_openMyComBtn_clicked();//串口
//    void on_closeMyComBtn_clicked();//串口
//    void on_sendMsgBtn_clicked();
//    void on_ComClearBtn_clicked();
//    void on_ComDisplayBtn_clicked(bool checked);
//    void on_ComSendAutocheckBox_toggled(bool checked);
//    void AutoSendMessage();
    void on_OKpushButton_clicked();
};

#endif // COM_H
