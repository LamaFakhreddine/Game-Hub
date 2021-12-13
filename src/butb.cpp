/**
  * \file butb.cpp
  * \brief the blue disk in game 2
  */
#include "butb.h"
#include <QDebug>

/**
  * \brief butb constructor
  * \param parent, a pointer to a parent QObject, initialized to a nullptr
  * \param pos, position by which the button falls
  */
butb::butb(QObject *parent, int pos) : QObject(parent)
{
    setPixmap((QPixmap(":/objb.png")).scaled(80,80));
    //int random_number = rand() % 900; //randomly generated number for the randomness of the position of the button
    setPos(350,100);

    timer = new QTimer(this); //timer for the connect function
    confirmConnect(timer, pos);
    //connect(timer, SIGNAL(timeout()), this, SLOT(buttonfall()));
    //qDebug() << "pos in butb.h = " << pos << endl;
    timer->start(100);
}

/**
 * \brief button falls slowly
 */
void butb::buttonfall1(){
    this->setPos(x(), y()+5);
}

/**
 * \brief button falls 2x faster
 */
void butb::buttonfall2(){
    this->setPos(x(), y()+10);
}

/**
 * \brief button falls 4x faster
 */
void butb::buttonfall3(){
    this->setPos(x(), y()+20);
}

/**
 * \brief button falls 8x faster
 */
void butb::buttonfall4(){
    this->setPos(x(), y()+40);
}

/**
 * \brief button falls 16x faster
 */
void butb::buttonfall5(){
    this->setPos(x(), y()+80);
}

/**
 * \brief connects button to correct signal depending on the falling speed needed
 */
void butb :: confirmConnect(QTimer *timer, int pos){

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

int butb :: type() const {

    return Blue;
}

