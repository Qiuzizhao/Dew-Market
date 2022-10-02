#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QFile>
#include <Tool.h>

class Goods
{
public:
    int getID() const;
    void setID(const int &value);

    QString getName() const;
    void setName(const QString &value);

    int getPrice() const;
    void setPrice(const int &value);

    int getQuantity() const;
    void setQuantity(const int &value);

    QString getDescribe() const;
    void setDescribe(const QString &value);

    QString getSeller() const;
    void setSeller(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    //将 goods_tempFile 的数据更新到对象
    void flushGoods();

    //将对象数据存储到 goods_tempFile
    void saveGoods();

    //从 goodsFile 删除订单数据，并存储到 goods_deleteFile 中
    void deleteGoods();


private:

    int ID = 10000;

    QString name;
    int price;
    int quantity;

    //详细介绍
    QString describe;

    //卖家
    QString seller;

    //上架 & 已下架
    QString status;
};

#endif // GOODS_H
