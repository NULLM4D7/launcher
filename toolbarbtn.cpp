#include "toolbarbtn.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include "widget.h"
#include <QTextCodec>

ToolBarBtn::ToolBarBtn(QWidget *parent, QString imgPath,
    bool isShowQR, int skipBtnNum, QWidget* mW, QString tipQRUseText)
    : QPushButton{parent}
{   
    this->setFixedSize(50, 50);

    //存储外来变量
    this->mainWidget = mW;
    this->m_imgPath = imgPath;
    this->m_isShowQR = isShowQR;
    this->m_skipBtnNum = skipBtnNum;
    this->m_tipQRUseText = tipQRUseText;
    //鼠标进入控件变为手形
    this->setCursor(QCursor(Qt::PointingHandCursor));

    //将二维码窗口绑定到主窗口上
    qrCode = new QScrollArea(this->mainWidget);

    //原按钮样式
    this->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   border: 0px solid rgba(0, 0, 0, 0);"
        "   border-radius: 25px;"
        "   background-color: rgba(0, 0, 0, 0.5);"
        "   }"
        );

    //设置二维码窗口样式
    this->qrCode->setStyleSheet(
        "QScrollArea{"
        "background: rgba(255, 255, 255, 1);"
        "}"
        );
    //设置二维码窗口为无边框
    qrCode->setFrameStyle(0);


    //设置按钮图标
    this->img = new QLabel(this);
    this->img->setFixedSize(this->width(), this->height());
    //设置图像显示位置为垂直和水平居中
    this->img->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //默认图像
    QPixmap pix(imgPath);

    pix = pix.scaled(this->width() / sub, this->height() / sub);

    this->img->setPixmap(pix);

    this->qrImg = new QLabel(this->qrCode);

    this->tipQRUse = new QLabel(this->qrCode);



    //设置二维码窗口 不使用Qt默认标题栏
    this->qrCode->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    //显示二维码窗口
    if(m_isShowQR)
    {
        qrCode->setFixedSize(qrW, qrH + this->m_skipBtnNum * skipBtnH);

    }
    //不显示二维码窗口
    else
    {
        qrCode->setFixedSize(qrW, this->m_skipBtnNum * skipBtnH);
    }


    //将范围控件绑定到二维码窗口上
    qrCodeArea = new LabelArea(this->mainWidget);

    //设置鼠标默认可移动范围(出界隐藏窗口)
    qrCodeArea->resize(this->qrCode->width(), qrCode->height());
    //将范围检测控件置顶
    this->qrCodeArea->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    //默认情况下关闭范围检测
    qrCodeArea->hide();

    qrCode->hide();


    //实例化跳转按钮并插入容器
    this->creatSkipBtnAndPush();
    //移动并缩放跳转按钮
    this->moveAndResizeSkipBtn();
    //设置按钮的提示信息图像
    setSkipBtnTip();



    //鼠标进入二维码窗口范围
    connect(this->qrCodeArea, &LabelArea::mouseEnterArea, this->qrCode, [=](){
        this->isInTipWidget = true;

        showBtnImgAndQR();

    });

    //鼠标离开二维码窗口范围
    connect(this->qrCodeArea, &LabelArea::mouseLeaveArea, this->qrCode, [=](){
        this->isInTipWidget = false;

        showBtnImgAndQR();

    });

    //鼠标进入按钮
    connect(this, &ToolBarBtn::mouseEnter, this, [=](){
        this->isInBtn = true;

        showBtnImgAndQR();

    });

    //鼠标离开按钮
    connect(this, &ToolBarBtn::mouseLeave, this, [=](){
        this->isInBtn = false;

        showBtnImgAndQR();

    });
}

//移动二维码窗口的位置 相对于按钮的位置
void ToolBarBtn::moveQR(int x, int y)
{
    Widget* mW = static_cast<Widget*>(mainWidget);
    this->qrCode->move(mW->toolBar->x() + this->x() + x, mW->toolBar->y() + this->y() + y);
    qrCodeArea->move(qrCode->pos());
}

//设置二维码窗口可供鼠标活动的追加的大小(默认为二维码窗口大小)
void ToolBarBtn::setQRCodeArea(int addWidth, int addHeight)
{
    this->qrCodeArea->resize(this->qrCode->width() + addWidth, qrCode->height() + addHeight);

}

void ToolBarBtn::enterEvent(QEvent* ev)
{
    emit mouseEnter();

    return QPushButton::enterEvent(ev);
}

void ToolBarBtn::leaveEvent(QEvent* ev)
{
    emit mouseLeave();

    return QPushButton::leaveEvent(ev);
}

//处理按钮图像和二维码窗口显示
void ToolBarBtn::showBtnImgAndQR()
{
    //鼠标在按钮内
    if(this->isInBtn)
    {
        showAllTip();
    }
    //鼠标不在按钮内
    else
    {
        //在二维码窗口中
        if(this->isInTipWidget)
        {
            showAllTip();
        }
        //不在二维码窗口中
        else
        {
            //显示原按钮图像
            QPixmap pix(this->m_imgPath);
            //调整图片大小
            pix = pix.scaled(this->width() / sub, this->height() / sub);
            this->img->setPixmap(pix);


            //隐藏二维码窗口 取消范围检测
            qrCode->hide();
            qrCodeArea->hide();

        }

    }
}

//处理按钮提示状态下的各种控件显示
void ToolBarBtn::showAllTip()
{
    //拼接金色按钮图像的路径
    QString imgPathG = QString("%1%2").arg(this->m_imgPath.split(".")[0]).arg("G.png");
    QPixmap pixG(imgPathG);
    this->img->setPixmap(pixG);

    //显示二维码窗口及其判定区域
    qrCode->show();
    qrCodeArea->show();

    //若有二维码显示
    if(m_isShowQR)
    {
        //设置二维码图像
        qrImg->setFixedSize(qrCode->width() - 30, qrCode->width() - 30);
        qrImg->move(qrCode->width() / 2 - qrImg->width() / 2, 0);
        //二维码图像路径
        QString qrImgPath = QString("%1%2").arg(m_imgPath.split(".")[0]).arg("QR.jpg");
        QPixmap qrPix(qrImgPath);
        qrPix= qrPix.scaled(qrImg->width(), qrImg->height());
        qrImg->setPixmap(qrPix);

        //设置居中显示
        this->qrImg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //二维码图像向下调整距离
        int qrMoveDownSize = 15;
        qrImg->move((qrCode->width() - qrImg->width()) / 2, qrMoveDownSize);
        qrImg->show();

        //设置二维码用途提示信息框
        this->tipQRUse->setFixedSize(qrW, this->qrH - qrImg->height() - qrMoveDownSize);
        //设置居中显示
        tipQRUse->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tipQRUse->setText(this->m_tipQRUseText);

        //设置字体样式、大小
        tipQRUse->setFont(QFont(QTextCodec::codecForName("GBK")->toUnicode("黑体"), 11));
        tipQRUse->setStyleSheet("color:rgb(140, 140, 140);");

        tipQRUse->move(0, qrH - tipQRUse->height());
        tipQRUse->show();
    }
}

void ToolBarBtn::creatSkipBtnAndPush()
{
    //实例化跳转按钮并插入容器
    for(int i = 0; i < this->m_skipBtnNum; i++)
    {
        //为了保证跳转按钮不会被范围检测控件遮挡 将跳转按钮绑定到范围检测控件上
        SkipBtn* skipBtn = new SkipBtn(this->qrCodeArea);
        skipBtnV.append(skipBtn);
    }
}

void ToolBarBtn::moveAndResizeSkipBtn()
{
    for(int i = 0; i < this->m_skipBtnNum; i++)
    {
        //移动
        //有二维码
        if(this->m_isShowQR)
        {
            skipBtnV[i]->move(0, qrH + i * skipBtnH);
        }
        //没有二维码
        else
        {
            skipBtnV[i]->move(0, i * skipBtnH);
        }

        //缩放
        skipBtnV[i]->resize(qrW, skipBtnH);
        skipBtnV[i]->tipSkip->resize(qrW, skipBtnH);
    }
}

//设置跳转按钮的信息提示
void ToolBarBtn::setSkipBtnTip()
{
    for(int i = 0; i < this->m_skipBtnNum; i++)
    {
        //提示信息图像路径
        QString tipImgPath = QString("%1%2%3%4").arg(this->m_imgPath.split(".")[0]).
                             arg("Skip").
                             arg(QString::number(i)).
                             arg(".png");
        //加载图像
        skipBtnV[i]->tipSkip->setPixmap(QPixmap(tipImgPath));
    }
}

//设置跳转按钮的跳转路径 参数1为设置按钮的下标数 参数2为路径
void ToolBarBtn::setSkipPath(int index, QString path)
{
    //判断下标是否越界
    if(index + 1 > this->m_skipBtnNum || index < 0) return;

    connect(this->skipBtnV[index], &SkipBtn::clicked, this->skipBtnV[index], [=](){
        const QUrl regUrl(path);
        QDesktopServices::openUrl(regUrl);
    });
}



//-------------------------------------------------


LabelArea::LabelArea(QWidget *parent)
    : QLabel{parent}
{

}

void LabelArea::enterEvent(QEvent* ev)
{
    emit this->mouseEnterArea();
    return QLabel::enterEvent(ev);
}
void LabelArea::leaveEvent(QEvent* ev)
{
    emit this->mouseLeaveArea();
    return QLabel::leaveEvent(ev);
}


//-------------------------------------------------

SkipBtn::SkipBtn(QWidget *parent)
    : QPushButton{parent}
{
    //将信息提示控件绑定到跳转按钮按钮
    this->tipSkip = new QLabel(this);
    //当鼠标进入按钮时设置为手形
    this->tipSkip->setCursor(Qt::PointingHandCursor);
    //将控件置顶
    this->tipSkip->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}


