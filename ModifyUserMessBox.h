// 用户信息修改窗口
#ifndef MODIFYUSERMESSBOX_H
#define MODIFYUSERMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDialog>

#include "User.h"
#include "Goods.h"
#include "Tool.h"



class ModifyUserMessBox : public QDialog
{
    Q_OBJECT
public:
    //构建修改用户信息界面
    ModifyUserMessBox();

signals:
    void closeBox();

public slots:
    //保存修改的信息
    void saveUserMess();

public:
    //发出 closeBox 信号
    void emitCloseBox();

private:
    //个人信息
    QLineEdit * ID;
    QLineEdit * name;
    QLineEdit * password;
    QLineEdit * address;
    QLineEdit * userType;

    //原密码
    QLineEdit * originPassword;

    QPushButton * modify;
    QPushButton * cancel;

    User users;
};

#endif // MODIFYUSERMESSBOX_H
