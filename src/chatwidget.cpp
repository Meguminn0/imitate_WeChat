#include "include/chatMessagebox.h"
#include "include/chatwidget.h"

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
}

void chatWidget::init()
{
    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    m_userInfoWidget = new QWidget(this);
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
    m_layout->addWidget(m_userInfoWidget);

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

    m_listwidget = new QListWidget(this);
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
            width: 15px; /* 滚动条宽度 */
            margin: 0px 8px 0px 0px; /* 外边距 */
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
    m_listwidget->setVerticalScrollBar(listWidgetVerticalBar);
    m_listwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listwidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_layout->addWidget(m_listwidget);

    m_textInWidget = new QWidget(this);
    m_textInWidget->setStyleSheet(R"(
        QWidget {
            border: 1px solid rgb(214, 214, 214);
            border-top: none;
        }
    )");
    m_layout->addWidget(m_textInWidget);

    m_textInlayout = new QVBoxLayout();
    m_textInlayout->setContentsMargins(20, 0, 20, 10);
    m_textInlayout->setSpacing(0);
    m_textInWidget->setLayout(m_textInlayout);

    m_chatToolBarLayout = new QHBoxLayout();
    m_chatToolBarLayout->setContentsMargins(0, 10, 0, 10);
    m_chatToolBarLayout->setSpacing(5);
    m_textInlayout->addLayout(m_chatToolBarLayout);

    m_textEdit = new QTextEdit(m_textInWidget);
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

    connect(m_sendBtn, &QPushButton::clicked, this, &chatWidget::sendMessage);
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

        dealMessage(msgBox, item, msgBox->getMessageText(), msgBox->getSendTime(), msgBox->getMsgType());
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

void chatWidget::sendMessage()
{
    QString msg = m_textEdit->toPlainText();
    m_textEdit->setText("");
    QString time = QString::number(QDateTime::currentMSecsSinceEpoch()); //时间戳

    chatMessageBox* messageBox = new chatMessageBox(m_listwidget);
    QListWidgetItem* item = new QListWidgetItem(m_listwidget);
    dealMessage(messageBox, item, msg, time, chatMessageBox::ME);

//    emit sig_lastMessage(messageBox->getMessageText());
}
