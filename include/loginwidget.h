/******************************************************
 *
 * @file            loginwidget.h
 * @briefly-Cn      仿照微信登录窗口
 * @briefly-En      Imitation wechat login window
 *
 * @author          Meguminn0
 * @date            2024/04/7
 * @history
 *
********************************************************/

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

#include "wechatmainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void loginCheck();

private:
    void init();
    bool checkUserValue();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::LoginWidget *ui;
    bool readyMove; /* the widget is ready to move */
    QPoint m_currentPoint;  /* the widget current position in the window */
    QPoint m_mouseStartPoint;   /* the position where the mouse is pressed when pressed */
    wechatmainwidget *m_mainwidget;
};
#endif // LOGINWIDGET_H
