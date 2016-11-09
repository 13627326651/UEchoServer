#ifndef UECHOSERVER_H
#define UECHOSERVER_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>

class UEchoServer : public QWidget
{
    Q_OBJECT

public:
    UEchoServer(QWidget *parent = 0);
    ~UEchoServer();
private slots:
    void closeWindow();
    void readMessage();
private:
    void socketCreate();
    QTextEdit *textEdit;
    QPushButton *closeBtn;
    QUdpSocket *socket;
    quint16 port;
};

#endif // UECHOSERVER_H
