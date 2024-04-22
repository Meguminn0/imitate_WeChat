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

    current_screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->setGeometry(400, 100, 700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);
    this->setMinimumSize(700 + WIDGET_MARGIN * 2, 500 + WIDGET_MARGIN * 2);

    init();
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

void wechatmainwidget::init()
{
    QPalette palette;

    // 设置背景
    palette = m_background_widget->palette();
    palette.setColor(QPalette::Window, QColor(245,245,245));
    m_background_widget->setAutoFillBackground(true);
    m_background_widget->setPalette(palette);
    m_background_widget->setGeometry(WIDGET_MARGIN, WIDGET_MARGIN, this->width() - WIDGET_MARGIN * 2, this->height() - WIDGET_MARGIN * 2);

    // 设置阴影
    QGraphicsDropShadowEffect *backGround_shadowEffect = new QGraphicsDropShadowEffect(this);
    backGround_shadowEffect->setEnabled(true);
    backGround_shadowEffect->setBlurRadius(10);
    backGround_shadowEffect->setColor(QColor(0, 0, 0, 64));
    backGround_shadowEffect->setOffset(0, 0);
    m_background_widget->setGraphicsEffect(backGround_shadowEffect);

    // 设置整体布局
    QHBoxLayout *layout_background = new QHBoxLayout(m_background_widget);
    QVBoxLayout *layout_optionBar = new QVBoxLayout(m_background_widget);
    QVBoxLayout *layout_friendList = new QVBoxLayout(m_background_widget);
//    QVBoxLayout *layout_chat = new QVBoxLayout(m_background_widget);

    QSpacerItem *spacer_friend_chat = new QSpacerItem(-1, -1, QSizePolicy::Expanding);

    // 设置布局中控件与布局之间的间距
    layout_background->setContentsMargins(0, 0, 0, 0);
    layout_optionBar->setContentsMargins(0, 0, 0, 0);
    layout_friendList->setContentsMargins(0, 0, 0, 0);
//    layout_chat->setContentsMargins(0, 0, 0, 0);

    // 设置两个相邻布局或者布局与布局外控件之间的间距
    layout_background->setSpacing(0);
    layout_optionBar->setSpacing(0);

    layout_background->setDirection(QBoxLayout::LeftToRight);
    layout_optionBar->setDirection(QBoxLayout::TopToBottom);
    layout_friendList->setDirection(QBoxLayout::TopToBottom);
//    layout_chat->setDirection(QBoxLayout::TopToBottom);

    m_background_widget->setLayout(layout_background);

    layout_background->addLayout(layout_optionBar);
    layout_background->addLayout(layout_friendList);
    layout_background->addItem(spacer_friend_chat);
//    layout_background->addLayout(layout_chat);

    layout_optionBar->addWidget(m_OptionBarWidget, 1);
    layout_friendList->addWidget(m_friendListWidget, 1);
//    layout_chat->addWidget(m_chatWidget);


    // 关闭按钮
//    m_btn_close = new roundedBtn(m_background_widget);
//    m_btn_close->setFixedSize(35, 27);
//    m_btn_close->move(m_background_widget->width() - m_btn_close->width() + 2, -1);
//    m_btn_close->setText("");
//    m_btn_close->setIcon(QIcon(":/icon/close.png"));
//    m_btn_close->setIconSize(QSize(13, 13));
//    m_btn_close->setMouseNormaldColor(QColor(Qt::transparent));
//    m_btn_close->setMouseHovedColor(QColor(251, 115, 115));
//    m_btn_close->setMousePressedColor(QColor(225, 72, 72));
//    layout_chat->addWidget(m_btn_close);

    // 全屏按钮
//    m_btn_fullScreen = new roundedBtn(m_background_widget);
//    m_btn_fullScreen->setFixedSize(35, 27);
//    m_btn_fullScreen->move(m_btn_close->x() - m_btn_fullScreen->width() + 2, -1);
//    m_btn_fullScreen->setText("");
//    m_btn_fullScreen->setIcon(QIcon(":/icon/fullScreen2.png"));
//    m_btn_fullScreen->setIconSize(QSize(10, 10));
//    m_btn_fullScreen->setMouseNormaldColor(QColor(Qt::transparent));
//    m_btn_fullScreen->setMouseHovedColor(QColor(226, 226, 226));
//    m_btn_fullScreen->setMousePressedColor(QColor(209, 209, 209));
//    layout_chat->addWidget(m_btn_fullScreen);

    // 最小化按钮
//    m_btn_min = new roundedBtn(m_background_widget);
//    m_btn_min->setFixedSize(35, 27);
//    m_btn_min->move(m_btn_fullScreen->x() - m_btn_min->width() + 2, -1);
//    m_btn_min->setText("");
//    m_btn_min->setIcon(QIcon(":/icon/min.png"));
//    m_btn_min->setIconSize(QSize(13, 13));
//    m_btn_min->setMouseNormaldColor(QColor(Qt::transparent));
//    m_btn_min->setMouseHovedColor(QColor(226, 226, 226));
//    m_btn_min->setMousePressedColor(QColor(209, 209, 209));
//    layout_chat->addWidget(m_btn_min);

    // 窗口固定按钮
//    m_btn_fixed = new roundedBtn(m_background_widget);
//    m_btn_fixed->setFixedSize(35, 27);
//    m_btn_fixed->move(m_btn_min->x() - m_btn_fixed->width() + 2, -1);
//    m_btn_fixed->setText("");
//    m_btn_fixed->setIcon(QIcon(":/icon/fixed.png"));
//    m_btn_fixed->setIconSize(QSize(15, 15));
//    m_btn_fixed->setMouseNormaldColor(QColor(Qt::transparent));
//    m_btn_fixed->setMouseHovedColor(QColor(226, 226, 226));
//    m_btn_fixed->setMousePressedColor(QColor(209, 209, 209));
//    layout_chat->addWidget(m_btn_fixed);
}

void wechatmainwidget::showFullScreenOrNormal()
{
    if(isFullScreen())
    {
        m_background_widget->setGeometry(WIDGET_MARGIN, WIDGET_MARGIN, this->width() - WIDGET_MARGIN * 2, this->height() - WIDGET_MARGIN * 2);
        this->showNormal();
    }
    else
    {
        m_background_widget->setGeometry(current_screenGeometry);

        this->showFullScreen();
    }
}

