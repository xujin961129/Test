#include <QMessageBox>
#include "tcpserver.h"
#include "ui_tcpserver.h"

TCPServer::TCPServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TCPServer)
{
    ui->setupUi(this);
    tcpserver = new QTcpServer(this);
    connect (tcpserver, SIGNAL(newConnection()), this, SLOT(updateserver()));

    linkList.clear();
    showbox = true;
    initListen();
}

TCPServer::~TCPServer()
{
    delete ui;
}

void TCPServer::on_OKpushButton_clicked()
{
    serverStoplisten();
    serverlisten();
    this->close();
}

void TCPServer::sendmessage()
{
    if(linkList.count() == 0)
        return;
    QTcpSocket* client = 0;
    foreach(QTcpSocket* s,linkList)
    {
        if(!s) continue;
        client = s;
        if(!client) return;

        QString sdata= main_ui->SendtextEdit->toPlainText();
        if(sdata.isEmpty())return;
        //datagram = sdata.toAscii().data();
        QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());
        client->write(aa);
    }
}

void TCPServer::serverlisten()
{
    serverPort = ui->serverPortlineEdit->text();

    if(serverPort.isEmpty ())
    {
        QMessageBox::warning (this, tr("���棺"), tr("�˿�Ϊ�գ�"));
        return;
    }
    if(!tcpserver) return;
    tcpserver->listen (QHostAddress::Any, serverPort.toInt());

    main_ui->Statelabel->setText(tr("��ʼ����"));
    //    ui->serverlistenpushButton->setEnabled(false);
    //    ui->stoppushButton->setEnabled(true);
}

void TCPServer::serverStoplisten()
{
    foreach(QTcpSocket* st ,linkList)
    {
        if(!st) continue;

        st->disconnect();
        st->close();
        st->deleteLater();
    }

    tcpserver->close();
    main_ui->Statelabel->setText(tr("ֹͣ����"));
    //    ui->serverlistenpushButton->setEnabled(true);
    //    ui->stoppushButton->setEnabled(false);
    //    ui->serverSendpushButton->setEnabled(false);

    linkList.clear();

    updataWidgetList();
}

void TCPServer::updateserver()
{
    main_ui->Statelabel->setText(tr("������"));
    //ui->serverSendpushButton->setEnabled(true);
    QTcpSocket *tcpclient = tcpserver->nextPendingConnection ();
    if(!tcpclient) return;

    QString clientip = tcpclient->peerAddress().toString();
    // ���ɽ��ܵ�Ip���Ͽ�������
    if(clientip.isNull() || clientip.isEmpty())
    {
        tcpclient->disconnectFromHost();
        return;
    }

    linkList.append(tcpclient);

    connect (tcpclient, SIGNAL(disconnected()), this, SLOT(updateSendStatus()));
    connect (tcpclient, SIGNAL(readyRead()), this, SLOT(serverReadMessage()));

    updataWidgetList();
}

void TCPServer::updataWidgetList()
{
    //int count = linkList.count();
    //ui->connectStatlineEdit->setText(QString::number(count));

    foreach(QTcpSocket* st,linkList)
    {
        if(!st) continue;

        QString name = st->peerName();
        QString ip = st->peerAddress().toString();



    }
}

//������
void TCPServer::updateSendStatus()
{
    main_ui->Statelabel->setText(tr("������"));
    //ui->serverSendpushButton->setEnabled(false);

    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    linkList.removeOne(client);
    client->disconnect();
    client->close();
    client->deleteLater();

    updataWidgetList();
}

void TCPServer::serverReadMessage()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if(!client) return;
    QByteArray byte_data=client->readAll();
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
        QString stIP = client->peerAddress().toString();
        quint16 intport = client->peerPort();
        QString stPort = QString::number(intport);

        main_ui->ViewtextEdit->append(tr("�ԡ�%1:%2��:%3").arg(stIP).arg(stPort).arg(stt));
    }
}

void TCPServer::initListen()
{
    serverPort = ui->serverPortlineEdit->text();

    if(serverPort.isEmpty ())
    {
        QMessageBox::warning (this, tr("���棺"), tr("�˿�Ϊ�գ�"));
        return;
    }
    if(!tcpserver) return;
    tcpserver->listen (QHostAddress::Any, serverPort.toInt());
}


bool TCPServer::WorkOpen()
{
    serverPort = ui->serverPortlineEdit->text();

    if(serverPort.isEmpty ())
    {
        QMessageBox::warning (this, tr("���棺"), tr("�˿�Ϊ�գ�"));
        return false;
    }
    if(!tcpserver) return false;
    tcpserver->listen (QHostAddress::Any, serverPort.toInt());

    main_ui->Statelabel->setText(tr("��ʼ����"));
    return true;
}

void TCPServer::WorkClose()
{
    foreach(QTcpSocket* st ,linkList)
    {
        if(!st) continue;

        st->disconnect();
        st->close();
        st->deleteLater();
    }

    tcpserver->close();
    main_ui->Statelabel->setText(tr("ֹͣ����"));
    //    ui->serverlistenpushButton->setEnabled(true);
    //    ui->stoppushButton->setEnabled(false);
    //    ui->serverSendpushButton->setEnabled(false);

    linkList.clear();

    updataWidgetList();
}

void TCPServer::WorkSendMessage()
{
    if(linkList.count() == 0)
        return;
    QTcpSocket* client = 0;
    foreach(QTcpSocket* s,linkList)
    {
        if(!s) continue;
        client = s;
        if(!client) return;

        QString sdata= main_ui->SendtextEdit->toPlainText();
        if(sdata.isEmpty())return;
        //datagram = sdata.toAscii().data();
        QByteArray aa = QByteArray::fromHex (sdata.toLatin1().data());
        client->write(aa);
    }
}
