//商品评论窗口
#ifndef COMMENTGOODSBOX_H
#define COMMENTGOODSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QListWidget>

#include "User.h"
#include "Goods.h"
#include "Comment.h"
#include "Tool.h"

class CommentGoodsBox : public QDialog
{
//    Q_OBJECT
public:
    //构建评论界面
    CommentGoodsBox();

public slots:
    //当添加评论后，更新列表
    void flushCommentList();

    //添加评论
    void AddComment();

private:
    QListWidget * CommentList;
    QPushButton * comment;
    //退出
    QPushButton * goOut;
    QLineEdit * newComment;

    User users;

    //goodss存储当前选中的尚萍
    Goods goodss;

    //comments 用于存储新添加的订单
    Comment comments;

};

#endif // COMMENTGOODSBOX_H
