#include <QGraphicsDropShadowEffect>
#include <QLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QMouseEvent>
#include "include/friendlistwidget.h"
#include "include/roundedbtn.h"
#include "include/wechatmainwidget.h"
#include "include/backgroundwidget.h"

#define MARGIN_WIDTH 4

wechatmainwidget::wechatmainwidget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setMinimumSize(700 + MARGIN_WIDTH * 2, 500 + MARGIN_WIDTH * 2);
    this->resize(700 + MARGIN_WIDTH * 2, 500 + MARGIN_WIDTH * 2);

    init();

    m_OptionBarWidget->show();
    m_friendListWidget->show();
    m_chatWidget->show();

    connect(m_background_widget, &backGroundWidget::sig_close, this, &wechatmainwidget::sig_close);
    connect(m_background_widget, &backGroundWidget::sig_fullScreen, this, &wechatmainwidget::sig_fullSreen);
    connect(m_background_widget, &backGroundWidget::sig_min, this, &wechatmainwidget::sig_min);
    connect(m_background_widget, &backGroundWidget::sig_enter, this, &wechatmainwidget::sig_backEnter);
    connect(m_background_widget, &backGroundWidget::sig_leave, this, &wechatmainwidget::sig_backLeave);
}

void wechatmainwidget::setMyselfId(const QString &id)
{
    this->m_myselfId = id;
}

void wechatmainwidget::setContentsMargins(int left, int top, int right, int bottom)
{
    this->m_layout->setContentsMargins(left, top, right, bottom);
}

void wechatmainwidget::init()
{
    QPalette palette;

    // 设置整体布局
    m_layout = new QBoxLayout(QBoxLayout::LeftToRight);
    m_layout_background = new QHBoxLayout();
    m_layout_optionBar = new QVBoxLayout();
    m_layout_friendList = new QVBoxLayout();
    m_layout_chat = new QVBoxLayout();

    // 设置布局中控件与布局之间的间距
    m_layout->setContentsMargins(MARGIN_WIDTH, MARGIN_WIDTH, MARGIN_WIDTH, MARGIN_WIDTH);
    m_layout_background->setContentsMargins(0, 0, 0, 0);
    m_layout_optionBar->setContentsMargins(0, 0, 0, 0);
    m_layout_friendList->setContentsMargins(0, 0, 0, 0);
    m_layout_chat->setContentsMargins(0, 0, 0, 0);

    // 设置两个相邻布局或者布局与布局外控件之间的间距
    m_layout_background->setSpacing(0);
    m_layout_optionBar->setSpacing(0);

    m_background_widget = new backGroundWidget(this);
    m_OptionBarWidget = new OptionBarWidget(m_background_widget);
    m_friendListWidget = new friendListWidget(m_background_widget);
    m_chatWidget = new chatWidget(m_background_widget);

    // 设置背景
    palette = m_background_widget->palette();
    palette.setColor(QPalette::Window, QColor(245,245,245));
    m_background_widget->setAutoFillBackground(true);
    m_background_widget->setPalette(palette);
    m_background_widget->setGeometry(0, 0, this->width(), this->height());

    this->setLayout(m_layout);
    m_layout->addWidget(m_background_widget);
    m_background_widget->setLayout(m_layout_background);

    m_layout_background->addLayout(m_layout_optionBar);
    m_layout_background->addLayout(m_layout_friendList);
    m_layout_background->addLayout(m_layout_chat);

    m_layout_optionBar->addWidget(m_OptionBarWidget);
    m_layout_friendList->addWidget(m_friendListWidget);
    m_layout_chat->addWidget(m_chatWidget);
}

