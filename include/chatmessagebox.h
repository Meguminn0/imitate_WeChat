/******************************************************
 *
 * @file            chatmessagebox.h
 * @briefly-Cn      聊天框
 * @briefly-En      Chat box
 *
 * @author          Meguminn0
 * @date            2024/05/07
 * @history
 *
********************************************************/

#ifndef CHATMESSAGEBOX_H
#define CHATMESSAGEBOX_H

#include <QSize>
#include <QWidget>

class chatMessageBox : public QWidget
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

    explicit chatMessageBox(QWidget *parent = nullptr);

    QSize setText(const QString &text, const QString &time, const MSG_TYPE& type);

protected:
    void paintEvent(QPaintEvent *event) override;

    void initMsgBoxRect();
    QSize getTextLineBreaksSize();

signals:

protected slots:


private:
    int m_marginLeft;
    int m_marginRight;
    int m_marginTop;
    int m_marginBottom;

    int m_textBackgroundWidth;
    int m_textLineMaxWidth;
    int m_textLineHeight;
    QString m_msg;
    QString m_sendTime;

    MSG_TYPE m_msgType;

    /* him message Box
     * ________   ______________________
     * |      |  / __________________   |
     * | head | < |_______text_______|  |
     * |______|  \______________________|
     */
    QPixmap *m_himHeadPix;
    QRect m_himHeadRect;
    QRect m_himMsgBoxRect;
    QRect m_himMsgBoxTriangleRect;
    QRect m_himMsgBoxTextRect;

    /* him message Box
     *   ______________________   ________
     *  | ___________________  \  |      |
     *  | |_______text_______|  > | head |
     *  |______________________/  |______|
     */
    QPixmap *m_myHeadPix;
    QRect m_myHeadRect;
    QRect m_myMsgBoxRect;
    QRect m_myMsgBoxTriangleRect;
    QRect m_myMsgBoxTextRect;
};

#endif // CHATMESSAGEBOX_H
