#include "SellerOrderBox.h"

SellerOrderBox::SellerOrderBox()
{
    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("订单");

    this->resize(700,700);

    QVBoxLayout * VBox = new QVBoxLayout;

    //订单表格
    OrderTable = new QTableWidget;

    OrderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    OrderTable->setColumnCount(5);
    OrderTable->setHorizontalHeaderLabels(QStringList() <<"订单号"<<"商品编号"<<"商品"<<"买家"<<"卖家");

    //更新 users 对象信息
    users.flushUser();

    //更新订单表格
    flushTable();

    //表格信息不可修改
    OrderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);



    VBox->addWidget(OrderTable);

    this->setLayout(VBox);




}

//更新订单列表
void SellerOrderBox::flushTable()
{
    //打开 OrderFile
    QFile file(orderFile);
    file.open(QIODevice::ReadWrite);
    QDataStream dataStr(&file);

    OrderTable->setRowCount(0);

    while(!dataStr.atEnd())
    {
        //读入数据
        dataStr>>ID>>goodsID>>goodsName>>buyer>>seller;

        //判断卖家
        if(seller == users.getName())
        {
            OrderTable->setRowCount(OrderTable->rowCount()+1);
            OrderTable->setItem(OrderTable->rowCount()-1,0,new QTableWidgetItem(QString::number(ID)));
            OrderTable->setItem(OrderTable->rowCount()-1,1,new QTableWidgetItem(QString::number(goodsID)));
            OrderTable->setItem(OrderTable->rowCount()-1,2,new QTableWidgetItem(goodsName));
            OrderTable->setItem(OrderTable->rowCount()-1,3,new QTableWidgetItem(buyer));
            OrderTable->setItem(OrderTable->rowCount()-1,4,new QTableWidgetItem(seller));
        }
    }

    file.close();

}



void SellerOrderBox::closeBox()
{

}



//发送信号
void SellerOrderBox::emitCloseBox()
{
    emit closeBox();
}
