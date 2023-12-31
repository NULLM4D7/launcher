#include "setbtn.h"
#include "setwidget.h"
#include "widget.h"

SetBtn::SetBtn(QWidget *parent)
    : QPushButton{parent}
{
    this->setStyleSheet
    (
        "SetBtn:!checked{"
        "background-image: url(:/res/set1.png);"
        "background-position: center;"
        "background-repeat: no-repeat;"
        "background-color:rgb(20, 20, 20);"
        "border:2px;"
        "}"
        "SetBtn:hover {"
        "background-color:rgb(50, 50, 50);"
        "}"
        "SetBtn:pressed {"
        "background-color:rgb(45, 45, 45);"
        "}"
    );

    connect(this, &QPushButton::clicked, this, [=]()
    {
        Widget* parent = static_cast<Widget*>(this->parent());
        //为主窗口添加一层透明的黑色
        parent->showTrans->show();

        //设置对话框 setWidget为模态窗口 若未关闭将不会向下执行
        parent->setWidget = new SetWidget(parent);

        //窗口关闭时隐藏透明层
        parent->showTrans->hide();

    });
}

//void SetBtn::paintEvent(QPaintEvent* pev)
//{
//    QPainter pt(this);
//    QPen* penBG(new QPen(qRgb(50, 50, 50)));
//    QBrush* brushBG(new QBrush(qRgb(50, 50, 50)));

//    //控制是否最小化的的颜色 若最小化则颜色变深
//    QWidget* w = static_cast<QWidget*>(parent());
//    //鼠标相对控件的位置
//    int thisX = QCursor().pos().x() - w->x() - this->x();
//    int thisY = QCursor().pos().y() - w->y()  - this->y();

//    if(isPress && thisX < width() && thisX > 0 && thisY < height() && thisY > 0)
//    {
//        penBG->setColor(qRgb(45, 45, 45));
//        brushBG->setColor(qRgb(45, 45, 45));
//    }

//    //当鼠标在按钮中按下不松开 移出鼠标后isInBtn不刷新
//    if(this->isInBtn)
//    {
//        pt->setPen(*penBG);
//        pt->setBrush(*brushBG);

//        pt->drawRect(QRect(QPoint(0, 0), QPoint(this->width(), this->height())));
//    }

//    //加载图标
//    QPixmap pix = QPixmap(":/res/set.png");
//    double s = 1.22;
//    pt.drawPixmap((this->width() - pix.width() * s) / 2, (this->height() - pix.height() * s) / 2, pix.width() * s, pix.height() * s, pix);

//    delete pt;
//    delete penBG;
//    delete brushBG;

//    pt = NULL;
//    penBG = NULL;
//    brushBG = NULL;

    //QPushButton::paintEvent(pev);
//}

//void SetBtn::doCode()
//{
//    //为主窗口添加一层透明的黑色
//    Widget* parent = static_cast<Widget*>(this->parent());
//    parent->showTrans->show();

//    //设置对话框 setWidget为模态窗口 若未关闭将不会向下执行
//    setWidget = new SetWidget(this);

//    //窗口关闭时隐藏透明层
//    parent->showTrans->hide();

//    delete setWidget;
//    setWidget = NULL;
//}


