/**
  * \file noTurns.cpp
  * \brief The game over popup that shows when the number of turns reaches zero.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */
#include "noturns.h"

/**
 * @brief noTurns constructor
 * @param parent, a pointer to a QWidget parent
 * @param json, a QJsonObject for a given user
 * @param scoreNum, the player's score.
 */
noTurns::noTurns(QWidget *parent, QJsonObject json,int scoreNum) : QWidget(parent)
{

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

    score = scoreNum;
    userJson = jh->updateScores(json, score, "game1");//This is where the json object is updateed using jsonhandler class.
    initBg();

    //set title
    title = new QLabel();
    QPixmap bg(QPixmap(":/game-over.png"));
    title->setPixmap(bg.scaled(390,55));
    title->setAlignment(Qt::AlignCenter);

    oops = new QLabel("OOPS! You ran out of turns");
    oops->setWordWrap(true);
    oops->setAlignment(Qt::AlignCenter);
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

    QObject :: connect(exit, SIGNAL(clicked()), this, SLOT(onExit()));
    QObject :: connect(again, SIGNAL(clicked()), this, SLOT(onAgain()));

}
/**
 * @brief sets the widgets of a horizontal box layout
 * @param hbox, a pointer to a QHBoxLayout.
 */
void noTurns::setHBoxLayout(QHBoxLayout *hbox)
{
    hbox->addWidget(again);
    hbox->setSpacing(150);
    hbox->addWidget(exit);

}
/**
 * @brief sets the widgets of a vertical box layout
 * @param vbox, a pointer to a QVBoxLayout.
 */
void noTurns::setVBoxLayout(QVBoxLayout *vbox)
{
    vbox->setMargin(30);
    vbox->addWidget(title);
    vbox->addWidget(oops);
    vbox->addWidget(score_ach);
    vbox->setSpacing(50);
    vbox->addItem(hbox);
}

/**
 * @brief Returns to g1_startmenu
 */
void noTurns::onExit()
{
    g1_startmenu* menu = new g1_startmenu(nullptr, userJson);
    Centering::centerWidget(menu);
    hide();
    menu->show();
}
/**
 * @brief Returns to g1_setup widget
 */
void noTurns::onAgain(){

    g1_setup* g1_again = new g1_setup(nullptr, userJson);
    Centering::centerWidget(g1_again);
    hide();
    g1_again->show();
}

/**
 * @brief Initializes the bg of the widget
 */
void noTurns::initBg(){
    QString bgColor = jh->getBgColor(userJson, "game1");
    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}
