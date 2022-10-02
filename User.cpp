#include <User.h>


//读取
QString User::getID() const
{
    return ID;
}

QString User::getName() const
{
    return name;
}

QString User::getPassword() const
{
    return password;
}

QString User::getAddress() const
{
    return address;
}

QString User::getUserType() const
{
    return userType;
}


//写入
void User::setID(const QString &value)
{
    ID = value;
}

void User::setName(const QString &value)
{
    name = value;
}

void User::setPassword(const QString &value)
{
    password = value;
}

void User::setAddress(const QString &value)
{
    address = value;
}

void User::setUserType(const QString &value)
{
    userType = value;
}


//从 user_tempFile 更新对象信息
void User::flushUser()
{
    QFile file(user_tempFile);
    file.open(QIODevice::ReadOnly);
    QDataStream Str(&file);

    if(!file.atEnd())
    {
        Str >> ID >> name >> password >> address >> userType;
    }

    file.close();

}



//将对象信息存储到 user_tempFile
void User::saveUser()
{
    QFile file(user_tempFile);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream Str(&file);

    Str << ID << name << password << address << userType;

    file.close();

}



//判断用户是否购买了商品
bool User::IsBuy(int goodsID)
{
    bool IsBuy = 0;

    int orderID = 10000, orderGoodsID = 10000;
    QString orderGoodsName,orderBuyer,orderSeller;

    QFile file(orderFile);
    file.open(QIODevice::ReadOnly);
    QDataStream Str(&file);

    while(!file.atEnd())
    {

        //读入数据
        Str>>orderID>>orderGoodsID>>orderGoodsName>>orderBuyer>>orderSeller;

        //判断是否为该商品
        if(goodsID == orderGoodsID){

            //判断订单买家是否一致,若一致则更新bool值并退出循环
            if(name == orderBuyer)
            {
            IsBuy = 1;
            break;
            }
        }

    }

    file.close();

    return IsBuy;

}


//删除用户信息，并存储到 user_deleteFile
void User::deleteUser()
{
    QString userID, userName, userPassword, userAddress, userUserType;

    //利用 user_superFile 作为中转，写入 userFile，删除该用户的信息
    QFile file(userFile);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile superFile(user_superFile);
    superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream writeDataStr(&superFile);


    while (!readDataStr.atEnd())
    {
        readDataStr >> userID >> userName >> userPassword >> userAddress >> userUserType;
        if(userName != name)
        {
            //并非当前用户则直接写入 user_superFile
            writeDataStr << userID << userName << userPassword << userAddress << userUserType;
        }
        else
        {
            //读取到当前用户则不写入

        }

    }

    //关闭文件
    //删除 userFile 原文件，并将 user_superFile 改名为 userFile 来取替原文件
    file.close();
    superFile.close();
    file.remove();
    superFile.rename(userFile);

    //将该用户信息写入 user_deleteFile
    QFile deleteFile(user_deleteFile);
    deleteFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
    QDataStream deleteDataStr(&deleteFile);

    deleteDataStr<<ID<<name<<password<<address<<userType;

    deleteFile.close();

}
