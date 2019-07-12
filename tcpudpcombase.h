#ifndef TCPUDPCOMBASE_H
#define TCPUDPCOMBASE_H

//#include "ui_mainwindow.h"

class TcpUdpComBase
{
public:
    TcpUdpComBase();
    //virtual void WorkPeiZhi()=0;
    virtual bool WorkOpen()=0;
    virtual void WorkClose()=0;
    virtual void WorkSendMessage()=0;
    virtual void WorkSetDisplayFlag(bool)=0;
    //virtual void WorksetMainUiPoint()=0;
//    void setMainUiPoint(Ui::MainWindow *ui){main_ui=ui;}
//    Ui::MainWindow *main_ui;
};

#endif // TCPUDPCOMBASE_H
