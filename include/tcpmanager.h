#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <mutex>

class tcpManager : public QObject
{
public:
    ~tcpManager();
    static tcpManager *getInstance();

    int64_t sendData(QString data);
    QByteArray receptionData();

    bool isConnected();
    void connectToServer();

protected:

private:
    tcpManager(QObject *parent = nullptr);
    tcpManager(const tcpManager &tcpMgr) = delete;
    const tcpManager& operator=(const tcpManager &tcpMgr) = delete;

signals:

private:
    static std::once_flag m_singleOnceFlag;
    static std::shared_ptr<tcpManager> m_singleInstance;
    QTcpSocket *m_clientSocket;
};

#endif // TCPMANAGER_H
