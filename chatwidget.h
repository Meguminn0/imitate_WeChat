/******************************************************
 *
 * @file            chatwidget.h
 * @briefly-Cn      聊天界面
 * @briefly-En      Chat interface
 *
 * @author          Meguminn0
 * @date            2024/04/23
 * @history
 *
********************************************************/

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "chatmessage.h"

#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class chatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit chatWidget(QWidget *parent = nullptr);

protected:
    void init();
    void dealMessage(chatMessage *msg, QListWidgetItem *item, QString text, QString time, chatMessage::MSG_TYPE type);


signals:

protected slots:
    void sendMessage();

private:
    QVBoxLayout *m_layout;
    QVBoxLayout *m_textInlayout;

    QWidget *m_userInfoWidget;
    QListWidget *m_listwidget;
    QWidget *m_textInWidget;
    QTextEdit *m_textEdit;
    QPushButton *m_sendBtn;
};

#endif // CHATWIDGET_H
