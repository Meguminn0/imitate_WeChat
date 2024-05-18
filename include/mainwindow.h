#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "include/loginwidget.h"
#include "include/wechatmainwidget.h"
#include "include/tcpmanager.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*                      topEdge
     *  topLeftCorner 1        2        3  topRightCorner
     *             1 ___|_____________|___
     *                  |             |
     *                  |             |
     *                  |             |
     *   leftEdge  2    |     none    |  rightEdge
     *                  |             |
     *                  |             |
     *               ___|_____________|___
     *             3    |             |
     * bottomLeftCorner   bottomEdge    bottomRightCorner
     *               --------------------
     */
    enum CURSOR_EDGE
    {
        none = 22,
        topEdge = 12,
        bottomEdge = 32,
        leftEdge = 21,
        rightEdge = 23,
        topLeftCorner = 11,
        topRightCorner = 13,
        bottomLeftCorner = 31,
        bottomRightCorner = 33
    };

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

protected:
    void init();
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool verifyUserInfor(const QString &id, const QString &pwd);
    void checkMousePosition(const QPoint &mousePoint);
    void resizeWidget(QPoint &movedPoint);

signals:
    void sig_finishedFullScreen(bool isFullScreen);

protected slots:
    void slot_userLogin(QString id, QString pwd);
    void slot_fullScreen();
    void slot_turnOnResize();
    void slot_turnOffResize();
    void slot_sendChatData(QString targetUserId);

private:
    bool m_forbidResize;

    bool m_mousePressed;        // 鼠标是否按下
    QPoint m_pressedPoint;      // 鼠标按下时的位置
    QRect m_pressedRect;        // 鼠标按下时的矩形框
    CURSOR_EDGE m_cursorEdge;

    LoginWidget *m_loginWidget;
    wechatmainwidget *m_wechatWidget;
    tcpManager *m_tcpMger;
};

#endif // MAINWINDOW_H
