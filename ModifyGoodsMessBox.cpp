#include "ModifyGoodsMessBox.h"


//构建用户信息修改窗口
ModifyGoodsMessBox::ModifyGoodsMessBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout & QHBoxLayout
     * QFormLayout 中放置5个输入框，分别为 ID,name,price,quantity,describe
     * 其中 ID 不可更改
     * QHBoxLayout 中放置两个按钮 modify & cancel
    */

    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("商品信息修改");

    QVBoxLayout * VBox = new QVBoxLayout;

    //输入栏
    QFormLayout * FormLayout = new QFormLayout;

    //更新 goodss 对象的数据
    goodss.flushGoods();

    //个人信息
    ID = new QLineEdit(QString::number(goodss.getID()));
    name = new QLineEdit(goodss.getName());
    price = new QLineEdit(QString::number(goodss.getPrice()));
    quantity = new QLineEdit(QString::number(goodss.getQuantity()));
    describe = new QLineEdit(goodss.getDescribe());

    //ID 不可修改
    ID->setReadOnly(1);


    FormLayout->addRow("编号：",ID);
    FormLayout->addRow("商品：",name);
    FormLayout->addRow("价格：",price);
    FormLayout->addRow("库存：",quantity);
    FormLayout->addRow("描述：",describe);



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


    //点击修改时，存储商品信息
    QObject::connect(modify,&QPushButton::clicked,this,&ModifyGoodsMessBox::saveGoodsMess);
    //点击取消时，关闭登录窗口
    QObject::connect(cancel,&QPushButton::clicked,this,&ModifyGoodsMessBox::close);
}



/*
 * 当用户点击修改按钮时
 * 修改 gooodss，并写入 goodsFile & goods_tempFile
 * 利用 goods_superFile 作为中转写入 goodsFile
*/

void ModifyGoodsMessBox::saveGoodsMess()
{
    int ID = 10000,price,quantity;
    QString name,describe,seller,status;



    if(this->name->text() != "" && this->price->text() != "" && this->quantity->text() != "" && this->describe->text() != "")
    {
        //已填写完整


            //修改 goodss 参数
            goodss.setName(this->name->text());
            goodss.setPrice(this->price->text().toInt());
            goodss.setQuantity(this->quantity->text().toInt());
            goodss.setDescribe(this->describe->text());

            //写入 goods_tempFile
            goodss.saveGoods();


            //利用 goods_superFile 作为中转，写入 goodsFile
            QFile file(goodsFile);
            file.open(QIODevice::ReadOnly);
            QDataStream readDataStr(&file);

            QFile superFile(goods_superFile);
            superFile.open(QIODevice::WriteOnly);
            QDataStream writeDataStr(&superFile);

            while (!readDataStr.atEnd())
            {
                readDataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;
                if(ID != goodss.getID())
                {
                    //并非当前用户则直接写入 goods_superFile
                    writeDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;
                }
                else
                {
                    //读取到当前用户则写入修改值
                    writeDataStr<<goodss.getID()<<goodss.getName()<<goodss.getPrice()<<goodss.getQuantity()<<goodss.getDescribe()<<goodss.getSeller()<<goodss.getStatus();


                }

            }

            //关闭文件与窗口
            //删除 goodsFile 原文件，并将 goods_superFile 改名为 goodsFile 来取替原文件
            file.close();
            superFile.close();

            file.remove();
            superFile.rename(goodsFile);

            //发送关闭信号

            emitCloseBox();

            //关闭窗口
            this->close();
    }
    else{
        //未填写完整
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }

}


//发送信号
void ModifyGoodsMessBox::emitCloseBox()
{
    emit closeBox();
}
