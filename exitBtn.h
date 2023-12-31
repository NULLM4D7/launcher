#ifndef EXITBTN_H
#define EXITBTN_H

//关闭按钮

#include <QLabel>
#include <QThread>
#include <QEvent>

class ExitBtn : public QLabel
{
    Q_OBJECT
public:
    explicit ExitBtn(QLabel *parent = nullptr);

    //鼠标是否在按钮内按下
    bool isPress = false;

    //鼠标是否在按钮内释放
    bool isRelease = false;

    void enterEvent(QEvent* ev) override;

    void leaveEvent(QEvent* ev) override;

    //鼠标是否在按钮内
    bool isInBtn = false;

    void paintEvent(QPaintEvent* pev) override;

    void mousePressEvent(QMouseEvent* mev) override;

    void mouseReleaseEvent(QMouseEvent* mev) override;

    void mouseMoveEvent(QMouseEvent* mev) override;

    //按钮核心功能
    virtual void doCode() {static_cast<QWidget*>(parent())->hide();};
};

#endif // EXITBTN_H
