/**
  * \file butg.cpp
  * \brief the green disk in game 2
  */
#include "butg.h"
#include <QDebug>

/**
  * \brief butg constructor
  * \param parent, a pointer to a parent QObject, initialized to a nullptr
  * \param x, the x coordinate at which the grey button should fall
  * \param pos, position by which the button falls
  */
butg::butg(QObject *parent, int pos) : QObject(parent)
{
    setPixmap((QPixmap(":/objg.png")).scaled(80,80));
    //int random_number = rand() % 900; //randomly generated number for the randomness of the position of the rubbish
    setPos(70,100);

    timer = new QTimer(this); //timer for the connect function
    confirmConnect(timer, pos);
    timer->start(100);
}

/**
 * \brief button falls slowly
 */
void butg::buttonfall1(){
    this->setPos(x(), y()+5);
}
/**
 * \brief button falls faster
 */
void butg::buttonfall2(){
    this->setPos(x(), y()+10);
}
/**
 * \brief button falls faster
 */
void butg::buttonfall3(){
    this->setPos(x(), y()+20);
}
/**
 * \brief button falls faster
 */
void butg::buttonfall4(){
    this->setPos(x(), y()+40);
}
/**
 * \brief button falls faster
 */
void butg::buttonfall5(){
    this->setPos(x(), y()+80);
}

/**
 * \brief connects button to correct signal depending on the falling speed needed
 */
void butg :: confirmConnect(QTimer *timer, int pos){

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
int butg :: type() const {

    return Green;
}
