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

//断开连接
void TcpClient::ClientDisconnect()
{
    tcplink->disconnectFromHost();
}

//连接
void TcpClient::ClientConnect()
{
    serverIP = ui->clientIPlineEdit->text();
    serverPort = ui->clientPortlineEdit->text();
    if(serverIP.isEmpty()||serverPort.isEmpty())
    {
        QMessageBox::warning (this,tr("警告："),tr("IP或端口为空！"));
        return;
    }
    tcplink = new QTcpSocket(this);

    tcplink->connectToHost(serverIP,serverPort.toInt());

    connect(tcplink, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcplink, SIGNAL(connected()), this, SLOT(updateclient()));
    connect(tcplink, SIGNAL(readyRead()), this, SLOT(clientReadMessage()));
}

//客户端无连接
void TcpClient::displayError(QAbstractSocket::SocketError)
{
    //QMessageBox::warning(this,tr("警告："),tr("未发现连接！"));
    tcplink->close();
    main_ui->OpenpushButton->setEnabled(true);
    main_ui->ClosepushButton->setEnabled(false);
    main_ui->SendpushButton->setEnabled(false);
    main_ui->Statelabel->setText(tr("未发现连接！"));
}

//客户端读取消息
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

        main_ui->ViewtextEdit->append(tr("自【%1:%2】:%3").arg(stIP).arg(stPort).arg(stt));
        //main_ui->ViewtextEdit->insertPlainText(stt);
    }

}

//已连接上服务器
void TcpClient::updateclient()
{
    main_ui->Statelabel->setText(tr("已连接"));
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
        QMessageBox::warning (this,tr("警告："),tr("IP或端口为空！"));
        return false;
    }
    tcplink = new QTcpSocket(this);

    tcplink->connectToHost(serverIP,serverPort.toInt());
    main_ui->Statelabel->setText(tr("已连接！"));

    connect(tcplink, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcplink, SIGNAL(connected()), this, SLOT(updateclient()));
    connect(tcplink, SIGNAL(readyRead()), this, SLOT(clientReadMessage()));
    return true;
}

void TcpClient::WorkClose()
{
    tcplink->disconnectFromHost();
    main_ui->Statelabel->setText(tr("断开连接！"));
}

void TcpClient::WorkSendMessage()
{
    QString sdata= main_ui->SendtextEdit->toPlainText();
    if(sdata.isEmpty())return;
    //datagram = sdata.toAscii().data();
    QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());

    tcplink->write(aa);
}
