#include "g2_setup.h"
#include "timeup.h"
#include <QDebug>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/**
  * \brief g2_setup constructor
  * \param json, the player's QJsonObject, initialized to an empty json object
  */
g2_setup::g2_setup(QJsonObject json) : QGraphicsScene()
{
    userJson = json;
  
    //sets bg music
    bgMusic = new QMediaPlayer();
    bgMusic->setMedia(QUrl("qrc:/sounds/take-on-me-8bit.mp3"));
    bgMusic->setVolume(50);
    bgMusic->play();

    //sets SFX sounds
    popSFX = new QMediaPlayer();
    popSFX->setMedia(QUrl("qrc:/sounds/pop-SFX.mp3"));
    popSFX->setVolume(75);

    setSceneRect(0,0,500,800);
    initBg();
    changeMaxScore();
    qDebug() << "maxScore = " << maxScore << endl;
    qDebug() << "lives_num = " << lives_num << endl;

    QImage image1(":/butg.png");
    item1 = new QGraphicsPixmapItem(QPixmap::fromImage(image1));
    item1->setScale(1.5);
    item1->setPos(50,700);
    addItem(item1);

    QImage image2(":/butp.png");
    item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2));
    item2->setScale(1.5);
    item2->setPos(190,700);
    addItem(item2);

    QImage image3(":/butb.png");
    item3 = new QGraphicsPixmapItem(QPixmap::fromImage(image3));
    item3->setScale(1.5);
    item3->setPos(310,705);
    addItem(item3);

    targetScore = new QGraphicsSimpleTextItem();
    targetScore->setText("Target Score: ");
    targetScore->setBrush(QBrush(Qt::white));
    QFont font("Newyork", 18);
    targetScore->setFont(font);
    targetScore->setPos(100, 15);

    currscore = new QGraphicsSimpleTextItem();
    currscore->setText("Current score: ");
    currscore->setBrush(QBrush(Qt::white));
    currscore->setFont(font);
    currscore->setPos(100, 40);

    lives = new QGraphicsSimpleTextItem();
    lives->setText("Lives: ");
    lives->setBrush(QBrush(Qt::white));
    lives->setFont(font);
    lives->setPos(100, 65);

    targetScoretxt = new QGraphicsSimpleTextItem();
    //int hs = jh->getHighscore(userJson, "game2");
    int ts = maxScore;
    targetScoretxt->setText(QString::number(ts));
    targetScoretxt->setBrush(QBrush(Qt::white));
    targetScoretxt->setFont(font);
    targetScoretxt->setPos(300, 15);

    total = initTotal();
    currscoretxt = new QGraphicsSimpleTextItem();
    currscoretxt->setText(QString::number(total));
    currscoretxt->setBrush(QBrush(Qt::white));
    currscoretxt->setFont(font);
    currscoretxt->setPos(300, 40);

    livestxt = new QGraphicsSimpleTextItem();
    int m = lives_num - misses;
    livestxt->setText(QString::number(m));
    livestxt->setBrush(QBrush(Qt::white));
    livestxt->setFont(font);
    livestxt->setPos(300, 65);

    addItem(lives);
    addItem(currscore);
    addItem(targetScore);
    addItem(livestxt);
    addItem(currscoretxt);
    addItem(targetScoretxt);

    // for timer QLabel (same as g1)
    gtimer1 = new QTimer();
    QObject::connect(gtimer1, SIGNAL(timeout()), this, SLOT(updateTimer()));
    gtimer1->start(1000);

    gtimer2 = new QTimer();
    QObject::connect(gtimer2, SIGNAL(timeout()), this, SLOT(endGame()));
    gtimer2->setSingleShot(true);
    gtimer2->start(getTimer()*60*1000);

    time_lbl = new QLabel(QString::number(getTimer())+":00");
    time_lbl->setStyleSheet("font-size:26px;");
    addWidget(time_lbl);


    tim1 = new QTimer(this);
    tim2 = new QTimer(this);
    confirmTime(pos);
}
/**
 * \brief changes target score  based on selected game difficulty
 */
void g2_setup::changeMaxScore(){
    QJsonObject g2 = userJson.value("game2").toObject();
    QJsonObject s  = g2.value("settings").toObject();
    int diff = s.value("difficulty").toInt();

    qDebug() << "in changeMaxScore()" << endl;
    if (diff == 0){
        maxScore = 100;
        lives_num = 10;
    }
    else if (diff == 1){
        maxScore = 150;
        lives_num = 6;
    }
    else{
        maxScore = 210;
        lives_num = 3;
    }
}


void g2_setup::initBg(){
    QString bgImg = jh->getBgImg(userJson, "game2");
    qDebug() << "img: " << bgImg;
    //set bg image
    setBackgroundBrush(QBrush(QImage(bgImg).scaledToHeight(800).scaledToWidth(490)));
}


/**
 * \brief sets timer limit based on userJson difficulty
*/
int g2_setup::getTimer(){
    int diff = userJson.value("game2").toObject().value("settings").toObject().value("difficulty").toInt();
    if(diff == 0){
        return 3;
    }if(diff == 1){
        return 2;
    }else{
        return 1;
    }
}

/**
* \brief creates instances of butb, butg, and butp randomly
*/
void g2_setup::fallg()
{
    if (!gend){
        checkMisses();
        srand((unsigned int)time(NULL));
        int random_number = rand() % 3;
        if (random_number == 0){
            qDebug() << "pos in random bg = " << pos << endl;
            bg = new butg(nullptr, pos); //the green button falling
            addItem(bg);
            //g_fall++;
           }
        else if (random_number == 1){
            qDebug() << "pos in random bp = " << pos << endl;
            bp = new butp(nullptr, pos); //the purple button falling
            addItem(bp);
            //p_fall++;
           }
        else{
            qDebug() << "pos in random bb = " << pos << endl;
            bb = new butb(nullptr, pos); //the blue button falling
            addItem(bb);
            //b_fall++;
           }
    }

}

/**
* \brief shoots disks when the correct keys are pressed and turns them grey
*/
void g2_setup::keyPressEvent(QKeyEvent *event){
    playPopSounds();
    if (event->key() == Qt::Key_Left){

        left = true;
        if (!(item1->collidingItems().isEmpty())){
            QGraphicsItem* collide = item1->collidingItems().first();
            removeItem(collide);
            addBBlack(70, pos);
            bl1 = true;
            updateTotal(5);
            checkSpeed(total);
            g_hit++;
            qDebug() << "pos = " << pos << endl;
            qDebug() << "green button collision" << endl;
        }
        bl1 = false;
        left = false;
    }
    if (event->key() == Qt::Key_Down){

        down = true;
        if (!(item2->collidingItems().isEmpty())){
            QGraphicsItem* collide = item2->collidingItems().first();
            removeItem(collide);
            addBBlack(200, pos);
            bl2 = true;
            updateTotal(3);
            checkSpeed(total);
            p_hit++;
            qDebug() << "pos = " << pos << endl;
            qDebug() << "purple button collision" << endl;
        }
        bl2 = false;
        down = false;
    }
    if (event->key() == Qt::Key_Right){

        right = true;
        if (!item3->collidingItems().isEmpty()){
            QGraphicsItem* collide = item3->collidingItems().first();
            removeItem(collide);
            addBBlack(350, pos);
            bl3 = true;
            updateTotal(7);
            checkSpeed(total);
            b_hit++;
            qDebug() << "pos = " << pos << endl;
            qDebug() << "blue button collision" << endl;
        }
        bl3 = false;
        right = false;
    }
}

/**
 * @brief initTotal, initializes the score to the bonus from the previous game
 * @return integer, the bonus points
 */
int g2_setup::initTotal(){
    return userJson.value("game2").toObject().value("bonus").toInt();
}

/**
 * \brief adds a butblack object at specified px falling with displacement pos
 * \param px, x-axis coordinate
 * \param pos, displacement of fall
 * \return
 */
butblack* g2_setup :: addBBlack(int px, int pos){

    butblack* bblack = new butblack(nullptr, px, pos);
    addItem(bblack);
    return bblack;
}

/**
* \brief calculates and updates the total score
*/
void g2_setup :: updateTotal(int add){
    total += add;
    currscoretxt->setText(QString::number(total));
}

/**
 * \brief updates falling disks' speed based on current score
 * \param score
 */
void g2_setup :: checkSpeed(int score){

    if (score >= 30 && score < 60){
        pos = 10;
        qDebug() << "in checkSpeed, pos updated to " << pos << endl;
    }
    else if (score >= 60 && score < 90){
        pos = 20;
        qDebug() << "in checkSpeed, pos updated to " << pos << endl;
    }
    else if (score >= 90 && score < 120){
        confirmTime(score);
        pos = 40;
        qDebug() << "in checkSpeed, pos updated to " << pos << endl;
    }
    else if (score >= 120){
        confirmTime(score);
        pos = 80;
        qDebug() << "in checkSpeed, pos updated to " << pos << endl;
    }
}

/**
 * \brief sets time for timer to create falling disks based on current score
 * \param score
 */
void g2_setup :: confirmTime(int score){
    checkMisses();
    if (score <= 90){
        connect(tim1, SIGNAL(timeout()), this, SLOT(fallg()));
        tim1->start(1500);
    }
    else{
        connect(tim2, SIGNAL(timeout()), this, SLOT(fallg()));
        tim2->start(500);
    }
}

/**
* \brief updates the timer displayed on the screen
*/
void g2_setup::updateTimer(){
    int rem = gtimer2->remainingTime();
    int m = (rem / 1000) / 60;  //get min
    int ss = (rem / 1000) - m * 60;
    QString s = (ss < 10)? "0" + QString::number(ss) : QString::number(ss);
    time_lbl->setText(QString::number(m) + ":" + s);
}

/**
* \brief Checks if the player lost yet or not (number of misses)
*/
void g2_setup :: checkMisses(){

    qDebug()<< "in misses";
    if (misses < lives_num){
        if (!(item1->collidingItems().empty()) && !left){
            misses+=1;
        }
        else if (!(item2->collidingItems().empty()) && !down){
            misses+=1;
        }
        else if (!(item1->collidingItems().empty()) && !right){
            misses+=1;
        }
        int m = lives_num - misses;
        livestxt->setText(QString::number(m));
    }
    else if (misses == lives_num){
        bgMusic->stop();
        delete bgMusic;
        jh->updateScores(userJson, total, "game2");
        gameLost* gl = new gameLost(nullptr, userJson, total, "game2");
        Centering::centerWidget(gl);
        gl->show();
        gend = true;
        this->views()[0]->close();

    }
}

/**
* \brief creates an instance of gamelost when the player loses
*/
void g2_setup::endGame(){
    bgMusic->stop();
    delete bgMusic;
    jh->updateScores(userJson, total, "game2");
    qDebug() << "stopping timer" << endl;
    //stop timer
    gtimer1->stop();
    timeUp *go = new timeUp(nullptr, userJson, total, "game2");
    Centering::centerWidget(go);
    go->show();
    gend = true;
    this->views()[0]->close();
}

/**
 * @brief plays the pop SFX on keypressevent
 */
void g2_setup::playPopSounds(){
    if(popSFX->state() == QMediaPlayer::PlayingState){
        popSFX->setPosition(0);
    }if(popSFX->state() == QMediaPlayer::StoppedState){
        popSFX->play();
    }
}
