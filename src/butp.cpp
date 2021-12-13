/**
  * \file butp.cpp
  * \brief the purple disk in game 2
  */
#include "butp.h"
#include <QDebug>

/**
  * \brief butp constructor
  * \param parent, a pointer to a parent QObject, initialized to a nullptr
  * \param pos, position by which the button falls
  */
butp::butp(QObject *parent, int pos) : QObject(parent)
{

    setPixmap((QPixmap(":/objp.png")).scaled(80,80));
    //int random_number = rand() % 900; //randomly generated number for the randomness of the position of the rubbish
    setPos(200,100);

    timer = new QTimer(this); //timer for the connect function
    confirmConnect(timer, pos);
    //qDebug() << "pos in butp.h = " << pos << endl;
    timer->start(100);


}

/**
 * \brief button falls slowly
 */
void butp::buttonfall1(){
    this->setPos(x(), y()+5);
}

/**
 * \brief button falls faster
 */
void butp::buttonfall2(){
    this->setPos(x(), y()+10);
}

/**
 * \brief button falls faster
 */
void butp::buttonfall3(){
    this->setPos(x(), y()+20);
}

/**
 * \brief button falls faster
 */
void butp::buttonfall4(){
    this->setPos(x(), y()+40);
}

/**
 * \brief button falls faster
 */
void butp::buttonfall5(){
    this->setPos(x(), y()+80);
}

/**
 * \brief connects button to correct signal depending on the falling speed needed
 */
void butp :: confirmConnect(QTimer *timer, int pos){

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

int butp :: type() const {

    return Purple;
}
