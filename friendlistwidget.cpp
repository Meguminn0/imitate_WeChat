#include "friendlistwidget.h"

friendListWidget::friendListWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(WIDGETWIDTH);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(217, 216, 217));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}
