#include "chatmessage.h"

#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>

chatMessage::chatMessage(QWidget *parent)
    : QWidget{parent}
{
    QFont font = this->font();
    font.setFamily("MicrosoftYaHei");
    font.setPointSize(12);
    this->setFont(font);
    m_himHeadPix = new QPixmap(":/head2.png");
    m_himHeadPix->scaled(15, 15);
    m_myHeadPix = new QPixmap(":/head.png");
    m_myHeadPix->scaled(15, 15);
}

void chatMessage::setText(const QString &text, const QString &time, const MSG_TYPE& type)
{
    m_msg = text;
    m_sendTime = time;
    m_msgType = type;

    initMsgBoxRect();

    this->update();
}

void chatMessage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    // 头像
    painter.drawPixmap(m_myHeadRect, *m_myHeadPix);

    // 消息背景框
    QColor color(75,164,242);
    painter.setBrush(QBrush(color));
    painter.drawRoundedRect(m_myMsgBoxRect,4,4);

    //三角
    QPointF points[3] = {
        QPointF(m_myMsgBoxTriangleRect.x() + m_myMsgBoxTriangleRect.width(), 30),
        QPointF(m_myMsgBoxTriangleRect.x(), 25),
        QPointF(m_myMsgBoxTriangleRect.x(), 35),
    };
    QPen pen;
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawPolygon(points, 3);

    //内容
    QPen penText;
    penText.setColor(Qt::white);
    painter.setPen(penText);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter.setFont(this->font());
    painter.drawText(m_myMsgBoxTextRect, m_msg, option);
}

/*
 * @briefly 初始化聊天框的矩形大小
 */
void chatMessage::initMsgBoxRect()
{
    int headWidth = 30;
    int headSpacing = 12;
    int triangleWidth = 6;
    int triangleHeight = 30;
    int textBackgoundRightSpacing = 20;
    int textSpacing = 12;

    m_textBackgroundWidth = this->width()  - textBackgoundRightSpacing - 2 * (2 * headSpacing + headWidth);
    m_textLineWidth = m_textBackgroundWidth - textSpacing * 2;

    m_himheadRect = QRect(headSpacing, headSpacing, headWidth, headWidth);
    m_myHeadRect = QRect(this->width() - headWidth - headSpacing, headSpacing, headWidth, headWidth);

    QSize textSize = getTextLineBreaksSize();

    qDebug() << "get text size: " << textSize;

    m_himMsgBoxTriangleRect = QRect(headWidth + 2 * headSpacing, m_textLineHeight / 2, triangleWidth, triangleHeight);
    m_myMsgBoxTriangleRect = QRect(this->width() - headWidth - 2 * headSpacing - triangleWidth,
                                   m_textLineHeight / 2,
                                   triangleWidth,
                                   triangleHeight);

    if(textSize.width() < m_textLineWidth)
    {
        m_himMsgBoxRect = QRect(m_himMsgBoxTriangleRect.x() + m_himMsgBoxTriangleRect.width(),
                                m_textLineHeight / 4 * 3,
                                textSize.width() + 2 * textSpacing,
                                textSize.height() + textSpacing * 2);
        m_myMsgBoxRect = QRect(this->width() - textBackgoundRightSpacing - 2 * textSpacing - textSize.width() - m_myMsgBoxTriangleRect.width() - headWidth - headSpacing,
                               m_textLineHeight / 4 * 3,
                               textSize.width() + 2 * textSpacing,
                               textSize.height() + textSpacing * 2);
    }
    else
    {
        m_himMsgBoxRect = QRect(m_himMsgBoxTriangleRect.x() + m_himMsgBoxTriangleRect.width(),
                                m_textLineHeight / 4 * 3,
                                m_textBackgroundWidth + 2 * textSpacing,
                                textSize.height() + textSpacing * 2);
        m_myMsgBoxRect = QRect(this->width() - textBackgoundRightSpacing - 2 * textSpacing - textSize.width() - m_myMsgBoxTriangleRect.width() - headWidth - headSpacing,
                               m_textLineHeight / 4 * 3,
                               m_textBackgroundWidth + 2 * textSpacing,
                               textSize.height() + textSpacing * 2);
    }

    m_himMsgBoxTextRect = QRect(m_himMsgBoxRect.x() + textSpacing, m_himMsgBoxRect.y() + headSpacing,
                                textSize.width(), m_himMsgBoxRect.height() - 2 * textSpacing);
    m_himMsgBoxTextRect = QRect(m_myMsgBoxRect.x() + textSpacing, m_myMsgBoxRect.y() + headSpacing,
                                textSize.width(), m_myMsgBoxRect.height() - 2 * textSpacing);

//    return textSize;
    this->setFixedSize(textSize);
}

/*
 * @briefly 获取文本信息在自动换行后的信息框大小
 */
QSize chatMessage::getTextLineBreaksSize()
{
    QFontMetricsF fontMetr(this->font());
    m_textLineHeight = fontMetr.lineSpacing();
    int count_LineBreak = m_msg.count('\n');
    int lineMaxWidth = 0;
    if(count_LineBreak == 0)
    {
        // 如果消息中换行符数量为0
        lineMaxWidth = fontMetr.horizontalAdvance(m_msg);
        if(lineMaxWidth > m_textLineWidth)
        {
            // 消息行宽大于消息框中文本行的宽度
            int lines = lineMaxWidth / m_textLineWidth;
//            int line_Characters = m_textLineWidth / fontMetr.horizontalAdvance(" ");
            lineMaxWidth = m_textLineWidth;
            count_LineBreak += lines;
        }
    }
    else
    {
        for(int i = 0; i < count_LineBreak; ++i)
        {
            QString value = m_msg.split('\n').at(i);
            int thislineWidth = fontMetr.horizontalAdvance(value);
            lineMaxWidth = thislineWidth > lineMaxWidth ? thislineWidth : lineMaxWidth;
            if(lineMaxWidth > m_textLineWidth)
            {
                int lines = lineMaxWidth / m_textLineWidth;
//                int line_Characters = m_textLineWidth / fontMetr.horizontalAdvance(" ");
                lineMaxWidth = m_textLineWidth;
                count_LineBreak += lines;
            }
        }
    }

    return QSize(lineMaxWidth, (count_LineBreak + 1) * m_textLineHeight);
}
