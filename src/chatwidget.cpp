#include "include/chatMessagebox.h"
#include "include/chatwidget.h"

#include <QDateTime>
#include <QDebug>
#include <QScrollBar>

chatWidget::chatWidget(QWidget *parent)
    : QWidget{parent}
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    init();
}

void chatWidget::init()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    m_userInfoWidget = new QWidget(this);
    m_userInfoWidget->move(0, -1);
    m_userInfoWidget->setFixedHeight(60);
    QPalette palette = m_userInfoWidget->palette();
    palette.setColor(QPalette::Window, QColor(245, 245, 245));
    m_userInfoWidget->setAutoFillBackground(true);
    m_userInfoWidget->setPalette(palette);
    m_userInfoWidget->setStyleSheet(R"(
        QWidget {
            background-color: rgb(245, 245, 245);
            border-bottom: 1px solid rgb(214, 214, 214);
            border-left: 1px solid rgb(214, 214, 214);
            border-top: 1px solid rgb(208, 208, 208);
            border-right: 1px solid rgb(208, 208, 208);
        }
    )");
    m_layout->addWidget(m_userInfoWidget);

    m_listwidget = new QListWidget(this);
    m_listwidget->setStyleSheet(R"(
        QListWidget {
            background-color: rgb(245, 245, 245);
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
    QScrollBar *verticalBar = new QScrollBar(m_listwidget);
    verticalBar->setStyleSheet(R"(
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
    m_listwidget->setVerticalScrollBar(verticalBar);
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

    m_textInlayout = new QVBoxLayout(m_textInWidget);
    m_textInlayout->setContentsMargins(0, 0, 0, 0);
    m_textInlayout->setSpacing(0);
    m_textInWidget->setLayout(m_textInlayout);

    m_textEdit = new QTextEdit(m_textInWidget);
    m_textInlayout->addWidget(m_textEdit);

    m_sendBtn = new QPushButton(m_textInWidget);
    m_sendBtn->setText("发送(S)");
    m_textInlayout->addWidget(m_sendBtn);

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

void chatWidget::sendMessage()
{
    QString msg = m_textEdit->toPlainText();
    m_textEdit->setText("");
    //    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    QString time = QString::number(QDateTime::currentMSecsSinceEpoch()); //时间戳

    chatMessageBox* messageW = new chatMessageBox(m_listwidget);
    QListWidgetItem* item = new QListWidgetItem(m_listwidget);
    dealMessage(messageW, item, msg, time, chatMessageBox::ME);

    m_listwidget->setCurrentRow(m_listwidget->count() - 1);
}
