#include "newswidget.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QVector2D>
#include <math.h>
#include <QPropertyAnimation>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <thread>

NewsWidget::NewsWidget(QWidget *parent, int newsNum)
    : QScrollArea{parent}
{
    //当鼠标进入按钮时设置为手形
    this->setCursor(Qt::PointingHandCursor);

    //取消边框
    this->setFrameStyle(0);

    //设置窗口阴影
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect->setOffset(0, 0);
    //设置阴影颜色
    effect->setColor(Qt::gray);
    //设定阴影的模糊半径，数值越大越模糊
    effect->setBlurRadius(20);
    this->setGraphicsEffect(effect);
//    ———————————————————
//        版权声明：本文为CSDN博主「daboluo520」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//        原文链接：https://blog.csdn.net/guorong520/article/details/88946582



    //设置宽高
    this->setFixedSize(w, h);

    this->newsNum = newsNum;

    //设置网站路径容器大小
    this->newsPaths.resize(newsNum);

    //将总控件绑定到新闻窗口
    this->allNews = new QLabel(this);
    //设置总控件宽高
    this->allNews->setFixedSize(this->width() * this->newsNum, this->height());

    //向海报容器中插入数据 并绑定到总控件
    pushNewsInV();



    //将前后按钮绑定到新闻窗口
    this->forwardBtn = new FlipBtn(this, 1);
    this->backBtn = new FlipBtn(this, 0);

    //设置按钮大小
    forwardBtn->resize(40, h);
    backBtn->resize(40, h);

    //移动按钮
    forwardBtn->move(0, 0);
    backBtn->move(this->w - backBtn->width(), 0);

    //向前翻转按钮被按下
    connect(forwardBtn, &QPushButton::clicked, this, [=](){
        //禁用按钮
        forwardBtn->setEnabled(false);

        newsIndex--;

        if(newsIndex == -1)
        {
            newsIndex = this->newsNum -1;
        }

        doFlipAnimation(forwardBtn);

    });

    //向后翻转按钮被按下
    connect(backBtn, &QPushButton::clicked, this, [=](){
        //禁用按钮
        backBtn->setEnabled(false);

        newsIndex++;

        if(newsIndex == newsNum)
        {
            newsIndex = 0;
        }

        doFlipAnimation(backBtn);

    });



    //跳转按钮存放位置
    this->flipBtnsLabel = new QLabel(this);
    flipBtnsLabel->resize(this->width(), 30);
    flipBtnsLabel->move(0, this->height() - 45);
    flipBtnsLabel->setCursor(Qt::ArrowCursor);

    //跳转按钮直径
    int lOfFlipBtn = 18;
    //跳转按钮间距
    int subOfFlipBtns = 10;

    //第一个跳转按钮的X坐标
    int xOfFlipBtn0 = 0;
    //偶数
    if(newsNum % 2 ==0)
    {
        xOfFlipBtn0 = this->width() / 2 - newsNum * lOfFlipBtn / 2 - subOfFlipBtns * 2.5;
    }
    //奇数
    else
    {
        xOfFlipBtn0 = this->width() / 2
        - (newsNum - 1) * lOfFlipBtn / 2 - 0.5 * lOfFlipBtn
        - (newsNum - 1) * subOfFlipBtns / 2;
    }

    for(int i = 0; i < this->newsNum; i++)
    {
        QPushButton* flipBtn = new QPushButton(flipBtnsLabel);
        flipBtn->resize(lOfFlipBtn, lOfFlipBtn);
        flipBtn->setStyleSheet(
            "border-radius: 9px;"
            "background-color: rgba(0, 0, 0, 0);"
            "border:2px solid rgb(180, 180, 180);"
        );
        flipBtn->move(xOfFlipBtn0 + i * (subOfFlipBtns + lOfFlipBtn), 10);
        flipBtn->setCursor(Qt::PointingHandCursor);
        connect(flipBtn, &QPushButton::clicked, this, [=](){
            newsIndex = i;
            doFlipAnimation(flipBtn);
        });
        //默认情况下不显示 当鼠标进入新闻窗口显示
        flipBtn->hide();
        flipBtns.push_back(flipBtn);
    }
    //设置当前所处的跳转按钮样式
    this->flipBtns[newsIndex]->setStyleSheet
    (
        "border-radius: 9px;"
        "background-color: rgb(255, 255, 255);"
        "border:2px solid rgb(255, 255, 255);"
    );

    //每10秒播放下一张海报
    QTimer* timer = new QTimer(this);
    timer->start(10000);

    connect(timer, &QTimer::timeout, this, [=]()
    {
        int index = newsIndex;
        (++index <= newsNum - 1) ? newsIndex++ : newsIndex = 0;
        doFlipAnimation(this->backBtn);
    });
}


//播放跳转动画
void NewsWidget::doFlipAnimation(QPushButton* btn)
{
    //动画对象
    //创建动画对象
    QPropertyAnimation* animation = new QPropertyAnimation(this->allNews, "geometry");

    //设置动画间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(allNews->x(), allNews->y(), allNews->width(), allNews->height()));
    //结束位置
    animation->setEndValue(QRect(-newsIndex * this->w, allNews->y(), allNews->width(), allNews->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutCurve);

    //动画结束后取消禁用 对应的跳转按钮变亮
    connect(animation, &QPropertyAnimation::finished, this, [=](){
        btn->setEnabled(true);
        for(int i = 0; i < newsNum; i++)
        {
            //当前所在的跳转按钮
            if(i == newsIndex)
            {
                this->flipBtns[newsIndex]->setStyleSheet
                (
                    "border-radius: 9px;"
                    "background-color: rgb(255, 255, 255);"
                    "border:2px solid rgb(255, 255, 255);"
                );
            }
            //其它跳转按钮
            else
            {
                this->flipBtns[i]->setStyleSheet
                (
                    "border-radius: 9px;"
                    "background-color: rgba(0, 0, 0, 0);"
                    "border:2px solid rgb(180, 180, 180);"
                );
            }
        }

    });
    animation->start();
}

//向海报容器中插入数据
void NewsWidget::pushNewsInV()
{
    for(int i = 0; i < newsNum; i++)
    {
        //将各海报绑定到总控件
        NewsLabel* news = new NewsLabel(this->allNews);
        //插入数据
        this->newsV.append(news);
        //将各海报控件移动到对应位置
        news->move(i * w + 1, 1);
    }
}

//设置新闻海报路径 参数1为海报的下标索引值 参数2为图像路径
void NewsWidget::setNewsImgPath(int index, QString imgPath, const char* newsPath)
{
    //判断是否越界
    if(index < 0 || index + 1 > this->newsNum) return;
    QPixmap pix(imgPath);
    //是否图像 留出空白作为边框
    pix = pix.scaled(w - 2, h - 2);
    this->newsV[index]->setPixmap(pix);

    //设置网站路径
    this->newsPaths[index] = newsPath;

    //点击新闻跳转至对应网页
    connect(this->newsV[index], &NewsLabel::clicked, this, [=]()
    {
        QDesktopServices::openUrl(QUrl(this->newsPaths[index]));
    });

}

void NewsWidget::enterEvent(QEvent* ev)
{
    emit this->enter();
    //显示下方跳转按钮
    for(QPushButton* btn : this->flipBtns)
    {
        btn->show();
    }
    return QScrollArea::enterEvent(ev);
}
void NewsWidget::leaveEvent(QEvent* ev)
{
    emit this->leave();
    //隐藏下方跳转按钮
    for(QPushButton* btn : this->flipBtns)
    {
        btn->hide();
    }
    return QScrollArea::leaveEvent(ev);
}

//------------------------------------------------------------



FlipBtn::FlipBtn(NewsWidget *parent, bool direction)
    :QPushButton{parent}
{
    this->m_direction = direction;

    //鼠标进入新闻窗口
    connect(parent, &NewsWidget::enter, this, [=](){
        this->isInNewsWidget = true;
        //判断鼠标的位置并处理翻转按钮的透明度
        this->changeFlipBtnA();
    });
    //鼠标离开新闻窗口
    connect(parent, &NewsWidget::leave, this, [=](){
        this->isInNewsWidget = false;
        //判断鼠标的位置并处理翻转按钮的透明度
        this->changeFlipBtnA();
    });

    //鼠标进入翻转按钮
    connect(this, &FlipBtn::enter, this, [=](){
        this->isInFlipBtn = true;
        //判断鼠标的位置并处理翻转按钮的透明度
        this->changeFlipBtnA();
    });

    //鼠标离开翻转按钮
    connect(this, &FlipBtn::leave, this, [=](){
        this->isInFlipBtn = false;
        //判断鼠标的位置并处理翻转按钮的透明度
        this->changeFlipBtnA();
    });

}

//判断鼠标的位置并处理翻转按钮的透明度
void FlipBtn::changeFlipBtnA()
{
    //鼠标在新闻窗口内
    if(this->isInNewsWidget)
    {
        //在翻转按钮内
        if(this->isInFlipBtn)
        {
            this->flipBtnA = 0.5;
        }
        //不在翻转按钮内
        else
        {
            this->flipBtnA = 0.25;
        }
    }
    //鼠标不在新闻窗口内
    else
    {
        this->flipBtnA = 0;
    }
    //刷新绘图事件
    update();
}

void FlipBtn::enterEvent(QEvent* ev)
{
    emit this->enter();
    return QPushButton::enterEvent(ev);
}
void FlipBtn::leaveEvent(QEvent* ev)
{
    emit this->leave();
    return QPushButton::leaveEvent(ev);
}


void FlipBtn::paintEvent(QPaintEvent*)
{
    QPainter pt(this);
    //设置透明度
    pt.setOpacity(this->flipBtnA);
    //向右
    if(this->m_direction)
    {
        pt.drawPixmap(0, 0, QPixmap(":/res/forwardBtn.png"));
    }
    //向左
    else
    {
        pt.drawPixmap(0, 0, QPixmap(":/res/backBtn.png"));
    }



}
