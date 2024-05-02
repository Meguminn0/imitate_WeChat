#include "roundedbtn.h"

#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

roundedBtn::roundedBtn(QWidget *parent) :
    QPushButton(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFlat(true);

    this->setText("myroundedBtn");

    // 默认值
    this->setGeometry(0, 0, 93, 28);
    m_allowButton = Qt::LeftButton;
    m_roundedCorner = RoundedCorner::none;
    m_radius = 0;
    m_normalColor = QColor(225, 225, 225);
    m_hovedColor = QColor(229, 241, 251);
    m_pressColor = QColor(204, 228, 247);
}

roundedBtn::roundedBtn(QString content, QWidget *parent) : roundedBtn(parent)
{
    this->setText(content);
}

void roundedBtn::setAllowButton(QFlags<Qt::MouseButton> mouseButton)
{
    m_allowButton = mouseButton;
}

int roundedBtn::setRoundedCorner(int corner)
{
    m_roundedCorner = QFlags<RoundedCorner>(corner);
    return m_roundedCorner.toInt();
}

void roundedBtn::setRadius(int radius)
{
    m_radius = radius;
}

void roundedBtn::setMouseNormalColor(const QColor &color)
{
    m_normalColor = color;
}

void roundedBtn::setMouseHovedColor(const QColor &color)
{
    m_hovedColor = color;
}

void roundedBtn::setMousePressedColor(const QColor &color)
{
    m_pressColor = color;
}

void roundedBtn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::NoPen);
    painter.setPen(pen);
    // 设置颜色
    QColor currentColor;

    if(isDown() && m_pressColor.isValid())
    {
        currentColor = m_pressColor;
    }
    else if(underMouse() && m_hovedColor.isValid())
    {
        currentColor = m_hovedColor;
    }
    else if(m_normalColor.isValid())
    {
        currentColor = m_normalColor;
    }
    else
    {
        m_normalColor = QColor(225,225,225);
        currentColor = m_normalColor;
    }

    QBrush brush(currentColor);
    painter.setBrush(brush);

    // 获得按钮矩形
    QRect rect = this->contentsRect();
    int rect_x = rect.x();
    int rect_y = rect.y();
    int rect_width = rect.width();
    int rect_height = rect.height();
    int half_min_edge = std::min(rect_width, rect_height) / 2;
    // 重新绘制按钮的矩形圆角样式
    if(m_roundedCorner.toInt() == RoundedCorner::none || m_radius == 0)
    {
        painter.drawRoundedRect(rect.adjusted(1, 1, -1, -1), 0, 0);
    }
    else
    {
        if(this->m_radius < half_min_edge)
        {
            // 圆半径小于按钮宽度
            painter.drawRect(rect_x, rect_y + m_radius, rect_width, rect_height - 2 * m_radius);
            painter.drawRect(rect_x + m_radius, rect_y, rect_width - 2 * m_radius, rect_height);
            QPoint topLeftEllipse(rect_x + m_radius, rect_x + m_radius);
            QPoint topRightEllipse(topLeftEllipse.x() + rect_width - 2 * m_radius, topLeftEllipse.y());
            QPoint bottomLeftEllipse(topLeftEllipse.x(), topLeftEllipse.y() + rect_height - 2 * m_radius);
            QPoint bottomRightEllipse(bottomLeftEllipse.x() + rect_width - 2 * m_radius, bottomLeftEllipse.y());
            if((m_roundedCorner & RoundedCorner::topLeft).toInt() == 0)
            {
                painter.drawRect(rect_x, rect_y, m_radius, m_radius);
            }
            else
            {
                painter.drawEllipse(topLeftEllipse, m_radius, m_radius);
            }

            if((m_roundedCorner & RoundedCorner::topRight).toInt() == 0)
            {
                painter.drawRect(rect_width - m_radius, rect_y, m_radius, m_radius);
            }
            else
            {
                painter.drawEllipse(topRightEllipse, m_radius, m_radius);
            }

            if((m_roundedCorner & RoundedCorner::bottomLeft).toInt() == 0)
            {
                painter.drawRect(rect_x, rect_height - m_radius, m_radius, m_radius);
            }
            else
            {
                painter.drawEllipse(bottomLeftEllipse, m_radius, m_radius);
            }

            if((m_roundedCorner & RoundedCorner::bottomRight).toInt() == 0)
            {
                painter.drawRect(rect_width - m_radius, rect_height - m_radius, m_radius, m_radius);
            }
            else
            {
                painter.drawEllipse(bottomRightEllipse, m_radius, m_radius);
            }
        }

        if(this->m_radius >= half_min_edge)
        {
            // 圆半径大于等于按钮宽度
            m_radius = half_min_edge;
            QPoint leftOrTopEllipse(rect_x + m_radius, rect_y + m_radius);
            QPoint rightOrBottomEllipse;
            if(half_min_edge == rect_width / 2)
            {
                // 当按钮是竖着的
                rightOrBottomEllipse.setX(leftOrTopEllipse.x());
                rightOrBottomEllipse.setY(leftOrTopEllipse.y() + rect_height - 2 * m_radius);
                painter.drawRect(rect_x, rect_y + m_radius, rect_width, rect_height - 2 * m_radius);
            }
            else
            {
                rightOrBottomEllipse.setX(leftOrTopEllipse.x() + rect_width - 2 * m_radius);
                rightOrBottomEllipse.setY(leftOrTopEllipse.y());
                painter.drawRect(rect_x + m_radius, rect_y, rect_width - 2 * m_radius, rect_height);
            }

            if((m_roundedCorner & RoundedCorner::topLeft).toInt() == 0)
            {
                painter.drawRect(rect_x, rect_y, m_radius, m_radius);
            }
            if((m_roundedCorner & RoundedCorner::topRight).toInt() == 0)
            {
                painter.drawRect(rect_width - m_radius, rect_y, m_radius, m_radius);
            }
            if((m_roundedCorner & RoundedCorner::bottomLeft).toInt() == 0)
            {
                painter.drawRect(rect_x, rect_height - m_radius, m_radius, m_radius);
            }
            if((m_roundedCorner & RoundedCorner::bottomRight).toInt() == 0)
            {
                painter.drawRect(rect_width - m_radius, rect_height - m_radius, m_radius, m_radius);
            }

            painter.drawEllipse(leftOrTopEllipse, m_radius, m_radius);
            painter.drawEllipse(rightOrBottomEllipse, m_radius, m_radius);
        }
    }

    // 绘制按钮文本
    if(!this->text().isEmpty())
    {
        painter.setFont(this->font());
        pen.setStyle(Qt::SolidLine);
        pen.setColor(this->palette().color(QPalette::ButtonText));
        painter.setPen(pen);
        painter.drawText(this->rect(), Qt::AlignCenter, this->text());
    }

    // 绘制icon
    if(!this->icon().isNull())
    {
        QPixmap pixmap = this->icon().pixmap(this->iconSize());
        pixmap.scaled(this->iconSize());
        painter.drawPixmap(rect.center() - pixmap.rect().center(), pixmap);
    }

    event->accept();
}

void roundedBtn::enterEvent(QEnterEvent *event)
{
    update();
    QPushButton::enterEvent(event);
}

void roundedBtn::leaveEvent(QEvent *event)
{
    update();
    QPushButton::leaveEvent(event);
}

void roundedBtn::mousePressEvent(QMouseEvent *event)
{
    if (m_allowButton.testFlags(event->button()))
    {
        QPushButton::mousePressEvent(event);
        this->setDown(true);
        update();
        event->accept();
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
}
