#include "optionbarwidget.h"

#include <QButtonGroup>
#include <QEvent>
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
    connect(m_chatOption, &roundedBtn::toggled, this, [=](bool checked){
        if(m_chatOption->isChecked())
        {
            m_chatOption->setIcon(QIcon(":/icon/chatChecked.png"));
        }
        else
        {
            m_chatOption->setIcon(QIcon(":/icon/chat.png"));
        }
    });
    connect(m_contacts, &roundedBtn::toggled, this, [=](){
        if(m_contacts->isChecked())
        {
            m_contacts->setIcon(QIcon(":/icon/userChecked.png"));
        }
        else
        {
            m_contacts->setIcon(QIcon(":/icon/user.png"));
        }
    });
    connect(m_collection, &roundedBtn::toggled, this, [=](bool checked){
        if(m_collection->isChecked())
        {
            m_collection->setIcon(QIcon(":/icon/collectionChecked.png"));
        }
        else
        {
            m_collection->setIcon(QIcon(":/icon/collection.png"));
        }
    });
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
    m_userHead->installEventFilter(this);
    m_userHead->setFixedSize(35, 35);
    m_userHead->setAlignment(Qt::AlignHCenter);
    m_userHead->setScaledContents(true);
    m_userHead->setPixmap(QPixmap(":/head.png"));

    m_chatOption = new roundedBtn("", m_topBar);
    m_chatOption->installEventFilter(this);
    m_chatOption->setCheckable(true);
    m_chatOption->setChecked(true);
    m_chatOption->setFixedSize(WIDGETWIDTH - 6, 40);
    m_chatOption->setMouseNormalColor(Qt::transparent);
    m_chatOption->setMouseHovedColor(Qt::transparent);
    m_chatOption->setMousePressedColor(Qt::transparent);
    m_chatOption->setIcon(QIcon(":/icon/chatChecked.png"));
    m_chatOption->setIconSize(QSize(23, 23));

    m_contacts = new roundedBtn("", m_topBar);
    m_contacts->installEventFilter(this);
    m_contacts->setCheckable(true);
    m_contacts->setFixedSize(WIDGETWIDTH - 6, 40);
    m_contacts->setMouseNormalColor(Qt::transparent);
    m_contacts->setMouseHovedColor(Qt::transparent);
    m_contacts->setMousePressedColor(Qt::transparent);
    m_contacts->setIcon(QIcon(":/icon/user.png"));
    m_contacts->setIconSize(QSize(23, 23));

    m_collection = new roundedBtn("", m_topBar);
    m_collection->installEventFilter(this);
    m_collection->setCheckable(true);
    m_collection->setFixedSize(WIDGETWIDTH - 6, 40);
    m_collection->setMouseNormalColor(Qt::transparent);
    m_collection->setMouseHovedColor(Qt::transparent);
    m_collection->setMousePressedColor(Qt::transparent);
    m_collection->setIcon(QIcon(":/icon/collection.png"));
    m_collection->setIconSize(QSize(23, 23));

    m_chatFiles = new roundedBtn("", m_topBar);
    m_chatFiles->installEventFilter(this);
    m_chatFiles->setFixedSize(WIDGETWIDTH - 6, 40);
    m_chatFiles->setMouseNormalColor(Qt::transparent);
    m_chatFiles->setMouseHovedColor(Qt::transparent);
    m_chatFiles->setMousePressedColor(Qt::transparent);
    m_chatFiles->setIcon(QIcon(":/icon/file.png"));
    m_chatFiles->setIconSize(QSize(23, 23));

    m_miniProgramPanel = new roundedBtn("", m_bottomBar);
    m_miniProgramPanel->installEventFilter(this);
    m_miniProgramPanel->setFixedSize(WIDGETWIDTH - 6, 40);
    m_miniProgramPanel->setMouseNormalColor(Qt::transparent);
    m_miniProgramPanel->setMouseHovedColor(Qt::transparent);
    m_miniProgramPanel->setMousePressedColor(Qt::transparent);
    m_miniProgramPanel->setIcon(QIcon(":/icon/smallLink.png"));
    m_miniProgramPanel->setIconSize(QSize(23, 23));

    m_yourPhone = new roundedBtn("", m_bottomBar);
    m_yourPhone->installEventFilter(this);
    m_yourPhone->setFixedSize(WIDGETWIDTH - 6, 40);
    m_yourPhone->setMouseNormalColor(Qt::transparent);
    m_yourPhone->setMouseHovedColor(Qt::transparent);
    m_yourPhone->setMousePressedColor(Qt::transparent);
    m_yourPhone->setIcon(QIcon(":/icon/phone.png"));
    m_yourPhone->setIconSize(QSize(23, 23));

    m_setAndOther = new roundedBtn("", m_bottomBar);
    m_setAndOther->installEventFilter(this);
    m_setAndOther->setFixedSize(WIDGETWIDTH - 6, 40);
    m_setAndOther->setMouseNormalColor(Qt::transparent);
    m_setAndOther->setMouseHovedColor(Qt::transparent);
    m_setAndOther->setMousePressedColor(Qt::transparent);
    m_setAndOther->setIcon(QIcon(":/icon/more.png"));
    m_setAndOther->setIconSize(QSize(23, 23));

    topLayout->addWidget(m_userHead);
    topLayout->setAlignment(m_userHead, Qt::AlignHCenter);
    topLayout->addSpacing(25);
    topLayout->addWidget(m_chatOption);
    topLayout->setAlignment(m_chatOption, Qt::AlignRight);
    topLayout->addWidget(m_contacts);
    topLayout->setAlignment(m_contacts, Qt::AlignRight);
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
    bottomLayout->addSpacing(8);

    // 实现聊天、通信录、收藏三个按钮互斥
    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(m_chatOption);
    btnGroup->addButton(m_contacts);
    btnGroup->addButton(m_collection);
}

bool OptionBarWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_userHead)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
        }
    }
    else if(watched == m_chatOption)
    {
        if(event->type() == QEvent::HoverEnter && !m_chatOption->isChecked())
        {
            this->setCursor(Qt::PointingHandCursor);
            m_chatOption->setIcon(QIcon(":/icon/chatEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave && !m_chatOption->isChecked())
        {
            m_chatOption->setIcon(QIcon(":/icon/chat.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_contacts)
    {
        if(event->type() == QEvent::HoverEnter && !m_contacts->isChecked())
        {
            this->setCursor(Qt::PointingHandCursor);
            m_contacts->setIcon(QIcon(":/icon/userEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave && !m_contacts->isChecked())
        {
            m_contacts->setIcon(QIcon(":/icon/user.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_collection)
    {
        if(event->type() == QEvent::HoverEnter && !m_collection->isChecked())
        {
            this->setCursor(Qt::PointingHandCursor);
            m_collection->setIcon(QIcon(":/icon/collectionEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave && !m_collection->isChecked())
        {
            m_collection->setIcon(QIcon(":/icon/collection.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_chatFiles)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
            m_chatFiles->setIcon(QIcon(":/icon/fileEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_chatFiles->setIcon(QIcon(":/icon/file.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_miniProgramPanel)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
            m_miniProgramPanel->setIcon(QIcon(":/icon/smallLinkEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_miniProgramPanel->setIcon(QIcon(":/icon/smallLink.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_yourPhone)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
            m_yourPhone->setIcon(QIcon(":/icon/phoneEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_yourPhone->setIcon(QIcon(":/icon/phone.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }
    else if(watched == m_setAndOther)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            this->setCursor(Qt::PointingHandCursor);
            m_setAndOther->setIcon(QIcon(":/icon/moreEnter.png"));
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_setAndOther->setIcon(QIcon(":/icon/more.png"));
            this->setCursor(Qt::ArrowCursor);
        }
    }

    return QWidget::eventFilter(watched, event);
}
