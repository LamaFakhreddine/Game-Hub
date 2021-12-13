/**
  * \file timeUp.cpp
  * \brief The time's up popup that shows when the user wins the game.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */
#include "timeup.h"
#include "g1_startmenu.h"
#include "centering.h"

/**
 * @brief timeUp constructor
 * @param parent, a pointer to a QWidget parent
 * @param json, a QJsonObject for a given user
 * @param scoreNum, the player's score.
 * @param gameId, QString that specifies which game is being played.
 */
timeUp::timeUp(QWidget *parent, QJsonObject json, int scoreNum, QString gameId) : QWidget(parent)
{
    ID = gameId;
    score = scoreNum;
    userJson = jh->updateScores(json, score, ID);

    if(ID == "game1"){
        setStyleSheet("QLabel{font-size:24px;"
                      "text-transform: uppercase;"
                      "color: #fff;}"

                      "QPushButton{"
                      "background-color: #fff;"
                      "border: 5px solid #fff;"
                      "border-radius:4px;"
                      "font-size:24px;"
                      "font-weight:bold;"
                      "color: #FF5454;"
                      "width:150px;"
                      "height: 35px;}"
                      "QPushButton:hover{"
                      "border-right:5px solid #FF5454;"
                      "border-bottom:5px solid #FF5454;"
                      "border-left:5px solid #73FFFF;"
                      "border-top: 5px solid #73FFFF;}");

    }else{
        setStyleSheet("QWidget{background: #0F0012}"
                      "QLabel{font-size:24px;"
                      "text-transform: uppercase;"
                      "color: #fff;}"

                      "QPushButton{"
                      "background-color: #fff;"
                      "border: 5px solid #fff;"
                      "border-radius:4px;"
                      "font-size:24px;"
                      "font-weight:bold;"
                      "color: #ED0EED;"
                      "width:150px;"
                      "height: 35px;}"
                      "QPushButton:hover{"
                      "border-right:5px solid #ED0EED;"
                      "border-bottom:5px solid #ED0EED;"
                      "border-left:5px solid #73FFFF;"
                      "border-top: 5px solid #73FFFF;}");

    }

    //initialize bg
    initBg();

    //set title
    title = new QLabel();
    QPixmap bg = (ID == "game1")? QPixmap(":/time-up.png") : QPixmap(":/time-up-2.png");
    title->setPixmap(bg.scaled(390,55));
    //set congrats text
    congrats = new QLabel("Congratulations! New highscore achieved!");
    //set text
    text = new QLabel();
    (gameId == "game2")? text->setText("Your score is " + QString::number(score) + " XP. You earned " + QString::number(computeBonus()) + " XP as bonus.")
                       : text->setText("Your score is " + QString::number(score) + " XP");
    //create exit button
    exitBtn = new QPushButton("Exit");

    vLayout = new QVBoxLayout();
    vLayout->setMargin(20);
    vLayout->addWidget(title);
    vLayout->addSpacing(30);
    checkScore();
    vLayout->addWidget(text);
    vLayout->addSpacing(30);
    vLayout->addWidget(exitBtn);
    vLayout->setAlignment(title, Qt::AlignCenter);
    vLayout->setAlignment(congrats, Qt::AlignCenter);
    vLayout->setAlignment(text, Qt::AlignCenter);
    vLayout->setAlignment(exitBtn, Qt::AlignCenter);
    setLayout(vLayout);

    QObject::connect(exitBtn, SIGNAL(clicked()), this, SLOT(onExit()));
}
/**
 * @brief if gameId = game1, onExit() creates and shows a new instance of g1_startmenu.
 * Else, if gameId = game2, it creates and shows a new instance of g2_startmenu.
 */
void timeUp::onExit(){
    if (ID == "game1"){
        g1_startmenu* menu = new g1_startmenu(nullptr, userJson);
        Centering::centerWidget(menu);
        hide();
        menu->show();
    }
    else {
        g2_startmenu* menu = new g2_startmenu(nullptr, userJson);
        Centering::centerWidget(menu);
        hide();
        menu->show();
    }
}
/**
 * @brief Initializes the bg of the widget
 */
void timeUp::initBg(){
    if(ID == "game1"){
        QString bgColor = jh->getBgColor(userJson, ID);
        //set bg color
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, bgColor);
        setAutoFillBackground(true);
        setPalette(pal);
    }

}
/**
 * @brief checks if the score is a new highscore.
 * If the condition is true, display congrats QLabel.
 */
void timeUp::checkScore(){
    QJsonObject g = userJson.value(ID).toObject();
    QJsonArray scoresArr = jh->getScoresArr(userJson, ID);
    if(score == scoresArr.last().toInt() && score >= jh->getHighscore(userJson, ID)){
        vLayout->addWidget(congrats);
    }
}
/**
 * @brief timeUp::computeBonus, computes the bonus points earned in game 2
 * @return int, the bonus points
 */
int timeUp::computeBonus(){
    //get difficulty from json
    int diff = userJson.value("game2").toObject().value("settings").toObject().value("difficulty").toInt();
    int bonusXP;
    if (diff == 0){
        bonusXP = score - 100;
    }
    else if (diff == 1){
        bonusXP = score - 150;
    }
    else{
        bonusXP = score - 210;
    }
    bonusXP = (bonusXP < 0)? 0 : bonusXP;
    //set bonus in json
    userJson = jh->updateBonus(userJson, bonusXP);
    return bonusXP;
}

