#include "include/mainwindow.h"

#include <QApplication>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowIcon(QIcon(":/img/icon/oneChat_pressed.png"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    init();

    connect(m_loginWidget, &LoginWidget::sig_login, this, &mainWindow::slot_userLogin);
    connect(m_loginWidget, &LoginWidget::sig_close, this, &mainWindow::close);
}

mainWindow::~mainWindow()
{

}

void mainWindow::init()
{
    m_forbidResize = true;
    m_cursorEdge = this->CURSOR_EDGE::none;

    m_loginWidget = new LoginWidget(this);
    m_loginWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    m_loginWidget->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(m_loginWidget->size());
    this->setMinimumSize(m_loginWidget->minimumSize());
    this->setCentralWidget(m_loginWidget);

    m_wechatWidget = nullptr;
}

bool mainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::HoverMove && !this->isFullScreen() && !m_forbidResize)
    {
        // 在鼠标处于 MainWindow 的 centralWidget 之外到 MainWindow 边框之间的区域更新鼠标状态
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        checkMousePosition(hoverEvent->position().toPoint());
    }

    return QWidget::event(event);
}

void mainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pressedPoint = event->globalPosition().toPoint();
        m_pressedRect = this->geometry();
        m_mousePressed = true;
        // 停止检查鼠标状态
        m_forbidResize = true;
    }

    QMainWindow::mousePressEvent(event);
}

void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        QPoint mouseMovedPoint = event->globalPosition().toPoint() - m_pressedPoint;

        if(m_cursorEdge == CURSOR_EDGE::none)
        {
            // 移动窗口
            if(this->isFullScreen())
            {
                // 如果是全屏状态
                this->showNormal();
                m_wechatWidget->setContentsMargins(4, 4, 4, 4);
                move(event->globalPosition().toPoint() - this->geometry().bottomRight() / 2);
                m_pressedPoint = event->globalPosition().toPoint();
            }
            move(mouseMovedPoint + m_pressedRect.topLeft());
        }
        else
        {
            resizeWidget(mouseMovedPoint);
        }
    }

    QMainWindow::mouseMoveEvent(event);
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(m_mousePressed)
        {
            m_mousePressed = false;
        }
    }

    QMainWindow::mouseReleaseEvent(event);
}

bool mainWindow::verifyUserInfor(const QString &id, const QString &pwd)
{
    /*
     * 网络连接服务器，由服务器验证用户信息
     */

    tcpManager *tcpMgr = tcpManager::getInstance();
    if(tcpMgr->isConnected())
    {
        tcpMgr->sendData("userId: " + id + "\t password: "  + pwd);
        QByteArray data = tcpMgr->receptionData();
        if(QString(data) == "OK")
        {
            return true;
        }
    }

    return false;
}

void mainWindow::checkMousePosition(const QPoint &mousePoint)
{
    int leftEdge = mousePoint.x();
    int topEdge = mousePoint.y();
    int rightEdge = this->width() - mousePoint.x();
    int bottomEdge = this->height() - mousePoint.y();

    if(topEdge <= 4 && leftEdge <= 4)
    {
        // 左上角
        m_cursorEdge = CURSOR_EDGE::topLeftCorner;
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(topEdge <= 4 && rightEdge <= 4)
    {
        // 右上角
        m_cursorEdge = CURSOR_EDGE::topRightCorner;
        this->setCursor(Qt::SizeBDiagCursor);
    }
    else if(bottomEdge <= 4 && leftEdge <= 4)
    {
        // 左下角
        m_cursorEdge = CURSOR_EDGE::bottomLeftCorner;
        this->setCursor(Qt::SizeBDiagCursor);
    }
    else if(bottomEdge <= 4 && rightEdge <= 4)
    {
        // 右下角
        m_cursorEdge = CURSOR_EDGE::bottomRightCorner;
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(leftEdge <= 4)
    {
        // 左边界
        m_cursorEdge = CURSOR_EDGE::leftEdge;
        this->setCursor(Qt::SizeHorCursor);
    }
    else if(topEdge <= 4)
    {
        // 上边界
        m_cursorEdge = CURSOR_EDGE::topEdge;
        this->setCursor(Qt::SizeVerCursor);
    }
    else if(rightEdge <= 4)
    {
        // 右边界
        m_cursorEdge = CURSOR_EDGE::rightEdge;
        this->setCursor(Qt::SizeHorCursor);
    }
    else if(bottomEdge <= 4)
    {
        // 下边界
        m_cursorEdge = CURSOR_EDGE::bottomEdge;
        this->setCursor(Qt::SizeVerCursor);
    }
    else
    {
        // 不在边界上
        m_cursorEdge = CURSOR_EDGE::none;
        this->setCursor(Qt::ArrowCursor);
    }
}

void mainWindow::resizeWidget(QPoint &movedPoint)
{
    QRect newRect = m_pressedRect;

    if(m_cursorEdge == CURSOR_EDGE::topLeftCorner)
    {
        if(movedPoint.x() > 0 && newRect.width() <= this->minimumWidth())
            movedPoint.setX(0);
        if(movedPoint.y() > 0 && newRect.height() <= this->minimumHeight())
            movedPoint.setY(0);
        newRect.setTopLeft(m_pressedRect.topLeft() + movedPoint);
    }
    else if(m_cursorEdge == CURSOR_EDGE::topRightCorner)
    {
        if(movedPoint.y() > 0 && newRect.height() <= this->minimumHeight())
            movedPoint.setY(0);
        newRect.setTopRight(m_pressedRect.topRight() + movedPoint);
    }
    else if(m_cursorEdge == CURSOR_EDGE::bottomLeftCorner)
    {
        if(movedPoint.x() > 0 && newRect.width() <= this->minimumWidth())
            movedPoint.setX(0);
        newRect.setBottomLeft(m_pressedRect.bottomLeft() + movedPoint);
    }
    else if(m_cursorEdge == CURSOR_EDGE::bottomRightCorner)
    {
        newRect.setBottomRight(m_pressedRect.bottomRight() + movedPoint);
    }
    else if(m_cursorEdge == CURSOR_EDGE::leftEdge)
    {
        if(movedPoint.x() > 0 && newRect.width() <= this->minimumWidth())
            movedPoint.setX(0);
        newRect.setLeft(m_pressedRect.left() + movedPoint.x());
    }
    else if(m_cursorEdge == CURSOR_EDGE::topEdge)
    {
        if(movedPoint.y() > 0 && newRect.height() <= this->minimumHeight())
            movedPoint.setY(0);
        newRect.setTop(m_pressedRect.top() + movedPoint.y());
    }
    else if(m_cursorEdge == CURSOR_EDGE::rightEdge)
    {
        newRect.setRight(m_pressedRect.right() + movedPoint.x());
    }
    else if(m_cursorEdge == CURSOR_EDGE::bottomEdge)
    {
        newRect.setBottom(m_pressedRect.bottom() + movedPoint.y());
    }

    this->setGeometry(newRect);
}

void mainWindow::slot_userLogin(QString id, QString pwd)
{
    if(verifyUserInfor(id, pwd))
    {
        m_wechatWidget = new wechatmainwidget(this);
        m_wechatWidget->setMyselfId(id);
        m_loginWidget->hide();
        this->resize(m_wechatWidget->size());
        this->setMinimumSize(m_wechatWidget->minimumSize());
        this->setCentralWidget(m_wechatWidget);
        m_forbidResize = false;

        connect(m_wechatWidget, &wechatmainwidget::sig_close, this, &mainWindow::close);
        connect(m_wechatWidget, &wechatmainwidget::sig_fullSreen, this, &mainWindow::slot_fullScreen);
        connect(m_wechatWidget, &wechatmainwidget::sig_min, this, &mainWindow::showMinimized);
        connect(m_wechatWidget, &wechatmainwidget::sig_backEnter, this, &mainWindow::slot_turnOffResize);
        connect(m_wechatWidget, &wechatmainwidget::sig_backLeave, this, &mainWindow::slot_turnOnResize);
    }
    else
    {
        /*
         * 提示用户
         */
        qDebug() << "账号或密码错误";
    }
}

void mainWindow::slot_fullScreen()
{
    if(this->isFullScreen())
    {
        this->showNormal();
        m_wechatWidget->setContentsMargins(4, 4, 4, 4);
    }
    else
    {
        this->showFullScreen();
        m_wechatWidget->setContentsMargins(0, 0, 0, 0);
    }
}

void mainWindow::slot_turnOnResize()
{
    m_forbidResize = false;
    m_cursorEdge = CURSOR_EDGE::none;
    this->setCursor(Qt::ArrowCursor);
}

void mainWindow::slot_turnOffResize()
{
    m_forbidResize = true;
    m_cursorEdge = CURSOR_EDGE::none;
    this->setCursor(Qt::ArrowCursor);
}
