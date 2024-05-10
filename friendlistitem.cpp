#include "friendlistitem.h"

#include <QFont>
#include <QFontMetrics>
#include <QIcon>

friendlistItem::friendlistItem(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setFixedSize(QSize(parent->width(), 65));
    init();
}

void friendlistItem::setFriendId(const QString& id)
{
    this->m_friendId = id;
}

void friendlistItem::init()
{
    QPalette palette;
    setFriendName();
    setLastChatTime();
    setLastMsg();

    m_layout = new QHBoxLayout(this);
    m_leftLayout = new QVBoxLayout();
    m_rightLayout = new QVBoxLayout();
    m_rightTopLayout = new QHBoxLayout();
    m_rightBottomLayout = new QHBoxLayout();

    m_layout->setContentsMargins(LEFT_MARGIN, TOP_MARGIN, RIGHT_MARGIN, BOTTOM_MARGIN);
    m_layout->setSpacing(SPACING);
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(0);
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    m_rightTopLayout->setContentsMargins(0, 0, 0, 0);
    m_rightTopLayout->setSpacing(0);
    m_rightTopLayout->setDirection(QBoxLayout::LeftToRight);
    m_rightBottomLayout->setContentsMargins(0, 0, 0, 0);
    m_rightBottomLayout->setSpacing(0);
    m_rightBottomLayout->setDirection(QBoxLayout::LeftToRight);

    m_friendHeadLabel = new QLabel(this);
    m_friendHeadLabel->setFixedSize(40, 40);
    m_friendHeadLabel->setAlignment(Qt::AlignCenter);
    m_friendHeadLabel->setScaledContents(true);
    m_friendHeadLabel->setPixmap(getFriendHeadPix());

    m_friendNameLabel = new QLabel(this);
    m_friendNameLabel->setFont(QFont("微软雅黑", 10));
    m_friendNameLabel->setAlignment(Qt::AlignLeft);
    m_friendNameLabel->setFixedSize(getFriendNameSize());
    m_friendNameLabel->setText(m_friendName);

    m_lastChatTimeLabel = new QLabel(this);
    m_lastChatTimeLabel->setFont(QFont("微软雅黑", 8));
    m_lastChatTimeLabel->setAlignment(Qt::AlignRight);
    m_lastChatTimeLabel->setFixedSize(getLastChatTimeSize());
    m_lastChatTimeLabel->setText(m_lastChatTime);
    m_lastChatTimeLabel->setStyleSheet("QLabel{ color: rgb(157, 157, 157) }");

    m_lastMessageLabel = new QLabel(this);
    m_lastMessageLabel->setFont(QFont("微软雅黑", 8));
    m_lastMessageLabel->setAlignment(Qt::AlignLeft);
    m_lastMessageLabel->setFixedSize(getLastMsgSize());
    m_lastMessageLabel->setText(m_lastMsg);
    m_lastMessageLabel->setStyleSheet("QLabel{ color: rgb(157, 157, 157) }");

    /*
     * ----------------<layout>-----------------
     * |            |     <rightTopLayout>     |
     * |            | (Name) |(spacer)| (Time) |
     * |<leftleyout>|-------rightLayout--------|
     * |            |         (Message)        |
     * |            |    <rightBottomLayout>   |
     * ----------------------------------------
     */
    this->setLayout(m_layout);
    m_layout->addLayout(m_leftLayout);
    m_layout->addLayout(m_rightLayout);
    m_leftLayout->addWidget(m_friendHeadLabel);
    m_rightLayout->addLayout(m_rightTopLayout);
    m_rightLayout->addLayout(m_rightBottomLayout);
    m_rightTopLayout->addWidget(m_friendNameLabel, 1);
    m_rightTopLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding,QSizePolicy::Maximum));
    m_rightTopLayout->addWidget(m_lastChatTimeLabel, 0);
    m_rightBottomLayout->addWidget(m_lastMessageLabel);
}

QPixmap friendlistItem::getFriendHeadPix()
{
    // 获取id对应的头像
    QPixmap headPix;
    if(m_friendId == "0")
    {
        headPix.load(":/head2.png");
    }
    else
    {
        headPix.load(":/head.png");
    }

    return headPix;
}

void friendlistItem::setFriendName()
{
    static int num = 1;
    m_friendName = QString("好友") + QString::number(num);
}

QSize friendlistItem::getFriendNameSize()
{
    QFontMetrics fontMetr(this->font());
    m_friendName = fontMetr.elidedText(m_friendName, Qt::ElideRight, this->width());
    int nameWidth = fontMetr.horizontalAdvance(m_friendName);
    int nameHeight = fontMetr.lineSpacing();
    qDebug() << "friend name width: " << nameWidth << "height: " << nameHeight;

    return QSize(nameWidth, nameHeight);
}

void friendlistItem::setLastMsg()
{
    m_lastMsg = QString("last message assssssssss...");
}

QSize friendlistItem::getLastMsgSize()
{
    QFontMetrics fontMetr(this->font());
    m_lastMsg = fontMetr.elidedText(m_lastMsg, Qt::ElideRight, this->width() - LEFT_MARGIN - RIGHT_MARGIN - SPACING);
    int msgWidth = fontMetr.horizontalAdvance(m_lastMsg);
    int msgHeight = fontMetr.lineSpacing();
    qDebug() << "lasts message width: " << msgWidth << "height: " << msgHeight;

    return QSize(msgWidth, msgHeight);
}

void friendlistItem::setLastChatTime()
{
    m_lastChatTime = QString("24/11/11");
}

QSize friendlistItem::getLastChatTimeSize()
{
    QFontMetrics fontMetr(this->font());
    int lstTimeWidth = fontMetr.horizontalAdvance(m_lastChatTime);
    int lstTimeHeight = fontMetr.lineSpacing();
    qDebug() << "last chat time width: " << lstTimeWidth << "height: " << lstTimeHeight;

    return QSize(lstTimeWidth, lstTimeHeight);
}

