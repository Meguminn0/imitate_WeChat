#include "include/friendListwidget.h"
#include "include/friendListitem.h"

#include <QAction>
#include <QList>
#include <QVBoxLayout>

friendListWidget::friendListWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(WIDGETWIDTH);

    init();
    addfriendItem("0");
    addfriendItem("zdin404");

    connect(m_bottomWidget, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){
        friendlistItem* frientItem = static_cast<friendlistItem*>(m_bottomWidget->itemWidget(item));
        qDebug() << "item clicked, id: " << frientItem->getFriendId() << "row: " << m_bottomWidget->row(item);
    });
}

void friendListWidget::addfriendItem(const QString &friendId)
{
    friendlistItem *item = new friendlistItem(m_bottomWidget);
    item->setFriendId(friendId);

    QListWidgetItem *listwidgetItem = new QListWidgetItem();
    listwidgetItem->setSizeHint(item->size());
    m_bottomWidget->insertItem(m_bottomWidget->count(), listwidgetItem);
    m_bottomWidget->setItemWidget(listwidgetItem, item);
}

void friendListWidget::init()
{
    m_topWidget = new QWidget(this);
    m_bottomWidget = new QListWidget(this);

    m_topWidget->setFixedSize(this->width(), 64);
    m_topWidget->setStyleSheet(R"(
        QWidget {
            background-color: rgb(247, 247, 247);
            border-bottom: 1px solid rgb(214, 214, 214);
            border-top: 1px solid rgb(208, 208, 208);
        }
    )");

    m_bottomWidget->setFixedWidth(this->width());
    m_bottomWidget->setContentsMargins(0, 0, 0, 0);

    m_bottomWidget->setStyleSheet(R"(
        QListWidget {
            background-color: rgb(235, 233, 231);
            border: none;
            outline: 0;
        }

        QListWidget::item {
            background-color: rgba(0, 0, 0, 0);
            border-color:  rgba(0, 0, 0, 0);
        }

        QListWidget::item:hover {
            background-color: rgb(222, 219, 218);
            border-color:  rgba(0, 0, 0, 0);
        }

        QListWidget::item:selected {
            background-color: rgb(196, 196, 196);
            border-color:  rgba(0, 0, 0, 0);
        }
    )");
    m_bottomWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_bottomWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

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
    searchLineEdit_action->setIcon(QIcon(":/img/icon/seaerch.png"));

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
    m_createGroupChat->setIcon(QIcon(":/img/icon/plus.png"));
    m_createGroupChat->setIconSize(QSize(13, 13));

    this->setLayout(layout);
    layout->addWidget(m_topWidget);
    layout->addWidget(m_bottomWidget);
    m_topWidget->setLayout(topLayout);

    topLayout->addWidget(m_searchLineEdit);
    topLayout->addWidget(m_createGroupChat);
}
