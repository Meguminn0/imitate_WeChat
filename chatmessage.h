/******************************************************
 *
 * @file            chatmessage.h
 * @briefly-Cn      聊天框
 * @briefly-En      Chat box
 *
 * @author          Meguminn0
 * @date            2024/05/07
 * @history
 *
********************************************************/

#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>

class chatMessage : public QWidget
{
    Q_OBJECT
public:
    enum MSG_TYPE
    {
        SYSTEM = 0, // 系统消息
        ME = 1,     // 用户自己
        HIM = 2,    // 用户的聊天对象
        TIME = 3,   // 时间
    };

    explicit chatMessage(QWidget *parent = nullptr);

    void setText(const QString &text, const QString &time, const MSG_TYPE& type);

protected:
    void paintEvent(QPaintEvent *event) override;

    void initMsgBoxRect();
    QSize getTextLineBreaksSize();

signals:

protected slots:


private:
    int m_textBackgroundWidth;
    int m_textLineWidth;
    int m_textLineHeight;
    int m_spaceWid;
    QString m_msg;
    QString m_sendTime;

    MSG_TYPE m_msgType;

    /* him message Box
     *   ______________________
     *  /                      |
     * <         text          |
     *  \______________________|
     */
    QPixmap *m_himHeadPix;
    QRect m_himheadRect;
    QRect m_himMsgBoxRect;
    QRect m_himMsgBoxTriangleRect;
    QRect m_himMsgBoxTextRect;

    /* him message Box
     *   ______________________
     *  |                      \
     *  |        text           >
     *  |______________________/
     */
    QPixmap *m_myHeadPix;
    QRect m_myHeadRect;
    QRect m_myMsgBoxRect;
    QRect m_myMsgBoxTriangleRect;
    QRect m_myMsgBoxTextRect;
};

#endif // CHATMESSAGE_H
