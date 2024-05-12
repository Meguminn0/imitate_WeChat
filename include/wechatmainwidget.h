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
    enum Margin_Edge
    {
        none = 0,
        topEdge = 1,
        bottomEdge = 2,
        leftEdge = 4,
        rightEdge = 8,
        topLeftCorner = 16,
        topRightCorner = 32,
        bottomLeftCorner = 64,
        bottomRightCorner = 128
    };

public:
    const int EDGE_MIN_WIDTH = 2; // 窗口的边缘最小宽度
    const int EDGE_MAX_WIDTH = 8; // 窗口的边缘最大宽度

    explicit wechatmainwidget(QWidget *parent = nullptr);

protected:
    bool event(QEvent *event) override;
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void init();
    void updateEdgeCheck(QMouseEvent *event);
    void resizeWdige();

signals:

private slots:
    void showFullScreenOrNormal();

private:
    bool m_isPressed;
    QPoint m_mousePressedPoint;
    QPoint m_mouseMovePoint;

    bool m_readyResize;
    wechatmainwidget::Margin_Edge m_resizeEdge;
    QSize m_pressedSize;
    QPoint m_widgePressedPos;

    backGroundWidget *m_background_widget;
    OptionBarWidget *m_OptionBarWidget;
    friendListWidget *m_friendListWidget;
    chatWidget *m_chatWidget;

};

#endif // WECHATMAINWIDGET_H
