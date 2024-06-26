#include "include/chatMessagebox.h"
#include "include/chatwidget.h"
#include "include/tcpmanager.h"

#include <QDateTime>
#include <QDebug>
#include <QFontMetrics>
#include <QIcon>
#include <QScrollBar>

chatWidget::chatWidget(QWidget *parent)
    : QWidget{parent}
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(245, 245, 245));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    init();

    connect(m_sendBtn, &QPushButton::clicked, this, &chatWidget::slot_sendMessage);
}

void chatWidget::setCurrentChatingUserId(const QString &id)
{
    m_currentChatingUserId = id;
}

void chatWidget::init()
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    m_stkedWidget = new QStackedWidget(this);
    m_layout->addWidget(m_stkedWidget);

    noneWidgetInit();
    chatingWidgetInit();

    m_stkedWidget->addWidget(m_noneWidget);
    m_stkedWidget->addWidget(m_chatingWidget);

    m_stkedWidget->setCurrentIndex(1);
}

/*
 * @briefly  noneWidgetInit 函数用于为没有聊天对象时的显示界面进行初始化
 */
void chatWidget::noneWidgetInit()
{
    m_noneWidget = new QWidget(this);
    m_noneWidget->setStyleSheet(R"(
        QWidget {
            background-color: rgb(245, 245, 245);
            border: 1xp solid rgb(214, 214, 214);
        }
)");

    m_noneLayout = new QGridLayout();
    m_noneLayout->setContentsMargins(0, 0, 0, 0);
    m_noneLayout->setSpacing(0);
    m_noneWidget->setLayout(m_noneLayout);

    m_logol = new QLabel(m_noneWidget);
    m_logol->setFixedSize(100, 100);
    QPixmap pix(":/img/icon/oneChat.png");
    pix = pix.scaled(m_logol->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_logol->setPixmap(pix);
    m_logol->setAlignment(Qt::AlignCenter);

    m_noneLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 0, 1);
    m_noneLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 1, 0);
    m_noneLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 1, 2);
    m_noneLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 2, 1);
    m_noneLayout->addWidget(m_logol, 1, 1);
}

/*
 * @briefly  chatingWidgetInit 函数用于为有聊天对象时的显示界面进行初始化
 */
void chatWidget::chatingWidgetInit()
{
    m_chatingWidget = new QWidget(this);

    m_chatingLayout = new QVBoxLayout();
    m_chatingLayout->setContentsMargins(0, 0, 0, 0);
    m_chatingLayout->setSpacing(0);

    m_chatingWidget->setLayout(m_chatingLayout);

    m_userInfoWidget = new QWidget(m_chatingWidget);
    m_userInfoWidget->setFixedHeight(64);
    m_userInfoWidget->setStyleSheet(R"(
        QWidget {
            background-color: rgba(0, 0, 0, 0   );
            border-bottom: 1px solid rgb(214, 214, 214);
            border-left: 1px solid rgb(214, 214, 214);
            border-top: 1px solid rgb(208, 208, 208);
            border-right: 1px solid rgb(208, 208, 208);
        }
    )");
    m_chatingLayout->addWidget(m_userInfoWidget);

    m_userInfoLayout = new QHBoxLayout();
    m_userInfoLayout->setContentsMargins(25, 10, 10, 0);
    m_userInfoWidget->setLayout(m_userInfoLayout);

    m_userNameLabel = new QLabel(m_userInfoWidget);
    m_userNameLabel->setFont(QFont("微软雅黑", 14));
    setUserNameLabel();
    m_userNameLabel->setStyleSheet("border: none");
    m_userInfoLayout->addWidget(m_userNameLabel);
    m_userInfoLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    m_chatInfoBtn = new QPushButton(QIcon(":/img/icon/more_three_Point_style.png"), "", m_userInfoWidget);
    m_chatInfoBtn->setFixedSize(26, 26);
    m_chatInfoBtn->setIconSize(m_chatInfoBtn->size());
    m_chatInfoBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 0);
            border: none;
            icon: url(:/img/icon/more_three_Point_style.png);
        }

        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0);
            icon: url(:/img/icon/more_three_Point_style_hover.png);
        }

        QPushButton:pressed {
            background-color: rgba(0, 0, 0, 0);
            icon: url(:/img/icon/more_three_Point_style_pressed.png);
        }
    )");
    m_userInfoLayout->addWidget(m_chatInfoBtn);

    m_listwidget = new QListWidget(m_chatingWidget);
    m_listwidget->setStyleSheet(R"(
        QListWidget {
            background-color: rgba(0, 0, 0, 0);
            border: 1px solid rgb(214, 214, 214);
            border-top: none;
        }

        QListWidget::item:hover {
            background-color: rgba(0, 0, 0, 0);
        }

        QListWidget::item:selected {
            background-color: rgba(0, 0, 0, 0);
        }
    )");
    QScrollBar *listWidgetVerticalBar = new QScrollBar(m_listwidget);
    listWidgetVerticalBar->setStyleSheet(R"(
        QScrollBar {
            background: rgb(245, 245, 245); /* 背景透明 */
            width: 15px;                    /* 滚动条宽度 */
            margin: 2px 3px 2px 5px;        /* 外边距: 上, 右, 下, 左 */
        }

        QScrollBar::handle {
            /* 滑块部分 */
            background-color:rgb(215, 215, 215);
            min-height: 20px;
            border-radius: 2px;
        }

        QScrollBar::handle:hover {
            /* 滑块部分 */
            background-color:rgb(186, 186, 186);
        }

        QScrollBar::add-page, QScrollBar::sub-page {
            /* 滚动条两端的背景 */
            background-color: rgba(245, 245, 245); /* 或者设定颜色 */
        }

        QScrollBar::up-arrow, QScrollBar::down-arrow {
            /* 上下箭头部分 */
            border: none;
            background-color: transparent;
            height: 0px;                    /* 隐藏箭头 */
            width: 0px;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
            height: 0px;                    /* 隐藏箭头 */
            width: 0px;
        }
    )");
    m_listwidget->setVerticalScrollBar(listWidgetVerticalBar);
    m_listwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listwidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_chatingLayout->addWidget(m_listwidget);

    m_textInWidget = new QWidget(m_chatingWidget);
    m_textInWidget->setFixedHeight(220);
    m_textInWidget->setStyleSheet(R"(
        QWidget {
            border: 1px solid rgb(214, 214, 214);
            border-top: none;
        }
    )");
    m_chatingLayout->addWidget(m_textInWidget, 1);

    m_textInlayout = new QVBoxLayout();
    m_textInlayout->setContentsMargins(20, 0, 20, 10);
    m_textInlayout->setSpacing(0);
    m_textInWidget->setLayout(m_textInlayout);

    m_chatToolBarLayout = new QHBoxLayout();
    m_chatToolBarLayout->setContentsMargins(0, 10, 0, 0);
    m_chatToolBarLayout->setSpacing(10);
    m_textInlayout->addLayout(m_chatToolBarLayout);

    m_emoticonsBtn = new QPushButton(m_textInWidget);
    m_emoticonsBtn->setFixedSize(25, 25);
    m_emoticonsBtn->setIconSize(m_emoticonsBtn->size());
    m_emoticonsBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 0);
            border: none;
            icon: url(:/img/icon/smiley.png);
        }

        QPushButton:hover {
            icon: url(:/img/icon/smiley_hover.png);
        }

        QPushButton:pressed {
            icon: url(:/img/icon/smiley_pressed.png);
        }
    )");
    m_SendFileBtn = new QPushButton(m_textInWidget);
    m_SendFileBtn->setFixedSize(25, 25);
    m_SendFileBtn->setIconSize(m_emoticonsBtn->size());
    m_SendFileBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 0);
            border: none;
            icon: url(:/img/icon/file.png);
        }

        QPushButton:hover {
            icon: url(:/img/icon/file_hover.png);
        }

        QPushButton:pressed {
            icon: url(:/img/icon/file_pressed.png);
        }
    )");
    m_screenShotBtn = new QPushButton(m_textInWidget);
    m_screenShotBtn->setFixedSize(25, 25);
    m_screenShotBtn->setIconSize(m_emoticonsBtn->size());
    m_screenShotBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 0);
            border: none;
            icon: url(:/img/icon/screenShot.png);
        }

        QPushButton:hover {
            icon: url(:/img/icon/screenShot_hover.png);
        }

        QPushButton:pressed {
            icon: url(:/img/icon/screenShot_pressed.png);
        }
    )");
    m_chatHistoryBtn = new QPushButton(m_textInWidget);
    m_chatHistoryBtn->setFixedSize(25, 25);
    m_chatHistoryBtn->setIconSize(m_emoticonsBtn->size());
    m_chatHistoryBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0, 0, 0, 0);
            border: none;
            icon: url(:/img/icon/oneChat.png);
        }

        QPushButton:hover {
            icon: url(:/img/icon/oneChat_hover.png);
        }

        QPushButton:pressed {
            icon: url(:/img/icon/oneChat_pressed.png);
        }
    )");

    m_chatToolBarLayout->addWidget(m_emoticonsBtn);
    m_chatToolBarLayout->addWidget(m_SendFileBtn);
    m_chatToolBarLayout->addWidget(m_screenShotBtn);
    m_chatToolBarLayout->addWidget(m_chatHistoryBtn);
    m_chatToolBarLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    m_textEdit = new QTextEdit(m_textInWidget);
    m_textEdit->setFont(QFont("微软雅黑", 13));
    m_textEdit->setStyleSheet(R"(
        QTextEdit {
            background-color: rgba(0, 0, 0, 0);
            border: none;
        }
    )");
    QScrollBar *textEditVerticalBar = new QScrollBar(m_textEdit);
    textEditVerticalBar->setStyleSheet(R"(
        QScrollBar {
            background: rgb(245, 245, 245); /* 背景透明 */
            border: none;
            width: 10px; /* 滚动条宽度 */
            margin: 0px 0px 0px 0px; /* 外边距 */
        }

        QScrollBar::handle {
            /* 滑块部分 */
            background-color:rgb(215, 215, 215);
            min-height: 20px;
            width: 5px;
            border-radius: 3px;
        }

        QScrollBar::handle:hover {
            /* 滑块部分 */
            background-color:rgb(186, 186, 186);
            min-height: 20px;
            width: 5px;
            border-radius: 3px;
        }

        QScrollBar::up-arrow, QScrollBar::down-arrow {
            /* 上下箭头部分 */
            border-color: rgba(0, 0, 0, 0);
            height: 0px; /* 隐藏箭头 */
            width: 0px;
        }

        QScrollBar::add-page, QScrollBar::sub-page {
            /* 滚动条两端的背景 */
            background-color: rgba(245, 245, 245); /* 或者设定颜色 */
        }

        QScrollBar::add-line:vertical {
              border: none;
              background: none;
        }

        QScrollBar::sub-line:vertical {
              border: none;
              background: none;
        }
    )");
    m_textEdit->setVerticalScrollBar(textEditVerticalBar);
    m_textInlayout->addWidget(m_textEdit);

    m_sendBtnLayout = new QHBoxLayout();
    m_sendBtnLayout->setContentsMargins(0, 0, 10, 0);
    m_sendBtnLayout->setSpacing(0);
    m_textInlayout->addLayout(m_sendBtnLayout);

    m_sendBtn = new QPushButton(m_textInWidget);
    m_sendBtn->setText("发送(S)");
    m_sendBtn->setFont(QFont("微软雅黑", 11));
    m_sendBtn->setFixedSize(100, 35);
    m_sendBtn->setStyleSheet(R"(
        QPushButton {
            background-color: rgb(233, 233, 233);
            color: rgb(7, 193, 96);
            border: none;
            border-radius: 5px;
        }

        QPushButton:hover {
            background-color: rgb(210, 210, 210);
        }

        QPushButton:pressed {
            background-color: rgb(198, 198, 198);
        }
    )");
    m_sendBtnLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    m_sendBtnLayout->addWidget(m_sendBtn);
}

void chatWidget::dealMessage(chatMessageBox *msg, QListWidgetItem *item, QString text, QString time, chatMessageBox::MSG_TYPE type)
{
    msg->setFixedWidth(m_listwidget->width());
    QSize size = msg->setText(text, time, type);
    item->setSizeHint(size);

    m_listwidget->addItem(item);
    m_listwidget->setItemWidget(item, msg);
}

void chatWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    for(int i = 0; i < m_listwidget->count(); ++i)
    {
        chatMessageBox *msgBox = (chatMessageBox*)m_listwidget->itemWidget(m_listwidget->item(i));
        QListWidgetItem *item = m_listwidget->item(i);
        msgBox->setFixedWidth(m_listwidget->width());
        QSize size = msgBox->setText(msgBox->getMessageText(), msgBox->getSendTime(), msgBox->getMsgType());
        item->setSizeHint(size);
        msgBox->update();

//        dealMessage(msgBox, item, msgBox->getMessageText(), msgBox->getSendTime(), msgBox->getMsgType());
    }
}

void chatWidget::setUserNameLabel()
{
    QString name = getUserName();
    QFontMetrics fontMtr(m_userNameLabel->font());
    int nameLength = fontMtr.horizontalAdvance(name);
    int nameHeight = fontMtr.height();
    m_userNameLabel->resize(nameLength, nameHeight);
    this->m_userNameLabel->setText(name);
}

QString chatWidget::getUserName()
{
    return "R0621";
}

void chatWidget::slot_sendMessage()
{
    QString msg = m_textEdit->toPlainText();
    m_textEdit->clear();
    QString time = QString::number(QDateTime::currentMSecsSinceEpoch()); //时间戳

    chatMessageBox* messageBox = new chatMessageBox(m_listwidget);
    QListWidgetItem* item = new QListWidgetItem(m_listwidget);
    dealMessage(messageBox, item, msg, time, chatMessageBox::ME);

    tcpManager::getInstance()->sendData(m_currentChatingUserId + " " + msg);
}
