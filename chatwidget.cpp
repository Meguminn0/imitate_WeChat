#include "chatwidget.h"

chatWidget::chatWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(100);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}
