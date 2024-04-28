#include "backgroundwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QPushButton>
#include <QPen>
#include <QPainter>

backGroundWidget::backGroundWidget(QWidget *parent)
    : QWidget{parent}
{
    setShadow();

    init();

    connect(m_btn_close, &QPushButton::clicked, this, &backGroundWidget::signClose);
    connect(m_btn_fullScreen, &QPushButton::clicked, this, &backGroundWidget::signFullScreen);
    connect(m_btn_min, &QPushButton::clicked, this, &backGroundWidget::signMin);
}

void backGroundWidget::moveTopRightButtom()
{
    m_btn_close->move(this->width() - m_btn_close->width() + 2, -1);
    m_btn_fullScreen->move(m_btn_close->x() - m_btn_fullScreen->width() + 2, -1);
    m_btn_min->move(m_btn_fullScreen->x() - m_btn_min->width() + 2, -1);
    m_btn_fixed->move(m_btn_min->x() - m_btn_fixed->width() + 2,  -1);
    m_btn_close->raise();
    m_btn_fullScreen->raise();
    m_btn_min->raise();
    m_btn_fixed->raise();
}

void backGroundWidget::init()
{
    // 初始化成员变量
    m_btn_close = new roundedBtn("", this);
    m_btn_close->setFixedSize(35, 27);
    m_btn_close->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    m_btn_close->setAllowButton(Qt::LeftButton);
    m_btn_close->setMouseNormaldColor(Qt::transparent);
    m_btn_close->setMouseHovedColor(QColor(251, 115, 115));
    m_btn_close->setMousePressedColor(QColor(225, 72, 72));

    m_btn_fullScreen = new roundedBtn("", this);
    m_btn_fullScreen->setFixedSize(35, 27);
    m_btn_fullScreen->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    m_btn_fullScreen->setAllowButton(Qt::LeftButton);
    m_btn_fullScreen->setMouseNormaldColor(Qt::transparent);
    m_btn_fullScreen->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_fullScreen->setMousePressedColor(QColor(209, 209, 209));

    m_btn_min = new roundedBtn("", this);
    m_btn_min->setFixedSize(35, 27);
    m_btn_min->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMinButton));
    m_btn_min->setAllowButton(Qt::LeftButton);
    m_btn_min->setMouseNormaldColor(Qt::transparent);
    m_btn_min->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_min->setMousePressedColor(QColor(209, 209, 209));

    m_btn_fixed = new roundedBtn("", this);
    m_btn_fixed->setFixedSize(35, 27);
    m_btn_fixed->setIcon(QIcon(":/icon/fixed.png"));
    m_btn_fixed->setIconSize(QSize(15, 15));
    m_btn_fixed->setAllowButton(Qt::LeftButton);
    m_btn_fixed->setMouseNormaldColor(Qt::transparent);
    m_btn_fixed->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_fixed->setMousePressedColor(QColor(209, 209, 209));

}

void backGroundWidget::setShadow()
{
    // 设置阴影
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 64));
    shadowEffect->setOffset(0, 0);
    this->setGraphicsEffect(shadowEffect);
}

void backGroundWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    moveTopRightButtom();
}

void backGroundWidget::paintEvent(QPaintEvent *event)
{
//    QPainter *painter = new QPainter(this);
//    painter->setRenderHint(QPainter::SmoothPixmapTransform);
//    QPen pen(Qt::NoPen);
//    painter->setPen(pen);

//    QBrush brush(QColor(245,245,245));
//    painter->setBrush(brush);

//    painter->drawRoundedRect(this->rect(), 10, 10);

    QWidget::paintEvent(event);
}

void backGroundWidget::onFullScreen(bool isFullScreen, const int width, const int height)
{
    if(!isFullScreen)
    {
        setGeometry(4, 4, width - 8, height - 8);
        moveTopRightButtom();
    }
    else
    {
        setGeometry(0, 0, width, height);
        moveTopRightButtom();
    }
}

