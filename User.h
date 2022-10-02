#ifndef USER_H
#define USER_H

#include <QString>
#include <QFile>
#include "Tool.h"

class User
{
public:

    //set为写入
    //get为读取

    QString getID() const;
    void setID(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    QString getUserType() const;
    void setUserType(const QString &value);

    //将 user_tempFile 的数据更新到对象中
    void flushUser();

    //将对象数据存储到 user_tempFile
    void saveUser();

    //判断用户是否购买了商品
    bool IsBuy(int goodsID);

    //删除用户信息，并存储到 user_deleteFile
    void deleteUser();

private:
    /*
     * 用户信息
     * 账号
     * 昵称
     * 密码
     * 收货地址
     * 买家&卖家&管理员
    */

    QString ID;
    QString name;
    QString password;
    QString address;
    QString userType;
};

#endif // USER_H
