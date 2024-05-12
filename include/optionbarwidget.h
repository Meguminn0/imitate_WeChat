/******************************************************
 *
 * @file            optionbarwidget.h
 * @briefly-Cn      选择栏
 * @briefly-En      option bar
 *
 * @author          Meguminn0
 * @date            2024/04/23
 * @history
 *
********************************************************/

#ifndef OPTIONBARWIDGET_H
#define OPTIONBARWIDGET_H

#include "roundedbtn.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class OptionBarWidget : public QWidget
{
    Q_OBJECT
public:
    const int WIDGETWIDTH = 55;

    explicit OptionBarWidget(QWidget *parent = nullptr);

protected:
    void init();
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:

private:
    QWidget *m_topBar;
    QLabel *m_userHead;
    roundedBtn *m_chatOption;
    roundedBtn *m_contacts;
    roundedBtn *m_collection;
    roundedBtn *m_chatFiles;

    QWidget *m_bottomBar;
    roundedBtn *m_miniProgramPanel;
    roundedBtn *m_yourPhone;
    roundedBtn *m_setAndOther;
};

#endif // OPTIONBARWIDGET_H
