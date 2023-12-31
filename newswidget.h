#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

//新闻窗口 位于窗口左上处

#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

class NewsWidget;
//翻页按钮
class FlipBtn : public QPushButton
{
    Q_OBJECT
public:
    //绑定父级 翻转方向
    explicit FlipBtn(NewsWidget *parent = nullptr, bool direction = 0);
    //0为向右 1为向左
    bool m_direction;

protected:
    //鼠标是否在新闻窗口中
    bool isInNewsWidget = false;
    //鼠标是否在翻转按钮中
    bool isInFlipBtn = false;

    //当前翻转按钮的透明度
    float flipBtnA = 0;

    //判断鼠标的位置并处理翻转按钮的透明度
    void changeFlipBtnA();

    void paintEvent(QPaintEvent*) override;
    void enterEvent(QEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
signals:
    void enter();
    void leave();
};

//-----------------------------------------------------------------

class NewsLabel : public QLabel
{
    Q_OBJECT
public:
    NewsLabel(QWidget* parent = nullptr)
        : QLabel{parent}
    {

    }
protected:
    //是否在窗口内按下
    bool isPressInL = false;
    void mousePressEvent(QMouseEvent* mev) override
    {
        emit this->pressed();
        isPressInL = true;
        return QLabel::mousePressEvent(mev);
    }

    void mouseReleaseEvent(QMouseEvent* mev) override
    {
        emit this->released();
        //鼠标在窗口内
        if(mev->x() >= 0 && mev->x() <= this->width())
        {
            if(mev->y() >= 0 && mev->y() <= this->height())
            {
                if(isPressInL == true)
                {
                    emit clicked();
                    isPressInL = false;
                }


            }
        }
        return QLabel::mouseReleaseEvent(mev);
    }
signals:
    //NewsLabel被按下
    void pressed();
    //NewsLabel被松开
    void released();
    //点击
    void clicked();
};

//--------------------------------------------------------------


//新闻窗口
class NewsWidget : public QScrollArea
{
    Q_OBJECT
public:
    //绑定父级 新闻数量
    explicit NewsWidget(QWidget *parent = nullptr, int newsNum = 0);

    //设置新闻海报路径 参数1为海报的下标索引值 参数2为图像路径 参数3为跳转到的网站
    void setNewsImgPath(int index, QString imgPath, const char* newsPath = "#");

protected:
    //窗口宽高
    const int w = 580;
    const int h = 270;

    //新闻数量
    int newsNum = 0;

    //当前显示的新闻下标
    int newsIndex = 0;

    //总控件 将所有海报放入该控件
    QLabel* allNews;

    //储存新闻海报的容器
    QVector<NewsLabel*> newsV;

    //新闻被点击后跳转到的网站
    QVector<const char*> newsPaths;

    //向前按钮
    FlipBtn* forwardBtn;

    //向后按钮
    FlipBtn* backBtn;

    //存储跳转页面按钮
    QLabel* flipBtnsLabel;

    //跳转按钮容器
    QVector<QPushButton*> flipBtns;

    //向海报容器中插入数据
    void pushNewsInV();

    //播放跳转动画
    void doFlipAnimation(QPushButton* btn);

    void enterEvent(QEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
signals:
    void enter();
    void leave();
};

#endif // NEWSWIDGET_H
