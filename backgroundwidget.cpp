#include "backgroundwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QPushButton>

backGroundWidget::backGroundWidget(QWidget *parent)
    : QWidget{parent}
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 64));
    shadowEffect->setOffset(0, 0);
    this->setGraphicsEffect(shadowEffect);

    m_btn_close = new roundedBtn("", this);
    m_btn_fullScreen = new roundedBtn("", this);
    m_btn_min = new roundedBtn("", this);
    m_btn_fixed = new roundedBtn("", this);

    m_btn_close->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    m_btn_fullScreen->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    m_btn_min->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarMinButton));
    m_btn_fixed->setIcon(QIcon(":/icon/fixed.png"));
    m_btn_fixed->setIconSize(QSize(15, 15));

    m_btn_close->setFixedSize(35, 27);
    m_btn_fullScreen->setFixedSize(35, 27);
    m_btn_min->setFixedSize(35, 27);
    m_btn_fixed->setFixedSize(35, 27);

    m_btn_close->raise();
    m_btn_fullScreen->raise();
    m_btn_min->raise();
    m_btn_fixed->raise();
}

void backGroundWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void backGroundWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    m_btn_close->move(this->width() - m_btn_close->width() + 2, -1);
    m_btn_fullScreen->move(m_btn_close->x() - m_btn_fullScreen->width() + 2, -1);
    m_btn_min->move(m_btn_fullScreen->x() - m_btn_min->width() + 2, -1);
    m_btn_fixed->move(m_btn_min->x() - m_btn_fixed->width() + 2,  -1);
}
