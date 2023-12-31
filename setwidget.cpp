#include "setwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTextCodec>
#include <QCheckBox>
#include <QFontDialog>
#include <QRadioButton>
#include <QMouseEvent>
#include <QLineEdit>
#include <QFileDialog>
#include <QDesktopServices>


SetWidget::SetWidget(QWidget* parent, bool isMoveToDownloadPlace)
    : QDialog{parent}
{
    //实时检测鼠标移动
    setMouseTracking(1);

    QTextCodec* codec = QTextCodec::codecForName("GBK");

    //设置滚动条
    this->AreaBar.setParent(this);
    this->AreaBar.resize(7, 120);
    this->AreaBar.move(320 + 655 + 25, 110);
    this->AreaBar.setStyleSheet(
        //按钮默认样式
        "QPushButton {"
        "   border-color:rgb(240, 240, 240);"
        "   background-color: rgb(240, 240, 240);"
        "   border-radius: 5px;"
        "}"
        );


    //设置鼠标穿透滚动条 否则影响判定鼠标事件
    this->AreaBar.setAttribute(Qt::WA_TransparentForMouseEvents);


    this->setFixedSize(1020, 652);
    //不使用Qt默认标题栏
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);



    //配置设置框
    //右上角 975 110
    //右下角 975 530
    //左上角 320 110
    this->showSetMain = new QScrollArea(this);
    //设置主框样式
    this->showSetMain->setFrameStyle(0);
    this->showSetMain->setStyleSheet("background-color:transparent;");
    //设置主框固定大小
    showSetMain->setFixedSize(655, setMainHeight);
    showSetMain->move(320, this->setMainY);





    //遮挡越界的上部分
    QPixmap pixUp = QPixmap(":/res/setWidgetUp.jpg");
    labelU = new QLabel(this);
    labelU->setGeometry(0, 0, pixUp.width(), pixUp.height());
    labelU->setPixmap(pixUp);
    //设置鼠标穿透 否则影响mouseMoveEvent的判定
    labelU->setAttribute(Qt::WA_TransparentForMouseEvents);
    labelU->show();

    //遮挡越界的下部分
    QPixmap pixDown = QPixmap(":/res/setWidgetDown.jpg");
    labelD = new QLabel(this);
    labelD->setGeometry(0, 530, pixDown.width(), pixDown.height());
    labelD->setPixmap(pixDown);
    labelD->show();




    //取消按钮
    QPushButton* cancelBtn = new QPushButton(labelD);
    cancelBtn->setText(codec->toUnicode("取消"));
    //取消的文字样式
    QFont cancelFont(codec->toUnicode("黑体"), 14);
    cancelBtn->setFont(cancelFont);
    cancelBtn->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   color: rgb(225, 198, 21);"
        "   width: 235;"
        "   height: 57;"
        "   border: 2px solid rgb(225, 225, 225);"
        "   border-radius: 5px;"

        "   background-color: rgb(255, 255, 255);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(255, 250, 240);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(245, 239, 235);"
        "   }"
        );
    cancelBtn->move(490, 29);

    connect(cancelBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });




    //确认按钮
    QPushButton* confirmBtn = new QPushButton(labelD);
    confirmBtn->setText(codec->toUnicode("确认"));

    confirmBtn->setFont(cancelFont);
    confirmBtn->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   color: rgb(225, 198, 100);"
        "   width: 235;"
        "   height: 57;"
        "   border: 2px solid rgb(55, 55, 55);"
        "   border-radius: 5px;"

        "   background-color: rgb(55, 55, 55);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(80, 80, 80);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(55, 55, 55);"
        "   }"
        );
    confirmBtn->move(490 + 235 + 17, 29);

    connect(confirmBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });




    this->XLabel = new QLabel(labelU);
    XLabel->setPixmap(QPixmap(":/res/setXB.jpg"));
    XLabel->move(this->closeBtnPoint.x(), this->closeBtnPoint.y());
    XLabel->setFixedSize(this->closeBtnWH, this->closeBtnWH);
    //设置鼠标穿透 否则影响mouseMoveEvent的判定
    XLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    XLabel->show();



    //启动设置
    setOpen = new QScrollArea(this->showSetMain);
    setOpen->resize(500, 550);
    //设置启动设置样式
    setOpen->setFrameStyle(0);
    setOpen->setStyleSheet("background-color:transparent;");


    //标题
    QLabel text_setOpen(setOpen);
    //标题字体大小
    int Tsize = 15;
    //标题字体样式
    QFont Tfont(nullptr, Tsize);
    text_setOpen.setFont(Tfont);

    text_setOpen.setText(codec->toUnicode("启动设置"));
    text_setOpen.move(0, 0);

    //标题与选项距离
    int T_BSize = 32;

    //是否开机时自动启动
    QCheckBox autoOpen(setOpen);
    //设置按钮样式
    autoOpen.setStyleSheet(
        "QCheckBox::indicator {"
        "   width: 23px;"
        "   height: 23px;"
        "   border-style: solid;"
        "   border-width: 2px;"
        "   border-color:rgb(200, 200, 200);"
        "}"
        "QCheckBox::indicator:checked {"
        "   image: url(:/res/check.png);"
        "   border-width: 2px;"
        "   border-color:rgb(60, 60, 60);"
        "}"
        );

    //选项字体大小
    int boxSize = 12;
    //设置选项字体大小
    QFont boxFont = QFont(nullptr, boxSize);
    autoOpen.setFont(boxFont);
    autoOpen.setText(codec->toUnicode("开机自动启动"));
    autoOpen.move(0, Tsize + T_BSize);

    //选项与选项之间的距离
    int B_BSize = 30;

    //退出游戏时是否弹出
    QCheckBox showWhenExitGame(setOpen);
    showWhenExitGame.setStyleSheet(
        "QCheckBox::indicator {"
        "   width: 23px;"
        "   height: 23px;"
        "   border-style: solid;"
        "   border-width: 2px;"
        "   border-color:rgb(200, 200, 200);"
        "}"
        "QCheckBox::indicator:checked {"
        "   image: url(:/res/check.png);"
        "   border-width: 2px;"
        "   border-color:rgb(60, 60, 60);"
        "}"
        );
    //设置字体大小
    showWhenExitGame.setFont(boxFont);
    showWhenExitGame.setText(codec->toUnicode("退出游戏时弹出"));
    showWhenExitGame.move(0, Tsize + T_BSize + boxSize + B_BSize);
    //设置默认选项
    showWhenExitGame.setCheckState(Qt::Checked);

    setOpen->move(0, 0);
    setOpen->show();




    //启动设置底部
    int y1 = Tsize + T_BSize + boxSize + B_BSize + boxSize;

    //选项到下一个标题的距离
    int B_Tsize = 70;
    //关闭设置
    QScrollArea closeSet(this->showSetMain);
    //设置启动设置样式
    closeSet.setFrameStyle(0);
    closeSet.setStyleSheet("background-color:transparent;");
    //标题
    QLabel text_closeSet(&closeSet);

    //标题字体样式
    text_closeSet.setFont(Tfont);

    text_closeSet.setText(codec->toUnicode("关闭设置"));
    text_closeSet.move(0, 0);

    //关闭时最小化到系统托盘
    QRadioButton mini(&closeSet);
    mini.setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 35px;"
        "   height: 35px;"
        "   image: url(:/res/disChecked.png);"
        "}"
        "QRadioButton::indicator:checked {"
        "   image: url(:/res/checked.png);"
        "}"
        );
    mini.setFont(boxFont);
    mini.setText(codec->toUnicode("最小化到系统托盘"));
    //保证文字能显示完全
    closeSet.resize(500, 500);
    mini.move(0, T_BSize + Tsize);
    //设置默认选项为最小化到系统托盘
    mini.setChecked(true);

    //关闭时退出程序
    QRadioButton closeWhenExitGame(&closeSet);
    closeWhenExitGame.setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 35px;"
        "   height: 35px;"
        "   image: url(:/res/disChecked.png);"
        "}"
        "QRadioButton::indicator:checked {"
        "   image: url(:/res/checked.png);"
        "}"
        );
    closeWhenExitGame.setFont(boxFont);
    closeWhenExitGame.setText(codec->toUnicode("退出启动器"));
    closeWhenExitGame.move(0, T_BSize + Tsize + B_BSize + boxSize);

    closeSet.move(0, y1 + B_Tsize);
    closeSet.show();





    //关闭设置底部
    int y2 = y1 + B_Tsize + T_BSize + Tsize + B_BSize + boxSize * 2;
    //下载限速
    QScrollArea downloadSpeedLimit(this->showSetMain);
    downloadSpeedLimit.resize(600, 600);
    //设置下载限速样式
    downloadSpeedLimit.setFrameStyle(0);
    downloadSpeedLimit.setStyleSheet("background-color:transparent;");
    //标题
    QLabel text_speedLimit(&downloadSpeedLimit);
    //标题字体样式
    text_speedLimit.setFont(Tfont);
    text_speedLimit.setText(codec->toUnicode("下载限速"));
    text_speedLimit.move(0, 0);

    //提示控件
    limitTipBtn = new TipBtn(&downloadSpeedLimit, codec->toUnicode("限速效果同时适用与游戏下载和游戏预下载"));
    limitTipBtn->move(7.5 * Tsize, 2);

    //无限制
    QRadioButton noLimit(&downloadSpeedLimit);
    noLimit.setText(codec->toUnicode("无限制"));
    noLimit.setFont(boxFont);
    //设置样式
    noLimit.setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 35px;"
        "   height: 35px;"
        "   image: url(:/res/disChecked.png);"
        "}"
        "QRadioButton::indicator:checked {"
        "   image: url(:/res/checked.png);"
        "}"
        );
    noLimit.move(0, T_BSize + Tsize);
    //设置默认为无限制
    noLimit.setChecked(true);

    //限制下载速度
    QRadioButton limit(&downloadSpeedLimit);
    limit.setFont(boxFont);
    //设置样式
    limit.setStyleSheet(
        "QRadioButton::indicator {"
        "   width: 35px;"
        "   height: 35px;"
        "   image: url(:/res/disChecked.png);"
        "}"
        "QRadioButton::indicator:checked {"
        "   image: url(:/res/checked.png);"
        "}"
        );
    limit.move(0, T_BSize + Tsize + boxSize + B_BSize);
    //限速大小
    QLineEdit limitSize = QLineEdit(&downloadSpeedLimit);
    limitSize.setStyleSheet(
        "QLineEdit {"
        "   border: 2px solid rgb(230, 230, 230);"
        "   border-radius: 3px;"
        "   background-color: rgb(245, 245, 245);"
        "}"
        );
    limitSize.setText("4096");
    limitSize.setFont(boxFont);
    limitSize.setEnabled(false);
    limitSize.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    limitSize.move(50,  T_BSize + Tsize + boxSize + B_BSize);
    limitSize.resize(100, 37);
    limitSize.show();

    //若选择限制速度可编辑限制速度的大小 否则禁用编辑
    connect(&limit, &QRadioButton::clicked, this, [&](){
        limitSize.setEnabled(true);
    });
    connect(&noLimit, &QRadioButton::clicked, this, [&](){
        limitSize.setEnabled(false);
    });

    //补充限制的单位和范围
    QLabel addText(&downloadSpeedLimit);
    addText.setText("KB/S (100-10240)");
    addText.setFont(boxFont);
    addText.resize(200, limitSize.height());
    //设置垂直对齐
    addText.setAlignment(Qt::AlignVCenter);
    addText.move(50 + limitSize.width() + 10,  T_BSize + Tsize + boxSize + B_BSize);

    //编辑结束后检测输入的数据是否符合要求
    connect(&limitSize, &QLineEdit::editingFinished, this, [&](){
        bool isNum;
        //限制速度的大小
        double limitNum = limitSize.text().toDouble(&isNum);
        if(isNum)
        {
            //越界
            if(limitNum < 100)
            {
                limitSize.setText("100");
            }
            else if(limitNum > 10240)
            {
                limitSize.setText("10240");
            }
        }
        //非数字
        else
        {
            limitSize.setText("100");
        }

    });



    downloadSpeedLimit.move(0, y2 + B_Tsize);
    downloadSpeedLimit.show();




    //下载限制底部y坐标
    int y3 = y2 + B_Tsize + Tsize + T_BSize + boxSize + B_BSize + boxSize;
    //安装位置
    QScrollArea downloadSpace(this->showSetMain);
    downloadSpace.resize(600, 600);
    //设置安装位置样式
    downloadSpace.setFrameStyle(0);
    downloadSpace.setStyleSheet("background-color:transparent;");
    //标题
    QLabel text_DLSpace(&downloadSpace);
    //标题字体样式
    text_DLSpace.setFont(Tfont);
    text_DLSpace.setText(codec->toUnicode("安装位置"));
    text_DLSpace.move(0, 0);

    //提示控件
    downloadTipBtn = new TipBtn(&downloadSpace, codec->toUnicode("若没有正确检测到游戏安装位置，您可以在此处手动选择。"));
    downloadTipBtn->move(7.5 * Tsize, 2);

    //存储游戏文件路径
    QLineEdit gamePath = QLineEdit(&downloadSpace);
    gamePath.setStyleSheet(
        "QLineEdit {"
        "   border: 2px solid rgb(246, 245, 243);"
        "   background-color: rgb(246, 245, 243);"
        "}"
        );
    gamePath.resize(showSetMain->width(), boxSize * 3.5);
    gamePath.move(0, Tsize + T_BSize / 1.5);
    gamePath.setText("    C:\\Genshin Impact\\Genshin Impact Game");
    //设置为不可编辑状态
    gamePath.setEnabled(false);
    gamePath.setFont(boxFont);
    gamePath.show();
    //使用另外一个文件夹按钮
    QPushButton* selectOtherF = new QPushButton(&downloadSpace);
    selectOtherF->setText(codec->toUnicode("使用另外一个文件夹"));
    //金色文字的样式
    QFont goldFont(codec->toUnicode("黑体"), boxSize, QFont::Bold);
    selectOtherF->setFont(goldFont);
    //设置按钮样式
    selectOtherF->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   color: rgb(225, 198, 21);"
        "   width: 300;"
        "   height: 45;"
        "   border: 2px solid rgb(225, 225, 225);"
        "   border-radius: 5px;"

        "   background-color: rgb(255, 255, 255);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(255, 250, 240);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(245, 239, 235);"
        "   }"
        );
    selectOtherF->move(0, Tsize + (T_BSize / 1.5) + gamePath.height() + (B_BSize / 2));

    //点击按钮选择文件安装路径
    connect(selectOtherF, &QPushButton::clicked, this, [&](){
        QString str = QFileDialog::getExistingDirectory(this, codec->toUnicode("选择安装路径"), "C:\\Genshin Impact\\Genshin Impact Game");
        if(str == "")
        {
            gamePath.setText("    C:\\Genshin Impact\\Genshin Impact Game");
        }
        else
        {
            str = str.replace("/", "\\");
            QString result = QString("    %1").arg(str);
            gamePath.setText(result);
        }

    });



    downloadSpace.move(0, y3 + B_Tsize);
    downloadSpace.show();



    //安装路径底部坐标y
    int y4 = y3 + Tsize + (T_BSize / 1.5) + gamePath.height() + (B_BSize / 2) + selectOtherF->height();
    //启动器版本
    QScrollArea launcherVersion(this->showSetMain);
    launcherVersion.resize(600, 600);
    //设置安装位置样式
    launcherVersion.setFrameStyle(0);
    launcherVersion.setStyleSheet("background-color:transparent;");
    //标题
    QLabel text_LV(&launcherVersion);
    //标题字体样式
    text_LV.setFont(Tfont);
    text_LV.setText(codec->toUnicode("启动器版本"));
    text_LV.move(0, 0);
    //启动器更新按钮
    QPushButton* updataLauncher = new QPushButton(&launcherVersion);
    updataLauncher->setText(codec->toUnicode("启动器更新"));
    updataLauncher->setFont(goldFont);
    updataLauncher->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   color: rgb(225, 198, 21);"
        "   width: 300;"
        "   height: 45;"
        "   border: 2px solid rgb(225, 225, 225);"
        "   border-radius: 5px;"

        "   background-color: rgb(255, 255, 255);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(255, 250, 240);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(245, 239, 235);"
        "   }"
        );
    updataLauncher->move(0, text_LV.height() + (T_BSize / 2));

    //按下启动器更新按钮检测启动器更新
    connect(updataLauncher, &QPushButton::clicked, this, [=](){

    });

    //当前版本
    QLabel* version = new QLabel(&launcherVersion);
    version->setText(codec->toUnicode("当前版本：2.29.0.1"));
    version->setFont(boxFont);
    version->move(0, text_LV.height() + (T_BSize / 2) + updataLauncher->height() + B_BSize);
    version->show();




    launcherVersion.move(0, y4 + B_Tsize * 2.5);
    launcherVersion.show();




    //启动器版本底部y坐标
    int y5 = y4 + (B_Tsize * 2.5) + text_LV.height() + (T_BSize / 2) + updataLauncher->height() + B_BSize + version->height();
    //启动器更新日志
    QScrollArea updataLog(this->showSetMain);
    updataLog.resize(600, 600);
    //设置安装位置样式
    updataLog.setFrameStyle(0);
    updataLog.setStyleSheet("background-color:transparent;");
    //标题
    QLabel text_ULog(&updataLog);
    //标题字体样式
    text_ULog.setFont(Tfont);
    text_ULog.setText(codec->toUnicode("启动器更新日志"));
    text_ULog.move(0, 0);

    //查看按钮 按下后查看更新日志
    QPushButton* uLogBtn = new QPushButton(&updataLog);

    connect(uLogBtn, &QPushButton::clicked, this, [=](){

    });

    uLogBtn->setText(codec->toUnicode("查看"));
    uLogBtn->setFont(goldFont);
    uLogBtn->setStyleSheet(
        //未选中的样式
        "   QPushButton:!checked {"

        "   color: rgb(225, 198, 21);"
        "   width: 300;"
        "   height: 45;"
        "   border: 2px solid rgb(225, 225, 225);"
        "   border-radius: 5px;"

        "   background-color: rgb(255, 255, 255);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   background-color: rgb(255, 250, 240);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   background-color: rgb(245, 239, 235);"
        "   }"
        );
    uLogBtn->move(0, text_ULog.height() + (T_BSize / 2));





    updataLog.move(0, y5 + (B_Tsize / 1.3));
    updataLog.show();





    //更新日志底部坐标y
    int y6 = y5 + (B_Tsize / 1.3) + text_ULog.height() + (T_BSize / 2) + uLogBtn->height();
    //关于
    QLabel* about = new QLabel(showSetMain);
    about->setText(codec->toUnicode("关于"));
    about->setFont(Tfont);

    about->move(0, y6 + B_Tsize);
    about->show();



    //用户协议
    QPushButton* userAgreement = new QPushButton(showSetMain);

    //点击跳转至对应网页
    connect(userAgreement, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://ys.mihoyo.com/launcher/18/zh-cn/agreement?api_url=https%3A%2F%2Fhk4e-launcher.mihoyo.com%2Fhk4e_cn&key=eYd89JmJ&prev=false"));
    });

    userAgreement->setText(codec->toUnicode("用户协议"));
    userAgreement->setFont(goldFont);
    //设置字体颜色
    userAgreement->setStyleSheet("color: rgb(225, 198, 21);");

    userAgreement->move(0, y6 + B_Tsize + about->height() + (T_BSize / 2));
    userAgreement->show();



    //隐私政策
    QPushButton* privacyPolicy = new QPushButton(showSetMain);

    //点击跳转至对应网页
    connect(privacyPolicy, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://ys.mihoyo.com/launcher/18/zh-cn/agreementPrivacy?api_url=https%3A%2F%2Fhk4e-launcher.mihoyo.com%2Fhk4e_cn&key=eYd89JmJ&prev=false"));
    });

    privacyPolicy->setText(codec->toUnicode("隐私政策"));
    privacyPolicy->setFont(goldFont);
    //设置字体颜色
    privacyPolicy->setStyleSheet("color: rgb(225, 198, 21);");

    privacyPolicy->move(userAgreement->width(), y6 + B_Tsize + about->height() + (T_BSize / 2));
    privacyPolicy->show();



    //copyright
    QLabel* copyright = new QLabel(showSetMain);
    copyright->setPixmap(QPixmap(":/res/copyright.png"));
    copyright->move(0,  y6 + B_Tsize + about->height() + (T_BSize / 2) + privacyPolicy->height() + (B_BSize / 4));
    copyright->show();




    //通用设置按钮 按下跳转至设置框顶部
    commonlySet = new QPushButton(this);
    commonlySet->setText(codec->toUnicode("通用设置                  "));
    commonlySet->setFont(boxFont);
    commonlySet->setStyleSheet(
        "   width: 270;"
        "   height: 60;"
        "   border: 2px solid rgb(255, 255, 255);"
        "   background-color: rgb(255, 255, 255);"
        );
    commonlySet->move(5, 106);

    connect(commonlySet, &QPushButton::clicked, this, [=](){
        this->showSetMain->move(showSetMain->x(), 110);
        this->AreaBar.move(AreaBar.x(), 110);
        this->setMainY = 110;

        //该按钮变亮
        this->setUpBtnSty(commonlySet);
        //其余按钮变暗
        this->setDownBtnSty(gameRes);
        this->setDownBtnSty(versionInformation);

    });

    //通用设置按钮高度
    int cSHeight = 60;

    //游戏资源按钮 按下跳转至设置框中部
    gameRes = new QPushButton(this);
    gameRes->setText(codec->toUnicode("游戏资源                  "));
    gameRes->setFont(boxFont);
    gameRes->setStyleSheet(
        "   width: 270;"
        "   height: 60;"
        "   border: 2px solid rgb(246, 245, 243);"
        "   background-color: rgb(246, 245, 243);"
        );
    gameRes->move(5, 106 + cSHeight);

    connect(gameRes, &QPushButton::clicked, this, [=](){
        this->moveToDownloadPlace();
    });

    //版本信息按钮 按下跳转至设置框底部
    versionInformation = new QPushButton(this);
    versionInformation->setText(codec->toUnicode("版本信息                  "));
    versionInformation->setFont(boxFont);
    versionInformation->setStyleSheet(
        "   width: 270;"
        "   height: 60;"
        "   border: 2px solid rgb(246, 245, 243);"
        "   background-color: rgb(246, 245, 243);"
        );
    versionInformation->move(5, 106 + cSHeight * 2);

    connect(versionInformation, &QPushButton::clicked, this, [=](){
        this->showSetMain->move(showSetMain->x(), 110 - this->wheelSize * 10);
        this->AreaBar.move(AreaBar.x(), 110 + this->AreaBarMoveSize * 10);
        this->setMainY = 108 - this->wheelSize * 10;

        //该按钮变亮
        this->setUpBtnSty(versionInformation);
        //其余按钮变暗
        this->setDownBtnSty(commonlySet);
        this->setDownBtnSty(gameRes);
    });



    //根据设置框的位置调整按钮样式
    connect(this, &SetWidget::setMainMoveSignal, this, [=](){
        //在通用设置范围内
        if(this->AreaBar.y() >= 110 && AreaBar.y() < 110 + AreaBarMoveSize * 7)
        {
            //该按钮变亮
            this->setUpBtnSty(commonlySet);
            //其余按钮变暗
            this->setDownBtnSty(gameRes);
            this->setDownBtnSty(versionInformation);
        }
        //在游戏资源范围内
        else if(this->AreaBar.y() >= 110 + AreaBarMoveSize * 7 && AreaBar.y() < 110 + AreaBarMoveSize * 10)
        {
            //该按钮变亮
            this->setUpBtnSty(gameRes);
            //其余按钮变暗
            this->setDownBtnSty(commonlySet);
            this->setDownBtnSty(versionInformation);
        }
        //在版本信息范围内
        else if(this->AreaBar.y() >= 110 + AreaBarMoveSize * 10 && AreaBar.y() <= 110 + AreaBarMoveSize * 12)
        {
            //该按钮变亮
            this->setUpBtnSty(versionInformation);
            //其余按钮变暗
            this->setDownBtnSty(commonlySet);
            this->setDownBtnSty(gameRes);
        }
    });

    showSetMain->show();


    //判断是否移动到安装位置
    if(isMoveToDownloadPlace)
    {
        this->moveToDownloadPlace();
    }


    //设置模态对话框
    this->exec();
}

SetWidget::~SetWidget()
{
    delete this->showSetMain;
}

void SetWidget::paintEvent(QPaintEvent* pev)
{


    QPainter pt(this);
    pt.drawPixmap(0, 0, QPixmap(":/res/setWidget.jpg"));

    if(this->isCloseBtnY)
    {
        XLabel->setPixmap(QPixmap(":/res/setXY.jpg"));
    }
    else
    {
        XLabel->setPixmap(QPixmap(":/res/setXB.jpg"));
    }


}

void SetWidget::mousePressEvent(QMouseEvent* mev)
{
    //当鼠标左键按下 若鼠标在标题栏内则可进行对窗口的移动
    if(mev->x() < this->width() && mev->x() > 0 && mev->y() < this->BarH && mev->y() >0 && mev->button() == Qt::LeftButton)
    {
        this->isMoveable = true;
        //记录鼠标位置
        this->mousePoint = QPoint(mev->x(), mev->y());

    }
    else this->isMoveable = false;

    //鼠标 按下时在关闭按钮内
    if(mev->x() > this->closeBtnPoint.x() && mev->x() < this->closeBtnPoint.x() + this->closeBtnWH
        && mev->y() > this->closeBtnPoint.y() && mev->y() < this->closeBtnPoint.y() + this->closeBtnWH)
    {
        this->isCloseBtnY = false;
        this->isPressInCB = true;
    }

    //鼠标在滚动条内按下
    if(AreaBar.x() < mev->x() && AreaBar.x() + AreaBar.width() > mev->x()
        && AreaBar.y() < mev->y() && AreaBar.y() + AreaBar.height() > mev->y())
    {
        this->isRe = true;
        this->mouseY = mev->y();
        this->sliderY = AreaBar.y();
        this->tempSMY = this->setMainY;
    }





    update();
    return QDialog::mousePressEvent(mev);
}

void SetWidget::mouseReleaseEvent(QMouseEvent* mev)
{
    this->isMoveable = false;


    //鼠标释放时在关闭按钮内
    if(mev->x() > this->closeBtnPoint.x() && mev->x() < this->closeBtnPoint.x() + this->closeBtnWH
        && mev->y() > this->closeBtnPoint.y() && mev->y() < this->closeBtnPoint.y() + this->closeBtnWH && this->isPressInCB)
    {
        this->close();
    }

    this->isPressInCB = false;
    this->isCloseBtnY = false;
    this->isRe = false;

    update();
    return QDialog::mouseReleaseEvent(mev);
}

void SetWidget::mouseMoveEvent(QMouseEvent* mev)
{
    //是否满足移动条件
    if(this->isMoveable)
    {
        //鼠标在x和y方向上的移动距离
        int moveX = mev->x() - this->mousePoint.x();
        int moveY = mev->y() - this->mousePoint.y();

        this->move(QPoint(this->x() + moveX, this->y() + moveY));

    }

    //鼠标进入关闭按钮
    if(mev->x() > this->closeBtnPoint.x() && mev->x() < this->closeBtnPoint.x() + this->closeBtnWH
        && mev->y() > this->closeBtnPoint.y() && mev->y() < this->closeBtnPoint.y() + this->closeBtnWH)
    {
        //若鼠标为松开状态 则按钮发黄光
        if(!this->isPressInCB) this->isCloseBtnY = true;
        //鼠标按下 按钮不发黄光
        else this->isCloseBtnY = false;

    }
    //鼠标离开按钮
    else
    {
        //鼠标松开 按钮不发黄光
        if(!this->isPressInCB) this->isCloseBtnY = false;

        //鼠标按下 按钮发黄光
        else this->isCloseBtnY = true;

    }

    bool isInRoll = AreaBar.x() < mev->x() && AreaBar.x() + AreaBar.width() > mev->x()
                    && AreaBar.y() < mev->y() && AreaBar.y() + AreaBar.height() > mev->y();

    //若鼠标在滚动条内
    if(isInRoll)
    {
        this->AreaBar.setStyleSheet(
            //按钮默认样式
            "QPushButton {"
            "   border-color:rgb(200, 200, 200);"
            "   background-color: rgb(200, 200, 200);"
            "   border-radius: 5px;"
            "}"

            );
    }
    //不在滚动条内 且鼠标松开
    if(!isInRoll && !isRe)
    {
        this->AreaBar.setStyleSheet(
            //按钮默认样式
            "QPushButton {"
            "   border-color:rgb(240, 240, 240);"
            "   background-color: rgb(240, 240, 240);"
            "   border-radius: 5px;"
            "}"

            );
    }

    //操控滚动条
    if(isRe)
    {


        int relativeSize = mev->y() - mouseY;
        //限制滚动条的范围
        if(sliderY + relativeSize > 110 && sliderY + relativeSize + AreaBar.height() < 530)
        {
            AreaBar.move(AreaBar.x(), sliderY + relativeSize);
            //设置框需要移动的距离
            float mainMoveSize = (wheelSize * relativeSize) / 25;

            this->showSetMain->move(320, this->tempSMY - mainMoveSize);
            this->setMainY = this->tempSMY - mainMoveSize;

        }
        else if(sliderY + relativeSize <= 110)
        {
            AreaBar.move(AreaBar.x(), 110);
            this->showSetMain->move(320, 110);
            this->setMainY = 110;
        }
        else if(sliderY + relativeSize + AreaBar.height() >= 530 - AreaBar.height())
        {
            AreaBar.move(AreaBar.x(), 530 - AreaBar.height());
            this->showSetMain->move(320, 110 - (this->setMainHeight - (530 - 110)));
            this->setMainY = 110 - (this->setMainHeight - (530 - 110));
        }

        //发出设置框移动信号
        emit this->setMainMoveSignal();
    }

    update();
    return QDialog::mouseMoveEvent(mev);
}

void SetWidget::wheelEvent(QWheelEvent *wev)
{

    //鼠标滚轮滚动 调节设置框的位置
    //向上移动
    if(wev->delta() > 0)
    {
        int relativeSize = -this->AreaBarMoveSize;
        //设置框需要移动的距离
        double mainMoveSize = -wheelSize;

        if(AreaBar.y() + relativeSize > 110 && AreaBar.y() + relativeSize + AreaBar.height() < 530)
        {
            AreaBar.move(AreaBar.x(), AreaBar.y() + relativeSize);

            this->showSetMain->move(320, this->showSetMain->y() - mainMoveSize);
            this->setMainY = this->showSetMain->y() - mainMoveSize;
        }
        //范围不够则置顶
        else if(AreaBar.y() + relativeSize <= 110)
        {
            AreaBar.move(AreaBar.x(), 110);

            this->showSetMain->move(320, 110);
            this->setMainY = 110;
        }
    }
    //向下移动
    else
    {
        int relativeSize = this->AreaBarMoveSize;
        //设置框需要移动的距离
        double mainMoveSize = wheelSize;

        if(AreaBar.y() + relativeSize > 110 && AreaBar.y() + relativeSize + AreaBar.height() < 530)
        {
            AreaBar.move(AreaBar.x(), AreaBar.y() + relativeSize);

            this->showSetMain->move(320, showSetMain->y() - mainMoveSize);
            this->setMainY = showSetMain->y() - mainMoveSize;
        }
        //范围不够则置底
        else if(AreaBar.y() + relativeSize >= 530 - AreaBar.height())
        {
            AreaBar.move(AreaBar.x(), 530 - AreaBar.height());

            this->showSetMain->move(320, 110 - (this->setMainHeight - (530 - 110)));
            this->setMainY = 110 - (this->setMainHeight - (530 - 110));
        }
    }

    //发出设置框移动信号
    emit this->setMainMoveSignal();

    update();
    return QDialog::wheelEvent(wev);
}

//设置前台跳转按钮样式
void SetWidget::setUpBtnSty(QPushButton* btn)
{
    btn->setStyleSheet(
        "   QPushButton:!checked {"
        "   width: 270;"
        "   height: 60;"
        "   border: 2px solid rgb(255, 255, 255);"
        "   background-color: rgb(255, 255, 255);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   border: 2px solid rgb(255, 255, 255);"
        "   background-color: rgb(255, 255, 255);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   border: 2px solid rgb(255, 255, 255);"
        "   background-color: rgb(255, 255, 255);"
        "   }"
        );
}
//设置后台跳转按钮样式
void SetWidget::setDownBtnSty(QPushButton* btn)
{
    btn->setStyleSheet(
        "   QPushButton:!checked {"
        "   width: 270;"
        "   height: 60;"
        "   border: 2px solid rgb(246, 245, 243);"
        "   background-color: rgb(246, 245, 243);"
        "   }"

        //悬停样式
        "   QPushButton:hover {"
        "   border: 2px solid rgb(236, 235, 233);"
        "   background-color: rgb(236, 235, 233);"
        "   }"

        //按下的样式
        "   QPushButton:pressed {"
        "   border: 2px solid rgb(255, 255, 255);"
        "   background-color: rgb(255, 255, 255);"
        "   }"
        );
}

void SetWidget::moveToDownloadPlace()
{
    this->showSetMain->move(showSetMain->x(), 110 - this->wheelSize * 7);
    this->AreaBar.move(AreaBar.x(), 110 + this->AreaBarMoveSize * 7);
    this->setMainY = 108 - this->wheelSize * 7;

    //该按钮变亮
    this->setUpBtnSty(gameRes);
    //其余按钮变暗
    this->setDownBtnSty(commonlySet);
    this->setDownBtnSty(versionInformation);

}
