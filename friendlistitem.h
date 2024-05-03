/******************************************************
 *
 * @file            friendlistitem.h
 * @briefly-Cn      好友列表表项
 * @briefly-En      Friends list table entries
 *
 * @author          Meguminn0
 * @date            2024/05/03
 * @history
 *
********************************************************/

#ifndef FRIENDLISTITEM_H
#define FRIENDLISTITEM_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class friendlistItem : public QWidget
{
    Q_OBJECT
public:
    explicit friendlistItem(QWidget *parent = nullptr);
    void setFriendId(QString id);

protected:
    void init();
    QPixmap getFriendHeadPix(QString friendId);
    QString getFriendName(QString friendId);

signals:

private:
    QString m_friendId;

    QHBoxLayout *m_layout;
    QVBoxLayout *m_rightLayout;
    QHBoxLayout *m_rightTopLayout;

    QLabel *m_friendHead;
    QLabel *m_friendName;
    QLabel *m_lastMessage;
    QLabel *m_lastChatTime;
};

#endif // FRIENDLISTITEM_H
