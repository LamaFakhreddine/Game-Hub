#ifndef G2_SETUP_H
#define G2_SETUP_H

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include "jsonhandler.h"
#include "butg.h"
#include "butp.h"
#include "butb.h"
#include "butblack.h"
#include "gamelost.h"

class g2_setup : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
      * \brief g2_setup constructor
      * \param json, the player's QJsonObject, initialized to an empty json object
      */
    explicit g2_setup(QJsonObject json = {});

signals:
private:
    int pos = 5;
    /**
     * \brief updates falling disks' speed based on current score
     * \param score
     */
    void checkSpeed(int score);

    QJsonObject userJson;
    QString bgColor;
    jsonhandler *jh = new jsonhandler();
    QTimer *tim1;
    QTimer* tim2;
    butg *bg;
    butp *bp;
    butb *bb;
    butblack *bblack1;
    butblack *bblack2;
    butblack *bblack3;
    QGraphicsPixmapItem* item1;
    QGraphicsPixmapItem* item2;
    QGraphicsPixmapItem* item3;
    int y;

    bool left, down, right, gend = false;

    QLabel* time_lbl;
    QTimer *gtimer1; //signals every 1s to update the time displayed
    QTimer *gtimer2; //signals end of game period (10min, 5 min, etc...)
    QMediaPlayer* bgMusic;//background music
    QMediaPlayer* popSFX;//pop sound effects

    int misses = 0;
    int lives_num;
    int maxScore = 150;
    int total = 0;
    int bonus = 0;

    bool bl1, bl2, bl3 = false;     // boolean variables gor black buttons
    int g_hit, p_hit, b_hit = 0;



    QGraphicsSimpleTextItem *targetScore;
    QGraphicsSimpleTextItem *currscore;
    QGraphicsSimpleTextItem *lives;
    QGraphicsSimpleTextItem *targetScoretxt;
    QGraphicsSimpleTextItem *currscoretxt;
    QGraphicsSimpleTextItem *livestxt;

    /**
     * @brief initTotal, initializes the score to the bonus from the previous game
     * @return integer, the bonus points
     */
    int initTotal();
    /**
    * \brief calculates and updates the total score
    */
    void updateTotal(int add);
    /**
     * \brief sets time for timer to create falling disks based on current score
     * \param score
     */
    void confirmTime(int pos);
    /**
     * \brief sets timer limit based on userJson difficulty
    */
    int getTimer();
    /**
    * \brief Checks if the player lost yet or not (number of misses)
    */
    void checkMisses();
    /**
     * \brief plays the pop SFX on keypressevent
     */
    void playPopSounds();
    /**
     * \brief initBg, initializes bg image as specified in user json object.
     */
    void initBg();
 /**
     * \brief changes target score  based on selected game difficulty
     */
    void changeMaxScore();

    /**
     * \brief adds a butblack object at specified px falling with displacement pos
     * \param px, x-axis coordinate
     * \param pos, displacement of fall
     * \return
     */
    butblack* addBBlack(int px, int pos);


private slots:
    /**
    * \brief creates an instance of gamelost when the player loses
    */
    void endGame();
    /**
    * \brief shoots disks when the correct keys are pressed and turns them grey
    */
    void keyPressEvent(QKeyEvent *event);
    /**
    * \brief updates the timer displayed on the screen
    */
    void updateTimer();
    /**
    * \brief creates instances of butb, butg, and butp randomly
    */
    void fallg();

};

#endif // G2_SETUP_H
