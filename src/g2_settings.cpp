/**
  * \file g2_settings.cpp
  * \brief This class creates the settings QWidget for Shooting discs.
  * In the settings, the user can change the game difficulty and background image.
  * Changing the difficulty changes the target score and lives.
  * Changing the background updates the image of the gameplay ONLY.
  * (unlike Battleships, the start menu and settings do not change backgrounds).
  */

#include "g2_settings.h"
#include "g2_setup.h"
#include "g2_startmenu.h"
#include "centering.h"

/**
  * \brief g2_settings constructor
  * \param parent, a nullptr to the QWidget parent
  * \param json, the QJsonObject for a given user.
  */
g2_settings::g2_settings(QWidget *parent, QJsonObject json) : QWidget(parent)
{

    userJson = json;
    QString css = "QWidget{background: #0F0012}"
                  "QLabel{font-size:24px;"
                  "font-weight: bold;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:22px;"
                  "font-weight:bold;"
                  "color: #ED0EED;"
                  "width:60px;"
                  "height: 40px;}"

                  "QPushButton:hover{"
                  "border-right:5px solid #ED0EED;"
                  "border-bottom:5px solid #ED0EED;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}"

                   "QGroupBox{border-top:2px solid #dbdbdb;}";

    setStyleSheet(css);

    backBtn = new QPushButton("    Back    ");
    title = new QLabel();
    QPixmap bg(QPixmap(":/settings-2"));
    title->setPixmap(bg.scaled(550,70));
    topicLabel = new QLabel("Topics");
    bgLabel = new QLabel("Background");

    //difficulty section
    diffLabel = new QLabel("Difficulty");
    easyBtn = new QPushButton("Easy");
    mediumBtn = new QPushButton("Medium");
    hardBtn = new QPushButton("Hard");
    difficultyBox  = new QGroupBox();
    diffBoxLayout = new QHBoxLayout();
    //create difficulty button box
    createDifficultyBox();

    //background section
    bg1Btn = new QPushButton("Void");
    bg2Btn = new QPushButton("Vaporwave Sunset");
    bg3Btn = new QPushButton("Space Grid");
    bgBox = new QGroupBox();
    bgBoxLayout = new QHBoxLayout();
    //create bg box
    createBgBox();

    grid = new QGridLayout();
    setGridLayout();
    setFixedSize(1000,800);

    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    QSignalMapper *signalMapper3 = new QSignalMapper(this);

    QObject::connect(backBtn, SIGNAL(clicked()), this, SLOT(goBack()));

    //mapping difficulty buttons
    QObject::connect(easyBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    QObject::connect(mediumBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    QObject::connect(hardBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    signalMapper1->setMapping(easyBtn, 0);
    signalMapper1->setMapping(mediumBtn, 1);
    signalMapper1->setMapping(hardBtn, 2);
    QObject::connect(signalMapper1, SIGNAL(mapped(int)), this, SLOT(changeDifficulty(int)));

    //mapping bg buttons
    QObject::connect(bg1Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    QObject::connect(bg2Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    QObject::connect(bg3Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    signalMapper3->setMapping(bg1Btn, ":/g2b1.png");
    signalMapper3->setMapping(bg2Btn, ":/g2b2.webp");
    signalMapper3->setMapping(bg3Btn, ":/g2b3.jpg");
    QObject::connect(signalMapper3, SIGNAL(mapped(QString)), this, SLOT(changeBg(QString)));

}
/**
 * @brief createDifficultyBox, creates the box of difficulty buttons
 */
void g2_settings::createDifficultyBox(){
    diffBoxLayout->addWidget(easyBtn);
    diffBoxLayout->addWidget(mediumBtn);
    diffBoxLayout->addWidget(hardBtn);
    diffBoxLayout->setSpacing(40);
    difficultyBox->setLayout(diffBoxLayout);
}
/**
 * @brief createBgBox, creates the box of bg buttons
 */
void g2_settings::createBgBox(){
    bgBoxLayout->addWidget(bg1Btn);
    bgBoxLayout->addWidget(bg2Btn);
    bgBoxLayout->addWidget(bg3Btn);
    bgBoxLayout->setSpacing(40);
    bgBox->setLayout(bgBoxLayout);
}
/**
 * @brief setGridLayout, sets the widgets of a grid layout
 */
void g2_settings::setGridLayout(){
    grid->setMargin(30);
    grid->addWidget(backBtn, 0, 0, Qt::AlignLeft);
    grid->addWidget(title, 0, 0, Qt::AlignCenter);
    grid->addWidget(diffLabel, 1,0, Qt::AlignCenter);
    grid->addWidget(difficultyBox, 2, 0);
    grid->addWidget(bgLabel, 5, 0, Qt::AlignCenter);
    grid->addWidget(bgBox, 6, 0);
    setLayout(grid);
}
/**
 * @brief changeBg, changes the bg image path in the user json
 * @param bgImg, the path to the image.
 */
void g2_settings::changeBg(QString bgImg){

    //extract bg ID from json obj
    QJsonObject g2 = userJson.value("game2").toObject();
    QJsonObject s  = g2.value("settings").toObject();
    QString jsonBgImg = s.value("bg").toString();

    //if the selected bgId is different than the existing one
    //update json object
    if(bgImg != jsonBgImg){
        s.insert("bg", bgImg);
        g2.insert("settings", s);
        userJson.insert("game2", g2);
    }
}
/**
 * @brief changeDifficulty, changes the difficulty of the game in the user json
 * @param d, the difficulty level (easy = 0, medium = 1, hard = 2)
 */
void g2_settings::changeDifficulty(int d){
    QJsonObject g2 = userJson.value("game2").toObject();
    QJsonObject s  = g2.value("settings").toObject();
    int diff = s.value("difficulty").toInt();

    if(d != diff){
        s.insert("difficulty", d);
        g2.insert("settings", s);
        userJson.insert("game2", g2);
    }
}
/**
 * @brief goBack, returns to g2_startmenu
 */
void g2_settings::goBack(){
    //write to json file to update user
    jsonhandler *handler = new jsonhandler();
    handler->updateUserarr(userJson);
    handler->writeFile(handler->userPath);

    //go back to start menu
    g2_startmenu *startmenu = new g2_startmenu(nullptr, userJson);
    Centering::centerWidget(startmenu);
    startmenu->show();
    this->hide();
}


