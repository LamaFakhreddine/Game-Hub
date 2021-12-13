/**
  * \file g1_startmenu.cpp
  * \brief the start menu of Battleships
  */


#include "g2_startmenu.h"
#include "account.h"
#include "g2_settings.h"
#include "g2_setup.h"
#include "centering.h"

/**
  * \brief g2_startmenu constructor
  * \param parent, a pointer to a parent QWidget, initialized to a nullptr
  * \param json, the player's QJsonObject, initialized to an empty json object
  */

g2_startmenu::g2_startmenu (QWidget *parent, QJsonObject json) : QWidget(parent)
{
    userJson = json;
    setStyleSheet("QWidget{background: #0F0012}"

                  "QLabel{font-size:64px;"
                  "font-weight: bold;"
                  "text-transform: uppercase;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:24px;"
                  "font-weight:bold;"
                  "color: #ED0EED;"
                  "width:200px;"
                  "height: 50px;}"
                  "QPushButton:hover{"
                  "border-right:5px solid #ED0EED;"
                  "border-bottom:5px solid #ED0EED;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}");


    //set menu widgets
    playBtn = new QPushButton("Play");
    settingsBtn = new QPushButton("Settings");
    exitBtn = new QPushButton("Exit");
    gameLogo = new QLabel();
    gameLogo->setPixmap(QPixmap(":/shooting-discs-bg.png").scaled(850,200));

    //set layout
    vLayout = new QVBoxLayout();
    vLayout->addSpacing(50);
    vLayout->addWidget(gameLogo, 0, Qt::AlignCenter);
    vLayout->addSpacing(75);
    vLayout->addWidget(playBtn, 0, Qt::AlignCenter);
    vLayout->addWidget(settingsBtn, 0,  Qt::AlignCenter);
    vLayout->addWidget(exitBtn, 0, Qt::AlignCenter);
    vLayout->addSpacing(50);




    setLayout(vLayout);
    window()->setFixedSize(1000, 800);

    QObject::connect(playBtn, SIGNAL(clicked()), this, SLOT(onPlay()));
    QObject::connect(settingsBtn, SIGNAL(clicked()), this, SLOT(onSettings()));
    QObject::connect(exitBtn, SIGNAL(clicked()), this, SLOT(onExit()));
}

/**
 * \brief Navigates to gameplay when player clicks play button
 */

void g2_startmenu::onPlay(){
    g2_setup *g2 = new g2_setup(userJson);
    //Centering::centerWidget(g2);
    //g2->show();
    v1 = new QGraphicsView(g2); //graphics of the scene
    v1->setFixedSize(500, 800);
    v1->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    v1->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    v1->setFocus();
    Centering::centerScene(v1);
    v1->show();
    this->hide();

}

/**
 * \brief navigates back to account
 */
void g2_startmenu::onExit(){
    account *a = new account(nullptr, userJson);
    Centering::centerWidget(a);
    a->show();
    this->hide();
}

/**
 * \brief Navigates to game settings
 */

void g2_startmenu::onSettings(){
    g2_settings *settings = new g2_settings(nullptr, userJson);
    this->hide();
    Centering::centerWidget(settings);
    settings->show();
}

/**
 * \brief Proceeds to gameplay when player presses F1 key
 * \param event
 */

void g2_startmenu::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F1)
        {
            g2_setup *g2 = new g2_setup(userJson);
            //Centering::centerWidget(g2);
            //g2->show();
            QGraphicsView *v1 = new QGraphicsView(g2); //graphics of the scene
            v1->setFixedSize(500, 800);
            v1->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
            v1->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
            v1->setFocus();
            Centering::centerScene(v1);
            v1->show();
            this->hide();
        }
}




