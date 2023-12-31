#include "exitBtn.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>


ExitBtn::ExitBtn(QLabel *parent)
    : QLabel{parent}
{
    update();
}

void ExitBtn::enterEvent(QEvent* ev)
{
    this->isInBtn = 1;
    update();
    return QLabel::enterEvent(ev);
}

void ExitBtn::leaveEvent(QEvent* ev)
{
    this->isInBtn = 0;
    update();
    return QLabel::leaveEvent(ev);
}

void ExitBtn::paintEvent(QPaintEvent* pev)
{
    int rgb = 163;
    QPainter* pt = new QPainter(this);
    QPen* penW = new QPen(QColor(qRgb(rgb, rgb, rgb)));
    penW->setWidth(2);

    QPen* penR = new QPen(QColor(qRgb(255, 100, 50)));
    QBrush* brushR = new QBrush(QColor(qRgb(255, 100, 50)));



    //控制是否关闭的的颜色 若关闭则颜色变深
    QWidget* w = static_cast<QWidget*>(parent());
    //鼠标相对控件的位置
    int thisX = QCursor().pos().x() - w->x() - this->x();
    int thisY = QCursor().pos().y() - w->y()  - this->y();

    if(isPress && thisX < this->width() && thisX > 0
        && thisY < this->height() && thisY > 0)
    {
        penR->setColor(qRgb(235, 80, 30));
        brushR->setColor(qRgb(235, 80, 30));
    }


    //当鼠标在按钮中按下不松开 移出鼠标后isInBtn不刷新
    //若鼠标进入关闭按钮 将按钮背景色修改为橙红色
    if(this->isInBtn)
    {
        pt->setPen(*penR);
        pt->setBrush(*brushR);
        pt->drawRect(QRect(QPoint(0, 0), QPoint(this->width(), this->height())));

    }

    //绘制关闭标志
    pt->setPen(*penW);

    //按钮的左上角到按钮顶部的距离
    int subSize = 19;

    pt->drawLine(QLine(QPoint(subSize, subSize), QPoint(this->width() - subSize, this->height() - subSize)));
    pt->drawLine(QLine(QPoint(subSize, this->height() - subSize), QPoint(this->width() - subSize, subSize)));

    delete pt;
    delete penW;
    delete penR;
    delete brushR;

    return QLabel::paintEvent(pev);
}

void ExitBtn::mousePressEvent(QMouseEvent* mev)
{
    if(mev->button() == Qt::LeftButton && isInBtn) isPress = true;
    else isPress = false;

    update();
}

void ExitBtn::mouseReleaseEvent(QMouseEvent* mev)
{
    if(mev->x() < this->width() && mev->x() > 0 && mev->y() < this->height() && mev->y() > 0) this->isRelease = true;
    else this->isRelease = false;

    if(isPress && isRelease) doCode();
    else isPress = false; isRelease = false;
}

void ExitBtn::mouseMoveEvent(QMouseEvent* mev)
{
    //鼠标按下 但鼠标被移出控件
    if(isPress && ((mev->x() < 0 || mev->x() > this->width()) || (mev->y() < 0 || mev->y() > this->height())))
    {
        update();
    }
    //鼠标移出后又回到按钮内
    if(isPress && mev->x() < this->width() && mev->x() > 0 && mev->y() < this->height() && mev->y() > 0)
    {
        update();
    }
}

