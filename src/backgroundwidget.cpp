#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QIcon>

#include "include/backgroundwidget.h"

backGroundWidget::backGroundWidget(QWidget *parent)
    : QWidget{parent}
{
    setShadow();

    init();

    connect(m_btn_close, &QPushButton::clicked, this, &backGroundWidget::sig_close);
    connect(m_btn_fullScreen, &QPushButton::clicked, this, &backGroundWidget::sig_fullScreen);
    connect(m_btn_min, &QPushButton::clicked, this, &backGroundWidget::sig_min);
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
    QIcon closeIcon(":/img/icon/close.png");
    m_btn_close->setIcon(closeIcon.isNull() ? this->style()->standardIcon(QStyle::SP_TitleBarCloseButton) : closeIcon);
    m_btn_close->setIconSize(QSize(11, 11));
    m_btn_close->setAllowButton(Qt::LeftButton);
    m_btn_close->setMouseNormalColor(Qt::transparent);
    m_btn_close->setMouseHovedColor(QColor(251, 115, 115));
    m_btn_close->setMousePressedColor(QColor(225, 72, 72));

    m_btn_fullScreen = new roundedBtn("", this);
    m_btn_fullScreen->setFixedSize(35, 27);
    QIcon fullScreenIcon(":/img/icon/fullScreen2.png");
    m_btn_fullScreen->setIcon(fullScreenIcon.isNull() ? this->style()->standardIcon(QStyle::SP_TitleBarMaxButton) : fullScreenIcon);
    m_btn_fullScreen->setIconSize(QSize(11, 11));
    m_btn_fullScreen->setAllowButton(Qt::LeftButton);
    m_btn_fullScreen->setMouseNormalColor(Qt::transparent);
    m_btn_fullScreen->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_fullScreen->setMousePressedColor(QColor(209, 209, 209));

    m_btn_min = new roundedBtn("", this);
    m_btn_min->setFixedSize(35, 27);
    QIcon minIcon(":/img/icon/min.png");
    m_btn_min->setIcon(minIcon.isNull() ? this->style()->standardIcon(QStyle::SP_TitleBarMinButton) : minIcon);
    m_btn_min->setIconSize(QSize(11, 11));
    m_btn_min->setAllowButton(Qt::LeftButton);
    m_btn_min->setMouseNormalColor(Qt::transparent);
    m_btn_min->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_min->setMousePressedColor(QColor(209, 209, 209));

    m_btn_fixed = new roundedBtn("", this);
    m_btn_fixed->setFixedSize(35, 27);
    QIcon fixedIcon(":/img/icon/fixed.png");
    m_btn_fixed->setIcon(fixedIcon);
    m_btn_fixed->setIconSize(QSize(15, 15));
    m_btn_fixed->setAllowButton(Qt::LeftButton);
    m_btn_fixed->setMouseNormalColor(Qt::transparent);
    m_btn_fixed->setMouseHovedColor(QColor(226, 226, 226));
    m_btn_fixed->setMousePressedColor(QColor(209, 209, 209));
}

void backGroundWidget::setShadow()
{
    // 设置阴影
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(12);
    shadowEffect->setColor(QColor(0, 0, 0, 64));
    shadowEffect->setOffset(0, 0);
    this->setGraphicsEffect(shadowEffect);
}

void backGroundWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    moveTopRightButtom();
}

void backGroundWidget::enterEvent(QEnterEvent *event)
{
    QWidget::enterEvent(event);
    emit sig_enter();
}

void backGroundWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    emit sig_leave();
}
