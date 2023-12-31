#ifndef TOOLBARBTN_H
#define TOOLBARBTN_H

//窗口右边的栏 鼠标放到栏内的按钮上弹出二维码和跳转网页按钮

#include <QPushButton>
#include <QLabel>
#include <QScrollArea>


//在QLabel的基础上添加发射鼠标进出控件的信号
class LabelArea : public QLabel
{
    Q_OBJECT
public:
    LabelArea(QWidget *parent = nullptr);
protected:
    void enterEvent(QEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
signals:
    void mouseEnterArea();
    void mouseLeaveArea();
};



//--------------------------------------------------------------------------

//跳转按钮
class SkipBtn : public QPushButton
{
    Q_OBJECT
public:
    SkipBtn(QWidget *parent = nullptr);
    //提示跳转位置信息控件
    QLabel* tipSkip;
signals:

};



//--------------------------------------------------------------------------


class ToolBarBtn : public QPushButton
{
    Q_OBJECT
public:
    //父级 图像路径 是否显示二维码 跳转页面按钮的个数 主窗口 二维码用途提示信息
    explicit ToolBarBtn(QWidget *parent = nullptr, QString imgPath = "",
                        bool isShowQR = false, int skipBtnNum = false, QWidget* mW = NULL,
                        QString tipQRUseText = "");

    //二维码窗口宽度
    int qrW = 210;
    //二维码窗口原高度（不包括跳转按钮）
    int qrH = 235;

    //跳转按钮高度
    int skipBtnH = 50;

    //记录二维码窗口的相对按钮的位置
    QPoint qrPoint = QPoint(100, 100);

    //移动二维码窗口的位置  相对于按钮的位置
    void moveQR(int x, int y);

    //设置二维码窗口可供鼠标活动的追加的大小(默认为二维码窗口大小)
    void setQRCodeArea(int addWidth, int addHeight);

    //设置跳转按钮的跳转路径 参数1为设置按钮的下标数 参数2为路径
    void setSkipPath(int index = 0, QString path = "");

protected:

    QString m_imgPath;
    //保存按钮图标控件
    QLabel* img;
    //调整图像大小
    float sub = 1.6f;

    //是否显示二维码
    bool m_isShowQR = false;

    //跳转按钮的个数
    int m_skipBtnNum = 0;

    //提示二维码用途文本
    QString m_tipQRUseText = "";

    //鼠标是否在提示窗口内
    bool isInTipWidget = false;
    //鼠标是否在按钮内
    bool isInBtn = false;

    //二维码窗口
    QScrollArea* qrCode;
    //存储二维码图像的控件
    QLabel* qrImg = NULL;
    //鼠标进入该区域 二维码窗口不会被隐藏
    LabelArea* qrCodeArea;

    //主窗口
    QWidget* mainWidget;

    //二维码用途提示文字控件
    QLabel* tipQRUse;

    //跳转按钮容器
    QVector<SkipBtn*> skipBtnV;

    //生成跳转按钮并插入容器
    void creatSkipBtnAndPush();

    //调整跳转按钮大小并移动到对应位置
    void moveAndResizeSkipBtn();

    //设置跳转按钮的信息提示
    void setSkipBtnTip();

    //处理按钮图像和二维码窗口显示
    void showBtnImgAndQR();

    //处理按钮提示状态下的各种控件显示
    void showAllTip();


    void enterEvent(QEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
signals:
    void mouseEnter();
    void mouseLeave();

};







#endif // TOOLBARBTN_H
