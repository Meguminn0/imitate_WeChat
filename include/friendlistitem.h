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

#define LEFT_MARGIN 10
#define TOP_MARGIN 7
#define RIGHT_MARGIN 20
#define BOTTOM_MARGIN 10
#define SPACING 10

class friendlistItem : public QWidget
{
    Q_OBJECT
public:
    explicit friendlistItem(QWidget *parent = nullptr);
    void setFriendId(const QString& id);

protected:
    void init();
    QPixmap getFriendHeadPix();

    void setFriendName();
    QSize getFriendNameSize();

    void setLastMsg();
    QSize getLastMsgSize();

    void setLastChatTime();
    QSize getLastChatTimeSize();

signals:

private:
    QString m_friendId;
    QString m_friendName;
    QString m_lastMsg;
    QString m_lastChatTime;

    QHBoxLayout *m_layout;
    QVBoxLayout *m_leftLayout;
    QVBoxLayout *m_rightLayout;
    QHBoxLayout *m_rightTopLayout;
    QHBoxLayout *m_rightBottomLayout;

    QLabel *m_friendHeadLabel;
    QLabel *m_friendNameLabel;
    QLabel *m_lastMessageLabel;
    QLabel *m_lastChatTimeLabel;
};

#endif // FRIENDLISTITEM_H
