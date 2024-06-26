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

#include "friendlistitem.h"
#include "roundedbtn.h"

#include <QWidget>
#include <QLineEdit>
#include <QList>
#include <QListWidget>

class friendListWidget : public QWidget
{
    Q_OBJECT
public:
    const int WIDGETWIDTH = 216;

    explicit friendListWidget(QWidget *parent = nullptr);

    void addfriendItem(const QString &friendId);

protected:
    void init();

signals:


private:
    QWidget *m_topWidget;
    QListWidget *m_bottomWidget;

    QLineEdit *m_searchLineEdit;
    roundedBtn *m_createGroupChat;
};

#endif // FRIENDLISTWIDGET_H
