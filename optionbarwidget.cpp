#include "optionbarwidget.h"

#include <QHBoxLayout>
#include <QPalette>

OptionBarWidget::OptionBarWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedWidth(WIDGETWIDTH);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(46, 46, 46));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    init();
}

void OptionBarWidget::init()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_topBar = new QWidget(this);

    m_bottomBar = new QWidget(this);

    QVBoxLayout *topLayout = new QVBoxLayout(m_topBar);
    QVBoxLayout *bottomLayout = new QVBoxLayout(m_bottomBar);

    m_topBar->setLayout(topLayout);
    m_topBar->setContentsMargins(0, 0, 0, 0);
    m_bottomBar->setLayout(bottomLayout);
    m_bottomBar->setContentsMargins(0, 0, 0, 0);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(0);

    layout->addSpacerItem(new QSpacerItem(0, 35));
    layout->addWidget(m_topBar);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addWidget(m_bottomBar);

    m_userHead = new QLabel("", m_topBar);
    m_userHead->setFixedSize(35, 35);
    m_userHead->setAlignment(Qt::AlignHCenter);
    m_userHead->setScaledContents(true);
    m_userHead->setPixmap(QPixmap(":/head.png"));

    m_chatOption = new roundedBtn("", m_topBar);
    m_chatOption->setFixedSize(WIDGETWIDTH - 4, 40);
    m_chatOption->setMouseNormaldColor(Qt::transparent);
    m_chatOption->setMouseHovedColor(Qt::transparent);
    m_chatOption->setMousePressedColor(Qt::transparent);
    m_chatOption->setIcon(QIcon(":/icon/chat.png"));
    m_chatOption->setIconSize(QSize(25, 25));

    m_Contacts = new roundedBtn("", m_topBar);
    m_Contacts->setFixedSize(WIDGETWIDTH - 4, 40);
    m_Contacts->setMouseNormaldColor(Qt::transparent);
    m_Contacts->setMouseHovedColor(Qt::transparent);
    m_Contacts->setMousePressedColor(Qt::transparent);
    m_Contacts->setIcon(QIcon(":/icon/user.png"));
    m_Contacts->setIconSize(QSize(25, 25));

    m_collection = new roundedBtn("", m_topBar);
    m_collection->setFixedSize(WIDGETWIDTH - 4, 40);
    m_collection->setMouseNormaldColor(Qt::transparent);
    m_collection->setMouseHovedColor(Qt::transparent);
    m_collection->setMousePressedColor(Qt::transparent);
    m_collection->setIcon(QIcon(":/icon/collection.png"));
    m_collection->setIconSize(QSize(25, 25));

    m_chatFiles = new roundedBtn("", m_topBar);
    m_chatFiles->setFixedSize(WIDGETWIDTH - 4, 40);
    m_chatFiles->setMouseNormaldColor(Qt::transparent);
    m_chatFiles->setMouseHovedColor(Qt::transparent);
    m_chatFiles->setMousePressedColor(Qt::transparent);
    m_chatFiles->setIcon(QIcon(":/icon/file.png"));
    m_chatFiles->setIconSize(QSize(25, 25));

    m_miniProgramPanel = new roundedBtn("", m_bottomBar);
    m_miniProgramPanel->setFixedSize(WIDGETWIDTH - 4, 40);
    m_miniProgramPanel->setMouseNormaldColor(Qt::transparent);
    m_miniProgramPanel->setMouseHovedColor(Qt::transparent);
    m_miniProgramPanel->setMousePressedColor(Qt::transparent);
    m_miniProgramPanel->setIcon(QIcon(":/icon/user.png"));
    m_miniProgramPanel->setIconSize(QSize(25, 25));

    m_yourPhone = new roundedBtn("", m_bottomBar);
    m_yourPhone->setFixedSize(WIDGETWIDTH - 4, 40);
    m_yourPhone->setMouseNormaldColor(Qt::transparent);
    m_yourPhone->setMouseHovedColor(Qt::transparent);
    m_yourPhone->setMousePressedColor(Qt::transparent);
    m_yourPhone->setIcon(QIcon(":/icon/phone.png"));
    m_yourPhone->setIconSize(QSize(25, 25));

    m_setAndOther = new roundedBtn("", m_bottomBar);
    m_setAndOther->setFixedSize(WIDGETWIDTH - 4, 40);
    m_setAndOther->setMouseNormaldColor(Qt::transparent);
    m_setAndOther->setMouseHovedColor(Qt::transparent);
    m_setAndOther->setMousePressedColor(Qt::transparent);
    m_setAndOther->setIcon(QIcon(":/icon/more.png"));
    m_setAndOther->setIconSize(QSize(25, 25));

    topLayout->addWidget(m_userHead);
    topLayout->setAlignment(m_userHead, Qt::AlignHCenter);
    topLayout->addSpacing(25);
    topLayout->addWidget(m_chatOption);
    topLayout->setAlignment(m_chatOption, Qt::AlignRight);
    topLayout->addWidget(m_Contacts);
    topLayout->setAlignment(m_Contacts, Qt::AlignRight);
    topLayout->addWidget(m_collection);
    topLayout->setAlignment(m_collection, Qt::AlignRight);
    topLayout->addWidget(m_chatFiles);
    topLayout->setAlignment(m_chatFiles, Qt::AlignRight);

    bottomLayout->addWidget(m_miniProgramPanel);
    bottomLayout->setAlignment(m_miniProgramPanel, Qt::AlignRight);
    bottomLayout->addWidget(m_yourPhone);
    bottomLayout->setAlignment(m_yourPhone, Qt::AlignRight);
    bottomLayout->addWidget(m_setAndOther);
    bottomLayout->setAlignment(m_setAndOther, Qt::AlignRight);
    bottomLayout->addSpacing(10);
}
