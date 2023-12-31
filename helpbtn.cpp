#include "helpbtn.h"
#include <QLabel>
#include <QTextCodec>
#include "setwidget.h"
#include "widget.h"

HelpBtn::HelpBtn(QWidget *parent, QString tipContent)
    : QPushButton{parent}
{
    //设置提示框属性
    //不使用Qt默认标题栏 将窗口置顶
    this->tipMessage.setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    tipMessage.setFixedSize(155, 40);
    //文本提示控件
    QLabel* tip = new QLabel(&this->tipMessage);
    tip->setWordWrap (true);
    tip->setFixedSize(tipMessage.width(), tipMessage.height());
    //设置文字对齐方式 水平居中和垂直居中
    tip->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    //设置文字与边框的距离
    tip->setIndent(10);
    tip->move(0, 0);
    tip->setText(tipContent);

    //tip设置样式
    tip->setStyleSheet(
        "color: rgb(100, 100, 100);"
        "border-style: solid;"
        "border-radius: 5px;"
        "border-width: 1px;"
        "border-color: rgb(255, 255, 255);"
        "background-color: rgb(255, 255, 255);"
        );
    //设置窗口背景透明
    tipMessage.setAttribute(Qt::WA_TranslucentBackground, true);


    tipMessage.hide();




    //设置按钮样式
    this->setFixedSize(45, 76);
    this->setIcon(QIcon(":/res/downloadHelp.png"));
    this->setIconSize(QSize(28, 28));
    this->setStyleSheet(
        "   QPushButton:!checked {"

        "   background-color: rgb(254, 203, 11);"
        "   border-top-right-radius: 5px;"
        "   border-bottom-right-radius: 5px;"
        "   border-left-style: solid;"
        "   border-left-width: 2px;"
        "   border-left-color: rgb(239, 188, 1);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(255, 213, 21);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(234, 183, 0);"
        "   }"
        );


    QTextCodec* codec = QTextCodec::codecForName("GBK");

    //向按钮中添加菜单栏
    helpMenu = new QMenu(this);

    QFont font(codec->toUnicode("微软雅黑"), 10);

    //设置菜单项的文本
    downloadPlace = new QAction(codec->toUnicode("安装位置"), this);
    downloadPlace->setFont(font);

    //安装位置按钮功能
    connect(downloadPlace, &QAction::triggered, this, [=](){
        //为主窗口添加一层透明的黑色
        Widget* parent = static_cast<Widget*>(this->parent());
        parent->showTrans->show();

        //设置对话框 setWidget为模态窗口 若未关闭将不会向下执行 直接移动到安装位置处
        parent->setWidget = new SetWidget(this, true);

        //窗口关闭时隐藏透明层
        parent->showTrans->hide();

    });

    fix = new QAction(codec->toUnicode("一键修复"), this);
    fix->setFont(font);

    cleanDownloadRes = new QAction(codec->toUnicode("清除下载资源"), this);
    cleanDownloadRes->setFont(font);

    checkGameUpdata = new QAction(codec->toUnicode("检查游戏更新"), this);
    checkGameUpdata->setFont(font);

    //添加菜单项
    helpMenu->addAction(downloadPlace);
    helpMenu->addAction(fix);
    helpMenu->addAction(cleanDownloadRes);
    helpMenu->addAction(checkGameUpdata);

    //设置菜单样式
    helpMenu->setStyleSheet(
        "QMenu{"
        "   background-color: rgb(255,255,255);"
        "   border:1px solid rgb(255,255,255);"
        "   border-radius:7px;"
        //填充
        "   padding:8px;"
        //留白
        //"   margin:10px;"
        "}"
        "QMenu::item{"
        "   border:1px solid rgb(255,255,255);"
        "   border-radius:7px;"
        //QACtion文本边框扩展的高度和宽度
        "   padding:8px 16px;"
        "}"
        //鼠标悬停在QAction上时
        "QMenu::item:selected{"
            "background-color: rgb(240,240,240);"
        "}"
        //QAction被按下时
        "QMenu::item:pressed{"
        "   background-color: rgb(230,230,230);"
        "}"
        );
    //菜单背景透明
    helpMenu->setAttribute(Qt::WA_TranslucentBackground);
    //菜单无边框 无阴影
    helpMenu->setWindowFlags(helpMenu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    //按下按钮唤出菜单
    connect(this, &QPushButton::clicked, this, [=](){
        //helpMenu未绑定父级 使用全局位置
        helpMenu->move(this->mapToGlobal(QPoint(0, 0)).x() - 110, this->mapToGlobal(QPoint(0, 0)).y() - 200);
        helpMenu->show();
    });

}

void HelpBtn::enterEvent(QEvent* ev)
{
    //tipMessage未绑定父级 使用全局位置
    tipMessage.move(this->mapToGlobal(QPoint(0, 0)).x() - 100, this->mapToGlobal(QPoint(0, 0)).y() - 60);
    tipMessage.show();

    return QPushButton::enterEvent(ev);
}

void HelpBtn::leaveEvent(QEvent* ev)
{
    tipMessage.hide();

    return QPushButton::leaveEvent(ev);
}
