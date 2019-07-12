#include <QMessageBox>
#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    tcplink = NULL;
    showbox = true;
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_OKpushButton_clicked()
{
    ClientConnect();
    this->close();
}

void TcpClient::sendmessage()
{
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    //datagram = sdata.toAscii().data();
    QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());

    tcplink->write(aa);
}

//�Ͽ�����
void TcpClient::ClientDisconnect()
{
    tcplink->disconnectFromHost();
}

//����
void TcpClient::ClientConnect()
{
    serverIP = ui->clientIPlineEdit->text();
    serverPort = ui->clientPortlineEdit->text();
    if(serverIP.isEmpty()||serverPort.isEmpty())
    {
        QMessageBox::warning (this,tr("���棺"),tr("IP��˿�Ϊ�գ�"));
        return;
    }
    tcplink = new QTcpSocket(this);

    tcplink->connectToHost(serverIP,serverPort.toInt());

    connect(tcplink, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcplink, SIGNAL(connected()), this, SLOT(updateclient()));
    connect(tcplink, SIGNAL(readyRead()), this, SLOT(clientReadMessage()));
}

//�ͻ���������
void TcpClient::displayError(QAbstractSocket::SocketError)
{
    //QMessageBox::warning(this,tr("���棺"),tr("δ�������ӣ�"));
    tcplink->close();
    main_ui->OpenpushButton->setEnabled(true);
    main_ui->ClosepushButton->setEnabled(false);
    main_ui->SendpushButton->setEnabled(false);
    main_ui->Statelabel->setText(tr("δ�������ӣ�"));
}

//�ͻ��˶�ȡ��Ϣ
void TcpClient::clientReadMessage()
{
    QByteArray byte_data=tcplink->readAll();
    QString str = byte_data.toHex().data();
    str = str.toUpper ();
    QString stt;
    for(int i = 0;i<str.length ();i+=2)
    {
        QString st = str.mid (i,2);
        stt += st;
        stt += " ";
    }

    if(showbox == true)
    {
        quint16 intPort = tcplink->peerPort();
        QString stPort = QString::number(intPort);

        QString stIP = tcplink->peerAddress().toString();

        main_ui->ViewtextEdit->append(tr("�ԡ�%1:%2��:%3").arg(stIP).arg(stPort).arg(stt));
        //main_ui->ViewtextEdit->insertPlainText(stt);
    }

}

//�������Ϸ�����
void TcpClient::updateclient()
{
    main_ui->Statelabel->setText(tr("������"));
    main_ui->OpenpushButton->setEnabled(false);
    main_ui->ClosepushButton->setEnabled(true);
    main_ui->SendpushButton->setEnabled(true);
}



bool TcpClient::WorkOpen()
{
    serverIP = ui->clientIPlineEdit->text();
    serverPort = ui->clientPortlineEdit->text();
    if(serverIP.isEmpty()||serverPort.isEmpty())
    {
        QMessageBox::warning (this,tr("���棺"),tr("IP��˿�Ϊ�գ�"));
        return false;
    }
    tcplink = new QTcpSocket(this);

    tcplink->connectToHost(serverIP,serverPort.toInt());
    main_ui->Statelabel->setText(tr("�����ӣ�"));

    connect(tcplink, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcplink, SIGNAL(connected()), this, SLOT(updateclient()));
    connect(tcplink, SIGNAL(readyRead()), this, SLOT(clientReadMessage()));
    return true;
}

void TcpClient::WorkClose()
{
    tcplink->disconnectFromHost();
    main_ui->Statelabel->setText(tr("�Ͽ����ӣ�"));
}

void TcpClient::WorkSendMessage()
{
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    //datagram = sdata.toAscii().data();
    QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());

    tcplink->write(aa);
}
