#include "g1_settings.h"
#include "g1_startmenu.h"
#include "jsonhandler.h"
#include "centering.h"

g1_settings::g1_settings(QWidget *parent, QJsonObject json) : QWidget(parent)
{
    userJson = json;
    QString css =
                  "QLabel{font-size:24px;"
                  "font-weight: bold;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:22px;"
                  "font-weight:bold;"
                  "color: #FF5454;"
                  "width:60px;"
                  "height: 40px;}"

                  "QPushButton:hover{"
                  "border-right:5px solid #FF5454;"
                  "border-bottom:5px solid #FF5454;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}"

                   "QGroupBox{border-top:2px solid #dbdbdb;}";

    setStyleSheet(css);

    //initialize bg
    initBg();

    backBtn = new QPushButton("    Back    ");
    title = new QLabel();
    QPixmap bg(QPixmap(":/bs-settings"));
    title->setPixmap(bg.scaled(475,70));
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

    //topics section
    t1Btn = new QPushButton("Arrays and Strings");
    t2Btn = new QPushButton("Basics");
    t3Btn = new QPushButton("Structs and Functions");
    topicBox = new QGroupBox();
    topicBoxLayout = new QHBoxLayout();
    //create topics box
    createTopicBox();

    //background section
    bg1Btn = new QPushButton("Default");
    bg2Btn = new QPushButton("Britannia");
    bg3Btn = new QPushButton("Night");
    bgBox = new QGroupBox();
    bgBoxLayout = new QHBoxLayout();
    //create bg box
    createBgBox();

    grid = new QGridLayout();
    setGridLayout();
    setFixedSize(1000,800);

    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    QSignalMapper *signalMapper3 = new QSignalMapper(this);

    QObject::connect(backBtn, SIGNAL(clicked()), this, SLOT(goBack()));

    //difficulty buttons
    QObject::connect(easyBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    QObject::connect(mediumBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    QObject::connect(hardBtn, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    signalMapper1->setMapping(easyBtn, 0);
    signalMapper1->setMapping(mediumBtn, 1);
    signalMapper1->setMapping(hardBtn, 2);
    QObject::connect(signalMapper1, SIGNAL(mapped(int)), this, SLOT(changeDifficulty(int)));

    //topic buttons
    QObject::connect(t1Btn, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    QObject::connect(t2Btn, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    QObject::connect(t3Btn, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    signalMapper2->setMapping(t1Btn, 0);
    signalMapper2->setMapping(t2Btn, 1);
    signalMapper2->setMapping(t3Btn, 2);
    QObject::connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(changeTopic(int)));

    //bg buttons
    QObject::connect(bg1Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    QObject::connect(bg2Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    QObject::connect(bg3Btn, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    signalMapper3->setMapping(bg1Btn, "#1F4E8D");
    signalMapper3->setMapping(bg2Btn, "#7d2727");
    signalMapper3->setMapping(bg3Btn, "#102745");
    QObject::connect(signalMapper3, SIGNAL(mapped(QString)), this, SLOT(changeBg(QString)));
}
/**
* \brief Sets the widget of the grid layout
*/
void g1_settings::setGridLayout(){
    grid->setMargin(30);
    grid->addWidget(backBtn, 0, 0, Qt::AlignLeft);
    grid->addWidget(title, 0, 0, Qt::AlignCenter);
    grid->addWidget(diffLabel, 1,0, Qt::AlignCenter);
    grid->addWidget(difficultyBox, 2, 0);
    grid->addWidget(topicLabel, 3, 0, Qt::AlignCenter);
    grid->addWidget(topicBox, 4, 0);
    grid->addWidget(bgLabel, 5, 0, Qt::AlignCenter);
    grid->addWidget(bgBox, 6, 0);
    setLayout(grid);
}
/**
 * \brief groups the difficulty buttons
 */
void g1_settings::createDifficultyBox(){
    diffBoxLayout->addWidget(easyBtn);
    diffBoxLayout->addWidget(mediumBtn);
    diffBoxLayout->addWidget(hardBtn);
    diffBoxLayout->setSpacing(40);
    difficultyBox->setLayout(diffBoxLayout);
}
/**
 * \brief groups the topic buttons
 */
void g1_settings::createTopicBox(){
    topicBoxLayout->addWidget(t1Btn);
    topicBoxLayout->addWidget(t2Btn);
    topicBoxLayout->addWidget(t3Btn);
    topicBoxLayout->setSpacing(40);
    topicBox->setLayout(topicBoxLayout);
}
/**
 * \brief groups the background buttons
 */
void g1_settings::createBgBox(){
    bgBoxLayout->addWidget(bg1Btn);
    bgBoxLayout->addWidget(bg2Btn);
    bgBoxLayout->addWidget(bg3Btn);
    bgBoxLayout->setSpacing(40);
    bgBox->setLayout(bgBoxLayout);
}
/**
 * \brief initializes the background color of the QWidget
 * as specified in userJson.
 */
void g1_settings::initBg(){
    //extract bg ID from json object
    QString bgColor = jh->getBgColor(userJson, "game1");

    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}
/**
 * \brief changes the background color to the option chosen by the player.
 * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
 */
void g1_settings::changeBg(QString bgColor){
    //map bg color to bg ID
    int bgId = 0;
    if(bgColor == "#7d2727"){
        bgId = 1;
    }else if(bgColor == "#102745"){
        bgId = 2;
    }

    //extract bg ID from json obj
    QJsonObject g1 = userJson.value("game1").toObject();
    QJsonObject s  = g1.value("settings").toObject();
    int jsonBgId = s.value("bg").toInt();

    //if the selected bgId is different than the existing one
    //update json object
    if(bgId != jsonBgId){
        s.insert("bg", bgId);
        g1.insert("settings", s);
        userJson.insert("game1", g1);
    }

    //set the bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}
/**
 * \brief changes Battleships question topic to the option chosen by the player.
 * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
 */
void g1_settings::changeTopic(int t){
    QJsonObject g1 = userJson.value("game1").toObject();
    QJsonObject s  = g1.value("settings").toObject();
    int topic = s.value("topic").toInt();

    if(t != topic){
        s.insert("topic", t);
        g1.insert("settings", s);
        userJson.insert("game1", g1);
    }
}
/**
 * \brief changes the difficulty level to the option chosen by the player.
 * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
 */
void g1_settings::changeDifficulty(int d){
    QJsonObject g1 = userJson.value("game1").toObject();
    QJsonObject s  = g1.value("settings").toObject();
    int diff = s.value("difficulty").toInt();

    if(d != diff){
        s.insert("difficulty", d);
        g1.insert("settings", s);
        userJson.insert("game1", g1);
    }
}
/**
 * \brief Navigates to the previous screen, the start menu.
 */
void g1_settings::goBack(){
    //write to json file to update user
    jsonhandler *handler = new jsonhandler();
    handler->updateUserarr(userJson);
    handler->writeFile(handler->userPath);

    //go back to start menu
    g1_startmenu *startmenu = new g1_startmenu(nullptr, userJson);
    Centering::centerWidget(startmenu);
    startmenu->show();
    this->hide();
}



