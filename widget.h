#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "exitBtn.h"
#include "minimizebtn.h"
#include "startbtn.h"
#include "setbtn.h"
#include <QPushButton>
#include "helpbtn.h"
#include <QScrollArea>
#include "toolbarbtn.h"
#include "newswidget.h"
#include "newstabwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Ui::Widget *ui;

    //进入设置主窗口为主窗口添加一层透明的黑色
    QLabel* showTrans = NULL;

    //窗口宽高
    int w = 1600;
    int h = 912;
    //标题栏高度
    int BarH = 48;

    //记录鼠标左键按下时鼠标的位置
    QPoint mousePoint = QPoint(0, 0);

    //窗口是否可移动
    bool isMoveable = false;

    //关闭按钮
    ExitBtn exitBtn;

    //最小化按钮
    MinimizeBtn miniBtn;

    //开始游戏按钮
    StartBtn startGameBtn;

    //设置按钮
    SetBtn setBtn;

    //版本热点
    QPushButton* versionHot;

    //游戏资源帮助按钮
    HelpBtn* gameResHelpBtn;

    //设置打开截图文件夹按钮
    QPushButton* scenceShootBtn;

    //右边的工具栏
    QScrollArea* toolBar;

    //米游社按钮
    ToolBarBtn* mysBtn;

    //微信按钮
    ToolBarBtn* weChatBtn;

    //微博按钮
    ToolBarBtn* weiBoBtn;

    //qq按钮
    ToolBarBtn* qqBtn;

    //大地图按钮
    ToolBarBtn* mapBtn;

    //问题反馈按钮
    ToolBarBtn* issueBtn;

    //启动器配置窗口
    SetWidget* setWidget;

    //新闻窗口
    NewsWidget* newsWidget;

    //新闻选项卡部件
    NewsTabWidget* newsTabWidget;

    //新闻文本全显示提示框（文本过长时无法显示）
    QVector<QLabel*> tipNewsLabels;

    void paintEvent(QPaintEvent* pev) override;

    void mousePressEvent(QMouseEvent* mev) override;

    void mouseReleaseEvent(QMouseEvent* mev) override;

    void mouseMoveEvent(QMouseEvent* mev) override;

};
#endif // WIDGET_H
