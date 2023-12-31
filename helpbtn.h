#ifndef HELPBTN_H
#define HELPBTN_H

//游戏本地文件管理按钮 位于开始游戏按钮右边

#include <QPushButton>
#include <QMenu>

class HelpBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit HelpBtn(QWidget *parent = nullptr, QString tipContent = "");

protected:
    //提示框
    QWidget tipMessage;

    //向按钮中添加菜单栏
    QMenu* helpMenu;

    //安装位置
    QAction* downloadPlace;

    //一键修复
    QAction* fix;

    //清除下载资源
    QAction* cleanDownloadRes;

    //检查游戏更新
    QAction* checkGameUpdata;

    void enterEvent(QEvent* ev) override;

    void leaveEvent(QEvent* ev) override;

signals:
    void entered();

    void leaved();
};

#endif // HELPBTN_H
