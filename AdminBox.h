//管理员窗口

#ifndef ADMINBOX_H
#define ADMINBOX_H


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
#include "Comment.h"
#include "Order.h"
#include "UserLoginBox.h"   //登录窗口
#include "UserResgisterBox.h"   //注册窗口
#include "ModifyUserMessBox.h"  //用户信息修改窗口

#include "CommentGoodsBox.h"    //商品评论窗口
#include "ModifyGoodsMessBox.h" //商品信息修改窗口

#include "AdminUserBox.h"   //管理员用户窗口
#include "AdminOrderBox.h"    //管理员订单窗口


#include "Tool.h"


/*
 * 管理员功能：
 * 查看所有商品，进行上下架，搜索商品，修改,查看所有评论
 * 查看所有订单，搜索订单，可取消
 * 查看所有用户，搜索用户，可删除
*/


class AdminBox : public QDialog
{
    Q_OBJECT

signals:

    //通往买家窗口的信号
    void gotoSignals1();

    //通往卖家窗口的信号
    void gotoSignals2();


public:
    //构建卖家窗口
    AdminBox();

    //当用户点击登录按钮时，弹出登录窗口
    void LoginBtnBox();

    //当用户点击注册按钮，弹出注册窗口
    void ResgisterBtnBox();

    //当用户点击修改用户信息按钮，弹出修改用户信息窗口
    void ModifyUserMessBtnBox();


    //当点击订单按钮，弹出管理员订单窗口
    void OrderBox();

    //当点击用户按钮，弹出管理员用户窗口
    void UserBox();


    //当用户点击评论按钮，弹出评论窗口
    void CommentBtnBox();

    //查找商品
    void FindGoods();

    //下架商品
    void DownGoods();

    //上架商品
    void UpGoods();

    //删除商品
    void DeleteGoods();

    //修改商品信息窗口
    void ModifyGoodsMessBtnBox();


    //初始化 goods_tempFile
    void InitialGoodsTempFile();






public slots:

    //更新表格中罗列的商品信息
    void flushTable();

    //更新列表中显示的商品信息
    void flushListWidget(int row);

    //更新列表中显示的用户信息
    void flushUserMessList();

    //快速更新列表中显示的商品信息，即不用通过Table中选择商品，直接更新为goodss的信息
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

    //主窗口的上架、下架、评论、搜索、修改、删除控件
    QPushButton * UpGoodsBtn;
    QPushButton * DownGoodsBtn;
    QPushButton * CommentBtn;
    QLineEdit * FindGoodsBtn;
    QPushButton * ModifyGoodsMessBtn;
    QPushButton * DeleteGoodsBtn;


    //弹出评论窗口
    CommentGoodsBox * CommentBox;

    //记录当前选中的行数
    int Row = 0;


    //主窗口的登录控件
    QPushButton * LoginBtn;

    //弹出登录窗口
    UserLoginBox * LoginBox;

    //主窗口的注册控件
    QPushButton * ResgisterBtn;

    //弹出注册窗口
    UserResgisterBox * ResgisterBox;

    //主窗口的修改用户信息控件
    QPushButton * ModifyUserMessBtn;

    //弹出修改用户信息的窗口
    ModifyUserMessBox * ModifyBox;

    //主窗口用户信息列表控件
    QListWidget * UserMessWidget;


    //主窗口的订单控件
    QPushButton * OrderBtn;

    //弹出订单窗口
    AdminOrderBox * AdminOrderBtnBox;

    //主窗口的用户控件
    QPushButton * UserBtn;

    //弹出用户窗口
    AdminUserBox * AdminUserBtnBox;


    //弹出修改商品信息的窗口
    ModifyGoodsMessBox * ModifyGoodsBox;





    //更换买家、卖家、管理员状态控件
    QPushButton * BuyerBtn;
    QPushButton * SellerBtn;
    QPushButton * AdminBtn;

    User users;

    Goods goodss;

    Order orders;


};

#endif // ADMINBOX_H
