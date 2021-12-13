#include <QApplication>
#include <QWidget>
#include "scene1.cpp"
#include <QScreen>

/**
* mainpage 435L-Project
* author Lama Fakhreddine
* author Milia Zeidan
* author Rana Hazimeh
* date 28/11/2021
*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    scene1 *intro = new scene1();
    Centering::centerWidget(intro);
    intro->show();
    return app.exec();
    return 0;
}


