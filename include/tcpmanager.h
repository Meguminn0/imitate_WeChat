#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <QObject>
#include <QTcpSocket>

class tcpManager : public QObject
{
public:
    tcpManager(QObject *parent);
    ~tcpManager();

    int64_t sendData(QString data);
    QByteArray receptionData();

    bool isConnected();
    void connectToServer();

signals:

private:
    QTcpSocket *m_clientSocket;
};

#endif // TCPMANAGER_H
