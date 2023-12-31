#ifndef TIPBTN_H
#define TIPBTN_H

//问号按钮 鼠标悬停时显示提示文本

#include <QPushButton>
#include <QWidget>

class TipBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit TipBtn(QWidget *parent = nullptr, QString tipContent = "");

protected:
    QWidget tipMessage;

    //提示相对问号的距离
    int tip_BtnSize = 30;
    QString m_tipContent;
    void enterEvent(QEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
    void wheelEvent(QWheelEvent* ev) override;
signals:

};

#endif // TIPBTN_H
