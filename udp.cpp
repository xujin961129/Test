#include "udp.h"
#include "ui_udp.h"

UDP::UDP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDP)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);

    getLocalIP();
    HexDisplayFlag = true;
    HexSendFlag = true;
    DisplayFlag = true;

    receiver = NULL;
    receiver = new QUdpSocket(this);
    int port = ui->UDPSenderPortlineEdit->text().toInt();

    if(receiver->bind(QHostAddress::Any,port))//�����κ�IP��ַ������

    {
        qDebug()<<"Udp client bind localhost ok!";
    }
    else
    {
        qDebug()<<"Udp client bind localhost failed!";
    }
    connect(receiver,SIGNAL(readyRead()),this,SLOT(ReadAndDisplayMessage()));
}

UDP::~UDP()
{
    delete ui;
}

void UDP::sendmessage()
{
    if(receiver == NULL) return;
    QByteArray datagram;
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    datagram = sdata.toUtf8().data();
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

void UDP::getLocalIP()
{
    IPlist = QNetworkInterface::allAddresses();

    foreach(QHostAddress IP, IPlist)
    {
        ui->UDPServerIPcomboBox->addItem(IP.toString());
    }
}

void UDP::BindUDPSocket()
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
    connect(receiver,SIGNAL(readyRead()),this,SLOT(ReadAndDisplayMessage()));
    main_ui->SendpushButton->setEnabled(true);
}

void UDP::DisBindUDPSocket()
{
    if(receiver == NULL)return;
    disconnect(receiver,SIGNAL(readyRead()),this,SLOT(ReadAndDisplayMessage()));
    receiver->disconnectFromHost();
    receiver->close();
    receiver = NULL;
    main_ui->SendpushButton->setEnabled(false);
    main_ui->Statelabel->setText(tr("UDPֹͣ����!"));
    ui->UDPServerStatelabel->setText(tr("UDPֹͣ����!"));
}

void UDP::ReadAndDisplayMessage()
{
    if(receiver == NULL) return;

    while(receiver->hasPendingDatagrams())//ӵ�еȴ������ݱ�
    {
        QByteArray datagram;//���ڴ�Ž��յ����ݱ�
        datagram.resize(receiver->pendingDatagramSize());
         //��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������

        QHostAddress senderAddress;
        quint16 senderPort;
        receiver->readDatagram(datagram.data(), datagram.size(),
                                &senderAddress, &senderPort);
        //�������ݱ��������ŵ�datagram��,senderAddress��senderPort�ֱ��ŷ����ߵ�IP��ַ�Ͷ˿ں�
        QString sPort = QString::number(senderPort);
        QString sAddress = senderAddress.toString();
        main_ui->ViewtextEdit->moveCursor(QTextCursor::Start,QTextCursor::MoveAnchor);
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
            main_ui->ViewtextEdit->insertPlainText(tr("From:%1:%2|%3").arg(sAddress).arg(sPort).arg(stt)+"\n");
            //qDebug()<<str;
        }
        else
        main_ui->ViewtextEdit->insertPlainText(tr("From:%1:%2|").arg(sAddress).arg(sPort)+datagram+"\n");
    }
}

void UDP::sendmessageslot()
{
    sendmessage();
}


void UDP::on_OKpushButton_clicked()
{
    BindUDPSocket();
    this->close();
}

bool UDP::WorkOpen()
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
    connect(receiver,SIGNAL(readyRead()),this,SLOT(ReadAndDisplayMessage()));
    main_ui->SendpushButton->setEnabled(true);
    return true;
}

void UDP::WorkClose()
{
    if(receiver == NULL)return;
    disconnect(receiver,SIGNAL(readyRead()),this,SLOT(ReadAndDisplayMessage()));
    receiver->disconnectFromHost();
    receiver->close();
    receiver = NULL;
    main_ui->SendpushButton->setEnabled(false);
    main_ui->Statelabel->setText(tr("UDPֹͣ����!"));
    ui->UDPServerStatelabel->setText(tr("UDPֹͣ����!"));
}

void UDP::WorkSendMessage()
{
    if(receiver == NULL) return;
    QByteArray datagram;
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    datagram = sdata.toUtf8().data();
    //datagram = QByteArray::fromHex (sdata.toLatin1 ().data ());UDPFarIP

    int port = ui->UDPFarPortlineEdit->text().toInt();
    QString add = ui->UDPFarIPlineEdit->text();
    QHostAddress IP;
    IP.setAddress(add);
//    if(true==HexSendFlag)
//    {
//        QByteArray aa = QByteArray::fromHex (sdata.toLatin1 ().data ());
//        sender->writeDatagram(aa.data(),aa.size(),IP,port);
//    }
//    else
        sender->writeDatagram(datagram.data(),datagram.size(),IP,port);
}
