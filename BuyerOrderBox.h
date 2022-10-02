#ifndef BUYERORDERBOX_H
#define BUYERORDERBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidget>

#include "User.h"
#include "Goods.h"
#include "Comment.h"
#include "Tool.h"

class BuyerOrderBox : public QDialog
{

public:
    //构建订单窗口
    BuyerOrderBox();

    //更新订单表格
    void flushTable();

signals:
    void closeBox();

public:
    //发出 closeBox 信号
    void emitCloseBox();

private:

    //订单信息
    int ID = 10000;

    int goodsID = 10000;

    QString goodsName;

    QString buyer;

    QString seller;

    //表格
    QTableWidget * OrderTable;

    User users;

};

#endif // BUYERORDERBOX_H
