#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->SendtextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
    P_udp = NULL;
    P_com = NULL;
    P_tcpclient = NULL;
    p_tcpserver = NULL;
    p_base = NULL;
    laststyle = 0;
    style = 0;//
    WorkCreate();//创建TCP服务器
    setWindowTitle(QString("三合一调试助手"));

    _time = new QTimer();
    _time->setInterval(2000);
    connect(_time,SIGNAL(timeout()),this,SLOT(SlectAutoSend()));
    connect(ui->StylecomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(HandleStyle()));
//    ui->OpenpushButton->setEnabled(false);
//    ui->ClosepushButton->setEnabled(false);
//    ui->DisplaypushButton->setEnabled(false);
//    ui->SendpushButton->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenpushButton_clicked()
{
    switch(style)
    {
    case 0://tcp server
        ui->Statelabel->setText(tr("已打开TCP服务器！"));
        p_base->WorkOpen();
        break;
    case 1://tcp client
        ui->Statelabel->setText(tr("已打开TCP客户端！"));
        p_base->WorkOpen();
        break;
    case 2://udp
        ui->Statelabel->setText(tr("已打开UDP！"));
        p_base->WorkOpen();
        break;
    case 3://com
        ui->Statelabel->setText(tr("已打开串口测试软件！"));
        p_base->WorkOpen();
        break;
    default:
        break;
    }
    ui->SendpushButton->setEnabled(true);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(true);
}

void MainWindow::on_ClosepushButton_clicked()
{
//    switch(style)
//    {
//    case 0://tcp server
//        p_base->WorkClose();
//        break;
//    case 1://tcp client
//        P_tcpclient->ClientDisconnect();
//        break;
//    case 2://udp
//        P_udp->DisBindUDPSocket();
//        break;
//    case 3://com
//        P_com->CloseSerialCom();
//        break;
//    default:
//        break;
//    }
    p_base->WorkClose();

    ui->OpenpushButton->setEnabled(true);
    ui->ClosepushButton->setEnabled(false);
    ui->SendpushButton->setEnabled(false);  //
    ui->PeizhipushButton->setEnabled(true);
}

void MainWindow::on_PeizhipushButton_clicked()
{
    ui->AutoSendcheckBox->setEnabled(true);
    ui->SendpushButton->setEnabled(true);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(true);
    ui->DisplaypushButton->setEnabled(true);
    ui->PeizhipushButton->setEnabled(true);

    style = ui->StylecomboBox->currentIndex();
    switch(style)
    {
    case 0://tcp server
        if(p_tcpserver!=NULL)
        {
            p_tcpserver->exec();//非模态
            ui->Statelabel->setText(tr("TCP服务器参数设置成功，可以使用！"));
        }
        break;
    case 1://tcp client
        if(P_tcpclient!=NULL)
        {
            P_tcpclient->exec();//非模态
            ui->Statelabel->setText(tr("TCP客户端参数设置成功，可以使用！"));
        }
        break;
    case 2://udp
        if(P_udp!=NULL)
        {
           P_udp->exec();//非模态
           ui->Statelabel->setText(tr("UDP参数设置成功，可以使用！"));
        }
        break;
    case 3://com
        if(P_com!=NULL)
        {
            P_com->exec();//非模态
            ui->Statelabel->setText(tr("串口参数设置成功，可以使用！"));
        }
//        else
//        {
//            DeleteCreation(style);
//            WorkCreate();
//        }
        break;
    default:
        break;
    }

}

void MainWindow::on_DisplaypushButton_clicked(bool checked)
{
    if(checked)
    {
        ui->DisplaypushButton->setText(tr("继续显示"));
        DisplayFlag = false;
    }
    else
    {
        ui->DisplaypushButton->setText(tr("停止显示"));
        DisplayFlag = true;
    }
    p_base->WorkSetDisplayFlag(DisplayFlag);
//    switch(style)
//    {
//    case 0://tcp server
//        p_tcpserver->setDisplayFlag(DisplayFlag);
//        break;
//    case 1://tcp client
//        P_tcpclient->setDisplayFlag(DisplayFlag);
//        break;
//    case 2://udp
//        P_udp->setDisplayFlag(DisplayFlag);
//        break;
//    case 3://com
//        P_com->setDisplayFlag(DisplayFlag);
//        break;
//    default:
//        break;
//    }
}

void MainWindow::on_ClearpushButton_clicked()
{
    ui->ViewtextEdit->setText("");
}

void MainWindow::OpenCreateUdp()
{
    ui->SendpushButton->setEnabled(false);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    ui->DisplaypushButton->setEnabled(false);
    ui->PeizhipushButton->setEnabled(true);
    ui->AutoSendcheckBox->setEnabled(false);
    ui->Statelabel->setText(tr("已打开UDP测试软件，等待配置参数！"));
    P_udp = new UDP();
    P_udp->setMainUiPoint(ui);
    //P_udp->exec();//非模态
    //form->show();//模态
}

void MainWindow::OpenCreateCOM()
{
    ui->SendpushButton->setEnabled(false);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    ui->DisplaypushButton->setEnabled(false);
    ui->PeizhipushButton->setEnabled(true);
    ui->AutoSendcheckBox->setEnabled(false);
    ui->Statelabel->setText(tr("已打开串口测试软件，等待配置参数！"));
    P_com = new COM();
    P_com->setMainUiPoint(ui);
    //P_com->exec();//非模态
    //form->show();//模态
}

void MainWindow::OpenCreateTcpClient()
{
    ui->SendpushButton->setEnabled(false);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    ui->DisplaypushButton->setEnabled(false);
    ui->PeizhipushButton->setEnabled(true);
    ui->AutoSendcheckBox->setEnabled(false);
    ui->Statelabel->setText(tr("已打开TCP客户端，等待配置参数"));
    P_tcpclient = new TcpClient();
    P_tcpclient->setMainUiPoint(ui);
    //P_tcpclient->exec();//非模态
    //form->show();//模态
}

void MainWindow::OpenCreateTcpServer()
{
    ui->SendpushButton->setEnabled(false);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    ui->DisplaypushButton->setEnabled(false);
    ui->PeizhipushButton->setEnabled(true);
    ui->AutoSendcheckBox->setEnabled(false);
    ui->Statelabel->setText(tr("已打开TCP服务器，等待配置参数！"));
    p_tcpserver = new TCPServer();
    p_tcpserver->setMainUiPoint(ui);
    //p_tcpserver->exec();//非模态
    //form->show();//模态
}

void MainWindow::on_SendpushButton_clicked()
{
    p_base->WorkSendMessage();
//    switch(style)
//    {
//    case 0://tcp server
//        p_tcpserver->sendmessage();
//        break;
//    case 1://tcp client
//        P_tcpclient->sendmessage();
//        break;
//    case 2://udp
//        P_udp->sendmessage();
//        break;
//    case 3://com
//        P_com->SendMessage();
//        break;
//    default:
//        break;
//    }
}

void MainWindow::on_AutoSendcheckBox_toggled(bool checked)
{
    if (checked)
    {
       int time = ui->timelineEdit->text().toInt();
        _time->start(time);
    }else {
        _time->stop();
    }
}

void MainWindow::SlectAutoSend()
{
    p_base->WorkSendMessage();
//    switch(style)
//    {
//    case 0://tcp server
//        p_tcpserver->sendmessage();
//        break;
//    case 1://tcp client
//        P_tcpclient->sendmessage();
//        break;
//    case 2://udp
//        P_udp->sendmessage();
//        break;
//    case 3://com
//        P_com->SendMessage();
//        break;
//    default:
//        break;
//    }
}

void MainWindow::HandleText()
{
    disconnect (ui->SendtextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
    QString AllStr = ui->SendtextEdit->toPlainText ();
    AllStr = AllStr.replace (" ","");

    QString stt;
    for(int i=0;i <AllStr.length ();i+=2)
    {
        QString ss = AllStr.mid(i,2);
        stt +=ss;

        if(i+2 >= AllStr.length ())
        {
            stt += AllStr.mid(i+2);
            break;
        }
        if(ss.length () == 2)
        {
            stt += " ";
        }
    }

    QString lastStr = stt.mid(stt.length ()-1,1);

    QRegExp regExp("[A-Fa-f0-9]{1}");//创建了一个正则表达式模式
    bool match = regExp.exactMatch(lastStr);
    if(true != match)
    {
       stt = stt.mid(0,stt.length ()-1);
    }

    stt = stt.toUpper ();
    ui->SendtextEdit->clear ();
    ui->SendtextEdit->insertPlainText (stt);
    connect (ui->SendtextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
}

void MainWindow::DeleteCreation(int index)
{
    if(p_base!=NULL)
    {
        //delete p_base;
        p_base = NULL;
    }
    switch(index)
    {
    case 0://tcp server
        if(P_com!=NULL)
        {
            delete P_com;
            P_com = NULL;
        }
        if(P_udp!=NULL)
        {
            delete P_udp;
            P_udp = NULL;
        }
        if(P_tcpclient!=NULL)
        {
            delete P_tcpclient;
            P_tcpclient = NULL;
        }
        break;
    case 1://tcp client
        if(P_com!=NULL)
        {
            delete P_com;
            P_com = NULL;
        }
        if(P_udp!=NULL)
        {
            delete P_udp;
            P_udp = NULL;
        }
        if(p_tcpserver!=NULL)
        {
            delete p_tcpserver;
            p_tcpserver = NULL;
        }
        break;
    case 2://udp
        if(P_com!=NULL)
        {
            delete P_com;
            P_com = NULL;
        }
        if(P_tcpclient!=NULL)
        {
            delete P_tcpclient;
            P_tcpclient = NULL;
        }
        if(p_tcpserver!=NULL)
        {
            delete p_tcpserver;
            p_tcpserver = NULL;
        }
        break;
    case 3://com
        if(P_udp!=NULL)
        {
            delete P_udp;
            P_udp = NULL;
        }
        if(P_tcpclient!=NULL)
        {
            delete P_tcpclient;
            P_tcpclient = NULL;
        }
        if(p_tcpserver!=NULL)
        {
            delete p_tcpserver;
            p_tcpserver = NULL;
        }
        break;
    default:
        break;
    }
}

void MainWindow::HandleStyle()
{
    style = ui->StylecomboBox->currentIndex();
    if(laststyle==style)return;
    else
    {
        DeleteCreation(style);
        WorkCreate();

        ui->AutoSendcheckBox->setChecked(false);
        ui->AutoSendcheckBox->setEnabled(false);
        ui->SendpushButton->setEnabled(false);
        ui->OpenpushButton->setEnabled(false);
        ui->ClosepushButton->setEnabled(false);
        ui->DisplaypushButton->setEnabled(false);
        ui->PeizhipushButton->setEnabled(true);
        laststyle = style;
    }
}

void MainWindow::WorkCreate()
{
    ui->SendpushButton->setEnabled(false);
    ui->OpenpushButton->setEnabled(false);
    ui->ClosepushButton->setEnabled(false);
    ui->DisplaypushButton->setEnabled(false);
    ui->PeizhipushButton->setEnabled(true);
    ui->AutoSendcheckBox->setEnabled(false);
    switch(style)
    {
    case 0://tcp server
        setWindowTitle(tr("TCP服务器"));
        ui->Statelabel->setText(tr("已打开TCP服务器，等待配置参数！"));
        p_tcpserver = new TCPServer();
        p_base = p_tcpserver;
        p_tcpserver->setMainUiPoint(ui);
        break;
    case 1://tcp client
        setWindowTitle(tr("TCP客户端"));
        ui->Statelabel->setText(tr("已打开TCP客户端，等待配置参数！"));
        P_tcpclient = new TcpClient();
        p_base = P_tcpclient;
        P_tcpclient->setMainUiPoint(ui);
        break;
    case 2://udp
        setWindowTitle(tr("UDP测试软件"));
        ui->Statelabel->setText(tr("已打开UDP，等待配置参数！"));
        P_udp = new UDP();
        P_udp->setMainUiPoint(ui);
        p_base = P_udp;
        break;
    case 3://com
        setWindowTitle(tr("串口测试软件"));
        ui->Statelabel->setText(tr("已打开串口，等待配置参数！"));
        P_com = new COM();
        p_base = P_com;
        P_com->setMainUiPoint(ui);
        break;
    default:
        break;
    }
}

void MainWindow::WorkDeleteCreation()
{
    if(p_base!=NULL)
    {
        delete p_base;
        p_base = NULL;
    }
}




