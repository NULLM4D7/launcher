#ifndef SETBTN_H
#define SETBTN_H

//设置按钮 点击后打开启动器配置窗口

#include <QPushButton>

class SetWidget;

class SetBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit SetBtn(QWidget *parent = nullptr);

protected:
    //设置对话框
    //SetWidget* setWidget;

    //void paintEvent(QPaintEvent* pev) override;

    //void doCode();
signals:

};

#endif // SETBTN_H
