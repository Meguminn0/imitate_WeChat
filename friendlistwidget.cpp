#include "friendListwidget.h"
#include "friendListitem.h"

#include <QAction>
#include <QList>
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
    m_bottomWidget = new QListWidget(this);

    m_topWidget->setFixedSize(this->width(), 60);
    palette = m_topWidget->palette();
    palette.setColor(QPalette::Window, QColor(247, 247, 247));
    m_topWidget->setAutoFillBackground(true);
    m_topWidget->setPalette(palette);

    m_bottomWidget->setFixedWidth(this->width());
    palette = m_bottomWidget->palette();
    palette.setColor(QPalette::Base, QColor(231, 229, 229));
    m_bottomWidget->setAutoFillBackground(true);
    m_bottomWidget->setPalette(palette);
    m_bottomWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    topLayout->setContentsMargins(12, 20, 12, 10);
    topLayout->setSpacing(10);

    m_searchLineEdit = new QLineEdit(m_topWidget);
    m_searchLineEdit->setFixedHeight(25);
    m_searchLineEdit->setStyleSheet(
        "QLineEdit { "
        "   border: 1px solid transparent;"
        "   border-radius : 5px;"
        "   background-color: rgb(226, 226, 226);"
        "}"
        "QLineEdit:focus {"
        "   outline: none;" // 去除获取焦点时的轮廓线
        "   border: 1px solid rgb(222,220,219);"
        "   background-color: transparent; /* 替换为所需的颜色 */"
        "}"
    );
    QAction *searchLineEdit_action = new QAction(m_searchLineEdit);
    searchLineEdit_action->setIcon(QIcon(":/icon/seaerch.png"));

    m_searchLineEdit->addAction(searchLineEdit_action, QLineEdit::LeadingPosition);
    m_searchLineEdit->setClearButtonEnabled(true);
    m_searchLineEdit->setPlaceholderText("搜索");

    m_createGroupChat = new roundedBtn("", m_topWidget);
    m_createGroupChat->setRoundedCorner(roundedBtn::RoundedCorner::all);
    m_createGroupChat->setRadius(5);
    m_createGroupChat->setFixedSize(25, 25);
    m_createGroupChat->setMouseNormalColor(QColor(226, 226, 226));
    m_createGroupChat->setMouseHovedColor(QColor(209, 209, 209));
    m_createGroupChat->setMousePressedColor(QColor(209, 209, 209));
    m_createGroupChat->setIcon(QIcon(":/icon/plus.png"));
    m_createGroupChat->setIconSize(QSize(13, 13));

    this->setLayout(layout);
    layout->addWidget(m_topWidget);
    layout->addWidget(m_bottomWidget);
    m_topWidget->setLayout(topLayout);
//    m_bottomWidget->setLayout(bottomLayout);

    topLayout->addWidget(m_searchLineEdit);
    topLayout->addWidget(m_createGroupChat);

//    m_friendList = new QList<friendlistItem*>();
    friendlistItem *item1 = new friendlistItem(m_bottomWidget);
    friendlistItem *item2 = new friendlistItem(m_bottomWidget);
    item1->setFriendId("0");
    item2->setFriendId("1");

    QListWidgetItem *listwidgetItem = new QListWidgetItem();
    listwidgetItem->setSizeHint(item1->size());
    m_bottomWidget->insertItem(0, listwidgetItem);
    m_bottomWidget->setItemWidget(listwidgetItem, item1);


    QListWidgetItem *listwidgetItem2 = new QListWidgetItem();
    listwidgetItem2->setSizeHint(item2->size());
    m_bottomWidget->insertItem(1, listwidgetItem2);
    m_bottomWidget->setItemWidget(listwidgetItem2, item2);
//    listwidgetItem->setSizeHint(QSize(this->width(), 40));
//    listwidgetItem->setText("listItem1111");
//    listwidgetItem->setSizeHint(QSize(0, 70));
//    listwidgetItem->setIcon(QIcon(":/icon/Icon/head/head.png"));
//    listwidgetItem->setToolTip("this is a list widget item");
//    m_bottomWidget->insertItem(0, listwidgetItem);
}
