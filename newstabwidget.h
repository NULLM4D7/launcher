#ifndef NEWSTABWIDGET_H
#define NEWSTABWIDGET_H

//新闻选项卡窗口 位于窗口左下处

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QDebug>

//文本控件 重载鼠标进出控件事件
class TextLabel : public QLabel
{
    Q_OBJECT
public:
    TextLabel(QWidget* parent = nullptr)
        : QLabel{parent}
    {

    }

    void enterEvent(QEvent* ev) override
    {
        emit entered();
        return QLabel::enterEvent(ev);
    }
    void leaveEvent(QEvent* ev) override
    {
        emit leaved();
        return QLabel::leaveEvent(ev);
    }
signals:
    void entered();
    void leaved();
};

//---------------------------------------------

//新闻文本
class NewsTextLabel : public QLabel
{
    Q_OBJECT
public:
    NewsTextLabel(QWidget* parent = nullptr)
        : QLabel{parent}
    {
        textLabel = new TextLabel(this);
        timeLabel = new QLabel(textLabel);

        textLabel->setCursor(Qt::PointingHandCursor);

        //控件宽高
        int labW = parent->width() * 8 / 9;
        int labH = parent->height() / 4;

        textLabel->resize(labW, labH);
        timeLabel->resize(labW, labH);

        textLabel->setStyleSheet
        (
            "QLabel:!checked {"
            "   background: transparent;"
            "   font-family: SimHei;"
            "   font-size: 18px;"
            "   color: rgb(235, 235, 235);"
            "}"

            "QLabel:hover {"
            "   color: rgb(230, 206, 112);"
            "}"
        );


        timeLabel->setStyleSheet("background: transparent; color: rgb(150, 150, 150); font-size: 20px;");

        timeLabel->setAlignment(Qt::AlignRight);

        connect(this->textLabel, &TextLabel::entered, this, [=]()
        {
            emit entered();
        });

        connect(this->textLabel, &TextLabel::leaved, this, [=]()
        {
            emit leaved();
        });

    }

    //内容文本
    TextLabel* textLabel;
    //发布时间
    QLabel* timeLabel;

    bool isPressedInLabel = false;
    bool isReleasedInLabel = false;

    //设置跳转路径
    void setPath(QString path)
    {
        connect(this, &NewsTextLabel::click, this, [=]()
        {
            QDesktopServices::openUrl(QUrl(path));
        });
    }

    void mousePressEvent(QMouseEvent* mev) override
    {
        isPressedInLabel = true;
        return QLabel::mousePressEvent(mev);
    }

    void mouseReleaseEvent(QMouseEvent* mev) override
    {
        if(mev->x() > 0 && mev->x() < this->width())
        {
            if(mev->y() > 0 && mev->y() < this->height())
            {
                isReleasedInLabel = true;
            }
        }

        if(isPressedInLabel && isReleasedInLabel)
        {
            emit click();
        }

        isPressedInLabel = false;
        isReleasedInLabel = false;

        return QLabel::mouseReleaseEvent(mev);
    }

signals:
    void click();
    void entered();
    void leaved();
};

//-----------------------------------------------------------------

//新闻选项窗口
class NewsTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewsTabWidget(QWidget *parent = nullptr, int width = 0, int height = 0);

    //设置新闻文本 两段新闻->新闻中的文本 | 新闻的发布时间
    void setNewsText(QMap<int, QPair<QPair<QString, QString>,QPair<QString, QString>>> texts);

    QVector<QString> getNewsText();

    //设置新闻文本Label的跳转路径
    void setPathOfNews(QVector<QString> paths);
    QMap<int, QPair<NewsTextLabel*, NewsTextLabel*>> getNewsMap() { return newsMap; }
protected:
    //选项按钮栏
    QLabel* btnBar;

    QPushButton* activityBtn;
    QPushButton* noticeBtn;
    QPushButton* messageBtn;

    //选项按钮容器 用于批量设置样式
    QVector<QPushButton*> btns;

    //当前选项的下标
    int labelIndex = 0;

    //活动窗口
    QLabel* activityLabel;
    //公告窗口
    QLabel* noticeLabel;
    //资讯窗口
    QLabel* messageLabel;

    //存放窗口的容器 用于批量设置样式
    QVector<QLabel*> labels;

    //新闻文本容器
    QMap<int, QPair<NewsTextLabel*, NewsTextLabel*>> newsMap;

    //设置选项按钮样式 参数1传入当前选项按钮下标 参数2传入设置样式的按钮
    void setBtnStyle(int n, QPushButton* btn);

signals:

};

#endif // NEWSTABWIDGET_H
