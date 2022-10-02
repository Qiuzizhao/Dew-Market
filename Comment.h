//商品评论

#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QFile>
#include <Tool.h>

class Comment
{
public:
    QString getCommenter() const;
    void setCommenter(const QString &value);

    QString getCommentMess() const;
    void setCommentMess(const QString &value);

    int getGoodsID() const;
    void setGoodsID(const int &value);

    //将 comment_tempFile 的数据更新到对象中
    void flushComment();

    //将对象的数据存储到 comment_tempFile
    void saveComment();

    //从 commentFile 删除评论数据，并存储到 comment_deleteFile 中
    void deleteOrder();

private:

    //评论者
    QString commenter;

    //评论内容
    QString commentMess;

    //商品ID
    int goodsID = 10000;


};

#endif // COMMENT_H
