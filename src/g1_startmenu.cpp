/**
  * \file g1_startmenu.cpp
  * \brief the start menu of Battleships
  */

#include "g1_settings.h"
#include "g1_setup.h"
#include "account.h"
#include "centering.h"
#include "g1_startmenu.h"

/**
  * \brief g1_startmenu constructor
  * \param parent, a pointer to a parent QWidget, initialized to a nullptr
  * \param json, the player's QJsonObject, initialized to an empty json object
  */
g1_startmenu::g1_startmenu(QWidget *parent, QJsonObject json) : QWidget(parent)
{
    userJson = json;
    setStyleSheet("QLabel{font-size:64px;"
                  "font-weight: bold;"
                  "text-transform: uppercase;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:24px;"
                  "font-weight:bold;"
                  "color: #FF5454;"
                  "width:200px;"
                  "height: 50px;}"
                  "QPushButton:hover{"
                  "border-right:5px solid #FF5454;"
                  "border-bottom:5px solid #FF5454;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}");

    initBg();//initialize bg color

    //set menu widgets
    playBtn = new QPushButton("Play");
    settingsBtn = new QPushButton("Settings");
    exitBtn = new QPushButton("Exit");
    gameLogo = new QLabel();
    gameLogo->setPixmap(QPixmap(":/battleship-bg.png").scaled(850,300));

    //set layout
    vLayout = new QVBoxLayout();
    vLayout->addSpacing(50);
    vLayout->addWidget(gameLogo, 0, Qt::AlignCenter);
    vLayout->addSpacing(50);
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
 * \brief Proceeds to gameplay when player presses F1 key
 * \param event
 */
void g1_startmenu::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F1)
        {
            g1_setup *g1 = new g1_setup(nullptr, userJson);
            Centering::centerWidget(g1);
            g1->show();
            this->hide();
        }
}
/**
 * \brief Navigates to gameplay when player clicks play button
 */
void g1_startmenu::onPlay(){
    g1_info *info = new g1_info(nullptr, userJson);
    Centering::centerWidget(info);
    info->show();
    this->hide();
}

/**
 * \brief Navigates to game settings
 */
void g1_startmenu::onSettings(){
    g1_settings *settings = new g1_settings(nullptr, userJson);
    this->hide();
    Centering::centerWidget(settings);
    settings->show();
}
/**
 * \brief navigates back to account
 */
void g1_startmenu::onExit(){
    account *a = new account(nullptr, userJson);
    Centering::centerWidget(a);
    a->show();
    this->hide();
}
/**
 * \brief initializes the background color of the QWidget
 * as specified in userJson.
 */
void g1_startmenu::initBg(){
    //extract bg ID from json object
    QString bgColor = jh->getBgColor(userJson, "game1");

    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}

