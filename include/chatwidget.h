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

#include "chatmessagebox.h"

#include <QLabel>
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
    void dealMessage(chatMessageBox *msg, QListWidgetItem *item, QString text, QString time, chatMessageBox::MSG_TYPE type);

    void resizeEvent(QResizeEvent *event);

    void setUserNameLabel();
    QString getUserName();

signals:
    void sig_lastMessage(int userId, QString lastMsg);

protected slots:
    void sendMessage();

private:
    int m_userId;

    QVBoxLayout *m_layout;
    QVBoxLayout *m_textInlayout;
    QHBoxLayout *m_chatToolBarLayout;
    QHBoxLayout *m_sendBtnLayout;
    QHBoxLayout *m_userInfoLayout;

    QWidget *m_userInfoWidget;
    QWidget *m_textInWidget;
    QListWidget *m_listwidget;

    QLabel *m_userNameLabel;

    QTextEdit *m_textEdit;
    QPushButton *m_sendBtn;
    QPushButton *m_chatInfoBtn;
};

#endif // CHATWIDGET_H
