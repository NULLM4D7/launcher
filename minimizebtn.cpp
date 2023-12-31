#include "minimizebtn.h"
#include <QPainter>

MinimizeBtn::MinimizeBtn(ExitBtn *parent)
    : ExitBtn{parent}
{

}

void MinimizeBtn::paintEvent(QPaintEvent* pev)
{
    int rgb = 163;
    QPainter* pt = new QPainter(this);
    QPen* penBG = new QPen(qRgb(50, 50, 50));
    QBrush* brushBG = new QBrush(qRgb(50, 50, 50));
    QPen* penW = new QPen(qRgb(rgb, rgb, rgb));



    //控制是否最小化的的颜色 若最小化则颜色变深
    QWidget* w = static_cast<QWidget*>(parent());
    //鼠标相对控件的位置
    int thisX = QCursor().pos().x() - w->x() - this->x();
    int thisY = QCursor().pos().y() - w->y()  - this->y();

    if(isPress && thisX < this->width() && thisX > 0
        && thisY < this->height() && thisY > 0)
    {
        penBG->setColor(qRgb(45, 45, 45));
        brushBG->setColor(qRgb(45, 45, 45));
    }


    //当鼠标在按钮中按下不松开 移出鼠标后isInBtn不刷新
    if(this->isInBtn)
    {
        pt->setPen(*penBG);
        pt->setBrush(*brushBG);

        pt->drawRect(QRect(QPoint(0, 0), QPoint(this->width(), this->height())));
    }

    penW->setWidth(2);
    pt->setPen(*penW);


    //图标左端离按钮左端的距离
    int sub = 17;

    //绘制最小化图标
    pt->drawLine(QPoint(sub, this->height() / 2), QPoint(this->width() - sub, this->height() / 2));

    delete pt;
    delete penBG;
    delete penW;
    delete brushBG;


}
