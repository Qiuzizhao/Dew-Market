#include "UserLoginBox.h"

//构建登录界面
UserLoginBox::UserLoginBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout & QHBoxLayout
     * QFormLayout 中放置两个单行输入框
     * QHBoxLayout 中放置两个按钮
    */

    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("登录");
    QVBoxLayout * VBox = new QVBoxLayout;

    //账号密码输入栏
    QFormLayout * FormLayout = new QFormLayout;
    ID = new QLineEdit;
    password = new QLineEdit;
    FormLayout->addRow("账号：",ID);
    FormLayout->addRow("密码：",password);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    password->setEchoMode(QLineEdit::Password);

    //登录&取消
    QHBoxLayout * HBox = new QHBoxLayout;
    login = new QPushButton("登录");
    cancel = new QPushButton("取消");
    face = new QPushButton("人脸识别");
    HBox->addWidget(login);
    HBox->addWidget(cancel);
    HBox->addWidget(face);

    VBox->addLayout(FormLayout,2);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);

    //点击登录按钮时，进行验证
    QObject::connect(login,&QPushButton::clicked,this,&UserLoginBox::vertify);
    //点击取消按钮时，关闭登录窗口
    QObject::connect(cancel,&QPushButton::clicked,this,&UserLoginBox::close);
}

//当用户点击登录按钮时，验证账号密码
void UserLoginBox::vertify()
{
    QString ID,name,password,address,userType;

    //确保账号密码都已输入，否则提示用户填写完整
    if(this->ID->text() != "" && this->password->text() != "")
    {
        QFile file(userFile);
        file.open(QIODevice::ReadOnly);
        QDataStream readDataStr(&file);
        while(!readDataStr.atEnd()){
            //读入数据
            readDataStr >> ID >> name >> password >> address >> userType;

            //用户存在
            if(ID == this->ID->text()){
                if(password == this->password->text()){
                    //当密码正确

                    //users对象
                    users.setID(ID);
                    users.setName(name);
                    users.setPassword(password);
                    users.setAddress(address);
                    users.setUserType(userType);

                    //写入临时文件
                    QFile tempFile(user_tempFile);
                    tempFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
                    QDataStream writeStr(&tempFile);
                    writeStr << ID << name << password << address << userType;

                    //登录成功提醒
                    QMessageBox::information(this,"提示","登录成功！",QMessageBox::Ok);

                    //关闭文件&窗口&发送信号
                    file.close();
                    tempFile.close();
                    this->close();
                    emitCloseBox();
                }
                else{
                    //密码错误
                    QMessageBox::critical(this,"提示","密码错误！",QMessageBox::Ok);
                    this->password->clear();
                }
            }
        }
    }else{
        QMessageBox::warning(this,"提示","请输入账号密码",QMessageBox::Ok);
    }
}

//发送信号
void UserLoginBox::emitCloseBox()
{
    emit closeBox();
}
