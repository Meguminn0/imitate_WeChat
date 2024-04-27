/******************************************************
 *
 * @file            backgroundwidget.h
 * @briefly-Cn      自定义背景界面
 * @briefly-En      Customize the background interface
 *
 * @author          Meguminn0
 * @date            2024/04/23
 * @history
 *
********************************************************/

#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include "roundedbtn.h"

#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>

class backGroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit backGroundWidget(QWidget *parent = nullptr);

    void moveTopRightButtom();

protected:
    void init();
    void setShadow();

public slots:
    void onFullScreen(bool isFullScreen, const int widht, const int height);

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void signClose();
    void signFullScreen();
    void signMin();

private:
    roundedBtn *m_btn_close;
    roundedBtn *m_btn_fullScreen;
    roundedBtn *m_btn_min;
    roundedBtn *m_btn_fixed;

    int m_radius;
};

#endif // BACKGROUNDWIDGET_H
