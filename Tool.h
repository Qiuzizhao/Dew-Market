#ifndef TOOL_H
#define TOOL_H

/*
 * userFile 存储所有用户的数据
 * user_tempFile 存储当前用户的数据
 * user_superFile 用于修改 userFile 的临时文件
 * user_deleteFile 用于储存已删除用户的信息
*/

//存储用户信息的文件
#define userFile "UserFile.txt"
#define user_tempFile "UserTempFile.txt"
#define user_superFile "UserSuperFile.txt"
#define user_deleteFile "UserDeleteFile.txt"

//存储商品信息的文件
#define goodsFile "GoodsFile.txt"
#define goods_tempFile "GoodsTempFile.txt"
#define goods_superFile "GoodsSuperFile.txt"
#define goods_deleteFile "GoodsDeleteFile.txt"

//存储订单信息的文件
#define orderFile "OrderFile.txt"
#define order_tempFile "OrderTempFile.txt"
#define order_superFile "OrderSuperFile.txt"
#define order_deleteFile "OrderDeleteFile.txt"

//存储商品评论的文件
#define commentFile "CommentFile.txt"
#define comment_tempFile "CommentTempFile.txt"
#define comment_superFile "CommentSuperFile.txt"
#define comment_deleteFile "CommentDeleteFile.txt"


#endif // TOOL_H
