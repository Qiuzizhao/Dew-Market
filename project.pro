QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddGoodsBox.cpp \
    AdminBox.cpp \
    AdminOrderBox.cpp \
    AdminUserBox.cpp \
    BuyerOrderBox.cpp \
    Comment.cpp \
    CommentGoodsBox.cpp \
    Goods.cpp \
    MainWidget.cpp \
    ModifyGoodsMessBox.cpp \
    ModifyUserMessBox.cpp \
    Order.cpp \
    SellerBox.cpp \
    SellerOrderBox.cpp \
    User.cpp \
    UserLoginBox.cpp \
    UserResgisterBox.cpp \
    main.cpp

HEADERS += \
    AddGoodsBox.h \
    AdminBox.h \
    AdminOrderBox.h \
    AdminUserBox.h \
    BuyerOrderBox.h \
    Comment.h \
    CommentGoodsBox.h \
    Goods.h \
    MainWidget.h \
    ModifyGoodsMessBox.h \
    ModifyUserMessBox.h \
    Order.h \
    SellerBox.h \
    SellerOrderBox.h \
    Tool.h \
    User.h \
    UserLoginBox.h \
    UserResgisterBox.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
