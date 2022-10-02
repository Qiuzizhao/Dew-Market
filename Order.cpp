#include "Order.h"

int Order::getID() const
{
    return ID;
}

int Order::getGoodsID() const
{
    return goodsID;
}

QString Order::getGoodsName() const
{
    return goodsName;
}

QString Order::getBuyer() const
{
    return buyer;
}

QString Order::getSeller() const
{
    return seller;
}


//写入
void Order::setID(const int &value)
{
    ID = value;
}

void Order::setGoodsID(const int &value)
{
    goodsID = value;
}

void Order::setGoodsName(const QString &value)
{
    goodsName = value;
}

void Order::setBuyer(const QString &value)
{
    buyer = value;
}

void Order::setSeller(const QString &value)
{
    seller = value;
}

//将 order_tempFile 的数据更新到对象中
void Order::flushOrder()
{
    QFile file(order_tempFile);
    file.open(QIODevice::ReadOnly);
    QDataStream Str(&file);

    if(!file.atEnd())
    {
        Str>>ID>>goodsID>>goodsName>>buyer>>seller;
    }

    file.close();
}



//将对象数据存储到 order_tempFile
void Order::saveOrder()
{
    QFile file(order_tempFile);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream Str(&file);

    Str<<ID<<goodsID<<goodsName<<buyer<<seller;


    file.close();
}



//从 orderFile 删除订单数据，并存储到 order_deleteFile 中
void Order::deleteOrder()
{
    int orderID = 10000, orderGoodsID = 10000;
    QString orderGoodsName,orderBuyer,orderSeller;


    //利用 order_superFile 作为中转，写入 orderFile，删除该用户的信息
    QFile file(orderFile);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile superFile(order_superFile);
    superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream writeDataStr(&superFile);


    while (!readDataStr.atEnd())
    {
        //从 orderFile 读取数据
        readDataStr>>orderID>>orderGoodsID>>orderGoodsName>>orderBuyer>>orderSeller;

        if(orderID != ID)
        {
            //并非当前用户则直接写入 order_superFile
            writeDataStr<<orderID<<orderGoodsID<<orderGoodsName<<orderBuyer<<orderSeller;


        }
        else
        {
            //读取到当前用户则不写入

        }

    }


    //关闭文件
    //删除 orderFile 原文件，并将 order_superFile 改名为 orderFile 来取替原文件
    file.close();
    superFile.close();
    file.remove();
    superFile.rename(orderFile);

    //将该用户信息写入 order_deleteFile
    QFile deleteFile(order_deleteFile);
    deleteFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
    QDataStream deleteDataStr(&deleteFile);

    deleteDataStr<<ID<<goodsID<<goodsName<<buyer<<seller;

    deleteFile.close();

}
