#include "newstabwidget.h"
#include <QTextCodec>
#include <QFont>
#include <QDebug>

NewsTabWidget::NewsTabWidget(QWidget *parent, int width, int height)
    : QWidget{parent}
{
    this->resize(width, height);

    QTextCodec* codec = QTextCodec::codecForName("GBK");

    //设置选项按钮栏
    btnBar = new QLabel(this);
    btnBar->resize(this->width(), this->height() / 3);
    btnBar->move(0, 0);

    //可选按钮
    activityBtn = new QPushButton(btnBar);
    noticeBtn = new QPushButton(btnBar);
    messageBtn = new QPushButton(btnBar);

    activityBtn->setText(codec->toUnicode("活动"));
    noticeBtn->setText(codec->toUnicode("公告"));
    messageBtn->setText(codec->toUnicode("资讯"));

    btns.push_back(activityBtn);
    btns.push_back(noticeBtn);
    btns.push_back(messageBtn);


    //计数器 判断当前为第几个按钮
    int n = 0;
    for(QPushButton* btn : btns)
    {
        btn->resize(90, btnBar->height());
        btn->move(10 + n * btn->width(), 0);

        btn->setCursor(Qt::PointingHandCursor);

        connect(btn, &QPushButton::clicked, this, [=]()
        {
            //设置当前选项下标
            this->labelIndex = n;
            //计数器 判断当前为第几个按钮
            int j = 0;
            for(QPushButton* btnj : this->btns)
            {
                //设置选项按钮样式
                this->setBtnStyle(j, btnj);

                //切换新闻选项窗口
                if(j == labelIndex)
                {
                    this->labels[j]->show();
                }
                else
                {
                    this->labels[j]->hide();
                }

                j++;
            }

        });

        //设置按钮样式 
        this->setBtnStyle(n, btn);

        n++;
    }
    //将计数器归零
    n = 0;

    //可选窗口
    this->activityLabel = new QLabel(this);
    this->noticeLabel = new QLabel(this);
    this->messageLabel = new QLabel(this);



    this->labels.append(activityLabel);
    this->labels.append(noticeLabel);
    this->labels.append(messageLabel);

    for(QLabel* label : labels)
    {
        label->resize(this->width(), this->height() * 2 / 3);
        label->move(0, activityBtn->height());
        if(n == labelIndex)
        {
            label->show();
        }
        else
        {
            label->hide();
        }
        n++;
    }
    //将计数器归零
    n = 0;

    //设置新闻文本框
    for(int i = 0; i < 3; i++)
    {
        //将新闻文本框绑定到对应选项窗口
        NewsTextLabel* newsTextLab1 = new NewsTextLabel(this->labels[i]);
        NewsTextLabel* newsTextLab2 = new NewsTextLabel(this->labels[i]);

        newsTextLab1->resize(this->width(), this->height() / 3);
        newsTextLab2->resize(this->width(), this->height() / 3);

        newsTextLab1->move(0, 0);
        newsTextLab2->move(0, newsTextLab1->height());

        //设置新闻文本位置
        newsTextLab1->textLabel->move(40, newsTextLab1->textLabel->height() / 2 + 6);
        newsTextLab2->textLabel->move(40, newsTextLab1->textLabel->height() / 4 - 3);

        this->newsMap.insert(i, {newsTextLab1, newsTextLab2});

    }

    //选项卡窗口样式
    this->setStyleSheet(
        {
            "background-color: rgba(0, 0, 0, 0.25);"
        });

    //选项按钮栏样式
    this->btnBar->setStyleSheet(
        {
           "background-color: rgba(30, 30, 30, 0.5);"
        });

}

void NewsTabWidget::setBtnStyle(int n, QPushButton* btn)
{
    //当前选项按钮样式
    if(this->labelIndex == n)
    {
        btn->setStyleSheet(
            {
                "QPushButton:!checked {"
                "   background:transparent;"
                "   border:none;"
                "   font-size: 22px;"
                "   font-weight: bold;"
                "   font-family: SimHei;"
                "   color: rgb(230, 206, 112);"
                "   border-bottom: 2px solid rgba(230, 206, 112, 1);"
                "}"
            });

    }
    //非当前选项按钮样式
    else
    {
        btn->setStyleSheet(
            {
                "QPushButton:!checked {"
                "   background-color: rgba(0, 0, 0, 0);"
                "   font-size: 22px;"
                "   font-weight: bold;"
                "   font-family: SimHei;"
                "   color: rgb(200, 200, 200);"
                "   border:none;"
                "   border-bottom: 2px solid rgba(0, 0, 0, 0);"
                "}"

                "QPushButton:hover {"
                "   color: rgb(230, 206, 112);"
                "}"
            });
    }


}

//设置新闻文本 两段新闻->新闻中的文本 | 新闻的发布时间
void NewsTabWidget::setNewsText(QMap<int, QPair<QPair<QString, QString>, QPair<QString, QString>>> texts)
{
    for(int i = 0; i < 3; i++)
    {
        //文本
        QString str1 = texts[i].first.first;
        QString str2 = texts[i].second.first;
        //若文本长度过长 取前21个字符
        if(str1.length() >= 21)
        {
            str1 = str1.mid(0, 21);
            str1 += "...";
        }
        if(str2.length() >= 21)
        {
            str2 = str2.mid(0, 21);
            str2 += "...";
        }
        newsMap[i].first->textLabel->setText(str1);
        newsMap[i].second->textLabel->setText(str2);
        //时间
        newsMap[i].first->timeLabel->setText(texts[i].first.second);
        newsMap[i].second->timeLabel->setText(texts[i].second.second);

    }

}

//设置新闻文本Label的跳转路径
void NewsTabWidget::setPathOfNews(QVector<QString> paths)
{
    for(int i = 0; i < 3; i++)
    {
        newsMap[i].first->setPath(paths[i * 2]);
        newsMap[i].second->setPath(paths[i * 2 + 1]);
    }
}

QVector<QString> NewsTabWidget::getNewsText()
{
    QVector<QString> strV;
    for(int i = 0; i < 3; i++)
    {
        strV.push_back(this->newsMap[i].first->textLabel->text());
        strV.push_back(this->newsMap[i].second->textLabel->text());
    }
    return strV;
}
