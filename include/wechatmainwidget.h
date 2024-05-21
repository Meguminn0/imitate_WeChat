/******************************************************
 *
 * @file            wechatmainwidget.h
 * @briefly-Cn      聊天主窗口
 * @briefly-En      The main chat window
 *
 * @author          Meguminn0
 * @date            2024/04/23
 * @history
 *
********************************************************/

#ifndef WECHATMAINWIDGET_H
#define WECHATMAINWIDGET_H

#include "chatwidget.h"
#include "friendlistwidget.h"
#include "optionbarwidget.h"
#include "roundedbtn.h"
#include "backgroundwidget.h"

#include <QPoint>
#include <QWidget>

class wechatmainwidget : public QWidget
{
    Q_OBJECT
public:
    explicit wechatmainwidget(QWidget *parent = nullptr);

    void setMyselfId(const QString& id);
    void setContentsMargins(int left, int top, int right, int bottom);

protected:

private:
    void init();

signals:
    void sig_close();
    void sig_fullSreen();
    void sig_min();
    void sig_backEnter();
    void sig_backLeave();

private slots:

private:
    QString m_myselfId;

    QBoxLayout *m_layout;
    QHBoxLayout *m_layout_background;
    QVBoxLayout *m_layout_optionBar;
    QVBoxLayout *m_layout_friendList;
    QVBoxLayout *m_layout_chat;

    backGroundWidget *m_background_widget;
    OptionBarWidget *m_OptionBarWidget;
    friendListWidget *m_friendListWidget;
    chatWidget *m_chatWidget;
};

#endif // WECHATMAINWIDGET_H
