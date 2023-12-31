#ifndef MINIMIZEBTN_H
#define MINIMIZEBTN_H

//最小化按钮

#include "exitBtn.h"

class MinimizeBtn : public ExitBtn
{
    Q_OBJECT
public:
    explicit MinimizeBtn(ExitBtn *parent = nullptr);

private:

    void paintEvent(QPaintEvent* pev) override;

    virtual void doCode() override {static_cast<QWidget*>(parent())->showMinimized();};
};

#endif // MINIMIZEBTN_H
