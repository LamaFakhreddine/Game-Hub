/**
  * \file Centering.cpp
  * \brief A class that centers a widget
  *
  */
#include "centering.h"
/**
 * \brief Centering constructor
 * \param parent, a pointer to parent QObject. Initialized to a nullptr
 */
Centering::Centering(QObject *parent) : QObject(parent)
{

}
/**
 * \brief a function that centers a widget
 * \param w, a pointer to the QWidget to be centered
 */
void Centering::centerWidget(QWidget *w){
    int width = w->frameGeometry().width();
    int height = w->frameGeometry().height();
    QDesktopWidget wid;
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    w->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
    w->show();
}

void Centering::centerScene(QGraphicsView *s){
    int width = s->frameGeometry().width();
    int height = s->frameGeometry().height();
    QDesktopWidget wid;
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    s->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
    s->show();
}

