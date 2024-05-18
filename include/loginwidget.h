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

signals:
    void sig_close();
    void sig_login(QString id, QString pwd);

private slots:
    void slot_loginCheck();

private:
    void init();
    bool checkUserValue();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::LoginWidget *ui;
    wechatmainwidget *m_mainwidget;
};
#endif // LOGINWIDGET_H
