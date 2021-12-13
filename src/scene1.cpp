/**
* \file Scene1.cpp
* \brief The landing view of the GameHub application
*
* This view includes the following entry options: sign-in, sign-up, and play-as-guest
*/

#include "scene1.h"
#include "signuppage.h"
#include "signinpage.h"
#include "playasguest.h"
#include "centering.h"

/**
 * \brief scene1 constructor
 * \param parent, a pointer to the parent widget
 */
scene1::scene1(QWidget *parent) : QWidget(parent)
{
    //instantiates widgets
    hello = new QLabel("Welcome to Game Hub!");
    hello->setStyleSheet("color: #ff711f; font-size: 20px; font-weight:bold;");
    hello->setAlignment(Qt::AlignCenter);
    paragraph = new QLabel();
    paragraph->setText("This is a platform that allows you to enjoy \nplaying games all while keeping track \nof your own progress!");
    paragraph->setStyleSheet("font-size:16px; margin-top:30px;");
    signin = new QPushButton("Sign in");
    signup = new QPushButton("Sign up");
    playasguest_ = new QPushButton("Play as Guest");

    //sets widgets inside the grid layout
    QGridLayout *Grid = new QGridLayout();
    setGridLayout(Grid);
    setLayout(Grid);

    //fixes window size and styles the widgets
    window()->setFixedSize(400,500);
    setStyleSheet("QWidget{background-color: #fff}"

                  "QPushButton{font-size:14px; "
                  "width:60px;"
                  "height:30px;"
                  "padding:5px, 2px;"
                  "margin-top: 10px;}");

    //connect QPushButtons
    QObject::connect(signup, SIGNAL(clicked()), this, SLOT(pushsignup()));
    QObject::connect(signin, SIGNAL(clicked()), this, SLOT(pushsignin()));
    QObject::connect(playasguest_, SIGNAL(clicked()), this, SLOT(pag()));
}

/**
* \brief Sets the widget of the grid layout
* \param *Grid, a pointer to a grid layout
*/
void scene1::setGridLayout(QGridLayout *Grid){
    Grid->addWidget(hello, 0, 0, 2, 1);
    Grid->addWidget(paragraph, 1, 0, Qt::AlignCenter);
    Grid->addWidget(signin, 2, 0, 2, 1);
    Grid->addWidget(signup, 3, 0, 2, 1);
    Grid->addWidget(playasguest_, 4, 0, 2, 1);
}

/**
* \brief Creates and displays the sign up widget and hides the current widget
*/
void scene1::pushsignup(){

    signupPage *sup = new signupPage();
    hide();
    Centering::centerWidget(sup);
    sup->show();

}

/**
* \brief Creates and displays the sign in widget and hides the current widget
*/
void scene1::pushsignin(){

    signinPage *sip = new signinPage();
    hide();
    Centering::centerWidget(sip);
    sip->show();

}

/**
* \brief Creates and displays the play as guest window and hides the current widget
*/
void scene1::pag(){
    playasguest *pag = new playasguest();
    hide();
    Centering::centerWidget(pag);
    pag->show();

}
