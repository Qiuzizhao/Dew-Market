#ifndef ADDGOODSBOX_H
#define ADDGOODSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QCheckBox>

#include "User.h"
#include "Goods.h"
#include "Tool.h"

class AddGoodsBox : public QDialog
{
    Q_OBJECT
public:
    //构建添加商品界面
    AddGoodsBox();

signals:
    //自定义信号，当添加成功后，更新商品目录
    void closeBox();

public slots:
    //将新商品的信息写入到文件中
    void saveGoodsMess();


public:
    //发出 closeBox 信号
    void emitCloseBox();

private:

    QLineEdit * name;
    QLineEdit * price;
    QLineEdit * quantity;
    QLineEdit * describe;

    QPushButton * add;
    QPushButton * cancel;

    User users;

    Goods goodss;
};


#endif // ADDGOODSBOX_H
