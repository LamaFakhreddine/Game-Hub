/**
  * \file butblack.cpp
  * \brief the grey disk in game 2
  */
#include "butblack.h"
#include <QDebug>

/**
  * \brief butb constructor
  * \param parent, a pointer to a parent QObject, initialized to a nullptr
  * \param x, the x coordinate at which the grey button should fall
  * \param pos, position by which the button falls
  */
butblack::butblack(QObject *parent, int x, int pos) : QObject(parent)
{
    timer = new QTimer(this); //timer for the connect function
    confirmConnect(timer, pos);
    timer->start(100);

    setPixmap((QPixmap(":/butgrey.png")).scaled(80,80));

    //int random_number = rand() % 900; //randomly generated number for the randomness of the position of the rubbish
    setPos(x,730);
    //qDebug()<<"black button out";
}
/**
 * \brief button falls slowly
 */
void butblack::buttonfall1(){
    this->setPos(x(), y()+5);
    if (this->y() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * \brief button falls faster
 */
void butblack::buttonfall2(){
    this->setPos(x(), y()+10);
    if (this->y() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * \brief button falls faster
 */
void butblack::buttonfall3(){
    this->setPos(x(), y()+20);
    if (this->y() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * \brief button falls faster
 */
void butblack::buttonfall4(){
    this->setPos(x(), y()+40);
    if (this->y() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * \brief button falls faster
 */
void butblack::buttonfall5(){
    this->setPos(x(), y()+80);
    if (this->y() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * \brief connects button to correct signal depending on the falling speed needed
 */
void butblack :: confirmConnect(QTimer *timer, int pos){

    if (pos == 5){
        connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall1()));
    }
    else if (pos == 10){
        connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall2()));
    }
    else if (pos == 20){
        connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall3()));
    }
    else if (pos == 40){
        connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall4()));
    }
    else if (pos == 80){
        connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall5()));
    }

}

int butblack :: type() const {

    return Black;
}
