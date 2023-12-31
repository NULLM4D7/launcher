#ifndef STARTBTN_H
#define STARTBTN_H

//开始游戏按钮

#include "exitBtn.h"
#include <QDesktopServices>
#include <QUrl>
#include <QSystemTrayIcon>

class StartBtn : public ExitBtn
{
    Q_OBJECT

public:
    explicit StartBtn(ExitBtn *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* pev) override;

    //绘制按钮
    void drawBtn(QPainter* pt);

    virtual void doCode() override;

};

#endif // STARTBTN_H
