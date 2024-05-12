/******************************************************
 *
 * @file            roundedbtn.h
 * @briefly-Cn      自定义的圆角按钮
 * @briefly-En      Customized rounded buttons
 *
 * @author          Meguminn0
 * @date            2024/04/8
 * @history
 *
********************************************************/

#ifndef ROUNDEDBTN_H
#define ROUNDEDBTN_H

#include <QPushButton>

class roundedBtn : public QPushButton
{
public:
    enum RoundedCorner
    {
        none = 0,
        topLeft = 1,
        topRight = 2,
        bottomLeft = 4,
        bottomRight = 8,
        all = 15
    };

public:
    roundedBtn(QWidget *parent = nullptr);
    roundedBtn(QString content, QWidget *parent = nullptr);
    void setAllowButton(QFlags<Qt::MouseButton> mouseButton);
    int setRoundedCorner(int corner);
    void setRadius(int radius);
    void setMouseNormalColor(const QColor &color);
    void setMouseHovedColor(const QColor &color);
    void setMousePressedColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    /* 允许的鼠标按钮，默认为鼠标左键
     * allow the mouse buttons, default value is  Left button
     */
    QFlags<Qt::MouseButton> m_allowButton;

    /* 设置圆角，默认为不设置
     * set rounded corners, default value is none */
    QFlags<roundedBtn::RoundedCorner> m_roundedCorner;

    /* 设置圆角半径
     * set rounded radius
     */
    int m_radius;

    /* 设置按钮三种状态的颜色 ：正常状态，鼠标悬停状态，按下状态。
     * set three status of Button color: nornal, hoved, pressed
     */
    QColor m_normalColor;
    QColor m_hovedColor;
    QColor m_pressColor;
};

#endif // ROUNDEDBTN_H
