#include "tipbtn.h"
#include <QFont>
#include <QTextCodec>
#include <QDebug>
#include <QLabel>
#include <QApplication>

TipBtn::TipBtn(QWidget *parent, QString tipContent)
    : QPushButton{parent}
{
    QTextCodec* codec = QTextCodec::codecForName("GBK");
    this->setText("?");
    QFont font(codec->toUnicode("微软雅黑"), 12, QFont::Bold);
    this->setFont(font);
    this->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"
        "   color: rgb(250, 250, 250);"
        "   width: 22;"
        "   height: 22;"

        "   border-radius: 11px;"

        "   background-color: rgb(230, 214, 168);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(210, 194, 148);"
        "   }"


        );

    this->m_tipContent = tipContent;

    //不使用Qt默认标题栏 将窗口置顶
    this->tipMessage.setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void TipBtn::enterEvent(QEvent* ev)
{


    tipMessage.setFixedSize(21 * 20, (21 * ((m_tipContent.size() + 20) / 20)) + 40);
    //文本提示控件
    QLabel* tip = new QLabel(&this->tipMessage);
    tip->setWordWrap (true);
    tip->setFixedSize(tipMessage.width(), tipMessage.height());
    //设置文字对齐方式 水平居中和垂直居中
    tip->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    //设置文字与边框的距离
    tip->setIndent(10);
    tip->move(0, 0);
    tip->setText(m_tipContent);
    QFont tipFont(NULL, 12);
    tip->setFont(tipFont);

    //tip设置样式
    tip->setStyleSheet(
        "color: rgb(100, 100, 100);"
        "border-style: solid;"
        "border-radius: 5px;"
        "border-width: 1px;"
        "border-color: rgb(180, 180, 180);"
        "background-color: rgb(246, 245, 243);"
        );
    //设置窗口背景透明
    tipMessage.setAttribute(Qt::WA_TranslucentBackground, true);

    //鼠标进入控件 显示提示
    tipMessage.move(this->mapToGlobal(QPoint(0, 0)).x()- tip_BtnSize + 5, this->mapToGlobal(QPoint(0, 0)).y() - tip_BtnSize - tipMessage.height());
    tipMessage.show();
    tip->show();
    //返回给父类处理
    return QPushButton::enterEvent(ev);
}

void TipBtn::leaveEvent(QEvent* ev)
{
    //鼠标离开控件 隐藏提示
    tipMessage.move(this->mapToGlobal(QPoint(0, 0)).x()- tip_BtnSize + 5, this->mapToGlobal(QPoint(0, 0)).y() - tip_BtnSize - tipMessage.height());
    tipMessage.hide();
    //返回给父类处理
    return QPushButton::leaveEvent(ev);
}

void TipBtn::wheelEvent(QWheelEvent* ev)
{
    //滑动鼠标滚轮 隐藏提示信息
    tipMessage.hide();

    return QPushButton::wheelEvent(ev);
}
