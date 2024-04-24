#include "chatwidget.h"

chatWidget::chatWidget(QWidget *parent)
    : QWidget{parent}
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}
