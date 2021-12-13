/**
  * \file gameLost.cpp
  * \brief The game over popup that shows when the user wins the game.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */
#include "gamelost.h"

/**
 * @brief gameLost constructor
 * @param parent, a pointer to a QWidget parent
 * @param json, a QJsonObject for a given user
 * @param scoreNum, the player's score.
 * @param gameId, a QString representing game Id. "game1" means Battleships and "game2" means Shooting Discs
 */
gameLost::gameLost(QWidget *parent, QJsonObject json, int scoreNum, QString gameId) : QWidget(parent)
{
    ID = gameId;
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
    score = scoreNum;
    userJson = jh->updateScores(json, score, ID);
    initBg();

    title = new QLabel();
    QPixmap bg = (ID == "game1")? QPixmap(":/game-over.png") : QPixmap(":/game-over-2.png");
    title->setPixmap(bg.scaled(390,55));
    title->setAlignment(Qt::AlignCenter);

    lost = new QLabel();
    setMessage(ID);

    score_ach = new QLabel("Your score is " + QString::number(score) + " XP");
    score_ach->setStyleSheet("text-transform: none;");
    score_ach->setAlignment(Qt::AlignCenter);

    again = new QPushButton("Play Again");
    exit = new QPushButton("Exit");

    mainVbox = new QVBoxLayout();
    hbox = new QHBoxLayout();

    setHBoxLayout(hbox);
    setVBoxLayout(mainVbox);
    setLayout(mainVbox);
//    setFixedSize(450, 450);

    QObject :: connect(exit, SIGNAL(clicked()), this, SLOT(onExit()));
    QObject :: connect(again, SIGNAL(clicked()), this, SLOT(onAgain()));    
}

/**
 * @brief sets the widgets of a horizontal box layout
 * @param hbox, a pointer to a QHBoxLayout.
 */
void gameLost::setHBoxLayout(QHBoxLayout *hbox)
{
    hbox->addWidget(again);
    hbox->setSpacing(150);
    hbox->addWidget(exit);

}
void setVBoxLayout(QVBoxLayout* vbox);
/**
 * @brief Initializes the bg of the widget
 */
void gameLost::setVBoxLayout(QVBoxLayout *vbox)
{
    vbox->setMargin(30);
    vbox->addWidget(title);
    vbox->addWidget(lost);
    vbox->addWidget(score_ach);
    vbox->setSpacing(50);
    vbox->addItem(hbox);
}
/**
 * @brief if gameId = game1, onExit() creates and shows a new instance of g1_startmenu.
 * Else, if gameId = game2, it creates and shows a new instance of g2_startmenu.
 */
void gameLost::onExit()
{
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
 * @brief if gameId = game1, onAgain() creates and shows a new instance of g1_setup.
 * Else, if gameId = game2, it creates and shows a new instance of g2_setup
 */
void gameLost::onAgain(){

    if (ID == "game1"){
        g1_setup* g1_again = new g1_setup(nullptr, userJson);
        Centering::centerWidget(g1_again);
        hide();
        g1_again->show();
    }
    else {
        g2_setup *g2 = new g2_setup(userJson);
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
/**
 * @brief Initializes the bg of the widget
 */
void gameLost::initBg(){
    if(ID == "game1"){
        QString bgColor = jh->getBgColor(userJson, "game1");
        //set bg color
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, bgColor);
        setAutoFillBackground(true);
        setPalette(pal);
    }
}
/**
 * @brief gameLost::setMessage sets the message to be displayed
 * @param gameId
 */
void gameLost::setMessage(QString gameId){
    if(gameId == "game1"){
        lost->setText("You missed 4 times and your ships were compromised.");
    }if(gameId == "game2"){
        int bonus = computeBonus();
        lost->setText("You lost all your lives! You earned " + QString::number(bonus) +" XP as bonus.");
    }
    lost->setWordWrap(true);
    lost->setAlignment(Qt::AlignCenter);
}

/**
 * @brief gameLost::computeBonus, computes the bonus points earned in game 2
 * @return int, the bonus points
 */
int gameLost::computeBonus(){
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

