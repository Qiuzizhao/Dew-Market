#include "CommentGoodsBox.h"

//构建评论界面
CommentGoodsBox::CommentGoodsBox()
{
    /*
     * QVBoxLayout 局部工具放置 QListWidget & QGridLayout
     * QListWidget 显示所有连到该商品的评论
     * QGridLayout 内包含评论&关闭 两个按钮 和一个单行输入框
    */

    //图标
    setWindowIcon(QIcon(":/logo.ico"));

    setWindowTitle("评论");

    QVBoxLayout * VBox = new QVBoxLayout;

    // CommentList 评论列表
    CommentList = new QListWidget;

    // QGridLayout 两个按钮 一个输入框
    QGridLayout * Buts = new QGridLayout;

    comment = new QPushButton("评论");
    goOut = new QPushButton("退出");

    //输入框
    newComment = new QLineEdit;
    newComment->setPlaceholderText("输入编号或商品名查找...");
    newComment->setClearButtonEnabled(true);
    newComment->setStyleSheet("QLineEdit{padding:3,3,3,3;}");

    Buts->addWidget(comment,0,0);
    Buts->addWidget(goOut,0,1);
    Buts->addWidget(newComment,1,0,1,0);

    VBox->addWidget(CommentList,4);
    VBox->addLayout(Buts,2);

    this->setLayout(VBox);

    users.flushUser();

    goodss.flushGoods();

    flushCommentList();

    //点击评论按钮时，执行 AddComment
    connect(comment,&QPushButton::clicked,this,&CommentGoodsBox::AddComment);

    //点击退出按钮时，关闭评论窗口
    connect(goOut,&QPushButton::clicked,this,&CommentGoodsBox::close);

}

//当点击评论按钮后，添加评论
void CommentGoodsBox::AddComment()
{

    //判断用户是否已购买该商品
    if(users.IsBuy(goodss.getID()) == 1)
    {
        //已购买该商品

        //判断是否已输入评论
        if(newComment->text() != "")
        {
            QString commenter,commentMess;
            int goodsID = 10000;

            commenter = users.getName();
            commentMess = newComment->text();
            goodsID = goodss.getID();

            // comment_tempFile 用于存储新添加的评论
            QFile tempFile(comment_tempFile);
            tempFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QDataStream tempDataStr(&tempFile);

            tempDataStr<<commenter<<commentMess<<goodsID;

            tempFile.close();

            //更新 comments 对象的数据
            comments.flushComment();

            //将新添加的评论写入 commentFile
            QFile file(commentFile);
            file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
            QDataStream dataStr(&file);

            dataStr<<comments.getCommenter()<<comments.getCommentMess()<<comments.getGoodsID();

            file.close();

            //弹出评论成功的提醒
            QMessageBox::information(this,"提示","评论成功！",QMessageBox::Ok);

            //清空输入文本框
            newComment->clear();

            //更新评论列表
            flushCommentList();
        }
        else{
            //未输入评价
            QMessageBox::warning(this,"提示","请输入评论",QMessageBox::Ok);
        }


    }
    else{
        //未购买该商品则无法评论

        QMessageBox::warning(this,"提示","该商品未购买",QMessageBox::Ok);
    }





}

//评论后，更新评论列表
void CommentGoodsBox::flushCommentList()
{
    QString commenter,commentMess;
    int goodsID;


    //判断评论列表中是否有信息，有则只添加新评论，无则从头读取
    if(CommentList->count() > 0)
    {
        //列表中已有信息
        CommentList->addItem(comments.getCommenter() + "：" + comments.getCommentMess());
    }
    else{
        //列表中未有信息
        QFile file(commentFile);
        file.open(QIODevice::ReadOnly);
        QDataStream readDataStr(&file);

        while(!readDataStr.atEnd())
        {
            //读入数据
            readDataStr>>commenter>>commentMess>>goodsID;

            //判断是否属于当前商品
            if(goodsID == goodss.getID())
            {
                CommentList->addItem(commenter + "：" + commentMess);
            }
        }

        file.close();
    }
}
