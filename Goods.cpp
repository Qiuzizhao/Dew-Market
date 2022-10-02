#include "Goods.h"


//读取
int Goods::getID() const
{
    return ID;
}

QString Goods::getName() const
{
    return name;
}

int Goods::getPrice() const
{
    return price;
}

int Goods::getQuantity() const
{
    return quantity;
}

QString Goods::getDescribe() const
{
    return describe;
}

QString Goods::getSeller() const
{
    return seller;
}

QString Goods::getStatus() const
{
    return status;
}


//写入
void Goods::setID(const int &value)
{
    ID = value;
}

void Goods::setName(const QString &value)
{
    name = value;
}

void Goods::setPrice(const int &value)
{
    price = value;
}

void Goods::setQuantity(const int &value)
{
    quantity = value;
}

void Goods::setDescribe(const QString &value)
{
    describe = value;
}

void Goods::setSeller(const QString &value)
{
    seller = value;
}

void Goods::setStatus(const QString &value)
{
    status = value;
}



//将 goods_tempFile 的数据更新到对象中
void Goods::flushGoods()
{
    QFile file(goods_tempFile);
    file.open(QIODevice::ReadOnly);
    QDataStream Str(&file);

    if(!file.atEnd())
    {
        Str>>ID>>name>>price>>quantity>>describe>>seller>>status;
    }

    file.close();
}



//将对象数据存储到 goods_tempFile
void Goods::saveGoods()
{
    QFile file(goods_tempFile);
    file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream Str(&file);

    Str<<ID<<name<<price<<quantity<<describe<<seller<<status;

    file.close();
}



//从 goodsFile 删除订单数据，并存储到 goods_deleteFile 中
void Goods::deleteGoods()
{
    int goodsID = 0,goodsPrice = 0,goodsQuantity = 0;
    QString goodsName,goodsDescribe,goodsSeller,goodsStatus;

    //利用 goods_superFile 作为中转，写入 goodsFile，删除该用户的信息
    QFile file(goodsFile);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile superFile(goods_superFile);
    superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream writeDataStr(&superFile);


    while (!readDataStr.atEnd())
    {
        //从 goodsFile 读取数据
        readDataStr>>goodsID>>goodsName>>goodsPrice>>goodsQuantity>>goodsDescribe>>goodsSeller>>goodsStatus;

        if(goodsID != ID)
        {
            //并非当前用户则直接写入 goods_superFile
            writeDataStr<<goodsID<<goodsName<<goodsPrice<<goodsQuantity<<goodsDescribe<<goodsSeller<<goodsStatus;

        }
        else
        {
            //读取到当前用户则不写入

        }

    }


    //关闭文件
    //删除 goodsFile 原文件，并将 goods_superFile 改名为 goodsFile 来取替原文件
    file.close();
    superFile.close();
    file.remove();
    superFile.rename(goodsFile);

    //将该用户信息写入 goods_deleteFile
    QFile deleteFile(goods_deleteFile);
    deleteFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
    QDataStream deleteDataStr(&deleteFile);

    deleteDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;

    deleteFile.close();

}
