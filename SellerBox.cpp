#include "SellerBox.h"

SellerBox::SellerBox()
{
    /*
     * 主界面利用 QVBoxLayout 放置两个 QVBoxLayout
     * 上层 QVBoxLayout Top_Table_Box
     * 下层 QVBoxLayout 分为三个区域 Left_Table_Box Mid_Table_Box Right_Table_Box
    */

    users.flushUser();

    //将 goods_tempFile 初始化，再将 goodss 初始化
    InitialGoodsTempFile();

    goodss.flushGoods();



    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("Dew Market");
    this->resize(1500,1000);

    QVBoxLayout *VBoxLayout = new QVBoxLayout(this);

    //四个区域
    QGroupBox *Top_Table_Box = createStatus();
    QGroupBox *Left_Table_Box = createUserMess();
    QGroupBox *Mid_Table_Box = createGoodsMess();
    QGroupBox *Right_Table_Box = createMenu();

    //下层
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);
    HBoxLayout->addWidget(Left_Table_Box,2);
    HBoxLayout->addWidget(Mid_Table_Box,4);
    HBoxLayout->addWidget(Right_Table_Box,2);

    //分为上下两层
    VBoxLayout->addWidget(Top_Table_Box,1);
    VBoxLayout->addLayout(HBoxLayout,8);





}


//初始化 goods_tempFile
void SellerBox::InitialGoodsTempFile()
{
    QFile file(goods_tempFile);

    file.remove();

}



/*************************
  状态面板 卖家&卖家&管理员
*************************/


QGroupBox *SellerBox::createStatus()
{
    QGroupBox *box = new QGroupBox("分区");
    QHBoxLayout *HBoxLayout = new QHBoxLayout;

    BuyerBtn = new QPushButton("买家");
    SellerBtn = new QPushButton("卖家");
    AdminBtn = new QPushButton("管理员");

    HBoxLayout->addWidget(BuyerBtn);
    HBoxLayout->addWidget(SellerBtn);
    HBoxLayout->addWidget(AdminBtn);

    box->setLayout(HBoxLayout);

    //点击买家按钮，执行 ChangeToBuyer()
    connect(BuyerBtn,&QPushButton::clicked,this,&SellerBox::ChangeToBuyer);
    //点击卖家按钮，执行 ChangeToSeller()
    connect(SellerBtn,&QPushButton::clicked,this,&SellerBox::ChangeToSeller);
    //点击管理员按钮，执行 ChangeToAdmin()
    connect(AdminBtn,&QPushButton::clicked,this,&SellerBox::ChangeToAdmin);

    return box;
}


//转换到买家界面
void SellerBox::ChangeToBuyer()
{
    //判断用户是否登录
    if(users.getID() != "")
    {
        //已登录
        this->hide();

        emit gotoSignals1();
    }
    else{
        //未登录
        QMessageBox::warning(this,"提示","请登录",QMessageBox::Ok);
    }


}

//转换到卖家界面
void SellerBox::ChangeToSeller()
{
    this->show();

    //更新用户信息列表
    flushUserMessList();

    //更新表格信息
    flushTable();
}

//转换到管理员界面
void SellerBox::ChangeToAdmin()
{

    //判断用户是否登录
    if(users.getID() != "")
    {
        //已登录

        //判断用户是否是管理员
        if(users.getUserType() == "管理员")
        {
            //是管理员

            this->hide();

            emit gotoSignals2();

        }
        else{
            //不是管理员

            QMessageBox::warning(this,"提示","您不是管理员",QMessageBox::Ok);
        }

    }
    else{
        //未登录

        QMessageBox::warning(this,"提示","请登录",QMessageBox::Ok);
    }
}


/*********************
    用户信息面板
*********************/

QGroupBox *SellerBox::createUserMess()
{
    /*
     * QVBoxLayout 分为三层
     * 顶层 QListWidget   用户信息
     * 中层 QHBoxLayout   登录&注册&修改
     * 中层分为两小层 登录&注册一层 修改一层
     * 底层 QPushButton   订单
    */

    //构建用户信息面板
    QGroupBox * box = new QGroupBox("用户信息");

    QVBoxLayout * VBoxLayout = new QVBoxLayout;

    //用户信息列表
    UserMessWidget = new QListWidget;

    //用户信息按钮
    QGridLayout * Buts = new QGridLayout;

    LoginBtn = new QPushButton("登录");
    ResgisterBtn = new QPushButton("注册");
    ModifyUserMessBtn = new QPushButton("修改用户信息");

    Buts->addWidget(LoginBtn,0,0);
    Buts->addWidget(ResgisterBtn,0,1);
    Buts->addWidget(ModifyUserMessBtn,1,0,1,0);

    //功能性按钮： 商品&订单
    QGridLayout * Buts2 = new QGridLayout;

    OrderBtn = new QPushButton("订单");

    Buts2->addWidget(OrderBtn,0,0);


    VBoxLayout->addWidget(UserMessWidget,4);
    VBoxLayout->addLayout(Buts,2);
    VBoxLayout->addWidget(OrderBtn,3);

    box->setLayout(VBoxLayout);

    //刷新用户信息列表
    flushUserMessList();

    //点击登录按钮，执行 UserLoginBox()
    connect(LoginBtn,&QPushButton::clicked,this,&SellerBox::LoginBtnBox);
    //点击注册按钮，执行 UserResgisterBox()
    connect(ResgisterBtn,&QPushButton::clicked,this,&SellerBox::ResgisterBtnBox);
    //点击修改按钮，执行 ModifyUserMessBox()
    connect(ModifyUserMessBtn,&QPushButton::clicked,this,&SellerBox::ModifyUserMessBtnBox);
    //点击订单按钮，执行 BuyerOrderBtnBox()
    connect(OrderBtn,&QPushButton::clicked,this,&SellerBox::OrderBox);

    return box;
}

//弹出登录窗口
void SellerBox::LoginBtnBox()
{
    //构建登录窗口
    LoginBox = new UserLoginBox;

    //当登录窗口关闭时，更新用户信息
    connect(LoginBox,&UserLoginBox::closeBox,this,&SellerBox::flushUserMessList);

    LoginBox->exec();

    flushTable();
}


//弹出注册窗口
void SellerBox::ResgisterBtnBox()
{
    //构建注册窗口
    ResgisterBox = new UserResgisterBox;

    //当注册窗口关闭时，更新用户信息
    connect(ResgisterBox,&UserResgisterBox::closeBox,this,&SellerBox::flushUserMessList);

    ResgisterBox->exec();
}


//弹出用户信息修改窗口
void SellerBox::ModifyUserMessBtnBox()
{

    //判断用户是否已登录
    if(users.getID() != ""){

        //构建用户信息修改窗口
        ModifyBox = new ModifyUserMessBox;

        //当用户信息修改窗口关闭时，更新用户信息
        connect(ModifyBox,&ModifyUserMessBox::closeBox,this,&SellerBox::flushUserMessList);

        ModifyBox->exec();

    }
    else{
        QMessageBox::warning(this,"提示","用户未登录",QMessageBox::Ok);
    }


}


//弹出订单窗口
void SellerBox::OrderBox()
{
    //判断用户是否已登录
    if(users.getID() != ""){

        //构建用户信息修改窗口
        SellerOrderBtnBox = new SellerOrderBox;


        SellerOrderBtnBox->exec();

    }
    else{
        QMessageBox::warning(this,"提示","用户未登录",QMessageBox::Ok);
    }

}

//更新列表中显示的用户信息
void SellerBox::flushUserMessList()
{
    users.flushUser();

    //直接使用users的数据

    //当列表中有信息，则直接修改，否则新建列表项
    if(UserMessWidget->count() > 0)
    {
        UserMessWidget->item(0)->setText("账号：" + users.getID());
        UserMessWidget->item(2)->setText("昵称：" + users.getName());
        UserMessWidget->item(4)->setText("地址：" + users.getAddress());
        UserMessWidget->item(6)->setText("用户类型：" + users.getUserType());
    }
    else{
        UserMessWidget->addItem("账号：" + users.getID());
        UserMessWidget->addItem("");
        UserMessWidget->addItem("昵称：" + users.getName());
        UserMessWidget->addItem("");
        UserMessWidget->addItem("地址：" + users.getAddress());
        UserMessWidget->addItem("");
        UserMessWidget->addItem("用户类型：" + users.getUserType());
    }
}





/*******************
    商品目录面板
*******************/

/* 构建商品目录面板
 * 面板是一个表格控件 TableWidget
 * 表格包含 编号&商品&价格&数量&卖家&状态 六项
 * 点击其中一行商品时，功能面板将展示商品详细信息
*/

QGroupBox * SellerBox::createGoodsMess()
{
    QGroupBox * box = new QGroupBox("商品目录");
    TableWidget = new QTableWidget;

    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableWidget->setColumnCount(6);
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"编号"<<"商品"<<"价格"<<"库存"<<"卖家"<<"状态");

    //表格信息不可修改
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //更新商品目录
    flushTable();

    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    //当用户点击某个商品时，更新功能面板中的商品信息列表
    connect(TableWidget,&QTableWidget::cellClicked,this,&SellerBox::flushListWidget);

    return box;
}

//更新商品表格
void SellerBox::flushTable()
{
    int ID,price,quantity;
    QString name,describe,seller,status;

    //打开 GoodsFile
    QFile file(goodsFile);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);

    TableWidget->setRowCount(0);

    while(!dataStr.atEnd())
    {
        //读入数据
        dataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

        //判断卖家是否一致
        if(seller == users.getName())
        {
            TableWidget->setRowCount(TableWidget->rowCount()+1);
            TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(ID)));
            TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(name));
            TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(price)));
            TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(quantity)));
            TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(seller));
            TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(status));

        }
    }

    file.close();

}





/********************
    功能面板
********************/

/* 构建功能面板
 * 最外层有 QGroupBox 分组框，内部用 QVBoxLayout 将整个区域分为上下两部分
 * 分别嵌入 QListWidget & QGridLayout
 * QListWidget 用于显示商品信息
 * 商品信息包括 编号&商品名&价格&数量&详细介绍&卖家&状态
 * QGridLayout 内包含 上架&下架&评论&修改&添加 5个按钮 和1个实现搜索功能的单行输入框
*/

QGroupBox * SellerBox::createMenu()
{
    QGroupBox * box = new QGroupBox("详细信息");

    QVBoxLayout * VBoxLayout = new QVBoxLayout;

    // GoodsListWidget 信息列表
    GoodsListWidget = new QListWidget;

    // QGridLayout 五个按钮 一个输入框
    QGridLayout * Buts = new QGridLayout;


    //五个按钮
    UpGoodsBtn = new QPushButton("上架");
    DownGoodsBtn = new QPushButton("下架");
    CommentBtn = new QPushButton("评论");
    ModifyGoodsMessBtn = new QPushButton("修改");
    DeleteGoodsBtn = new QPushButton("删除");
    AddGoodsBtn = new QPushButton("添加");

    //搜索框
    FindGoodsBtn = new QLineEdit;
    FindGoodsBtn->setPlaceholderText("输入编号或商品名查找...");
    FindGoodsBtn->setClearButtonEnabled(true);
    FindGoodsBtn->setStyleSheet("QLineEdit{padding:3,3,3,3;}");


    Buts->addWidget(UpGoodsBtn,0,0);
    Buts->addWidget(DownGoodsBtn,0,1);

    Buts->addWidget(CommentBtn,1,0);
    Buts->addWidget(ModifyGoodsMessBtn,1,1);

    Buts->addWidget(FindGoodsBtn,2,0,2,0);

    Buts->addWidget(DeleteGoodsBtn,3,0);
    Buts->addWidget(AddGoodsBtn,3,1);



    VBoxLayout->addWidget(GoodsListWidget,4);
    VBoxLayout->addLayout(Buts,2);

    box->setLayout(VBoxLayout);


    //点击上架按钮，执行 UpGoods()
    connect(UpGoodsBtn,&QPushButton::clicked,this,&SellerBox::UpGoods);
    //点击下架按钮，执行 DownGoods()
    connect(DownGoodsBtn,&QPushButton::clicked,this,&SellerBox::DownGoods);
    //点击评论按钮，执行 CommentGoods()
    connect(CommentBtn,&QPushButton::clicked,this,&SellerBox::CommentBtnBox);
    //点击修改按钮，执行 ModifyGoodsMessBtnBox()
    connect(ModifyGoodsMessBtn,&QPushButton::clicked,this,&SellerBox::ModifyGoodsMessBtnBox);
    //当向输入框内输入信息后，执行 FindGoods()
    connect(FindGoodsBtn,&QLineEdit::returnPressed,this,&SellerBox::FindGoods);
    //点击删除按钮，执行 DeleteGoods()
    connect(DeleteGoodsBtn,&QPushButton::clicked,this,&SellerBox::DeleteGoods);
    //点击添加按钮，执行 AddGoodsBtnBox()
    connect(AddGoodsBtn,&QPushButton::clicked,this,&SellerBox::AddGoodsBtnBox);


    return box;
}

//商品上架
void SellerBox::UpGoods()
{
    //更新 goodss 对象
    goodss.flushGoods();

    //判断当前是否已经选择商品
    if(goodss.getName() != "")
    {
        //已选择商品
        int ID = 0,price = 0,quantity = 0;
        QString name,describe,seller,status;


        //修改 goodss 对象的 status
        goodss.setStatus("上架");
        //将修改写入 goods_tempFile
        goodss.saveGoods();

        //打开 goodsFile & goods_superFile

        QFile file(goodsFile);
        file.open(QIODevice::ReadOnly);
        QDataStream readDataStr(&file);

        QFile superFile(goods_superFile);
        superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QDataStream writeDataStr(&superFile);

        while(!readDataStr.atEnd())
        {
            //读入数据
            readDataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

            //找到当前商品
            if(ID == goodss.getID())
            {
                writeDataStr<<goodss.getID()<<goodss.getName()<<goodss.getPrice()<<goodss.getQuantity()<<goodss.getDescribe()<<goodss.getSeller()<<goodss.getStatus();

            }
            else{
                //直接写入到 goods_superFile
                writeDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;
            }
        }

        //关闭文件
        file.close();
        superFile.close();

        //删除 goodsFile 并将 goods_superFile 重命名为 goodsFile
        file.remove();
        superFile.rename(goodsFile);


        //更新商品目录和详细信息
        flushTable();
        quickFlushList();

        //弹出提醒上架成功
        QMessageBox::information(this,"提示","上架成功！",QMessageBox::Ok);

    }
    else{
        //未选择商品
        QMessageBox::warning(this,"提示","请选择商品",QMessageBox::Ok);
    }


}

//商品下架
void SellerBox::DownGoods()
{
    //判断当前是否已经选择商品
    if(goodss.getName() != "")
    {
        //已选择商品
        int ID = 0,price = 0,quantity = 0;
        QString name,describe,seller,status;


        //修改 goodss 对象的 status
        goodss.setStatus("已下架");
        //将修改写入 goods_tempFile
        goodss.saveGoods();

        //打开 goodsFile & goods_superFile

        QFile file(goodsFile);
        file.open(QIODevice::ReadOnly);
        QDataStream readDataStr(&file);

        QFile superFile(goods_superFile);
        superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QDataStream writeDataStr(&superFile);

        while(!readDataStr.atEnd())
        {
            //读入数据
            readDataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

            //找到当前商品
            if(ID == goodss.getID())
            {
                writeDataStr<<goodss.getID()<<goodss.getName()<<goodss.getPrice()<<goodss.getQuantity()<<goodss.getDescribe()<<goodss.getSeller()<<goodss.getStatus();

            }
            else{
                //直接写入到 goods_superFile
                writeDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;
            }
        }

        //关闭文件
        file.close();
        superFile.close();

        //删除 goodsFile 并将 goods_superFile 重命名为 goodsFile
        file.remove();
        superFile.rename(goodsFile);


        //更新商品目录和详细信息
        flushTable();
        quickFlushList();

        //弹出提醒下架成功
        QMessageBox::information(this,"提示","下架成功！",QMessageBox::Ok);


    }
    else{
        //未选择商品
        QMessageBox::warning(this,"提示","请选择商品",QMessageBox::Ok);
    }
}



//更新功能面板中的详细信息
void SellerBox::flushListWidget(int row)
{
    //记录当前选中的行数
    Row = row;

    int ID = 0,price = 0,quantity = 0;
    QString name,describe,seller,status;

    QFile file(goodsFile);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    while(!readDataStr.atEnd())
    {
        //读入数据
        readDataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

        //找到当前商品,则终止循环
        if(QString::number(ID) == TableWidget->item(row,0)->text())
        {
            break;
        }
    }

    //当列表有信息时，直接修改即可
    if(GoodsListWidget->count() > 0)
    {
        //列表中已有信息
        GoodsListWidget->item(0)->setText("编号：" + QString::number(ID));
        GoodsListWidget->item(1)->setText("商品：" + name);
        GoodsListWidget->item(2)->setText("价格：" + QString::number(price));
        GoodsListWidget->item(3)->setText("库存：" + QString::number(quantity));
        GoodsListWidget->item(4)->setText("卖家：" + seller);
        GoodsListWidget->item(5)->setText("介绍：" + describe);
        GoodsListWidget->item(6)->setText("状态：" + status);
    }
    else{
        //列表中未有信息
        GoodsListWidget->addItem("编号：" + QString::number(ID));
        GoodsListWidget->addItem("商品：" + name);
        GoodsListWidget->addItem("价格：" + QString::number(price));
        GoodsListWidget->addItem("库存：" + QString::number(quantity));
        GoodsListWidget->addItem("卖家：" + seller);
        GoodsListWidget->addItem("介绍：" + describe);
        GoodsListWidget->addItem("状态：" + status);
    }

    //关闭文件
    file.close();

    //将选中商品数据写入到 goods_tempFile
    QFile tempFile(goods_tempFile);
    tempFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream tempDataStr(&tempFile);

    tempDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;

    tempFile.close();

    //更新goodss对象

    goodss.flushGoods();
}

//商品评论窗口
void SellerBox::CommentBtnBox()
{

    //判断用户是否已登录
    if(users.getID() != "")
    {
        //构建评论窗口
        CommentBox = new CommentGoodsBox;

        CommentBox->exec();
    }
    else{

        QMessageBox::warning(this,"提示","用户未登录",QMessageBox::Ok);
    }

}


//查找商品
void SellerBox::FindGoods()
{
    // 判断搜索框是否已输入

    if(FindGoodsBtn->text() != "")
    {
        int count = TableWidget->rowCount();

        //布尔值记录是否找到该商品
        bool findSuccess = false;

        if(count>0)
        {
            for(int i=0;i<count;i++)
            {
                QString ID = TableWidget->item(i,0)->text();
                QString name = TableWidget->item(i,1)->text();

                if(ID == FindGoodsBtn->text() || name == FindGoodsBtn->text())
                {
                    //布尔值设为 true
                    findSuccess = true;
                    //表格中选中该行
                    TableWidget->selectRow(i);
                    //更新商品详细信息
                    flushListWidget(i);
                    //结束循环
                    break;
                }
            }


            //没有找到，则弹窗提示
            if(findSuccess == false)
            {
                QMessageBox::information(this,"查找失败","没有找到【"+FindGoodsBtn->text()+"】商品");
            }
        }
    }
    else{
        QMessageBox::warning(this,"提示","请输入查找内容",QMessageBox::Ok);
    }


}


//弹出商品信息修改窗口
void SellerBox::ModifyGoodsMessBtnBox()
{


    //判断当前是否已经选择商品
    if(goodss.getName() != "")
    {
        //已选择商品

        //构建商品信息修改窗口
        ModifyGoodsBox = new ModifyGoodsMessBox;

        //当商品信息修改窗口关闭时，更新商品信息
        connect(ModifyGoodsBox,&ModifyGoodsMessBox::closeBox,this,&SellerBox::flushTable);


        ModifyGoodsBox->exec();

        quickFlushList();

    }
    else{
        //未选择商品
        QMessageBox::warning(this,"提示","请选择商品",QMessageBox::Ok);
    }
}


//弹出添加商品窗口
void SellerBox::AddGoodsBtnBox()
{
    //判断用户是否登录
    if(users.getID() != "")
    {
        //已登录

        //构建商品添加窗口
        AddGoodsMessBox = new AddGoodsBox;

        //当商品添加窗口关闭，更新商品目录
        connect(AddGoodsMessBox,&AddGoodsBox::closeBox,this,&SellerBox::flushTable);

        AddGoodsMessBox->exec();

    }
    else{
        //未登录

        QMessageBox::warning(this,"提示","用户未登录",QMessageBox::Ok);

    }

}


void SellerBox::DeleteGoods()
{
    //判断用户是否登录
    if(users.getID() != "")
    {
        //已登录

        //判断是否选择商品
        goodss.flushGoods();

        if(goodss.getName() != "")
        {
            //已选择商品

            int ID = 0,price = 0,quantity = 0;
            QString name,describe,seller,status;

            //将删除的商品存到 goods_deleteFile
            QFile deleteFile(goods_deleteFile);
            deleteFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
            QDataStream deleteDataStr(&deleteFile);

            deleteDataStr<<goodss.getID()<<goodss.getName()<<goodss.getPrice()<<goodss.getQuantity()<<goodss.getDescribe()<<goodss.getSeller()<<goodss.getStatus();


            deleteFile.close();



            //清空 goods_tempFile & goodss
            InitialGoodsTempFile();
            goodss.flushGoods();

            //清空 GoodsListWidget
            GoodsListWidget->clear();

            //打开 goodsFile & goods_superFile

            QFile file(goodsFile);
            file.open(QIODevice::ReadOnly);
            QDataStream readDataStr(&file);

            QFile superFile(goods_superFile);
            superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QDataStream writeDataStr(&superFile);

            while(!readDataStr.atEnd())
            {
                //读入数据
                readDataStr>>ID>>name>>price>>quantity>>describe>>seller>>status;

                //找到当前商品
                if(ID == goodss.getID())
                {
                    //不写入任何信息

                }
                else{
                    //直接写入到 goods_superFile
                    writeDataStr<<ID<<name<<price<<quantity<<describe<<seller<<status;
                }
            }

            //关闭文件
            file.close();
            superFile.close();

            //删除 goodsFile 并将 goods_superFile 重命名为 goodsFile
            file.remove();
            superFile.rename(goodsFile);


            //更新商品目录
            flushTable();

            //弹出提醒删除成功
            QMessageBox::information(this,"提示","删除成功！",QMessageBox::Ok);

        }
        else{
            //未选择商品
            QMessageBox::warning(this,"提示","请选择商品",QMessageBox::Ok);
        }

    }
    else{
        //未登录
        QMessageBox::warning(this,"提示","用户未登录",QMessageBox::Ok);
    }

}


//快速更新列表中显示的商品信息，即不用通过Table中选择商品，直接更新为goodss的信息
void SellerBox::quickFlushList()
{
    //更新 goodss 对象
    goodss.flushGoods();

    //当列表有信息时，直接修改即可
    if(GoodsListWidget->count() > 0)
    {
        //列表中已有信息
        GoodsListWidget->item(0)->setText("编号：" + QString::number(goodss.getID()));
        GoodsListWidget->item(1)->setText("商品：" + goodss.getName());
        GoodsListWidget->item(2)->setText("价格：" + QString::number(goodss.getPrice()));
        GoodsListWidget->item(3)->setText("库存：" + QString::number(goodss.getQuantity()));
        GoodsListWidget->item(4)->setText("卖家：" + goodss.getSeller());
        GoodsListWidget->item(5)->setText("介绍：" + goodss.getDescribe());
        GoodsListWidget->item(6)->setText("状态：" + goodss.getStatus());
    }
    else{
        //列表中未有信息
        GoodsListWidget->addItem("编号：" + QString::number(goodss.getID()));
        GoodsListWidget->addItem("商品：" + goodss.getName());
        GoodsListWidget->addItem("价格：" + QString::number(goodss.getPrice()));
        GoodsListWidget->addItem("库存：" + QString::number(goodss.getQuantity()));
        GoodsListWidget->addItem("卖家：" + goodss.getSeller());
        GoodsListWidget->addItem("介绍：" + goodss.getDescribe());
        GoodsListWidget->addItem("状态：" + goodss.getStatus());
    }

}
