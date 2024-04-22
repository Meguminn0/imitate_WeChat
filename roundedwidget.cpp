#include "roundedwidget.h"

#include <QPainter>

roundedWidget::roundedWidget(QWidget *parent)
    : QWidget{parent}
{

}

//void roundedWidget::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    // 开启抗锯齿
//    painter.setRenderHint(QPainter::Antialiasing);
//    QPen pen(Qt::NoPen);
//    painter.setPen(pen);
//    // 设置颜色
//    QColor currentColor;

//    if(isDown() && m_pressColor.isValid())
//    {
//        currentColor = m_pressColor;
//    }
//    else if(underMouse() && m_hovedColor.isValid())
//    {
//        currentColor = m_hovedColor;
//    }
//    else if(m_normalColor.isValid())
//    {
//        currentColor = m_normalColor;
//    }
//    else
//    {
//        m_normalColor = QColor(225,225,225);
//        currentColor = m_normalColor;
//    }

//    QBrush brush(currentColor);
//    painter.setBrush(brush);
//}
