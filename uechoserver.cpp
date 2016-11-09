#include "uechoserver.h"
#include <QMessageBox>
#include <QVBoxLayout>

UEchoServer::UEchoServer(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("回声服务器端"));

    textEdit = new QTextEdit;
    closeBtn = new QPushButton(tr("关闭"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(closeBtn);

    port = 9999;
    connect(closeBtn,SIGNAL(clicked(bool)),this,SLOT(closeWindow()));

    socketCreate();


}

UEchoServer::~UEchoServer()
{

}

void UEchoServer::closeWindow()
{
    close();
}

void UEchoServer::readMessage()
{
    if(socket->hasPendingDatagrams())
    {
        QHostAddress clntAddr;
        quint16 clntPort;
        QByteArray dataGram;
        dataGram.resize(socket->pendingDatagramSize());

        socket->readDatagram(dataGram.data(),dataGram.size(),&clntAddr,&clntPort);
        QString msg = dataGram.data();
        textEdit->append(msg);

        socket->writeDatagram(dataGram,clntAddr,clntPort);
    }
}
void UEchoServer::socketCreate()
{
   socket = new QUdpSocket;
   if(!socket->bind(QHostAddress::Any,port))
   {
      QMessageBox::information(this,tr("出错"),tr("绑定地址和端口出错"));
      return;
   }
   connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}
