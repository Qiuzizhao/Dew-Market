#include "ModifyUserMessBox.h"

//构建用户信息修改窗口
ModifyUserMessBox::ModifyUserMessBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout & QHBoxLayout
     * QFormLayout 中放置六个输入框，分别为 ID,name,password,address,userType,originPassword
     * 其中 ID & userType 不可更改
     * password 初始为空白
     * originPassword 初始为空白
     * QHBoxLayout 中放置两个按钮 modify & cancel
    */

    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("用户信息修改");

    QVBoxLayout * VBox = new QVBoxLayout;

    //输入栏
    QFormLayout * FormLayout = new QFormLayout;

    users.flushUser();

    //个人信息
    ID = new QLineEdit(users.getID());
    name = new QLineEdit(users.getName());
    password = new QLineEdit;   //密码空白
    address = new QLineEdit(users.getAddress());
    userType = new QLineEdit(users.getUserType());

    //ID & userType 不可修改
    ID->setReadOnly(1);
    userType->setReadOnly(1);

    //原密码
    originPassword = new QLineEdit;
    originPassword->setEchoMode(QLineEdit::Password);

    FormLayout->addRow("账号：",ID);
    FormLayout->addRow("昵称：",name);
    FormLayout->addRow("密码",password);
    FormLayout->addRow("地址：",address);
    FormLayout->addRow("用户类型：",userType);
    FormLayout->addRow("原密码",originPassword);

    //修改 & 取消
    QHBoxLayout * HBox = new QHBoxLayout;
    modify = new QPushButton("修改");
    cancel = new QPushButton("取消");

    HBox->addWidget(modify);
    HBox->addWidget(cancel);

    //添加到 VBox
    VBox->addLayout(FormLayout,3);
    VBox->addLayout(HBox,1);

    this->setLayout(VBox);

    //点击修改时，验证原密码
    QObject::connect(modify,&QPushButton::clicked,this,&ModifyUserMessBox::saveUserMess);
    //点击取消时，关闭登录窗口
    QObject::connect(cancel,&QPushButton::clicked,this,&ModifyUserMessBox::close);
}

/*
 * 当用户点击修改按钮时，验证是否填写完成，并验证密码
 * 当密码正确时，修改users，并写入 userFile & user_tempFile
 * 利用 user_superFile 作为中转写入 userFile
*/
void ModifyUserMessBox::saveUserMess()
{
    QString ID, name, password, address, userType;

    if(this->name->text() != "" && this->password->text() != "" && this->address->text() != "")
    {
        //已填写完整，验证密码是否正确
        if(this->originPassword->text() == users.getPassword())
        {
            //密码正确

            //修改 users 参数
            users.setName(this->name->text());
            users.setPassword(this->password->text());
            users.setAddress(this->address->text());

            //写入 user_tempFile
            QFile tempFile(user_tempFile);
            tempFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QDataStream tempStr(&tempFile);
            tempStr << users.getID() << users.getName() << users.getPassword() << users.getAddress() << users.getUserType();
            //关闭文件
            tempFile.close();

            //利用 user_superFile 作为中转，写入 userFile
            QFile file(userFile);
            file.open(QIODevice::ReadOnly);
            QDataStream readDataStr(&file);

            QFile superFile(user_superFile);
            superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QDataStream writeDataStr(&superFile);

            while (!readDataStr.atEnd())
            {
                readDataStr >> ID >> name >> password >> address >> userType;
                if(name != this->ID->text())
                {
                    //并非当前用户则直接写入 user_superFile
                    writeDataStr << ID << name << password << address << userType;
                }
                else
                {
                    //读取到当前用户则写入修改值
                    writeDataStr << users.getID() << users.getName() << users.getPassword() << users.getAddress() << users.getUserType();
                }

            }

            //关闭文件与窗口
            //删除 userFile 原文件，并将 user_superFile 改名为 userFile 来取替原文件
            file.close();
            superFile.close();
            file.remove();
            superFile.rename(userFile);

            this->close();

            //发送信号
            emitCloseBox();

        }
        else
        {
            //密码错误
            QMessageBox::critical(this,"提示","密码错误！",QMessageBox::Ok);
        }

    }
    else
    {
        //未填写完整
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }
}

//发送信号
void ModifyUserMessBox::emitCloseBox()
{
    emit closeBox();
}
