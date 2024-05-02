#include "friendlistwidget.h"

#include <QVBoxLayout>

friendListWidget::friendListWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(WIDGETWIDTH);

//    QPalette palette = this->palette();
//    palette.setColor(QPalette::Window, QColor(217, 216, 217));
//    this->setAutoFillBackground(true);
//    this->setPalette(palette);

    init();
}

void friendListWidget::init()
{
    QPalette palette;
    m_topWidget = new QWidget(this);
    m_bottomWidget = new QWidget(this);

    m_topWidget->setFixedHeight(60);
    palette = m_topWidget->palette();
    palette.setColor(QPalette::Window, QColor(247, 247, 247));
    m_topWidget->setAutoFillBackground(true);
    m_topWidget->setPalette(palette);

//    m_bottomWidget->setFixedSize(100, 30);
    palette = m_bottomWidget->palette();
    palette.setColor(QPalette::Window, QColor(231, 229, 229));
    m_bottomWidget->setAutoFillBackground(true);
    m_bottomWidget->setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    QVBoxLayout *bottomLayout = new QVBoxLayout(m_bottomWidget);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    topLayout->setContentsMargins(10, 20, 10, 10);
    topLayout->setSpacing(10);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(0);

    m_topWidget->setLayout(topLayout);
    m_bottomWidget->setLayout(bottomLayout);

    layout->addWidget(m_topWidget);
    layout->addWidget(m_bottomWidget);

    m_searchLineEdit = new QLineEdit(m_topWidget);

    m_createGroupChat = new roundedBtn("", m_topWidget);
    m_createGroupChat->setRadius(10);
    m_createGroupChat->setFixedSize(30, 30);
    m_createGroupChat->setMouseNormalColor(QColor(226, 226, 226));
    m_createGroupChat->setMouseHovedColor(QColor(209, 209, 209));
    m_createGroupChat->setMousePressedColor(QColor(209, 209, 209));
    topLayout->addWidget(m_searchLineEdit);
    topLayout->addWidget(m_createGroupChat);
}
