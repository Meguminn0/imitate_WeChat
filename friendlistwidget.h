/******************************************************
 *
 * @file            friendlistwidget.h
 * @briefly-Cn      好友列表
 * @briefly-En      Friends list
 *
 * @author          Meguminn0
 * @date            2024/04/23
 * @history
 *
********************************************************/

#ifndef FRIENDLISTWIDGET_H
#define FRIENDLISTWIDGET_H

#include <QWidget>

class friendListWidget : public QWidget
{
    Q_OBJECT
public:
    const int WIDGETWIDTH = 226;

    explicit friendListWidget(QWidget *parent = nullptr);

signals:

};

#endif // FRIENDLISTWIDGET_H
