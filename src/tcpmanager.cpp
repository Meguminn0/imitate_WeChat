#include "include/tcpmanager.h"
#include <QTcpSocket>
#include <mutex>

std::once_flag tcpManager::m_singleOnceFlag;
std::shared_ptr<tcpManager> tcpManager::m_singleInstance = nullptr;

tcpManager *tcpManager::getInstance()
{
    std::call_once(m_singleOnceFlag, [&](){
        m_singleInstance.reset(new tcpManager());
    });

    return m_singleInstance.get();
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
        qDebug() << "网络连接超时....";
        return "";
    }
}

bool tcpManager::isConnected()
{
    if(m_clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void tcpManager::connectToServer()
{
    if(m_clientSocket->state() == QAbstractSocket::UnconnectedState)
    {
        m_clientSocket->connectToHost(QHostAddress("127.0.0.1"), 2024);
    }
    else
    {
        qDebug() << "服务器已连接";
    }
}

tcpManager::tcpManager(QObject *parent)
    : QObject(parent)
{
    m_clientSocket = new QTcpSocket(this);

    connectToServer();

    connect(m_clientSocket, &QTcpSocket::connected, this, [](){
        qDebug() << "连接成功";
    });
}

tcpManager::~tcpManager()
{
    if(m_clientSocket)
    {
        m_clientSocket->close();
        delete m_clientSocket;
        m_clientSocket = nullptr;
    }
}

