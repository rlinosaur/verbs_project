#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec=QTextCodec::codecForName("UTF-8");

    #if QT_VERSION >= 0x050000
    // Qt5 code
    #else
    // Qt4 code
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    #endif

    QTextCodec::setCodecForLocale(codec);

    MainWindow w;
    w.show();
    
    return a.exec();
}
