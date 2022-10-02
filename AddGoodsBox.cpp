#include "AddGoodsBox.h"


//构建注册界面
AddGoodsBox::AddGoodsBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout & QHBoxLayout
     * QFormLayout 中放置四个单行输入框
     * QHBoxLayout 中放置两个按钮
    */

    //图标
    setWindowIcon(QIcon(":logo,ico"));

    setWindowTitle("添加商品");
    QVBoxLayout * VBox = new QVBoxLayout;

    //name price quantity describe 输入框
    QFormLayout * FormLayout = new QFormLayout;

    name = new QLineEdit;
    price = new QLineEdit;
    quantity = new QLineEdit;
    describe = new QLineEdit;

    FormLayout->addRow("商品：",name);
    FormLayout->addRow("价格：",price);
    FormLayout->addRow("库存：",quantity);
    FormLayout->addRow("描述：",describe);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);



    //添加 & 取消
    QHBoxLayout * HBox = new QHBoxLayout;
    add = new QPushButton("添加");
    cancel = new QPushButton("取消");
    HBox->addWidget(add);
    HBox->addWidget(cancel);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);

    this->setLayout(VBox);

    users.flushUser();


    //点击注册按钮时，写入新用户信息
    connect(add,&QPushButton::clicked,this,&AddGoodsBox::saveGoodsMess);
    //点击取消按钮时，关闭注册窗口
    connect(cancel,&QPushButton::clicked,this,&AddGoodsBox::close);
}



//当用户点击添加按钮，写入新商品信息
void AddGoodsBox::saveGoodsMess()
{
    users.flushUser();

    int ID = 10000,price,quantity;
    QString name,describe,seller,status;

    bool IsExist = 0;   //判断商品是否存在


    //确保用户信息都已经输入，否则提醒用户填写完整
    if(this->name->text() != "" && this->price->text() != "" && this->quantity->text() != "" && this->describe->text() != "")
    {
        //信息填写完整

        //打开 goodsFile 文件
        QFile file(goodsFile);
        file.open(QIODevice::ReadOnly);
        QDataStream DataStr(&file);

        //判断该卖家是否存在该商品
        while(!DataStr.atEnd() && IsExist == 0)
        {
            //读入数据
            DataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

            //判断用户是否存在
            if(name == this->name->text() && seller == users.getName())
            {
               //用户已存在
                QMessageBox::warning(this,"提示","您已添加过该商品",QMessageBox::Ok);
                IsExist = 1;
            }

        }

        //关闭文件
        file.close();

        //重新打开 goodsFile 文件
        file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
        QDataStream WriteDataStr(&file);

        //当卖家未添加过该商品
        if(IsExist == 0)
        {
            ID+=1;

            //写入 goodss 对象

            //ID为最大ID+1
            goodss.setID(ID);

            goodss.setName(this->name->text());
            goodss.setPrice(this->price->text().toInt());
            goodss.setQuantity(this->quantity->text().toInt());
            goodss.setDescribe(this->describe->text());
            goodss.setSeller(users.getName());
            goodss.setStatus("上架");


            ID = goodss.getID();
            name = goodss.getName();
            price = goodss.getPrice();
            quantity = goodss.getQuantity();
            describe = goodss.getDescribe();
            seller = goodss.getSeller();
            status = goodss.getStatus();


            //将新注册的用户信息写入 goodsFile
            WriteDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;

            //将新用户信息写入 goodss_tempFile
            goodss.saveGoods();


            //注册成功提示
            QMessageBox::information(this,"提示","商品添加成功！",QMessageBox::Ok);

            //关闭文件&窗口&发送信息
            file.close();

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
void AddGoodsBox::emitCloseBox()
{
    emit closeBox();
}
