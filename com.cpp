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

void COM::readMyCom()//�����ں���
{
    QByteArray temp = myCom->readAll();

    //��ȡ���ڻ��������������ݸ���ʱ����temp
    if(true==DisplayFlag)
    {
//        ui->textBrowser->insertPlainText(temp);
//        //�����ڵ�������ʾ�ڴ��ڵ��ı��������
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
    //500}; //����һ���ṹ�壬������Ŵ��ڸ�������
    QString portName = ui->portNameComboBox->currentText();  //
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
    //���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��
    bool flag = myCom  ->open(QIODevice::ReadWrite);
    if(false==flag)
    {
        QMessageBox::warning(this,tr("Warning"),tr("���ڲ����ڻ��ѱ�ռ��!"),QMessageBox::Yes);
        main_ui->Statelabel->setText(tr("���ڲ����ڻ��ѱ�ռ��!"));
        return false;
    }
    //�Կɶ�д��ʽ�򿪴���
    if(ui->baudRateComboBox->currentText()==tr("9600"))  //
    myCom->setBaudRate(BAUD9600);
    else  if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else  if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7);
    if(ui->parityComboBox->currentText()==tr("��"))
    myCom->setParity(PAR_NONE);
    else  if(ui->parityComboBox->currentText()==tr("��"))
    myCom->setParity(PAR_ODD);
    else  if(ui->parityComboBox->currentText()==tr("ż"))
    myCom->setParity(PAR_EVEN);
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else  if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(500);

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //�����ڻ�����������ʱ�����ж����ڲ���
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
    //500}; //����һ���ṹ�壬������Ŵ��ڸ�������
    QString portName = ui->portNameComboBox->currentText();  //
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
    //���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��
    bool flag = myCom  ->open(QIODevice::ReadWrite);
    if(false==flag)
    {
        QMessageBox::warning(this,tr("Warning"),tr("���ڲ����ڻ��ѱ�ռ��!"),QMessageBox::Yes);
        main_ui->Statelabel->setText(tr("���ڲ����ڻ��ѱ�ռ��!"));
        return false;
    }
    //�Կɶ�д��ʽ�򿪴���
    if(ui->baudRateComboBox->currentText()==tr("9600"))  //
    myCom->setBaudRate(BAUD9600);
    else  if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else  if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7);
    if(ui->parityComboBox->currentText()==tr("��"))
    myCom->setParity(PAR_NONE);
    else  if(ui->parityComboBox->currentText()==tr("��"))
    myCom->setParity(PAR_ODD);
    else  if(ui->parityComboBox->currentText()==tr("ż"))
    myCom->setParity(PAR_EVEN);
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else  if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(500);

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //�����ڻ�����������ʱ�����ж����ڲ���
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
    main_ui->Statelabel->setText(tr("�ѹرմ��ڲ��������"));
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
