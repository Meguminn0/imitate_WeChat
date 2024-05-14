#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "include/loginwidget.h"
#include "include/wechatmainwidget.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);

private:
    bool verifyUserInfor(const QString& id, const QString& pwd);

signals:

protected slots:
    void slot_move(QPoint point);
    void slot_userLogin(QString id, QString pwd);

private:
    LoginWidget *m_loginWidget;
    wechatmainwidget *m_wechatWidget;
};

#endif // MAINWINDOW_H
