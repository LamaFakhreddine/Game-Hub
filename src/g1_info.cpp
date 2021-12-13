/**
 * \file g1_info.cpp
 * \brief this class is a widget that informs the player on how to play Battleships.
 */
#include "g1_info.h"

/**
  * \brief g1_info constructor
  * \param parent, a pointer to a QWidget parent
  * \param json, the QJsonObject for a given user
  */
g1_info::g1_info(QWidget *parent, QJsonObject json) : QWidget(parent)
{
    setStyleSheet("QLabel{font-size:22px;"
                  "font-weight: normal;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:24px;"
                  "font-weight:bold;"
                  "color: #FF5454;"
                  "width:80px;"
                  "height: 35px;}"
                  "QPushButton:hover{"
                  "border-right:5px solid #FF5454;"
                  "border-bottom:5px solid #FF5454;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}");

    setFixedSize(600, 600);
    userJson = json;
    initBg();

    hi = new QLabel("Hi " + userJson.value("username").toString() + ",");
    hi->setAlignment(Qt::AlignCenter);

    info = new QLabel("Welcome to Battleships!\n\nHere's how you play the game:\nYour ships are under attack. You will fight to save them by trying to answer some programming questions. Every time you "
                      "answer a question correctly, you hit your enemy's ship. But, if you answer wrong, your enemy hits one of your ships! If you miss your enemy's ship, nothing happens, but you lose a turn."
                      "You have 10 turns per game. To win, you should answer at least 7 questions right within the time limit. If you answer 4 wrong, you lose...\nNow go ahead, ATTACK!\n\n");
    info->setWordWrap(true);
    info->setAlignment(Qt::AlignCenter);

    start = new QPushButton("Start");

    vbox = new QVBoxLayout();
    setVBoxLayout(vbox);
    setLayout(vbox);

    QObject :: connect(start, SIGNAL(clicked()), this, SLOT(onStart()));
}
/**
 * @brief sets the widgets of a vertical box layout
 * @param vbox, a pointer to a QVBoxLayout.
 */
void g1_info::setVBoxLayout(QVBoxLayout *vbox){

    vbox->addWidget(hi);
    vbox->addWidget(info);
    vbox->addWidget(start);
}
/**
 * @brief Navigates to g1_setup
 */
void g1_info::onStart(){

    g1_setup* g1 = new g1_setup(nullptr, userJson);
    Centering::centerWidget(g1);
    g1->show();
    this->hide();
}
/**
 * @brief initializes the background color of the widget
 */
void g1_info::initBg(){
    QString bgColor = jh->getBgColor(userJson, "game1");
    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}
