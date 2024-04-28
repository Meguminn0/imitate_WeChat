#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include "friendlistwidget.h"
#include "roundedbtn.h"
#include "wechatmainwidget.h"
#include "backgroundwidget.h"

#define WIDGET_MARGIN 4

wechatmainwidget::wechatmainwidget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Hover);

    m_onEdge = false;
    m_readyResize = false;
    m_resizeEdge = 0;
    m_resizeEdge = 0;
    m_readyMove = false;

    m_background_widget = new backGroundWidget(this);
    m_OptionBarWidget = new OptionBarWidget(m_background_widget);
    m_friendListWidget = new friendListWidget(m_background_widget);
    m_chatWidget = new chatWidget(m_background_widget);

    this->setGeometry(400, 100, 700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);
    this->setMinimumSize(700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);

    init();
    m_OptionBarWidget->show();
    m_friendListWidget->show();
    m_chatWidget->show();

    connect(m_background_widget, &backGroundWidget::signClose, this, &wechatmainwidget::close);
    connect(m_background_widget, &backGroundWidget::signFullScreen, this, &wechatmainwidget::showFullScreenOrNormal);
    connect(m_background_widget, &backGroundWidget::signMin, this, &wechatmainwidget::showMinimized);
}

bool wechatmainwidget::event(QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        QMouseEvent mouseEvent(QEvent::MouseMove, hoverEvent->position().toPoint(),
                               Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        mouseMoveEvent(&mouseEvent);
    }

    return QWidget::event(event);
}

void wechatmainwidget::enterEvent(QEnterEvent *event)
{
//    isOnEdge(event->position().toPoint());

    QWidget::enterEvent(event);
}

void wechatmainwidget::leaveEvent(QEvent *event)
{
    if(m_onEdge)
    {
        this->setCursor(Qt::ArrowCursor);
        m_onEdge = false;
    }

    QWidget::leaveEvent(event);
}

void wechatmainwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isOnEdge(event->position().toPoint()))
        {
            // 如果鼠标点击在窗口边框上
            m_readyResize = true;
            m_currentSize = this->size();
        }
        else
        {
            // 鼠标点击不在在窗口边框上，整体移动窗口
            m_readyMove = true;
            m_currentPos = this->frameGeometry().topLeft();
        }

        m_mouseStartPos = event->globalPosition().toPoint();
    }

    QWidget::mousePressEvent(event);
}

void wechatmainwidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_readyResize)
    {
        QPoint diff = event->globalPosition().toPoint() - m_mouseStartPos;
        QSize newSize = m_currentSize;
        if(m_resizeEdge == Qt::TopEdge || m_resizeEdge == Qt::BottomEdge)
        {
            newSize.setHeight(newSize.height() + (m_resizeEdge == Qt::TopEdge ? -diff.y() : diff.y()));
        }
        else if(m_resizeEdge == Qt::LeftEdge)
        {
            newSize.setWidth(newSize.width() + (m_resizeEdge == Qt::LeftEdge ? -diff.x() : diff.x()));
        }
        else if(m_resizeConer == Qt::TopLeftCorner)
        {
            newSize.setHeight(newSize.height() - diff.y());
            newSize.setWidth(newSize.width() - diff.x());
        }
        else if(m_resizeConer == Qt::TopRightCorner)
        {
            newSize.setHeight(newSize.height() - diff.y());
            newSize.setWidth(newSize.width() + diff.x());
        }
        else if(m_resizeConer == Qt::BottomLeftCorner)
        {
            newSize.setHeight(newSize.height() + diff.y());
            newSize.setWidth(newSize.width() - diff.x());
        }
        else if(m_resizeConer == Qt::BottomRightCorner)
        {
            newSize.setHeight(newSize.height() + diff.y());
            newSize.setWidth(newSize.width() + diff.x());
        }

        // 调整新窗口大小大于最小大小，小于最大大小
        newSize = newSize.expandedTo(this->minimumSize());
        newSize = newSize.boundedTo(this->maximumSize());
        this->resize(newSize);
        this->move(this->pos() + diff);
    }

    if(m_readyMove)
    {
        if(isFullScreen())
        {
            this->showNormal();
            this->move(event->globalPosition().toPoint() - this->geometry().bottomRight() / 2);
            this->m_currentPos = this->frameGeometry().topLeft();
        }
        QPoint mouseMovePos = event->globalPosition().toPoint() - m_mouseStartPos;
        this->move(m_currentPos + mouseMovePos);
    }

    if (windowState() != Qt::WindowMaximized) {
        isOnEdge(event->position().toPoint());
    }

    QWidget::mouseMoveEvent(event);
}

void wechatmainwidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(m_readyResize)
        {
            m_readyResize = false;
            m_resizeEdge = 0;
            m_resizeConer = 0;
        }

        if(m_readyMove)
        {
            m_readyMove = false;
        }

        event->accept();
    }

    QWidget::mouseReleaseEvent(event);
}

void wechatmainwidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_background_widget->onFullScreen(this->isFullScreen(), event->size().width(), event->size().height());
}

void wechatmainwidget::init()
{
    QPalette palette;

    // 设置背景
    palette = m_background_widget->palette();
    palette.setColor(QPalette::Window, QColor(245,245,245));
    m_background_widget->setAutoFillBackground(true);
    m_background_widget->setPalette(palette);
    m_background_widget->setGeometry(WIDGET_MARGIN, WIDGET_MARGIN, this->width() - WIDGET_MARGIN * 2, this->height() - WIDGET_MARGIN * 2);

    // 设置整体布局
    QHBoxLayout *layout_background = new QHBoxLayout(m_background_widget);
    QVBoxLayout *layout_optionBar = new QVBoxLayout(m_background_widget);
    QVBoxLayout *layout_friendList = new QVBoxLayout(m_background_widget);
    QVBoxLayout *layout_chat = new QVBoxLayout(m_background_widget);

//    // 设置布局中控件与布局之间的间距
    layout_background->setContentsMargins(0, 0, 0, 0);
    layout_optionBar->setContentsMargins(0, 0, 0, 0);
    layout_friendList->setContentsMargins(0, 0, 0, 0);
    layout_chat->setContentsMargins(0, 0, 0, 0);

    // 设置两个相邻布局或者布局与布局外控件之间的间距
    layout_background->setSpacing(0);
    layout_optionBar->setSpacing(0);

    layout_background->setDirection(QBoxLayout::LeftToRight);
    layout_optionBar->setDirection(QBoxLayout::TopToBottom);
    layout_friendList->setDirection(QBoxLayout::RightToLeft);
    layout_chat->setDirection(QBoxLayout::TopToBottom);

    m_background_widget->setLayout(layout_background);

    layout_background->addLayout(layout_optionBar);
    layout_background->addLayout(layout_friendList);
    layout_background->addLayout(layout_chat);

    layout_background->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
    layout_optionBar->addWidget(m_OptionBarWidget);
    layout_friendList->addWidget(m_friendListWidget);
//    layout_background->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));
    layout_chat->addWidget(m_chatWidget);
}

int wechatmainwidget::getEdge(QPoint mousePosition)
{
    if (mousePosition.y() <= EDGE_WIDTH)
    {
        return Qt::TopEdge;
    }
    else if (mousePosition.y() >= height() - EDGE_WIDTH)
    {
        return Qt::BottomEdge;
    }
    else if (mousePosition.x() <= EDGE_WIDTH)
    {
        return Qt::LeftEdge;
    }
    else if (mousePosition.x() >= width() - EDGE_WIDTH)
    {
        return Qt::RightEdge;
    }
    else
    {
        return 0; // 默认
    }
}

int wechatmainwidget::getCorner(QPoint mousePosition)
{
    if (mousePosition.x() <= EDGE_WIDTH && mousePosition.y() <= EDGE_WIDTH)
    {
        return Qt::TopLeftCorner;
    }
    else if (mousePosition.x() >= width() - EDGE_WIDTH && mousePosition.y() <= EDGE_WIDTH)
    {
        return Qt::TopRightCorner;
    }
    else if (mousePosition.x() <= EDGE_WIDTH && mousePosition.y() >= height() - EDGE_WIDTH)
    {
        return Qt::BottomLeftCorner;
    }
    else if (mousePosition.x() >= width() - EDGE_WIDTH && mousePosition.y() >= height() - EDGE_WIDTH)
    {
        return Qt::BottomRightCorner;
    }
    else
    {
        return 0;
    }
}

bool wechatmainwidget::isOnEdge(QPoint pos)
{
    m_resizeEdge = this->getEdge(pos);
    m_resizeConer = this->getCorner(pos);
    if(pos.x() <= EDGE_WIDTH || pos.x() >= this->width() - EDGE_WIDTH ||
        pos.y() <= EDGE_WIDTH || pos.y() >= this->height() - EDGE_WIDTH)
    {
        if(m_resizeEdge == Qt::TopEdge || m_resizeEdge == Qt::BottomEdge)
        {
            this->setCursor(Qt::SizeVerCursor);
        }
        else if(m_resizeEdge == Qt::LeftEdge || m_resizeEdge == Qt::RightEdge)
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        else if(m_resizeConer == Qt::TopLeftCorner || m_resizeConer == Qt::BottomRightCorner)
        {
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if(m_resizeConer == Qt::TopRightCorner || m_resizeConer == Qt::BottomLeftCorner)
        {
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else
        {
            this->setCursor(Qt::ArrowCursor);
        }
        m_onEdge = true;
    }
    else
    {
        m_onEdge = false;
    }

    return m_onEdge;
}

void wechatmainwidget::showFullScreenOrNormal()
{
    if(isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

