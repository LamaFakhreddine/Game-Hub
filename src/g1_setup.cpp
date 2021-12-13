#include "g1_setup.h"
#include "g1_startmenu.h"
#include "g1_settings.h"
#include "quests.h"
#include "timeup.h"
#include "gamewon.h"
#include "centering.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <iostream>
#include <QDebug>
using namespace std;

/**
  * \brief g1_setup constructor
  * \param parent, a pointer to a parent QWidget, initialized to a nullptr
  * \param json, the player's QJsonObject, initialized to an empty json object
  */

g1_setup::g1_setup(QWidget *parent, QJsonObject json) : QWidget(parent)
{
    userJson = json;
    qDebug() << "UP correct_tmp= " << correct_tmp;
    qDebug() << "UP WRONG = " << wrong;

    setStyleSheet("QLabel{font-size:20px;"
                  "font-weight: bold;"
                  "color: #fff;}"

                  "QPushButton{"
                  "border: 1px solid #ffffff;"
                  "border-radius:1px;"
                  "font-size:24px;"
                  "font-weight:bold;"
                  "color: #FF5454;"
                  "width:50px;"
                  "height: 50px;}");

    //initialize bg to chosen color
    bgColor = initBg();

    //sets background music
    bgMusic = new QMediaPlayer();
    bgMusic->setMedia(QUrl("qrc:/sounds/holy-wars-8bit.mp3"));
    bgMusic->setVolume(50);
    bgMusic->play();


    //set SFX sounds
    explosionSFX = new QMediaPlayer();
    explosionSFX->setMedia(QUrl("qrc:/sounds/explosion-SFX.mp3"));
    explosionSFX->setVolume(75);


    //score section
    score = new QLabel("Score: "+ QString::number(scoreNum));
    highscore = new QLabel("Highscore: " + QString::number(getHighscore()));

    //turns section
    turns = new QLabel("Turns: " + QString::number(10 - press_count));

    //Timer
    timer1 = new QTimer();
    QObject::connect(timer1, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer1->start(1000);

    timer2 = new QTimer();
    QObject::connect(timer2, SIGNAL(timeout()), this, SLOT(endGame()));
    timer2->setSingleShot(true);
    timer2->start(getTimer()*60*1000);
    time = new QLabel(QString::number(getTimer())+":00");
    time->setStyleSheet("font-size:26px;");

    // create exit
    exit_pb = new QPushButton();
    QPixmap exit(":/exit-icon.png");
    QIcon exit_icon(exit);
    exit_pb->setIcon(exit_icon);
    exit_pb->setIconSize(exit.scaled(40,40).size());
    exit_pb->setStyleSheet("border:none");

    //create settings btn
    settings_pb = new QPushButton();
    QPixmap settings(":/settings-icon.png");
    QIcon settings_icon(settings);
    settings_pb->setIcon(settings_icon);
    settings_pb->setIconSize(settings.scaled(40,40).size());
    settings_pb->setStyleSheet("border:none");

    //create replay btn
    replay_pb = new QPushButton();
    QPixmap replay(":/replay-icon.png");
    QIcon replay_icon(replay);
    replay_pb->setIcon(replay_icon);
    replay_pb->setIconSize(replay.scaled(35,35).size());
    replay_pb->setStyleSheet("border:none");

    //grid titles
    goodcp = new QLabel("Good Coding Practices");
    badcp = new QLabel("Bad Coding Practices");
    goodcp->setStyleSheet("font-size:30px; font-weight:100;");
    badcp->setStyleSheet("font-size:30px; font-weight:100;");

    scene = new QGridLayout();
    player_grid = new QGridLayout();
    cpu_grid = new QGridLayout();
    cpu_backgrid = new QGridLayout();

    // vert1 and vert2 are QVBoxLayouts that contain the caption and the grid for each, the player and user
    vert1 = new QVBoxLayout();
    vert2 = new QVBoxLayout();
    player_grid->setSpacing(0);
    cpu_grid->setSpacing(0);
    cpu_backgrid->setSpacing(0);
    player_grid->setContentsMargins(0,0,0,0);
    cpu_grid->setContentsMargins(0,0,0,0);
    cpu_backgrid->setContentsMargins(0,0,0,0);

    //create button grids for user and computer
    setButtonGrid(player_grid);
    setButtonGrid(cpu_grid);

    // placing the ships on player_grid
    QString pngs1[4] = {":/leftest2.png", ":/left2.png", ":/right2.png", ":/rightest2.png"};
    QString pngs2[2] = {":/shipleft.png", ":/shipright.png"};

    insertShip(1, 1, ":/ship.png", player_grid);
    insertShipSpan(3, 0, 4, player_grid, pngs1);
    insertShipSpan(0, 2, 4, player_grid, pngs2);

    setVerticalLayout(vert1, goodcp, player_grid);
    setVerticalLayout(vert2, badcp, cpu_grid);
    setGridLayout(scene);

    setLayout(scene);
    setFixedSize(900,600);


    QObject :: connect(exit_pb, SIGNAL(clicked()), this, SLOT(onExit()));
    QObject :: connect(replay_pb, SIGNAL(clicked()), this, SLOT(onReplay()));
    QObject::connect(settings_pb, SIGNAL(clicked()), this, SLOT(onSettings()));


    // Connecting each cpu_grid pushbutton to its slot
    QPushButton* pb0 = findPB(cpu_grid, 0, 0);
    QObject::connect(pb0, SIGNAL(clicked()), this, SLOT(pb0Pressed())); // no ship

    QPushButton* pb1 = findPB(cpu_grid, 0, 1);
    QObject::connect(pb1, SIGNAL(clicked()), this, SLOT(pb1Pressed())); // ship

    QPushButton* pb2 = findPB(cpu_grid, 0, 2);
    QObject::connect(pb2, SIGNAL(clicked()), this, SLOT(pb2Pressed())); // no ship

    QPushButton* pb3 = findPB(cpu_grid, 0, 3);
    QObject::connect(pb3, SIGNAL(clicked()), this, SLOT(pb3Pressed())); // no ship

    QPushButton* pb4 = findPB(cpu_grid, 1, 0);
    QObject::connect(pb4, SIGNAL(clicked()), this, SLOT(pb4Pressed())); // ship

    QPushButton* pb5 = findPB(cpu_grid, 1, 1);
    QObject::connect(pb5, SIGNAL(clicked()), this, SLOT(pb5Pressed())); // ship

    QPushButton* pb6 = findPB(cpu_grid, 1, 2);
    QObject::connect(pb6, SIGNAL(clicked()), this, SLOT(pb6Pressed())); // ship

    QPushButton* pb7 = findPB(cpu_grid, 1, 3);
    QObject::connect(pb7, SIGNAL(clicked()), this, SLOT(pb7Pressed())); // ship

    QPushButton* pb8 = findPB(cpu_grid, 2, 0);
    QObject::connect(pb8, SIGNAL(clicked()), this, SLOT(pb8Pressed())); // no ship

    QPushButton* pb9 = findPB(cpu_grid, 2, 1);
    QObject::connect(pb9, SIGNAL(clicked()), this, SLOT(pb9Pressed())); // no ship

    QPushButton* pb10 = findPB(cpu_grid, 2, 2);
    QObject::connect(pb10, SIGNAL(clicked()), this, SLOT(pb10Pressed())); // no ship

    QPushButton* pb11 = findPB(cpu_grid, 2, 3);
    QObject::connect(pb11, SIGNAL(clicked()), this, SLOT(pb11Pressed())); // no ship

    QPushButton* pb12 = findPB(cpu_grid, 3, 0);
    QObject::connect(pb12, SIGNAL(clicked()), this, SLOT(pb12Pressed())); // ship

    QPushButton* pb13 = findPB(cpu_grid, 3, 1);
    QObject::connect(pb13, SIGNAL(clicked()), this, SLOT(pb13Pressed())); // ship

    QPushButton* pb14 = findPB(cpu_grid, 3, 2);
    QObject::connect(pb14, SIGNAL(clicked()), this, SLOT(pb14Pressed())); // no ship

    QPushButton* pb15 = findPB(cpu_grid, 3, 3);
    QObject::connect(pb15, SIGNAL(clicked()), this, SLOT(pb15Pressed())); // no ship

}
/**
* \brief Sets the main grid layout
*/
void g1_setup::setGridLayout(QGridLayout *grid)
{
    grid->addWidget(score, 0, 0, Qt::AlignLeft);
    grid->addWidget(time, 0, 1, Qt::AlignCenter);
    grid->addWidget(highscore, 1, 0, Qt::AlignLeft);
    grid->addWidget(turns, 1, 1, Qt::AlignCenter);
    grid->addItem(vert1, 2, 0, Qt::AlignTop, Qt::AlignLeft);
    grid->addItem(vert2, 2, 2, Qt::AlignTop, Qt::AlignRight);
    grid->addWidget(exit_pb, 0, 2, Qt::AlignCenter);
    grid->addWidget(replay_pb, 0, 3, Qt::AlignLeft);
    grid->addWidget(settings_pb, 0, 3, Qt::AlignRight);
    grid->addItem(new QSpacerItem(140, 90), 1, 1);
    grid->setContentsMargins(30, 25, 30, 25);
}

/**
* \brief Sets the vertical layout of vbox
* \param vbox, the QVBoxLayout to set
* \param label, titles of player and enemy grids
* \param grid, main grid
*/
void g1_setup :: setVerticalLayout(QVBoxLayout *vbox, QLabel* label, QGridLayout* grid){

    vbox->addWidget(label, Qt::AlignCenter, Qt::AlignTop);
    vbox->setSpacing(-100);
    vbox->addItem(grid);

}
/**
 * \brief Sets the player and enemy grid layouts
 */
void g1_setup::setButtonGrid(QGridLayout *grid)
{
   for (int i = 0; i < 4; i++){
       for(int j = 0; j < 4; j++){
           QPushButton *pb = new QPushButton();
           pb->setStyleSheet("height:70px; width:70px");
           grid->addWidget(pb, i, j);
       }
   }
}
/**
 * \brief navigates to g1_startmenu
 */
void g1_setup :: onExit(){
    bgMusic->stop();
    delete bgMusic;
    timer1->stop();
    timer2->stop();
    g1_startmenu *menu = new g1_startmenu(nullptr, userJson);
    hide();
    Centering::centerWidget(menu);
    menu->show();
}
/**
 * \brief starts a new game
 */
void g1_setup :: onReplay(){
    bgMusic->stop();
    delete bgMusic;
    g1_setup* g1 = new g1_setup(nullptr, userJson);
    Centering::centerWidget(g1);
    g1->show();
    hide();
    delete this;
}
/**
 * \brief navigates to g1_settings
 */
void g1_setup :: onSettings(){
    bgMusic->stop();
    delete bgMusic;
    timer1->stop();
    timer2->stop();
    g1_settings *settings = new g1_settings(nullptr, userJson);
    hide();
    Centering::centerWidget(settings);
    settings->show();
}
/**
* \brief Inserts ship into grid at position [i,j]
*/
void g1_setup :: insertShip(int i, int j, QString png, QGridLayout* grid){

    //int i = rand() % 3;
    //int j = rand() % 3;

    //int i = 1;
    //int j = 1;

    QLayoutItem* item = grid->itemAtPosition(i, j);
    QWidget* widget = item->widget();
    QPushButton* pb = dynamic_cast<QPushButton*>(widget);

    QIcon btn_icon;
    btn_icon.addFile(png);
    pb->setIcon(btn_icon);
    pb->setIconSize(QSize(80, 400));
    /*pb->setStyleSheet( "QPushButton{background:rgba(0, 0, 0, 0);"
                           "border:0.75px solid white;}");*/

}
/**
* \brief inserts segmented ships into grid
*/
void g1_setup :: insertShipSpan(int row, int min, int max, QGridLayout* grid, QString arr []){

    for (int j = min; j < max; j++){
        QLayoutItem* item = grid->itemAtPosition(row, j);
        QWidget* widget = item->widget();
        QPushButton* pb = dynamic_cast<QPushButton*>(widget);

        QIcon btn_icon;
        btn_icon.addFile(arr[j]);
        pb->setIcon(btn_icon);
        pb->setIconSize(QSize(79, 69));
    }

}

/**
 * \brief initializes the background color of the QWidget
 * as specified in userJson.
 */
QString g1_setup::initBg(){
    bgColor = jh->getBgColor(userJson, "game1");
    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
    return bgColor;
}
/**
 * \brief retrieves user's highscore from userJson object
 */
int g1_setup::getHighscore(){
    QJsonObject g1 = userJson.value("game1").toObject();
    return g1.value("highscore").toInt();
}
/**
 * \brief updates displayed remaining time
 */
void g1_setup::updateTimer(){
    int rem = timer2->remainingTime();
    int m = (rem / 1000) / 60;  //get min
    int ss = (rem / 1000) - m * 60;
    QString s = (ss < 10)? "0" + QString::number(ss) : QString::number(ss);
    time->setText(QString::number(m) + ":" + s);
}
/**
 * \brief updates user's displayed score
 * \param scoreNum, the user's current score
 */
void g1_setup::updateScore(int scoreNum){

    score->setText("Score: "+ QString::number(scoreNum));
}
/**
 * \brief updates user's displayed remaining turns
 */
void g1_setup::updateTurns(){
    turns->setText("Turns: " + QString::number(10-press_count));
}
/**
 * \brief ends the game
 */
void g1_setup::endGame(){
    bgMusic->stop();
    delete bgMusic;
    //stop timer
    timer1->stop();
    timeUp *go = new timeUp(nullptr, userJson, scoreNum, "game1");
    Centering::centerWidget(go);
    go->show();
    this->hide();
}
/**
 * \brief declares user's win when 7 answers are correct
 */
void g1_setup::winGame(){
    bgMusic->stop();
    delete bgMusic;
    gameWon* win = new gameWon(nullptr, userJson, scoreNum, "game1");
    Centering::centerWidget(win);
    timer1->stop();
    win->show();
    hide();
}
/**
 * \brief declares user's loss when at least 4 answers are wrong
 */
void g1_setup::loseGame(){
    bgMusic->stop();
    delete bgMusic;
    gameLost* lost = new gameLost(nullptr, userJson, scoreNum, "game1");
    Centering::centerWidget(lost);
    timer1->stop();
    lost->show();
    hide();
}
/**
 * \brief declares user's loss when user has no more turns
 */
void g1_setup::loseTurns(){
    bgMusic->stop();
    delete bgMusic;
    noTurns* lose_turn = new noTurns(nullptr, userJson, scoreNum);
    Centering::centerWidget(lose_turn);
    timer1->stop();
    lose_turn->show();
    hide();
}

/**
 * \brief returns the pushButton found at grid[i,j]
 * \param grid
 * \param i
 * \param j
 */
QPushButton* g1_setup :: findPB(QGridLayout* grid, int i, int j){

    QLayoutItem* item = grid->itemAtPosition(i, j);
    QWidget* widget = item->widget();
    QPushButton* pb = dynamic_cast<QPushButton*>(widget);
    return pb;

}

// SLOTS

void g1_setup::pb0Pressed(){


    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb00 = findPB(cpu_grid, 0, 0);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb00->setIcon(btn_icon);
        pb00->setIconSize(QSize(79, 69));
    }
}


void g1_setup::pb1Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4) {
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        shipcount++;
        press_count++;
        updateTurns();
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb01 = findPB(cpu_grid, 0, 1);


        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }
            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb01->setIcon(btn_icon);
            pb01->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 0, 2);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb01->setIcon(btn2_icon);
            pb01->setIconSize(QSize(79, 69));
        }
        pb01->setEnabled(false);
    }
}

void g1_setup::pb2Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb02 = findPB(cpu_grid, 0, 2);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb02->setIcon(btn_icon);
        pb02->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb3Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb03 = findPB(cpu_grid, 0, 3);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb03->setIcon(btn_icon);
        pb03->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb4Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{

        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        qDebug() << "created quest\n";

        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb10 = findPB(cpu_grid, 1, 0);
        qDebug() <<"finding pb\n";

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            qDebug() << "CORRECT ANSWER\n";
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb10->setIcon(btn_icon);
            pb10->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            qDebug() << "WRONG ANSWER\n";
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 3, 0);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb10->setIcon(btn2_icon);
            pb10->setIconSize(QSize(79, 69));
        }
        pb10->setEnabled(false);
    }
}

void g1_setup::pb5Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb11 = findPB(cpu_grid, 1, 1);

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb11->setIcon(btn_icon);
            pb11->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 3, 2);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb11->setIcon(btn2_icon);
            pb11->setIconSize(QSize(79, 69));
        }
        pb11->setEnabled(false);
    }
}

void g1_setup::pb6Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb12 = findPB(cpu_grid, 1, 2);

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb12->setIcon(btn_icon);
            pb12->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 1, 1);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb12->setIcon(btn2_icon);
            pb12->setIconSize(QSize(79, 69));
        }
        pb12->setEnabled(false);
    }
}

void g1_setup::pb7Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb13 = findPB(cpu_grid, 1, 3);

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb13->setIcon(btn_icon);
            pb13->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 3, 1);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb13->setIcon(btn2_icon);
            pb13->setIconSize(QSize(79, 69));
        }
        pb13->setEnabled(false);
    }
}


void g1_setup::pb8Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb20 = findPB(cpu_grid, 2, 0);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb20->setIcon(btn_icon);
        pb20->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb9Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb21 = findPB(cpu_grid, 2, 1);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb21->setIcon(btn_icon);
        pb21->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb10Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
           loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb22 = findPB(cpu_grid, 2, 2);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb22->setIcon(btn_icon);
        pb22->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb11Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb23 = findPB(cpu_grid, 2, 3);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb23->setIcon(btn_icon);
        pb23->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb12Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{

        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb30 = findPB(cpu_grid, 3, 0);

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb30->setIcon(btn_icon);
            pb30->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 3, 3);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb30->setIcon(btn2_icon);
            pb30->setIconSize(QSize(79, 69));
        }
        pb30->setEnabled(false);
    }
}

void g1_setup::pb13Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        shipcount++;
        press_count++;
        updateTurns();
        qDebug() << "json in setup" << userJson;
        quests* quest = new quests(nullptr, userJson, shipcount);
        Centering::centerWidget(quest);
        quest->exec();
        QPushButton* pb31 = findPB(cpu_grid, 3, 1);

        // user answered question correct_tmply
        qDebug() << "CHECK ANS" << quest->checkAns;
        if (quest->checkAns == true){
            playExplosionSounds();
            correct_tmp++;
            scoreNum += 50;
            updateScore(scoreNum);
            int hs = getHighscore();
            if (scoreNum > hs){
                highscore->setText("Highscore: " + QString::number(scoreNum));
            }

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            pb31->setIcon(btn_icon);
            pb31->setIconSize(QSize(79, 69));

        }

            //user answered question incorrect_tmply
        else{
            playExplosionSounds();
            wrong++;
            // set a target icon on cpu_grid, and enemy hits player's ship
            QPushButton* player_pb = findPB(player_grid, 0, 3);

            QIcon btn_icon;
            btn_icon.addFile(":/redsplash.png");
            player_pb->setIcon(btn_icon);
            player_pb->setIconSize(QSize(79, 69));

            QIcon btn2_icon;
            btn2_icon.addFile(":/target.png");
            pb31->setIcon(btn2_icon);
            pb31->setIconSize(QSize(79, 69));
        }
        pb31->setEnabled(false);
    }
}

void g1_setup::pb14Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct = " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb32 = findPB(cpu_grid, 3, 2);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb32->setIcon(btn_icon);
        pb32->setIconSize(QSize(79, 69));
    }
}

void g1_setup::pb15Pressed(){

    qDebug() << "PRESS COUNT = " << press_count;
    qDebug() << "correct = " << correct_tmp;
    if (press_count > 9) {
        qDebug() << "correct_tmp= " << correct_tmp;
        qDebug() << "wrong = " << wrong;
        if (correct_tmp  >= 7){
            winGame();
        }
        else if (wrong >= 4){
            loseGame();
        }
        // no turns left
        else{
            loseTurns();
        }
    }

    else{
        playExplosionSounds();
        press_count++;
        updateTurns();
        QPushButton* pb33 = findPB(cpu_grid, 3, 3);
        QIcon btn_icon;
        btn_icon.addFile(":/bluesplash.png");
        pb33->setIcon(btn_icon);
        pb33->setIconSize(QSize(79, 69));
    }
}
/**
 * \brief retrieves timer limit from userJson object
 */
int g1_setup::getTimer(){
    int diff = userJson.value("game1").toObject().value("settings").toObject().value("difficulty").toInt();
    if(diff == 0){
        return 10;
    }if(diff == 1){
        return 8;
    }else{
        return 5;
    }
}
/**
 * @brief plays explosion SFX
 */
void g1_setup::playExplosionSounds(){
    if(explosionSFX->state() == QMediaPlayer::PlayingState){
        explosionSFX->setPosition(0);
    }if(explosionSFX->state() == QMediaPlayer::StoppedState){
        explosionSFX->play();
    }
}
