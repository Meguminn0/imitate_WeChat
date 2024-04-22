#include "optionbarwidget.h"

#include <QHBoxLayout>
#include <QPalette>

OptionBarWidget::OptionBarWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(55);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setDirection(QBoxLayout::TopToBottom);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(46, 46, 46));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}
