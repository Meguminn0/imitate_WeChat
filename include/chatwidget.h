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
#include <QStackedWidget>


class chatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit chatWidget(QWidget *parent = nullptr);
    void setCurrentChatingUserId(const QString &id);

protected:
    void init();
    void noneWidgetInit();
    void chatingWidgetInit();
    void dealMessage(chatMessageBox *msg, QListWidgetItem *item, QString text, QString time, chatMessageBox::MSG_TYPE type);

    void resizeEvent(QResizeEvent *event);

    void setUserNameLabel();
    QString getUserName();

signals:

protected slots:
    void slot_sendMessage();

private:
    QString m_currentChatingUserId;

    QVBoxLayout *m_layout;              /* 总窗口界面布局 */
    QGridLayout *m_noneLayout;          /* 空聊天界面总布局 */
    QVBoxLayout *m_chatingLayout;       /* 聊天子界面总布局 */
    QVBoxLayout *m_textInlayout;        /* 文本输入界面布局 */
    QHBoxLayout *m_chatToolBarLayout;   /* 聊天工具栏布局 */
    QHBoxLayout *m_sendBtnLayout;       /* 发送按钮布局 */
    QHBoxLayout *m_userInfoLayout;      /* 用户信息布局 */

    QStackedWidget *m_stkedWidget;      /* 界面切换控制 */
    QWidget *m_noneWidget;              /* 空的聊天子界面 */
    QWidget *m_chatingWidget;           /* 用户聊天子界面 */
    QWidget *m_userInfoWidget;          /* 用户信息界面 */
    QWidget *m_textInWidget;            /* 文本输入界面 */
    QListWidget *m_listwidget;          /* 聊天信息列表 */

    QLabel *m_logol;                    /* 空的聊天子界面中显示的图标 */
    QLabel *m_userNameLabel;            /* 用户名标签 */

    QTextEdit *m_textEdit;              /* 文本输入框 */
    QPushButton *m_emoticonsBtn;        /* 聊天表情按钮 */
    QPushButton *m_SendFileBtn;         /* 发送文件按钮 */
    QPushButton *m_screenShotBtn;       /* 截图按钮 */
    QPushButton *m_chatHistoryBtn;      /* 聊天记录按钮 */
    QPushButton *m_sendBtn;             /* 发送按钮 */
    QPushButton *m_chatInfoBtn;         /* 聊天信息按钮 */
};

#endif // CHATWIDGET_H
