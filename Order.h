//订单

#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QFile>
#include <Tool.h>

class Order
{
public:
    int getID() const;
    void setID(const int &value);

    int getGoodsID() const;
    void setGoodsID(const int &value);

    QString getGoodsName() const;
    void setGoodsName(const QString &value);

    QString getBuyer() const;
    void setBuyer(const QString &value);

    QString getSeller() const;
    void setSeller(const QString &value);

    //将 order_tempFile 的数据更新到对象
    void flushOrder();

    //将对象数据存储到 order_tempFile
    void saveOrder();

    //从 orderFile 删除订单数据，并存储到 order_deleteFile 中
    void deleteOrder();


private:

    int ID = 10000;

    int goodsID = 10000;

    QString goodsName;

    QString buyer;

    QString seller;


};

#endif // ORDER_H
