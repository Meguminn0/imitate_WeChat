#include "include/mainwindow.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowIcon(QIcon(":/img/icon/oneChat_pressed.png"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setContentsMargins(0, 0, 0, 0);
    this->resize(287, 386);
    m_loginWidget = new LoginWidget(this);
    m_loginWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    m_loginWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_wechatWidget = nullptr;

    this->setCentralWidget(m_loginWidget);

    connect(m_loginWidget, &LoginWidget::sig_login, this, &mainWindow::slot_userLogin);
    connect(m_loginWidget, &LoginWidget::sig_move, this, &mainWindow::slot_move);
}

bool mainWindow::verifyUserInfor(const QString &id, const QString &pwd)
{
    /*
     * 网络连接服务器，由服务器验证用户信息
     */

    return true;
}

void mainWindow::slot_move(QPoint point)
{
    this->move(point);
}

void mainWindow::slot_userLogin(QString id, QString pwd)
{
    if(verifyUserInfor(id, pwd))
    {
        m_wechatWidget = new wechatmainwidget();
        m_wechatWidget->setUserId(id);
        this->resize(m_wechatWidget->size());
        m_loginWidget->hide();
        this->setCentralWidget(m_wechatWidget);
    }
    else
    {
        /*
         * 提示用户
         */
    }
}
