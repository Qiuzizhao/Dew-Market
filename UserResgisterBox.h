#ifndef USERRESGISTERBOX_H
#define USERRESGISTERBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QCheckBox>

#include "User.h"
#include "Tool.h"


class UserResgisterBox : public QDialog
{
    Q_OBJECT
public:
    //构建注册界面
    UserResgisterBox();

signals:
    //自定义信号，当注册成功后，更新主界面登录状态
    void closeBox();

public slots:
    //将新用户的信息写入到文件中
    void saveUserMess();

    //选择了用户类型
    void IsUser();

    //选择了管理员类型
    void IsAdmin();

public:
    //发出 closeBox 信号
    void emitCloseBox();

private:
    QLineEdit * ID;
    QLineEdit * name;
    QLineEdit * password;
    QLineEdit * address;
    QCheckBox * userCheck;
    QCheckBox * adminCheck;
    QPushButton * resgister;
    QPushButton * cancel;

    User users;
};

#endif // USERRESGISTERBOX_H
