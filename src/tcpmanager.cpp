#include "include/tcpmanager.h"
#include <QTcpSocket>

tcpManager::tcpManager(QObject *parent)
    : QObject(parent)
{
    m_clientSocket = new QTcpSocket(this);
    unsigned int port = 2024;
    m_clientSocket->connectToHost(QHostAddress("127.0.0.1"), port);

    connect(m_clientSocket, &QTcpSocket::connected, this, [](){
        qDebug() << "连接成功";
    });
}

tcpManager::~tcpManager()
{
    m_clientSocket->close();
}

int64_t tcpManager::sendData(QString data)
{
    if(m_clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        return m_clientSocket->write(data.toUtf8());
    }
    else
    {
        qDebug() << "error socket is disconnected";
        return -1;
    }
}

QByteArray tcpManager::receptionData()
{
    if(m_clientSocket->waitForReadyRead(5000))
    {
        return m_clientSocket->readAll();
    }
    else
    {
        return "";
    }
}

