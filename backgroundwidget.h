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

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

signals:


private:
    QPushButton *m_btn_close;
    QPushButton *m_btn_fullScreen;
    QPushButton *m_btn_min;
    QPushButton *m_btn_fixed;

    int m_radius;
};

#endif // BACKGROUNDWIDGET_H
