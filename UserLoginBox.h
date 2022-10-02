//登录窗口
#ifndef USERLOGINBOX_H
#define USERLOGINBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

#include "User.h"
#include "Tool.h"


class UserLoginBox : public QDialog
{
    Q_OBJECT
public:
    //构建登录界面
    UserLoginBox();

signals:
    //自定义信号，当登录成功后，更新主界面登录状态
    void closeBox();

public slots:
    //验证用户名与密码
    void vertify();
public:
    //发出 closeBox 信号
    void emitCloseBox();

private:
    QLineEdit * ID;
    QLineEdit * password;
    QPushButton * login;
    QPushButton * cancel;
    QPushButton * face;

    User users;
};

#endif // USERLOGINBOX_H
