#include "chatmessage.h"
#include "chatwidget.h"

#include <QDateTime>

chatWidget::chatWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(250);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    init();
}

void chatWidget::init()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    m_userInfoWidget = new QWidget(this);
    m_userInfoWidget->setFixedHeight(60);
    m_userInfoWidget->setAutoFillBackground(true);
    m_layout->addWidget(m_userInfoWidget);

    m_listwidget = new QListWidget(this);
    m_layout->addWidget(m_listwidget);

    m_textInWidget = new QWidget(this);
    m_layout->addWidget(m_textInWidget);

    m_textInlayout = new QVBoxLayout(m_textInWidget);
    m_textInlayout->setContentsMargins(0, 0, 0, 0);
    m_textInlayout->setSpacing(0);
    m_textInWidget->setLayout(m_textInlayout);

    m_textEdit = new QTextEdit(m_textInWidget);
    m_textInlayout->addWidget(m_textEdit);

    m_sendBtn = new QPushButton(m_textInWidget);
    m_sendBtn->setText("发送(S)");
    m_textInlayout->addWidget(m_sendBtn);

    connect(m_sendBtn, &QPushButton::clicked, this, &chatWidget::sendMessage);
}

void chatWidget::dealMessage(chatMessage *msg, QListWidgetItem *item, QString text, QString time, chatMessage::MSG_TYPE type)
{
    msg->setFixedWidth(this->width());
    item->setSizeHint(msg->size());
    msg->setText(text, time, type);
    m_listwidget->addItem(item);
    m_listwidget->setItemWidget(item, msg);
}

void chatWidget::sendMessage()
{
    QString msg = m_textEdit->toPlainText();
    m_textEdit->setText("");
    //    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    QString time = QString::number(QDateTime::currentMSecsSinceEpoch()); //时间戳

    qDebug()<<"addMessage" << msg << time << m_listwidget->count();
    if(m_listwidget->count()%2) {
        chatMessage* messageW = new chatMessage(m_listwidget);
        QListWidgetItem* item = new QListWidgetItem(m_listwidget);
        dealMessage(messageW, item, msg, time, chatMessage::ME);
    }
    else
    {
        if(msg != "") {
            chatMessage* messageW = new chatMessage(m_listwidget);
            QListWidgetItem* item = new QListWidgetItem(m_listwidget);
            dealMessage(messageW, item, msg, time, chatMessage::HIM);
        }
    }
    m_listwidget->setCurrentRow(m_listwidget->count() - 1);
}
