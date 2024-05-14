#include <QGraphicsDropShadowEffect>
#include <QLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include "include/friendlistwidget.h"
#include "include/roundedbtn.h"
#include "include/wechatmainwidget.h"
#include "include/backgroundwidget.h"

#define WIDGET_MARGIN 4

wechatmainwidget::wechatmainwidget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_Hover);

    this->setMinimumSize(700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);
    this->move(400, 100);
    this->resize(700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);

    init();
    m_OptionBarWidget->show();
    m_friendListWidget->show();
    m_chatWidget->show();

    connect(m_background_widget, &backGroundWidget::signClose, this, &wechatmainwidget::close);
    connect(m_background_widget, &backGroundWidget::signFullScreen, this, &wechatmainwidget::showFullScreenOrNormal);
    connect(m_background_widget, &backGroundWidget::signMin, this, &wechatmainwidget::showMinimized);
}

void wechatmainwidget::setUserId(const QString &id)
{
    this->m_userId = id;
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
    QWidget::enterEvent(event);
}

void wechatmainwidget::leaveEvent(QEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    m_isPressed = false;
    m_readyResize = false;

    QWidget::leaveEvent(event);
}

void wechatmainwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_mousePressedPoint = event->globalPosition().toPoint();
        m_widgePressedPos = this->geometry().topLeft();
        m_pressedSize = this->size();
    }

    QWidget::mousePressEvent(event);
}

void wechatmainwidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        if(m_readyResize)
        {
            m_mouseMovePoint = event->globalPosition().toPoint() - m_mousePressedPoint;
        }
        else
        {
            if(this->isFullScreen())
            {
                // 如果是全屏状态
                this->showNormal();
                move(event->globalPosition().toPoint() - this->geometry().bottomRight() / 2);
                m_widgePressedPos = this->geometry().topLeft();
            }

            QPoint diff = event->globalPosition().toPoint() - m_mousePressedPoint;
            move(m_widgePressedPos + diff);
        }
    }

    if (windowState() != Qt::WindowMaximized) {
        updateEdgeCheck(event);
    }

    QWidget::mouseMoveEvent(event);
}

void wechatmainwidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isPressed = false;
        m_readyResize = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void wechatmainwidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(this->isFullScreen())
    {
        m_background_widget->onFullScreen(this->isFullScreen(), event->size().width(), event->size().height());
    }
    else
    {
        m_background_widget->resize(this->width() - WIDGET_MARGIN * 2, this->height() - WIDGET_MARGIN * 2);
    }

    m_chatWidget->setFixedWidth(this->width() - m_OptionBarWidget->width() - m_friendListWidget->width());
}

void wechatmainwidget::init()
{
    m_isPressed = false;
    m_readyResize = false;
    m_resizeEdge = this->Margin_Edge::none;

    m_background_widget = new backGroundWidget(this);
    m_OptionBarWidget = new OptionBarWidget(m_background_widget);
    m_friendListWidget = new friendListWidget(m_background_widget);
    m_chatWidget = new chatWidget(m_background_widget);

    QPalette palette;

    // 设置背景
    palette = m_background_widget->palette();
    palette.setColor(QPalette::Window, QColor(245,245,245));
    m_background_widget->setAutoFillBackground(true);
    m_background_widget->setPalette(palette);
    m_background_widget->setGeometry(WIDGET_MARGIN, WIDGET_MARGIN, this->width() - WIDGET_MARGIN * 2, this->height() - WIDGET_MARGIN * 2);

    // 设置整体布局
    QHBoxLayout *layout_background = new QHBoxLayout();
    QVBoxLayout *layout_optionBar = new QVBoxLayout();
    QVBoxLayout *layout_friendList = new QVBoxLayout();
    QVBoxLayout *layout_chat = new QVBoxLayout();

//    // 设置布局中控件与布局之间的间距
    layout_background->setContentsMargins(0, 0, 0, 0);
    layout_optionBar->setContentsMargins(0, 0, 0, 0);
    layout_friendList->setContentsMargins(0, 0, 0, 0);
    layout_chat->setContentsMargins(0, 0, 10, 0);

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
    layout_chat->addWidget(m_chatWidget);
}

void wechatmainwidget::updateEdgeCheck(QMouseEvent *event)
{
    QRect rect = this->geometry();

    int topEdge = event->globalPosition().y() - rect.y();
    int bottomEdge = rect.y() + rect.height() - event->globalPosition().y();
    int leftEdge = event->globalPosition().x() - rect.x();
    int rightEdge = rect.x() + rect.width() - event->globalPosition().x();

    if(!m_readyResize)
    {
        // 并没有开始调整窗口大小
        if((topEdge >= EDGE_MIN_WIDTH && topEdge <= EDGE_MAX_WIDTH) &&
            (leftEdge >= EDGE_MIN_WIDTH && leftEdge <= EDGE_MAX_WIDTH))
        {
            // 当鼠标位于左上角时
            m_resizeEdge = Margin_Edge::topLeftCorner;
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if((topEdge >= EDGE_MIN_WIDTH && topEdge <= EDGE_MAX_WIDTH) &&
                (rightEdge >= EDGE_MIN_WIDTH && rightEdge <= EDGE_MAX_WIDTH))
        {
            // 当鼠标位于右上角时
            m_resizeEdge = Margin_Edge::topRightCorner;
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else if((bottomEdge >= EDGE_MIN_WIDTH && bottomEdge <= EDGE_MAX_WIDTH) &&
                 (leftEdge >= EDGE_MIN_WIDTH && leftEdge <= EDGE_MAX_WIDTH))
        {
            // 当鼠标位于左下角时
            m_resizeEdge = Margin_Edge::bottomLeftCorner;
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else if((bottomEdge >= EDGE_MIN_WIDTH && bottomEdge <= EDGE_MAX_WIDTH) &&
                (rightEdge >= EDGE_MIN_WIDTH && rightEdge <= EDGE_MAX_WIDTH))
        {
            // 当鼠标位于右下角时
            m_resizeEdge = Margin_Edge::bottomRightCorner;
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if(topEdge >= EDGE_MIN_WIDTH && topEdge <= EDGE_MAX_WIDTH)
        {
            // 当鼠标位于上边缘时
            m_resizeEdge = Margin_Edge::topEdge;
            this->setCursor(Qt::SizeVerCursor);
        }
        else if(bottomEdge >= EDGE_MIN_WIDTH && bottomEdge <= EDGE_MAX_WIDTH)
        {
            // 当鼠标位于下边缘时
            m_resizeEdge = Margin_Edge::bottomEdge;
            this->setCursor(Qt::SizeVerCursor);
        }
        else if(leftEdge >= EDGE_MIN_WIDTH && leftEdge <= EDGE_MAX_WIDTH)
        {
            // 当鼠标位于左边缘时
            m_resizeEdge = Margin_Edge::leftEdge;
            this->setCursor(Qt::SizeHorCursor);
        }
        else if(rightEdge >= EDGE_MIN_WIDTH && rightEdge <= EDGE_MAX_WIDTH)
        {
            // 当鼠标位于右边缘时
            m_resizeEdge = Margin_Edge::rightEdge;
            this->setCursor(Qt::SizeHorCursor);
        }
        else
        {
            if(!m_isPressed)
            {
                this->setCursor(Qt::ArrowCursor);
            }
        }
    }

    if(m_resizeEdge != Margin_Edge::none)
    {
        m_readyResize = true;
        resizeWdige();
    }
}

void wechatmainwidget::resizeWdige()
{
    if (m_isPressed)
    {
        QPoint diff(m_mousePressedPoint.x() + m_mouseMovePoint.x(), m_mousePressedPoint.y() + m_mouseMovePoint.y());
        QSize newSize = m_pressedSize;
        if(m_resizeEdge == Margin_Edge::topLeftCorner)
        {
            newSize.setWidth(newSize.width() - m_mouseMovePoint.x());
            newSize.setHeight(newSize.height() - m_mouseMovePoint.y());
            if(diff.x() <= m_mousePressedPoint.x())
            {
                this->move(diff.x(), this->y());
            }
            if(diff.y() <= m_mousePressedPoint.y())
            {
                this->move(this->x(), diff.y());
            }
        }
        else if(m_resizeEdge == Margin_Edge::topRightCorner)
        {
            newSize.setWidth(newSize.width() + m_mouseMovePoint.x());
            newSize.setHeight(newSize.height() - m_mouseMovePoint.y());
            if(diff.y() <= m_mousePressedPoint.y())
            {
                this->move(this->x(), diff.y());
            }
        }
        else if(m_resizeEdge == Margin_Edge::bottomLeftCorner)
        {
            newSize.setWidth(newSize.width() - m_mouseMovePoint.x());
            newSize.setHeight(newSize.height() + m_mouseMovePoint.y());
            if(diff.x() <= m_mousePressedPoint.x())
            {
                this->move(diff.x(), this->y());
            }
        }
        else if(m_resizeEdge == Margin_Edge::bottomRightCorner)
        {
            newSize.setWidth(newSize.width() + m_mouseMovePoint.x());
            newSize.setHeight(newSize.height() + m_mouseMovePoint.y());
        }
        else if(m_resizeEdge == Margin_Edge::topEdge)
        {
            newSize.setHeight(newSize.height() - m_mouseMovePoint.y());
            if(diff.y() <= m_mousePressedPoint.y())
            {
                this->move(this->x(), diff.y());
            }
        }
        else if(m_resizeEdge == Margin_Edge::bottomEdge)
        {
            newSize.setHeight(newSize.height() + m_mouseMovePoint.y());
        }
        else if(m_resizeEdge == Margin_Edge::leftEdge)
        {
            newSize.setWidth(newSize.width() - m_mouseMovePoint.x());
            if(diff.x() <= m_mousePressedPoint.x())
            {
                this->move(diff.x(), this->y());
            }
        }
        else if(m_resizeEdge == Margin_Edge::rightEdge)
        {
            newSize.setWidth(newSize.width() + m_mouseMovePoint.x());
        }

        newSize = newSize.expandedTo(this->minimumSize());
        newSize = newSize.boundedTo(this->maximumSize());

        this->resize(newSize);
    }
    else
    {
        m_readyResize = false;
        m_resizeEdge = Margin_Edge::none;
    }
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

