#include <Comment.h>

//读取
QString Comment::getCommenter() const
{
    return commenter;
}

QString Comment::getCommentMess() const
{
    return commentMess;
}

int Comment::getGoodsID() const
{
    return goodsID;
}

//写入
void Comment::setCommenter(const QString &value)
{
    commenter = value;
}

void Comment::setCommentMess(const QString &value)
{
    commentMess = value;
}

void Comment::setGoodsID(const int &value)
{
    goodsID = value;
}


//将 goods_tempFile 的数据更新到对象中
void Comment::flushComment()
{
    QFile file(comment_tempFile);
    file.open(QIODevice::ReadOnly);
    QDataStream Str(&file);

    if(!file.atEnd())
    {
        Str>>commenter>>commentMess>>goodsID;
    }

    file.close();
}

//将对象的数据存储到 comment_tempFile
void Comment::saveComment()
{
    QFile file(comment_tempFile);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream Str(&file);

    Str<<commenter<<commentMess<<goodsID;

    file.close();
}



//从 CommentFile 删除评论数据，并存储到 Comment_deleteFile 中
void Comment::deleteOrder()
{
    int userGoodsID = 10000;
    QString userCommenter,userCommentMess;



    //利用 comment_superFile 作为中转，写入 commentFile，删除该用户的信息
    QFile file(commentFile);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile superFile(comment_superFile);
    superFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream writeDataStr(&superFile);


    while (!readDataStr.atEnd())
    {
        //从 orderFile 读取数据
        readDataStr>>userCommenter>>userCommentMess>>userGoodsID;

        //判断是否为当前评论
        if(userCommenter != commenter && userGoodsID != goodsID)
        {
            //并非当前评论则直接写入 comment_superFile
            writeDataStr<<userCommenter<<userCommentMess<<userGoodsID;

        }
        else
        {
            //读取到当前评论则不写入

        }

    }


    //关闭文件
    //删除 commentFile 原文件，并将 comment_superFile 改名为 commentFile 来取替原文件
    file.close();
    superFile.close();
    file.remove();
    superFile.rename(commentFile);


    //将该用户信息写入 comment_deleteFile
    QFile deleteFile(comment_deleteFile);
    deleteFile.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Append);
    QDataStream deleteDataStr(&deleteFile);

    deleteDataStr<<commenter<<commentMess<<goodsID;

    deleteFile.close();

}

