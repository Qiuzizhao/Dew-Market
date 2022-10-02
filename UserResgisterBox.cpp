#include <UserResgisterBox.h>

//构建注册界面
UserResgisterBox::UserResgisterBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout & QHBoxLayout & QHBoxLayout
     * QFormLayout 中放置四个单行输入框
     * QHBoxLayout 中放置两个复选框
     * QHBoxLayout 中放置两个按钮
    */

    //图标
    setWindowIcon(QIcon(":logo,ico"));

    setWindowTitle("注册");
    QVBoxLayout * VBox = new QVBoxLayout;

    //ID name password address 输入框
    QFormLayout * FormLayout = new QFormLayout;
    ID = new QLineEdit;
    name = new QLineEdit;
    password = new QLineEdit;
    address = new QLineEdit;

    FormLayout->addRow("账号：",ID);
    FormLayout->addRow("昵称：",name);
    FormLayout->addRow("密码：",password);
    FormLayout->addRow("地址：",address);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    //密码隐藏
    password->setEchoMode(QLineEdit::Password);

    //用户 & 管理员
    QHBoxLayout * HBox1 = new QHBoxLayout;
    userCheck = new QCheckBox;
    adminCheck = new QCheckBox;

    userCheck->setText("用户");
    adminCheck->setText("管理员");

    HBox1->addWidget(userCheck);
    HBox1->addWidget(adminCheck);

    //选择了用户
    connect(userCheck,&QCheckBox::clicked,this,&UserResgisterBox::IsUser);
    //选择了管理员
    connect(adminCheck,&QCheckBox::clicked,this,&UserResgisterBox::IsAdmin);

    //注册 & 取消
    QHBoxLayout * HBox2 = new QHBoxLayout;
    resgister = new QPushButton("注册");
    cancel = new QPushButton("取消");
    HBox2->addWidget(resgister);
    HBox2->addWidget(cancel);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox1,1);
    VBox->addLayout(HBox2,1);

    this->setLayout(VBox);

    //点击注册按钮时，写入新用户信息
    connect(resgister,&QPushButton::clicked,this,&UserResgisterBox::saveUserMess);
    //点击取消按钮时，关闭注册窗口
    connect(cancel,&QPushButton::clicked,this,&UserResgisterBox::close);
}

//选择了用户类型
void UserResgisterBox::IsUser()
{
    //设置管理员复选框状态为未选中
    adminCheck->setCheckState(Qt::Unchecked);
}

//选择了管理员类型
void UserResgisterBox::IsAdmin()
{
    //设置用户复选框为未选中
    userCheck->setCheckState(Qt::Unchecked);
}

//当用户点击注册按钮，写入新用户信息
void UserResgisterBox::saveUserMess()
{
    QString ID,name,password,address,userType;

    bool IsExist = 0;   //判断用户是否存在
    bool IsNameExist = 0;   //判断昵称是否已被使用

    //确保用户信息都已经输入，否则提醒用户填写完整
    if(this->ID->text() != "" && this->name->text() != "" && this->password->text() != "" && this->address->text() != "" && (this->userCheck->checkState() == Qt::Checked || this->adminCheck->checkState() == Qt::Checked))
    {
        //信息填写完整

        //打开 userfile 文件
        QFile file(userFile);
        file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
        QDataStream DataStr(&file);

        //判断用户ID和昵称是否存在
        while(!DataStr.atEnd() && IsExist == 0)
        {
            //读入数据
            DataStr >> ID >> name >> password >> address >> userType;

            //判断用户是否存在
            if(ID == this->ID->text())
            {
               //用户已存在
                QMessageBox::warning(this,"提示","该用户已存在",QMessageBox::Ok);
                IsExist = 1;
            }

            //判断昵称是否已被使用
            if(name == this->name->text())
            {
                //昵称已被使用
                QMessageBox::warning(this,"提示","该昵称已被使用",QMessageBox::Ok);
                IsNameExist = 1;
            }
        }



        //当用户不存在
        if(IsExist == 0 && IsNameExist == 0)
        {
            //写入 users 对象
            users.setID(this->ID->text());
            users.setName(this->name->text());
            users.setPassword(this->password->text());
            users.setAddress(this->address->text());
            //用户类型
            if(this->userCheck->checkState() == Qt::Checked)
            {
                users.setUserType(this->userCheck->text());
            }
            else{
                users.setUserType(this->adminCheck->text());
            }

            ID = users.getID();
            name = users.getName();
            password = users.getPassword();
            address = users.getAddress();
            userType = users.getUserType();

            //将新注册的用户信息写入 userFile
            DataStr << ID << name << password << address << userType;

            //将新用户信息写入 user_tempFile
            QFile tempFile(user_tempFile);
            tempFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QDataStream tempDataStr(&tempFile);

            tempDataStr << ID << name << password << address << userType;

            //注册成功提示
            QMessageBox::information(this,"提示","注册成功！",QMessageBox::Ok);

            //关闭文件&窗口&发送信息
            file.close();
            tempFile.close();
            this->close();
            emitCloseBox();

        }
    }
    else{
        //信息未填写完整
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }
}

//发送信号
void UserResgisterBox::emitCloseBox()
{
    emit closeBox();
}
