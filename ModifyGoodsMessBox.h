#ifndef MODIFYGOODSMESSBOX_H
#define MODIFYGOODSMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDialog>

#include "User.h"
#include "Goods.h"
#include "Tool.h"

class ModifyGoodsMessBox : public QDialog
{
    Q_OBJECT
public:
    //构建修改商品信息界面
    ModifyGoodsMessBox();

signals:
    void closeBox();

public slots:
    //保存修改的信息
    void saveGoodsMess();

public:
    //发出 closeBox 信号
    void emitCloseBox();

private:
    //商品信息
    QLineEdit * ID;
    QLineEdit * name;
    QLineEdit * price;
    QLineEdit * quantity;
    QLineEdit * describe;

    //修改 & 取消按钮
    QPushButton * modify;
    QPushButton * cancel;


    Goods goodss;

};


#endif // MODIFYGOODSMESSBOX_H
