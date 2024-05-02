#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPainter>

#include "wechatmainwidget.h"
#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    init();

    m_mainwidget = nullptr;

    connect(ui->Btn_close, &QPushButton::clicked, this, &this->close);
    connect(ui->Btn_login, &roundedBtn::clicked, this, &this->loginCheck);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::init()
{
    ui->label_changeUser->installEventFilter(this);
    ui->label_sendFile->installEventFilter(this);
    ui->label_head->installEventFilter(this);
    QPalette palette;

    // 设置阴影
    QGraphicsDropShadowEffect *backShadowEffect = new QGraphicsDropShadowEffect(this);
    backShadowEffect->setBlurRadius(10);
    backShadowEffect->setColor(QColor(QColor(0, 0, 0, 64)));
    backShadowEffect->setEnabled(true);
    backShadowEffect->setOffset(0, 0);
    ui->Widget_backGround->setGraphicsEffect(backShadowEffect);

    // 背景窗口 Widget_backGround
    ui->Widget_backGround->setAutoFillBackground(true);
    palette = ui->Widget_backGround->palette();
    palette.setColor(QPalette::Window, Qt::white);
    ui->Widget_backGround->setPalette(palette);

    // 关闭按钮 Btn_close
    ui->Btn_close->setAllowButton(Qt::LeftButton);
    ui->Btn_close->setRoundedCorner(roundedBtn::RoundedCorner::topRight);
    ui->Btn_close->setRadius(4);
    ui->Btn_close->setMouseNormalColor(Qt::transparent);
    ui->Btn_close->setMouseHovedColor(QColor(251,115,115));
    ui->Btn_close->setMousePressedColor(QColor(225,72,72));
    ui->Btn_close->setIcon(QIcon(":/icon/close.png"));
    ui->Btn_close->setIconSize(QSize(13, 13));

    // 设置按钮 Btn_set
    ui->Btn_set->setAllowButton(Qt::LeftButton);
    ui->Btn_set->setRoundedCorner(roundedBtn::RoundedCorner::none);
    ui->Btn_set->setMouseNormalColor(Qt::transparent);
    ui->Btn_set->setMouseHovedColor(QColor(0, 0, 0, 15));
    ui->Btn_set->setMousePressedColor(QColor(0, 0, 0, 30));
    ui->Btn_set->setIcon(QIcon(":/icon/setting.png"));
    ui->Btn_set->setIconSize(QSize(12, 12));

    // 标题 Label_title
    palette = ui->Label_title->palette();
    palette.setColor(QPalette::WindowText, QColor(167,166,170));
    ui->Label_title->setPalette(palette);
    ui->Label_title->setFont(QFont("微软雅黑", 11));

    // 头像 Label_head
    palette = ui->label_head->palette();
    palette.setColor(QPalette::WindowText, QColor(Qt::transparent));
    ui->label_head->setAutoFillBackground(true);
    ui->label_head->setPalette(palette);
    QPixmap headPix(":/head.png");
    ui->label_head->setPixmap(headPix);
    ui->label_head->setScaledContents(true);

    // 用户名 Label_userName
    ui->label_userName->setText("R0621");
    ui->label_userName->setAlignment(Qt::AlignHCenter);
    ui->label_userName->setFont(QFont("微软雅黑", 16));

    // 登录 Btn_login
    ui->Btn_login->setAllowButton(Qt::LeftButton);
    ui->Btn_login->setRoundedCorner(roundedBtn::RoundedCorner::all);
    ui->Btn_login->setRadius(6);
    ui->Btn_login->setFont(QFont("微软雅黑", 11));
    palette = ui->Btn_login->palette();
    palette.setColor(QPalette::ButtonText, QColor(Qt::white));
    ui->Btn_login->setPalette(palette);
    ui->Btn_login->setMouseNormalColor(QColor(7,193,96));
    ui->Btn_login->setMouseHovedColor(QColor(56,205,127));
    ui->Btn_login->setMousePressedColor(QColor(6,173,86));

    // 切换账号 Label_changeUser
    ui->label_changeUser->setAlignment(Qt::AlignRight);
    palette = ui->label_changeUser->palette();
    palette.setColor(QPalette::WindowText, QColor(67,104,149));
    ui->label_changeUser->setPalette(palette);
    ui->label_changeUser->setFont(QFont("微软雅黑", 11));

    // 传输文件 label_sendFile
    ui->label_sendFile->setAlignment(Qt::AlignLeft);
    palette = ui->label_sendFile->palette();
    palette.setColor(QPalette::WindowText, QColor(67,104,149));
    ui->label_sendFile->setPalette(palette);
    ui->label_sendFile->setFont(QFont("微软雅黑", 11));
}

bool LoginWidget::checkUserValue()
{
    return true;
}

// 事件过滤器
bool LoginWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_changeUser)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->label_changeUser->setCursor(Qt::PointingHandCursor);
            return true;
        }
    }
    else if(watched == ui->label_sendFile)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->label_sendFile->setCursor(Qt::PointingHandCursor);
            return true;
        }
    }
    else if(watched == ui->label_head)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->label_head->setCursor(Qt::PointingHandCursor);
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(readyMove)
    {
        QPoint mouseMoveDis = event->globalPos() - m_mouseStartPoint;
        move(m_currentPoint + mouseMoveDis);
    }

    QWidget::mouseMoveEvent(event);
}

void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        readyMove = true;
        // record the position of the current mouse pressed in the window
        m_mouseStartPoint = event->globalPos();
        // record the position of the widget in the window
        m_currentPoint = frameGeometry().topLeft();
        event->accept();
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void LoginWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(readyMove && event->button() == Qt::LeftButton)
    {
        readyMove = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void LoginWidget::loginCheck()
{
    if(checkUserValue())
    {
        m_mainwidget = new wechatmainwidget();
        m_mainwidget->show();
        this->hide();
    }
}
