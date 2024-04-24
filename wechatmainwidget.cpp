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
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_background_widget = new backGroundWidget(this);
    m_OptionBarWidget = new OptionBarWidget(m_background_widget);
    m_friendListWidget = new friendListWidget(m_background_widget);
    m_chatWidget = new chatWidget(m_background_widget);

    this->setGeometry(400, 100, 700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);
    this->setMinimumSize(700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);

    init();

    connect(m_background_widget, &backGroundWidget::signClose, this, &wechatmainwidget::close);
    connect(m_background_widget, &backGroundWidget::signFullScreen, this, &wechatmainwidget::showFullScreenOrNormal);
    connect(m_background_widget, &backGroundWidget::signMin, this, &wechatmainwidget::showMinimized);
}

void wechatmainwidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_readyMove)
    {
        QPoint mouseMovePos = event->globalPos() - m_mouseStartPos;
        this->move(m_currentPos + mouseMovePos);
    }

    QWidget::mouseMoveEvent(event);
}

void wechatmainwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_readyMove = true;
        m_mouseStartPos = event->globalPos();
        m_currentPos = this->frameGeometry().topLeft();
        event->accept();
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void wechatmainwidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_readyMove && event->button() == Qt::LeftButton)
    {
        m_readyMove = false;
        event->accept();
    }
    else
    {
        QWidget::mouseReleaseEvent(event);
    }
}

void wechatmainwidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_background_widget->onResize(this->isFullScreen(), event->size().width(), event->size().height());
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
    layout_friendList->setDirection(QBoxLayout::TopToBottom);
    layout_chat->setDirection(QBoxLayout::TopToBottom);

    m_background_widget->setLayout(layout_background);

    layout_background->addLayout(layout_optionBar);
    layout_background->addLayout(layout_friendList);
    layout_background->addLayout(layout_chat);

    layout_optionBar->addWidget(m_OptionBarWidget);
    layout_friendList->addWidget(m_friendListWidget);
    layout_chat->addWidget(m_chatWidget);
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

