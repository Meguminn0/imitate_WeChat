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
    const int EDGE_WIDTH = 5; // 窗口的边缘宽度

    explicit wechatmainwidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void init();

signals:

private slots:
    void showFullScreenOrNormal();

private:
    bool m_readyMove;
    QPoint m_currentPos;
    QPoint m_mouseStartPos;

    backGroundWidget *m_background_widget;
    OptionBarWidget *m_OptionBarWidget;
    friendListWidget *m_friendListWidget;
    chatWidget *m_chatWidget;

};

#endif // WECHATMAINWIDGET_H
