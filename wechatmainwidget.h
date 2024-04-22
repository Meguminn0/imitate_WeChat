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

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

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

    QRect current_screenGeometry;
};

#endif // WECHATMAINWIDGET_H