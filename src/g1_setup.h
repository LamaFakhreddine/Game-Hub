#ifndef G1_SETUP_H
#define G1_SETUP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QMediaPlayer>
#include "jsonhandler.h"
#include "quests.h"
#include "gamelost.h"
#include "noturns.h"

class g1_setup : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g1_setup constructor
      * \param parent, a pointer to a parent QWidget, initialized to a nullptr
      * \param json, the player's QJsonObject, initialized to an empty json object
      */
    explicit g1_setup(QWidget *parent = nullptr, QJsonObject json = {});

signals:
private:

    int press_count = 0;
    int wrong = 0;
    int correct_tmp = 0;

    QString pngs1[4];
    QString pngs2[2];

    QLabel* goodcp;
    QLabel* badcp;
    QLabel* design;
    QLabel* score;
    int scoreNum = 0;
    QLabel* highscore;
    QLabel* time;
    QLabel *turns;

    QPushButton* exit_pb;
    QPushButton* settings_pb;
    QPushButton* replay_pb;

    QGridLayout* scene;
    QGridLayout* player_grid;
    QGridLayout* cpu_grid;
    QGridLayout* cpu_backgrid;

    QVBoxLayout* vert1;
    QVBoxLayout* vert2;
    QHBoxLayout* horz;

    QMediaPlayer *bgMusic;
    QMediaPlayer *explosionSFX;
    QTimer *timer1; //signals every 1s to update the time displayed
    QTimer *timer2; //signals end of game period (10min, 5 min, etc...)
    QJsonObject userJson;
    QString bgColor;
    jsonhandler *jh = new jsonhandler();

    int shipcount = -1;

private:

    /**
    * \brief Sets the main grid layout
    */
    void setGridLayout(QGridLayout *grid);
    /**
     * \brief Sets the player and enemy grid layouts
     */
    void setButtonGrid(QGridLayout *grid);
    /**
    * \brief Sets the vertical layout of vbox
    * \param vbox, the QVBoxLayout to set
    * \param label, titles of player and enemy grids
    * \param grid, main grid
    */
    void setVerticalLayout(QVBoxLayout *vbox, QLabel* label, QGridLayout* grid);
    /**
    * \brief inserts segmented ships into grid
    */
    void insertShipSpan(int row, int min, int max, QGridLayout* grid, QString arr[]);
    /**
    * \brief Inserts ship into grid at position [i,j]
    */
    void insertShip(int i, int j, QString png, QGridLayout *grid);
    /**
     * \brief initializes the background color of the QWidget
     * as specified in userJson.
     */
    QString initBg();
    /**
     * \brief retrieves user's highscore from userJson object
     */
    int getHighscore();
    /**
     * \brief updates user's displayed score
     * \param scoreNum, the user's current score
     */
    void updateScore(int scoreNum);
    /**
     * \brief updates user's displayed remaining turns
     */
    void updateTurns();
    /**
     * @brief plays explosion SFX
     */
    void playExplosionSounds();
    /**
     * \brief returns the pushButton found at grid[i,j]
     * \param grid
     * \param i
     * \param j
     */
    QPushButton *findPB(QGridLayout *grid, int i, int j);
    /**
     * \brief retrieves timer limit from userJson object
     */
    int getTimer();
    /**
     * \brief declares user's win when 7 answers are correct
     */
    void winGame();
    /**
     * \brief declares user's loss when at least 4 answers are wrong
     */
    void loseGame();
    /**
     * \brief declares user's loss when user has no more turns
     */
    void loseTurns();



private slots:
    /**
     * \brief navigates to g1_startmenu
     */
    void onExit();
    /**
     * \brief navigates to g1_settings
     */
    void onSettings();
    /**
     * \brief starts a new game
     */
    void onReplay();
    /**
     * \brief updates displayed remaining time
     */
    void updateTimer();
    /**
     * \brief ends the game
     */
    void endGame();

    void pb0Pressed();
    void pb1Pressed(); //ship
    void pb2Pressed();
    void pb3Pressed();
    void pb4Pressed();  //ship
    void pb5Pressed();  //ship
    void pb6Pressed();  //ship
    void pb7Pressed();  //ship
    void pb8Pressed();
    void pb9Pressed();
    void pb10Pressed();
    void pb11Pressed();
    void pb12Pressed();  //ship
    void pb13Pressed();  //ship
    void pb14Pressed();
    void pb15Pressed();


};

#endif // G1_SETUP_H
