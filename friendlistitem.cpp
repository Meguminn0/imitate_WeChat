#include "friendlistitem.h"

#include <QFont>
#include <QIcon>

friendlistItem::friendlistItem(QWidget *parent)
    : QWidget{parent}
{
    init();
}

void friendlistItem::setFriendId(QString id)
{
    this->m_friendId = id;
}

void friendlistItem::init()
{
    m_friendId = "0";

    m_layout = new QHBoxLayout(this);
    m_rightLayout = new QVBoxLayout(this);
    m_rightTopLayout = new QHBoxLayout(this);

    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(5);

    m_friendHead = new QLabel(this);
    m_friendHead->setFixedSize(35, 35);
    m_friendHead->setAlignment(Qt::AlignHCenter);
    m_friendHead->setScaledContents(true);
    m_friendHead->setPixmap(getFriendHeadPix(m_friendId));

    m_friendName = new QLabel(this);
    m_friendName->setFont(QFont("微软雅黑", 15));
    m_friendName->setText(getFriendName(m_friendId));

    m_lastMessage = new QLabel(this);
    m_lastMessage->setFont(QFont("微软雅黑", 11));

    m_lastChatTime = new QLabel(this);
    m_lastChatTime->setFont(QFont("微软雅黑", 11));
    m_lastChatTime->setText("time");

    this->setLayout(m_layout);
    m_layout->addWidget(m_friendHead);
    m_layout->addLayout(m_rightLayout);
    m_rightLayout->addLayout(m_rightTopLayout);
    m_rightLayout->addWidget(m_lastMessage);
    m_rightTopLayout->addWidget(m_friendName);
    m_rightTopLayout->addWidget(m_lastChatTime);
}

QPixmap friendlistItem::getFriendHeadPix(QString friendId)
{
    // 获取id对应的头像
    QPixmap headPix;
    if(friendId == "0")
    {
        headPix.load(":/head2.png");
    }
    else
    {
        headPix.load(":/head.png");
    }

    return headPix;
}

QString friendlistItem::getFriendName(QString friendId)
{
    static int num = 1;
    return QString("好友 ") + QString::number(num);
}
