#include "com.h"
#include "ui_com.h"
#include <QDebug>
#include <QMessageBox>

COM::COM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COM)
{
    ui->setupUi(this);
    DisplayFlag = true;
    myCom = NULL;
}

COM::~COM()
{
    delete ui;
}

void COM::readMyCom()//读串口函数
{
    QByteArray temp = myCom->readAll();

    //读取串口缓冲区的所有数据给临时变量temp
    if(true==DisplayFlag)
    {
//        ui->textBrowser->insertPlainText(temp);
//        //将串口的数据显示在窗口的文本浏览器中
        //QByteArray to qstring start
        QString str = temp.toHex ().data ();
        //qDebug()<<str;
        str = str.toUpper ();
        QString stt;
        for(int i = 0;i<str.length ();i+=2)
        {
            QString st = str.mid (i,2);
            stt += st;
            stt += " ";
        }//QByteArray to qstring end             // str == "3f"
        //main_ui->ViewtextEdit->insertPlainText(stt+"\n");
        main_ui->ViewtextEdit->insertPlainText(stt);
    }
}

bool COM::OpenSerialCom()
{
    //struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,
    //500}; //定义一个结构体，用来存放串口各个参数
    QString portName = ui->portNameComboBox->currentText();  //
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    bool flag = myCom  ->open(QIODevice::ReadWrite);
    if(false==flag)
    {
        QMessageBox::warning(this,tr("Warning"),tr("串口不存在或已被占用!"),QMessageBox::Yes);
        main_ui->Statelabel->setText(tr("串口不存在或已被占用!"));
        return false;
    }
    //以可读写方式打开串口
    if(ui->baudRateComboBox->currentText()==tr("9600"))  //
    myCom->setBaudRate(BAUD9600);
    else  if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else  if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7);
    if(ui->parityComboBox->currentText()==tr("无"))
    myCom->setParity(PAR_NONE);
    else  if(ui->parityComboBox->currentText()==tr("奇"))
    myCom->setParity(PAR_ODD);
    else  if(ui->parityComboBox->currentText()==tr("偶"))
    myCom->setParity(PAR_EVEN);
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else  if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(500);

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //当串口缓冲区有数据时，进行读串口操作
//    ui->openMyComBtn->setEnabled(false);
//    ui->closeMyComBtn->setEnabled(true);
//    ui->sendMsgBtn->setEnabled(true);

    ui->baudRateComboBox->setEnabled(false);  //
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->portNameComboBox->setEnabled(false);
    return true;
}

void COM::CloseSerialCom()
{
    myCom->close();  //
//    ui->openMyComBtn->setEnabled(true);
//    ui->closeMyComBtn->setEnabled(false);
//    ui->sendMsgBtn->setEnabled(false);  //

    ui->baudRateComboBox->setEnabled(true);
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->portNameComboBox->setEnabled(true);
}


void COM::on_OKpushButton_clicked()
{
    if( myCom != NULL)
        delete myCom;
    OpenSerialCom();
    this->close();
}

void COM::SendMessage()
{
    if(!(myCom->isOpen()))return;
    //QByteArray datagram;
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    //datagram = sdata.toAscii().data();
    QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());
    //qDebug()<<"aa:"<<aa;
    //myCom->write(sdata.toAscii());
    myCom->write(aa);
}

bool COM::WorkOpen()
{
    //struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,
    //500}; //定义一个结构体，用来存放串口各个参数
    QString portName = ui->portNameComboBox->currentText();  //
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    bool flag = myCom  ->open(QIODevice::ReadWrite);
    if(false==flag)
    {
        QMessageBox::warning(this,tr("Warning"),tr("串口不存在或已被占用!"),QMessageBox::Yes);
        main_ui->Statelabel->setText(tr("串口不存在或已被占用!"));
        return false;
    }
    //以可读写方式打开串口
    if(ui->baudRateComboBox->currentText()==tr("9600"))  //
    myCom->setBaudRate(BAUD9600);
    else  if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else  if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7);
    if(ui->parityComboBox->currentText()==tr("无"))
    myCom->setParity(PAR_NONE);
    else  if(ui->parityComboBox->currentText()==tr("奇"))
    myCom->setParity(PAR_ODD);
    else  if(ui->parityComboBox->currentText()==tr("偶"))
    myCom->setParity(PAR_EVEN);
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else  if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(500);

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //当串口缓冲区有数据时，进行读串口操作
//    ui->openMyComBtn->setEnabled(false);
//    ui->closeMyComBtn->setEnabled(true);
//    ui->sendMsgBtn->setEnabled(true);

    ui->baudRateComboBox->setEnabled(false);  //
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->portNameComboBox->setEnabled(false);
    return true;
}

void COM::WorkClose()
{
    myCom->close();  //
    main_ui->Statelabel->setText(tr("已关闭串口测试软件！"));
//    ui->openMyComBtn->setEnabled(true);
//    ui->closeMyComBtn->setEnabled(false);
//    ui->sendMsgBtn->setEnabled(false);  //

    ui->baudRateComboBox->setEnabled(true);
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->portNameComboBox->setEnabled(true);
}

void COM::WorkSendMessage()
{
    if(!(myCom->isOpen()))return;
    //QByteArray datagram;
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    //datagram = sdata.toAscii().data();
    QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());
    //qDebug()<<"aa:"<<aa;
    //myCom->write(sdata.toAscii());
    myCom->write(aa);
}
