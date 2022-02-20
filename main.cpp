#include <QApplication>
#include <qmainwindows_.h>

int main(int argc,char **argv )
{
    QApplication a(argc,argv);

    Qmainwindows_ MainWindow;
    MainWindow.show();

    return a.exec();
}
