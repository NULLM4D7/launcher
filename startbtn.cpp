#include "startbtn.h"
#include <QPainter>
#include <QTextCodec>
#include <QIcon>
#include <QProcess>
#include <QTimer>

StartBtn::StartBtn(ExitBtn *parent)
    : ExitBtn{parent}
{
    //当鼠标悬停时 鼠标变为手形
    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setFixedSize(QSize(250, 76));
}

void StartBtn::drawBtn(QPainter* pt)
{
    for(int i = 0; i < this->height(); i++)
    {
        pt->drawLine(QPoint(3, i), QPoint(this->width(), i));
    }
    pt->drawLine(QPoint(2, 1), QPoint(2, this->height() - 2));
    pt->drawLine(QPoint(1, 2), QPoint(1, this->height() - 3));
    pt->drawLine(QPoint(0, 3), QPoint(1, this->height() - 4));
}

void StartBtn::paintEvent(QPaintEvent* pev)
{
    QPainter* pt = new QPainter(this);
    QPen* penBG = new QPen(qRgb(255, 213, 21));
    QPen* penT = new QPen(qRgb(116, 93, 24));


    //绘制默认背景色
    pt->setPen(QPen(qRgb(254, 203, 11)));

    drawBtn(pt);

    //控制是否启动游戏的的颜色 若启动游戏则颜色变深
    QWidget* w = static_cast<QWidget*>(parent());
    //鼠标相对控件的位置
    int thisX = QCursor().pos().x() - w->x() - this->x();
    int thisY = QCursor().pos().y() - w->y()  - this->y();

    if(isPress && thisX < this->width() && thisX > 0
        && thisY < this->height() && thisY > 0)
    {
        penBG->setColor(qRgb(234, 183, 0));
    }


    //当鼠标在按钮中按下不松开 移出鼠标后isInBtn不刷新
    if(this->isInBtn)
    {
        pt->setPen(*penBG);
        this->drawBtn(pt);
    }


    //绘制文字
    pt->setPen(*penT);

    pt->setFont(QFont(QTextCodec::codecForName("GBK")->toUnicode("微软雅黑 Light"), 18, QFont::Bold));
    pt->drawText(QRect(58, 19, this->width(), this->height()), QTextCodec::codecForName("GBK")->toUnicode("开始游戏"));



    delete pt;
    delete penBG;
    delete penT;


}

void StartBtn::doCode()
{
    bool isOpen = QDesktopServices::openUrl(QUrl("file:///C:/Genshin Impact/Genshin Impact Game/YuanShen.exe"));

    //主窗口
    QWidget* wMain = static_cast<QWidget*>(parent());

    if(isOpen)
    {
        wMain->hide();
    }


};


