#include "udpserverform.h"
#include <QDebug>

UDPServerForm::UDPServerForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDPServerForm)
{
    ui->setupUi(this);
    connect(ui->UDPSendertextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
    sender = new QUdpSocket(this);

    getLocalIP();
    HexDisplayFlag = false;
    HexSendFlag = false;
    DisplayFlag = true;
    //ui->BroadcastpushButton->setEnabled(false);

    _time = new QTimer();
    _time->setInterval(2000);
    connect(_time,SIGNAL(timeout()),this,SLOT(sendmessageslot()));

    receiver = NULL;
    receiver = new QUdpSocket(this);
    int port = ui->UDPSenderPortlineEdit->text().toInt();
//    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
//    QHostAddress address=info.addresses().first();

    if(receiver->bind(QHostAddress::Any,port))//�����κ�IP��ַ������

    {
        qDebug()<<"Udp client bind localhost ok!";
    }
    else
    {
        qDebug()<<"Udp client bind localhost failed!";
    }
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
//    connect(receiver,SIGNAL(disconnected()),receiver,SLOT(disconnectFromHostImplementation()));

//    connect(ui->UDPServerIPcomboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(BindUDPSocket()));
//    connect(ui->UDPSenderPortlineEdit,SIGNAL(textChanged(QString)),this,SLOT(BindUDPSocket()));

    ui->udpReceivetextEdit->setReadOnly(true);//textChanged(QString)

}

UDPServerForm::~UDPServerForm()
{
    delete _time;
    delete ui;
}

void UDPServerForm::getLocalIP ()
{
    IPlist = QNetworkInterface::allAddresses();

    foreach(QHostAddress IP, IPlist)
    {
        ui->UDPServerIPcomboBox->addItem(IP.toString());
    }
}
//���͡���ť�ĵ����¼��ۺ���
void UDPServerForm::on_BroadcastpushButton_clicked()
{
    sendmessage();
}

void UDPServerForm::on_UDPSendAutocheckBox_toggled(bool checked)
{
    if (checked)
    {
       int time = ui->timelineEdit->text().toInt();
        _time->start(time);
    }else {
        _time->stop();
    }
}

void UDPServerForm::sendmessageslot()
{
    sendmessage();
}

void UDPServerForm::sendmessage()
{
    if(receiver == NULL) return;
    QByteArray datagram;
    QString sdata= ui->UDPSendertextEdit->toPlainText();
    datagram = sdata.toAscii().data();
    //datagram = QByteArray::fromHex (sdata.toLatin1 ().data ());UDPFarIP

    int port = ui->UDPFarPortlineEdit->text().toInt();
    QString add = ui->UDPFarIPlineEdit->text();
    QHostAddress IP;
    IP.setAddress(add);
    if(true==HexSendFlag)
    {
        QByteArray aa = QByteArray::fromHex (sdata.toLatin1 ().data ());
        sender->writeDatagram(aa.data(),aa.size(),IP,port);
    }
    else
    sender->writeDatagram(datagram.data(),datagram.size(),IP,port);
}

//���ݽ��ռ���ʾ�ۺ���
void UDPServerForm::processPendingDatagram()
{
    if(receiver == NULL) return;
    //int port = ui->UDPFarPortlineEdit->text().toInt();
//    QString  name = receiver->peerName();
//    qDebug()<< name;

    while(receiver->hasPendingDatagrams())//ӵ�еȴ������ݱ�
    {
        QByteArray datagram;//���ڴ�Ž��յ����ݱ�
        datagram.resize(receiver->pendingDatagramSize());
         //��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������
//        receiver->readDatagram(datagram.data(),datagram.size());

        QHostAddress senderAddress;
        quint16 senderPort;
//        quint16 senderPort = ui->UDPSenderPortlineEdit->text().toShort();
        receiver->readDatagram(datagram.data(), datagram.size(),
                                &senderAddress, &senderPort);
        //�������ݱ��������ŵ�datagram��,senderAddress��senderPort�ֱ��ŷ����ߵ�IP��ַ�Ͷ˿ں�
        QString sPort = QString::number(senderPort);
        QString sAddress = senderAddress.toString();
        ui->udpReceivetextEdit->moveCursor(QTextCursor::Start,QTextCursor::MoveAnchor);
        //����ƶ�����ʼ��
        if(false==DisplayFlag) return;
        if(true==HexDisplayFlag)//16������ʾ
        {
            //QByteArray to qstring start
            QString str = datagram.toHex ().data ();
            str = str.toUpper ();
            QString stt;
            for(int i = 0;i<str.length ();i+=2)
            {
                QString st = str.mid (i,2);
                stt += st;
                stt += " ";
            }//QByteArray to qstring end             // str == "3f"
            ui->udpReceivetextEdit->insertPlainText(tr("From:%1:%2|%3").arg(sAddress).arg(sPort).arg(stt)+"\n");
            //qDebug()<<str;
        }
        else
        ui->udpReceivetextEdit->insertPlainText(tr("From:%1:%2|").arg(sAddress).arg(sPort)+datagram+"\n");
    }
}

void UDPServerForm::BindUDPSocket()
{
    if(receiver)
    {
        receiver->close();
        receiver = NULL;
    }
    receiver = new QUdpSocket(this);

    int port = ui->UDPSenderPortlineEdit->text().toInt();
    QHostAddress address;
    address = ui->UDPServerIPcomboBox->currentText();
    qDebug()<<address;

    if(receiver->bind(QHostAddress::Any,port))//�����κ�IP��ַ������

    {
        qDebug()<<"Udp client bind localhost ok!";
        ui->UDPServerStatelabel->setText(tr("Udp client bind localhost ok!"));
    }
    else
    {
        qDebug()<<"Udp client bind localhost failed!";
        ui->UDPServerStatelabel->setText(tr("Udp client bind localhost failed!"));
    }
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    ui->BroadcastpushButton->setEnabled(true);

    QString add,sip,ssip;
//    QHostAddress IP = receiver->peerAddress();
//    receiver->peek()
    add = receiver->peerAddress().toString();
    sip = sender->peerAddress().toString();
    ssip = receiver->localAddress().toString();
    port = receiver->peerPort();
    qDebug()<<tr("add:")<<add;
    qDebug()<<tr("sip:")<<sip;
    qDebug()<<tr("port:")<<port;
    qDebug()<<tr("ssip:")<<ssip;
}

void UDPServerForm::DisBindUDPSocket()
{
    disconnect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    receiver->disconnectFromHost();
    receiver->close();
    receiver = NULL;
    ui->BroadcastpushButton->setEnabled(false);
    ui->UDPServerStatelabel->setText(tr("ֹͣ����!"));
}

void UDPServerForm::on_UDPServerClearpushButton_clicked()
{
    ui->udpReceivetextEdit->setText("");
}


void UDPServerForm::closeEvent(QCloseEvent *e)
{
    emit(closef());
}

//16������ʾ
void UDPServerForm::on_HexDisplaycheckBox_toggled(bool checked)
{
    if (checked)
    {
       HexDisplayFlag = true;
    }else
    {
        HexDisplayFlag = false;
    }
}

//16���Ʒ���
void UDPServerForm::on_HexSendcheckBox_toggled(bool checked)
{
    if (checked)
    {
       HexSendFlag = true;
    }else
    {
        HexSendFlag = false;
    }
}

void UDPServerForm::on_UDPDisplayBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->UDPDisplayBtn->setText(tr("������ʾ"));
        DisplayFlag = false;
    }
    else
    {
        ui->UDPDisplayBtn->setText(tr("ֹͣ��ʾ"));
        DisplayFlag = true;
    }
}


//������ť
void UDPServerForm::on_UDPListenpushButton_clicked(bool checked)
{
    if(checked)
    {
        ui->UDPListenpushButton->setText(tr("ֹͣ����"));
        BindUDPSocket();
    }
    else
    {
        ui->UDPListenpushButton->setText(tr("��ʼ����"));
        DisBindUDPSocket();
    }
}

void UDPServerForm::HandleText()
{
    disconnect (ui->UDPSendertextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
    QString AllStr = ui->UDPSendertextEdit->toPlainText ();
    AllStr = AllStr.replace (" ","");

    qDebug () <<"��A��"<<AllStr;
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
    qDebug () <<"��S��" <<stt;

    QString lastStr = stt.mid(stt.length ()-1,1);

    QRegExp regExp("[A-Fa-f0-9]{1}");//������һ��������ʽģʽ
    bool match = regExp.exactMatch(lastStr);
    if(true != match)
    {
       stt = stt.mid(0,stt.length ()-1);
    }

    stt = stt.toUpper ();
    ui->UDPSendertextEdit->clear ();
    ui->UDPSendertextEdit->insertPlainText (stt);
    connect (ui->UDPSendertextEdit,SIGNAL(textChanged()),this,SLOT(HandleText()));
}


