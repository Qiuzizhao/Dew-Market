#include <QApplication>
#include "MainWidget.h"
#include "SellerBox.h"
#include "AdminBox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    MainWidget mWidget;

    SellerBox sellerWidget;

    AdminBox adminWidget;

    QObject::connect(&mWidget,&MainWidget::gotoSignals1,&sellerWidget,&SellerBox::ChangeToSeller);
    QObject::connect(&mWidget,&MainWidget::gotoSignals2,&adminWidget,&AdminBox::ChangeToAdmin);


    QObject::connect(&sellerWidget,&SellerBox::gotoSignals1,&mWidget,&MainWidget::ChangeToBuyer);
    QObject::connect(&sellerWidget,&SellerBox::gotoSignals2,&adminWidget,&AdminBox::ChangeToAdmin);


    QObject::connect(&adminWidget,&AdminBox::gotoSignals1,&mWidget,&MainWidget::ChangeToBuyer);
    QObject::connect(&adminWidget,&AdminBox::gotoSignals2,&sellerWidget,&SellerBox::ChangeToSeller);




    mWidget.show();

    a.exec();
    return 0;
}
