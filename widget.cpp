#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QTextCodec>
#include <QMouseEvent>
#include <QIcon>
#include <QFont>
#include <QDesktopServices>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>
#include <Windows.h>
#include <QTableView>
#include <QToolTip>
#include <vector>
#pragma comment  (lib, "User32.lib")

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTextCodec* codec = QTextCodec::codecForName("GBK");

    QIcon icon = QIcon(":/res/GI.jpg");
    //创建托盘菜单
    QMenu* trayIconMenu = new QMenu(this);
    //创建托盘内图标
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);



    trayIcon->setIcon(icon);
    trayIcon->show();

    //显示主窗口
    QAction* showMainW = new QAction(codec->toUnicode("打开主窗口"), this);
    connect(showMainW, &QAction::triggered, [=](){
        this->showNormal();
    });

    //退出
    QAction* exitW = new QAction(codec->toUnicode("退出"), this);
    connect(exitW, &QAction::triggered, [=](){
        this->close();
    });

    //点击托盘图标后窗口恢复正常显示
    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::Trigger)
        {
            this->showNormal();
            // 窗口置顶
            SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            // 取消窗口置顶
            SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

        }

    });


    trayIcon->setContextMenu(trayIconMenu);
    trayIconMenu->addAction(showMainW);
    trayIconMenu->addAction(exitW);



    //设置程序图标
    setWindowIcon(icon);

    //设置窗口名称
    setWindowTitle(codec->toUnicode("原神"));

    this->setFixedSize(w, h);
    //不使用Qt默认标题栏
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    this->move(50,50);
    


    //设置关闭按钮
    exitBtn.setParent(this);
    //误差调整
    int add = 2;
    exitBtn.resize(BarH + add, BarH + add);
    exitBtn.move(QPoint(w - BarH - add, 0));
    exitBtn.show();

    //设置最小化按钮
    miniBtn.setParent(this);
    miniBtn.resize(BarH + add, BarH + add);
    miniBtn.move(QPoint(w - (2 * (BarH + add)), 0));
    miniBtn.show();

    //设置开始游戏按钮
    startGameBtn.setParent(this);
    startGameBtn.move(1145, 770);
    startGameBtn.show();

    //配置设置按钮
    setBtn.setParent(this);
    setBtn.resize(BarH + add, BarH + add);
    setBtn.move(QPoint(w - (3 * (BarH + add)), 0));
    setBtn.show();

    //设置打开截图文件夹按钮
    this->scenceShootBtn = new QPushButton(this);
    scenceShootBtn->resize(BarH + add, BarH + add);
    scenceShootBtn->move(QPoint(w - (4 * (BarH + add)), 0));
    scenceShootBtn->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"
        "   image: url(:/res/scenceShoot.png);"
        "   border: 2px solid rgb(20, 20, 20);"
        "   background-color: rgb(20, 20, 20);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   border: 2px solid rgb(60, 60, 60);"
        "   background-color: rgb(60, 60, 60);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   border: 2px solid rgb(50, 50, 50);"
        "   background-color: rgb(50, 50, 50);"
        "   }"
        );
    //按下后打开截图所在的文件夹
    connect(scenceShootBtn, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:\\Genshin Impact\\Genshin Impact Game\\ScreenShot"));
    });




    //版本热点
    versionHot = new QPushButton(this);
    versionHot->move(1270,675);
    versionHot->setText(codec->toUnicode("版本热点"));
    versionHot->setFixedSize(163, 48);
    QFont font(codec->toUnicode("黑体"), 14, QFont::Bold);
    versionHot->setFont(font);
    //鼠标悬停时变为手型
    versionHot->setCursor(QCursor(Qt::PointingHandCursor));
    versionHot->setStyleSheet
    (
        "color: rgb(120, 64, 28);"
        "background-color: rgb(243, 249, 255);"
        "border: 6px solid rgb(250, 240, 240);"
        "border-radius: 24px;"
    );
    //点击后跳转至对应网页
    connect(versionHot, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://webstatic.mihoyo.com/ys/event/blue-post/index.html?page_sn=28c728e857d14cc5&bbs_presentation_style=fullscreen&utm_source=game&utm_medium=ys&utm_campaign=bt#/index"));
    });



    //游戏资源帮助按钮
    this->gameResHelpBtn = new HelpBtn(this, codec->toUnicode("游戏本地文件夹管理"));
    //250 76
    gameResHelpBtn->move(1395, 770);





    //右边的工具栏
    toolBar = new QScrollArea(this);
    toolBar->setStyleSheet(
        "QScrollArea{"
        "    background-color: rgba(0, 0, 0, 0.20);"
        "    border: 0px;"
        "    border-radius: 0px;"
        "}"

        );
    toolBar->setFixedSize(BarH * 2, this->height() - BarH);
    toolBar->move(this->width() - BarH * 2, BarH + add);

    //各按钮的间距
    int size = 38;
    //控件大小
    int componentSize = 50;
    //按钮的x坐标
    int btnX = (toolBar->width() / 2) - (componentSize / 2);
    //米游社
    mysBtn = new ToolBarBtn(toolBar, ":/res/mysImg.png", true, 1, this, codec->toUnicode("扫码下载App"));
    mysBtn->move(btnX, size + 6);
    mysBtn->moveQR(-mysBtn->x() - mysBtn->qrW, 0);
    mysBtn->setQRCodeArea(mysBtn->x(), 0);
    //点击米游社跳转按钮 跳转至对应网页
    mysBtn->setSkipPath(0, "https://www.miyoushe.com/ys/");

    //微信按钮
    weChatBtn = new ToolBarBtn(toolBar, ":/res/weChat.png", true, 0, this, codec->toUnicode("扫码关注微信公众号"));
    weChatBtn->move(btnX, mysBtn->y() + size + componentSize);
    weChatBtn->moveQR(-weChatBtn->x() - weChatBtn->qrW, 0);
    weChatBtn->setQRCodeArea(weChatBtn->x(), 0);

    //微博按钮
    weiBoBtn = new ToolBarBtn(toolBar, ":/res/weiBo.png", true, 1, this, codec->toUnicode("扫码关注官方微博"));
    weiBoBtn->move(btnX, weChatBtn->y() + size + componentSize);
    weiBoBtn->moveQR(-weiBoBtn->x() - weiBoBtn->qrW, 0);
    weiBoBtn->setQRCodeArea(weiBoBtn->x(), 0);
    //访问官方微博
    weiBoBtn->setSkipPath(0, "https://weibo.com/ysmihoyo");

    //qq按钮
    qqBtn = new ToolBarBtn(toolBar, ":/res/qq.png", false, 1, this);
    qqBtn->move(btnX, weiBoBtn->y() + size + componentSize);
    qqBtn->moveQR(-qqBtn->x() - qqBtn->qrW, 0);
    qqBtn->setQRCodeArea(qqBtn->x(), 0);
    //添加原神qq群
    qqBtn->setSkipPath(0, "https://ys.mihoyo.com/launcher/18/zh-cn/qq?api_url=https%3A%2F%2Fapi-sdk.mihoyo.com%2Fhk4e_cn&key=eYd89JmJ&prev=false");

    //大地图按钮
    mapBtn = new ToolBarBtn(toolBar, ":/res/map.png", true, 1, this, codec->toUnicode("扫码使用移动大地图"));
    mapBtn->move(btnX, qqBtn->y() + size + componentSize);
    mapBtn->moveQR(-mapBtn->x() - mapBtn->qrW, 0);
    mapBtn->setQRCodeArea(mapBtn->x(), 0);
    //访问大地图
    mapBtn->setSkipPath(0, "https://webstatic.mihoyo.com/ys/app/interactive-map/index.html?bbs_presentation_style=no_header&lang=zh-cn&utm_source=game&utm_medium=ys&utm_campaign=side&_markerFps=24#/map/2?shown_types=&center=2008.50,-1084.00&zoom=-3.00");

    //问题反馈按钮
    issueBtn = new ToolBarBtn(toolBar, ":/res/issue.png", false, 2, this);
    issueBtn->move(btnX, mapBtn->y() + size + componentSize);
    issueBtn->moveQR(-issueBtn->x() - issueBtn->qrW, 0);
    issueBtn->setQRCodeArea(issueBtn->x(), 0);
    //FAQ
    issueBtn->setSkipPath(0, "https://www.miyoushe.com/ys/article/39655595");
    //意见反馈
    issueBtn->setSkipPath(1, "https://www.miyoushe.com/ys/article/5780277");




    //新闻窗口
    //新闻数量
    int newsQua = 7;
    newsWidget = new NewsWidget(this, newsQua);
    newsWidget->move(60, 290);
    //显示新闻窗口
    newsWidget->show();

    //网站路径
    QVector<const char*>paths =
    {
        "https://www.miyoushe.com/ys/article/47011070",
        "https://act.mihoyo.com/ys/event/e20231227filmfest-qw321w/index.html?game_biz=hk4e_cn&mhy_presentation_style=fullscreen&mhy_auth_required=true&mhy_landscape=true&mhy_hide_status_bar=true&mode=fullscreen&utm_source=game&utm_medium=ys&utm_campaign=loader",
        "https://act.mihoyo.com/ys/event/e20231225melusine-questionnaire/index.html?game_biz=hk4e_cn&mhy_presentation_style=fullscreen&mhy_auth_required=true&mhy_landscape=true&mhy_hide_status_bar=true",
        "https://www.miyoushe.com/ys/article/46695284",
        "https://webstatic.mihoyo.com/ys/event/blue-post/index.html?page_sn=28c728e857d14cc5&bbs_presentation_style=fullscreen&utm_source=game&utm_medium=ys&utm_campaign=news#/index",
        "https://www.bilibili.com/blackboard/activity-HR50i12VLe.html",
        "https://act.mihoyo.com/ys/event/community-content-collection/index.html?game_biz=hk4e_cn&mhy_presentation_style=fullscreen&mhy_auth_required=true&utm_source=game&utm_medium=ys&utm_campaign=launcher#/home"
    };

    for(int i = 0; i < newsQua; i++)
    {
        newsWidget->setNewsImgPath(i, QString(":/res/news/#%1.png").arg(i + 1), paths[i]);
    }

    //设置新闻选项卡小部件
    this->newsTabWidget = new NewsTabWidget(this, newsWidget->width(), 150);

    newsTabWidget->move(newsWidget->x(), newsWidget->y() + newsWidget->height() + 20);


    //选项卡新闻文本
    QMap<int, QPair< QPair<QString, QString>, QPair<QString, QString>> > newsTexts =
    {
//index:元素下标 str1:新闻文本1 time1:文本1的发布时间 str2:新闻文本2 time2:文本2的发布时间
#define VALUE(index, str1, time1, str2, time2) \
        { index, { {codec->toUnicode(str1), #time1}, {codec->toUnicode(str2), #time2} } }

        VALUE(0, "【转发抽奖】提纳里生日活动开启！", 12/29, "【网页活动上线】小小幕后——参与可得原石等游戏内奖励。", 12/27),
        VALUE(1, "「刺玫的铭誓」祈愿：「明花蔓舵·娜维娅(岩)」概率UP！", 12/20, "PC版启动器常见问题FAQ", 4/12),
        VALUE(2, "《原神》蔷薇与铳枪活动过场动画-「两个铳枪手」", 12/27, "【玩家库招募】原神测试玩家招募开启", 12/14)
#undef VALUE
    };

    //设置选项卡新闻文本
    newsTabWidget->setNewsText(newsTexts);

    //设置选项卡新闻跳转路径
    this->newsTabWidget->setPathOfNews(
    {
        "https://www.miyoushe.com/ys/article/47094168",
        "https://act.mihoyo.com/ys/event/e20231227filmfest-qw321w/index.html?game_biz=hk4e_cn&mhy_presentation_style=fullscreen&mhy_auth_required=true&mhy_landscape=true&mhy_hide_status_bar=true&mode=fullscreen&utm_source=game&utm_medium=ys&utm_campaign=news",
        "https://www.miyoushe.com/ys/article/46664074",
        "https://www.miyoushe.com/ys/article/4004423",
        "https://www.miyoushe.com/ys/article/47011070",
        "https://www.miyoushe.com/ys/article/46522917"
    });

    //设置新闻文本全显示提示框
    for(int i = 0; i < 6; i++)
    {
        tipNewsLabels.push_back(new QLabel(this));
        auto newsMap = newsTabWidget->getNewsMap();
        int num;
        //鼠标进入对应文本框显示提示框 离开时隐藏
        if(i % 2 == 0)
        {
            num = i / 2;
            connect(newsMap[num].first, &NewsTextLabel::entered, tipNewsLabels[i], [=]()
            {
                tipNewsLabels[i]->show();
            });
            connect(newsMap[num].first, &NewsTextLabel::leaved, tipNewsLabels[i], [=]()
            {
                tipNewsLabels[i]->hide();
            });
        }
        else
        {
            num = (i - 1) / 2;
            connect(newsMap[num].second, &NewsTextLabel::entered, tipNewsLabels[i], [=]()
            {
                tipNewsLabels[i]->show();
            });
            connect(newsMap[num].second, &NewsTextLabel::leaved, tipNewsLabels[i], [=]()
            {
                tipNewsLabels[i]->hide();
            });
        }

        //设置提示框样式
        tipNewsLabels[i]->setStyleSheet
        (
            "border-radius: 5px;"
            "font: 15px Microsoft YaHei;"
            "color: rgb(100, 100, 100);"
            "background-color: rgb(230, 230, 225)"

        );
        tipNewsLabels[i]->setMargin(7);

        int maxLen = 28;
        //偶数
        if(i % 2 == 0)
        {
            QString str = newsTexts[i / 2].first.first;
            if(str.length() > maxLen)
            {
                str.insert(maxLen, "\n");
            }
            tipNewsLabels[i]->setText(str);
            tipNewsLabels[i]->move(this->newsTabWidget->x() + 40, newsTabWidget->y() + 95);
        }
        //奇数
        else
        {
            QString str = newsTexts[(i - 1) / 2].second.first;
            if(str.length() > maxLen)
            {
                str.insert(maxLen, "\n");
            }
            tipNewsLabels[i]->setText(str);
            tipNewsLabels[i]->move(this->newsTabWidget->x() + 40, newsTabWidget->y() + 130);
        }

        tipNewsLabels[i]->hide();

    }






    //设置透明层属性
    showTrans = new QLabel(this);
    showTrans->move(0, 0);
    showTrans->setFixedSize(this->width(), this->height());
    QPixmap transPix(":/res/transparency.png");
    transPix = transPix.scaled(this->width(), this->height());
    showTrans->setPixmap(transPix);
    showTrans->hide();

}

void Widget::paintEvent(QPaintEvent* pev)
{
    QPainter* painter = new QPainter(this);
    QPen* pen = new QPen(QColor(qRgb(20, 20, 20)));
    QBrush* brush = new QBrush(QColor(qRgb(20, 20, 20)));
    painter->setBrush(*brush);
    painter->setPen(*pen);

    //1600 913
    QPixmap bg = QPixmap(":/res/back.png");

    //绘制背景
    painter->drawPixmap(0, 0, w, h, bg);

    //绘制标题栏
    painter->drawRect(QRect(QPoint(0,0),QPoint(w,BarH)));
    
    //绘制标题
    QPen* penW = new QPen(qRgb(200, 200, 200));

    painter->setPen(*penW);
    painter->setFont(QFont(QTextCodec::codecForName("GBK")->toUnicode("华文宋体"), 11, QFont::Bold));

    painter->drawText(QRect(QPoint(13, 15), QPoint(300, BarH)), QTextCodec::codecForName("GBK")->toUnicode("原神"));

    //绘制版本
    painter->setPen(QPen(qRgb(70, 70, 70)));
    painter->setFont(QFont(QTextCodec::codecForName("GBK")->toUnicode("华文宋体"), 12));
    painter->drawText(QRect(QPoint(60, 13), QPoint(300, BarH)),"4.3.0");

    delete painter;
    delete pen;
    delete brush;
    delete penW;

    return QWidget::paintEvent(pev);
}

void Widget::mousePressEvent(QMouseEvent* mev)
{
    //当鼠标左键按下 若鼠标在标题栏内则可进行对窗口的移动
    if(mev->x() < this->w && mev->x() > 0 && mev->y() < this->BarH && mev->y() >0 && mev->button() == Qt::LeftButton)
    {
        this->isMoveable = true;
        //记录鼠标位置
        this->mousePoint = QPoint(mev->x(), mev->y());

    }
    else this->isMoveable = false;

    return QWidget::mousePressEvent(mev);
}

void Widget::mouseReleaseEvent(QMouseEvent* mev)
{
    this->isMoveable = false;

    return QWidget::mouseReleaseEvent(mev);
}

void Widget::mouseMoveEvent(QMouseEvent* mev)
{
    //是否满足移动条件
    if(this->isMoveable)
    {
        //鼠标在x和y方向上的移动距离
        int moveX = mev->x() - this->mousePoint.x();
        int moveY = mev->y() - this->mousePoint.y();

        this->move(QPoint(this->x() + moveX, this->y() + moveY));

    }

    return QWidget::mouseMoveEvent(mev);
}

Widget::~Widget()
{
    delete ui;
}

