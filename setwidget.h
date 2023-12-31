#ifndef SETWIDGET_H
#define SETWIDGET_H

//启动器配置设置窗口

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include "tipbtn.h"

class SetWidget : public QDialog
{
    Q_OBJECT
public:
    SetWidget(QWidget* parent, bool isMoveToDownloadPlace = false);
    ~SetWidget();

    int BarH = 48;

    int isMoveable = false;

    //记录鼠标按下时的位置
    QPoint mousePoint;

protected:
    //设置框的总高度
    int setMainHeight = 1296;


    //关闭按钮位置 955 40   980 40
    QPoint closeBtnPoint = QPoint(955, 40);
    //关闭按钮宽高
    int closeBtnWH = 24;
    //关闭按钮是否发黄光
    bool isCloseBtnY = false;
    //是否在关闭按钮内按下
    bool isPressInCB = false;
    //滚动条
    QPushButton AreaBar;
    //滚动一下滚轮的设置框移动距离
    int wheelSize = 73;
    //滑动一下滚动条的移动距离
    int AreaBarMoveSize = 25;

    //是否记录鼠标与滚动条的相对位置(滚动条是否可移动)
    bool isRe = false;
    //鼠标按下滚动条时鼠标的位置
    int mouseY;
    //鼠标按下滚动条时滚动条的位置
    int sliderY;

    //显示设置主窗口
    QScrollArea* showSetMain = NULL;

    //记录设置框的位置Y
    int setMainY = 110;
    //记录按下滚动条时设置框的位置
    int tempSMY = 110;
    //遮挡上部分越界
    QLabel* labelU;
    //遮挡下部分越界
    QLabel* labelD;
    //关闭按钮
    QLabel* XLabel;


    //启动设置
    QScrollArea* setOpen;


    //通用设置
    QPushButton* commonlySet;
    //游戏资源
    QPushButton* gameRes;
    //版本信息
    QPushButton* versionInformation;


    //下载限速提示控件
    TipBtn* limitTipBtn;

    //安装位置提示控件
    TipBtn* downloadTipBtn;

    //设置前台(3个控制区域的按钮中的现所在区域按钮)跳转按钮样式
    void setUpBtnSty(QPushButton* btn);
    //设置后台(3个控制区域的按钮中的现不在区域按钮)跳转按钮样式
    void setDownBtnSty(QPushButton* btn);

    //移动到安装位置
    void moveToDownloadPlace();

    void paintEvent(QPaintEvent* pev) override;

    void mousePressEvent(QMouseEvent* mev) override;

    void mouseReleaseEvent(QMouseEvent* mev) override;

    void mouseMoveEvent(QMouseEvent* mev) override;

    void wheelEvent(QWheelEvent *wev) override;

signals:
    //设置框移动信号
    void setMainMoveSignal();
};

#endif // SETWIDGET_H
