#include "include/chatmessagebox.h"
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QPointF>

chatMessageBox::chatMessageBox(QWidget *parent)
    : QWidget{parent}
{
    this->resize(parent->width(), this->height());
    QFont font = this->font();
    font.setFamily("微软雅黑");
    font.setPointSize(12);
    this->setFont(font);

    m_marginLeft = 12;
    m_marginRight = 30;
    m_marginTop = 12;
    m_marginBottom = 12;

    m_himHeadPix = new QPixmap(":/img/userHead/head2.png");
    m_himHeadPix->scaled(15, 15);
    m_myHeadPix = new QPixmap(":/img/userHead/head.png");
    m_myHeadPix->scaled(15, 15);
}

QSize chatMessageBox::setText(const QString &text, const QString &time, const MSG_TYPE& type)
{
    m_msg = text;
    m_sendTime = time;
    m_msgType = type;

    initMsgBoxRect();
    this->resize(this->width(), m_myMsgBoxRect.height());

    this->update();

    return QSize(this->width(), this->height() + m_marginBottom + m_marginTop);
}

void chatMessageBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);

    // 头像
    painter.drawPixmap(m_myHeadRect, *m_myHeadPix);

    // 消息背景框
    QColor color(149, 236, 105);
    painter.setBrush(QBrush(color));
    painter.drawRoundedRect(m_myMsgBoxRect,4,4);

    //三角
    int triangleHCenter = m_myMsgBoxTriangleRect.y() + m_myMsgBoxTriangleRect.height() / 2;
    QPointF points[3] = {
        QPointF(m_myMsgBoxTriangleRect.x() + m_myMsgBoxTriangleRect.width(), triangleHCenter),
        QPointF(m_myMsgBoxTriangleRect.x(), triangleHCenter - 5),
        QPointF(m_myMsgBoxTriangleRect.x(), triangleHCenter + 5),
    };
    QPen pen;
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawPolygon(points, 3);

    //内容
    QPen penText;
    penText.setColor(Qt::black);
    painter.setPen(penText);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter.setFont(this->font());
    painter.drawText(m_myMsgBoxTextRect, m_msg, option);
}

/*
 * @briefly 初始化聊天框的矩形大小
 * ___________________________this->width()________________________________
 * | headWidth  triangleWidth              textBackgoundRightSpacing      |
 * |   __↓____     ↓ ______________________________________  ↓            |
 * |   |     |    /|    ______________________________    |               |
 * |   |     |   < |   |______________________________|   |               |
 * |   |_____|    \|_↑__________________________________↑_|               |
 * |           ↑     |                                  |                 |
 * | head_boxSpacing textSpacing                   textSpacing              |
 * |______________________________________________________________________|
 *
 * ____________________________this->width()_______________________________
 * |       textBackgoundRightSpacing            triangleWidth   headWidth |
 * |             ↓ _______________________________________ ↓    __↓____   |
 * |               |    ______________________________    |\    |     |   |
 * |               |   |______________________________|   | >   |     |   |
 * |               |_↑__________________________________↑_|/    |_____|   |
 * |                 |                                  |     ↑           |
 * |              textSpacing                 textSpacing head_boxSpacing |
 * |______________________________________________________________________|
 */
void chatMessageBox::initMsgBoxRect()
{
    int headWidth = 32;
    int head_boxSpacing = 6;
    int triangleWidth = 6;
    int triangleHeight = headWidth;
    int textBackgoundRightSpacing = 20;
    int textSpacing = 8;

    m_textBackgroundWidth = this->width() - textBackgoundRightSpacing - m_marginLeft - m_marginRight - 2 * (head_boxSpacing + headWidth + triangleWidth);
    m_textLineMaxWidth = m_textBackgroundWidth - textSpacing * 2;

    m_himHeadRect = QRect(m_marginLeft, m_marginTop, headWidth, headWidth);
    m_myHeadRect = QRect(this->width() - headWidth - m_marginRight, m_marginTop, headWidth, headWidth);

    QSize textSize = getTextLineBreaksSize();

    m_himMsgBoxTriangleRect = QRect(m_marginLeft + headWidth + head_boxSpacing, m_marginTop, triangleWidth, triangleHeight);
    m_myMsgBoxTriangleRect = QRect(this->width() - m_marginRight - headWidth - head_boxSpacing - triangleWidth,
                                   m_marginTop,
                                   triangleWidth,
                                   triangleHeight);

    if(textSize.width() < m_textLineMaxWidth)
    {
        m_himMsgBoxRect = QRect(m_himMsgBoxTriangleRect.x() + m_himMsgBoxTriangleRect.width(),
                                m_marginTop,
                                textSize.width() + 2 * textSpacing,
                                textSize.height() + textSpacing);
        m_myMsgBoxRect = QRect(m_myMsgBoxTriangleRect.x() - textSize.width() - 2 * textSpacing,
                               m_marginTop,
                               textSize.width() + 2 * textSpacing,
                               textSize.height() + textSpacing);
    }
    else
    {
        m_himMsgBoxRect = QRect(m_himMsgBoxTriangleRect.x() + m_himMsgBoxTriangleRect.width(),
                                m_marginTop,
                                m_textBackgroundWidth,
                                textSize.height() + textSpacing);
        m_myMsgBoxRect = QRect(m_myMsgBoxTriangleRect.x() - textSize.width() - 2 * textSpacing,
                               m_marginTop,
                               m_textBackgroundWidth,
                               textSize.height() + textSpacing);
    }

    m_himMsgBoxTextRect = QRect(m_himMsgBoxRect.x() + textSpacing, m_himMsgBoxRect.y() + textSpacing / 2,
                                textSize.width(), textSize.height());
    m_myMsgBoxTextRect = QRect(m_myMsgBoxRect.x() + textSpacing, m_myMsgBoxRect.y() + textSpacing / 2,
                                textSize.width(),  textSize.height());
}

/*
 * @briefly 获取文本信息在自动换行后的信息框大小
 */
QSize chatMessageBox::getTextLineBreaksSize()
{
    QFontMetricsF fontMetr(this->font());
    m_textLineHeight = fontMetr.lineSpacing();
    int count_LineBreak = m_msg.count('\n');
    int lineWidth = 0;
    if(count_LineBreak == 0)
    {
        // 如果消息中换行符数量为0
        lineWidth = fontMetr.horizontalAdvance(m_msg);
        if(lineWidth > m_textLineMaxWidth)
        {
            // 消息行宽大于消息框中文本行的宽度
            int lines = lineWidth / m_textLineMaxWidth;
            lineWidth = m_textLineMaxWidth;
            count_LineBreak += lines;
        }
    }
    else
    {
        for(int i = 0; i < (count_LineBreak + 1); ++i)
        {
            QString thisLine = m_msg.split('\n').at(i);
            int thislineWidth = fontMetr.horizontalAdvance(thisLine);
            lineWidth = thislineWidth > lineWidth ? thislineWidth : lineWidth;
            if(lineWidth > m_textLineMaxWidth)
            {
                int lines = lineWidth / m_textLineMaxWidth;
                lineWidth = m_textLineMaxWidth;
                count_LineBreak += lines;
            }
        }
        ++count_LineBreak;
    }

    return QSize(lineWidth, (count_LineBreak + 1) * m_textLineHeight);
}
