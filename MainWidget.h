//主界面
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QDataStream>

#include "User.h"
#include "Goods.h"
#include "Order.h"
#include "UserLoginBox.h"   //登录窗口
#include "UserResgisterBox.h"   //注册窗口
#include "ModifyUserMessBox.h"  //用户信息修改窗口
#include "CommentGoodsBox.h"    //商品评论窗口
#include "BuyerOrderBox.h"    //买家订单窗口



#include "Tool.h"



class MainWidget : public QWidget
{
    Q_OBJECT

signals:

    //通往卖家窗口的信号
    void gotoSignals1();

    //通往买家窗口的信号
    void gotoSignals2();

public:
    //构建主窗口界面
    MainWidget();

    //当用户点击登录按钮时，弹出登录窗口
    void LoginBtnBox();

    //当用户点击注册按钮，弹出注册窗口
    void ResgisterBtnBox();

    //当用户点击修改用户信息按钮，弹出修改用户信息窗口
    void ModifyUserMessBtnBox();

    //当用户点击订单按钮，弹出买家订单窗口
    void OrderBox();

    //初始化 user_tempFile
    void InitialTempFile();

    //初始化 goods_tempoFile
    void InitialGoodsTempFile();

    //当用户点击评论按钮，弹出评论窗口
    void CommentBtnBox();

    //购买商品
    void BuyGoods();
    //查找商品
    void FindGoods();


public slots:
    //更新表格中罗列的商品信息
    void flushTable();

    //更新列表中显示的商品信息
    void flushListWidget(int row);

    //更新列表中显示的用户信息
    void flushUserMessList();


    //快速更新列表中显示的商品信息，即不用通过Table中选择商品，直接`更新为goodss的信息
    void quickFlushList();


    //调整为卖家窗口
    void ChangeToSeller();

    //调整为管理员窗口
    void ChangeToAdmin();

    //调整为买家窗口
    void ChangeToBuyer();


private:
    //创建主窗口的状态面板
    QGroupBox * createStatus();

    //创建主窗口的用户面板
    QGroupBox * createUserMess();

    //创建主窗口的商品信息面板
    QGroupBox * createGoodsMess();

    //创建主窗口的功能面板
    QGroupBox * createMenu();

private:
    //主窗口的表格控件
    QTableWidget * TableWidget;

    //主窗口的商品列表控件
    QListWidget * GoodsListWidget;

    //主窗口的购买、搜索、评论控件
    QPushButton * BuyGoodsBtn;
    QLineEdit * FindGoodsBtn;
    QPushButton * CommentBtn;

    //主窗口的订单控件
    QPushButton * OrderBtn;

    //主窗口的登录控件
    QPushButton * LoginBtn;

    //弹出登录窗口
    UserLoginBox * LoginBox;

    //主窗口的注册控件
    QPushButton * ResgisterBtn;

    //弹出注册窗口
    UserResgisterBox * ResgisterBox;

    //主窗口的修改控件
    QPushButton * ModifyUserMessBtn;

    //弹出修改用户信息的窗口
    ModifyUserMessBox * ModifyBox;

    //主窗口用户信息列表控件
    QListWidget * UserMessWidget;

    //更换买家、卖家、管理员状态控件
    QPushButton * BuyerBtn;
    QPushButton * SellerBtn;
    QPushButton * AdminBtn;

    //弹出评论窗口
    CommentGoodsBox * CommentBox;

    //弹出订单窗口
    BuyerOrderBox * BuyerOrderBtnBox;


    User users;

    Goods goodss;

    Order orders;
};

#endif // MAINWIDGET_H
