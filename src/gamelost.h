/**
  * \file gameLost.h
  * \brief The game over popup that shows when the user wins the game.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */

#ifndef GAMELOST_H
#define GAMELOST_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "g1_startmenu.h"
#include "g1_setup.h"
#include "centering.h"
#include "jsonhandler.h"
#include "g2_setup.h"
#include "g2_startmenu.h"

class gameLost : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief gameLost constructor
     * @param parent, a pointer to a QWidget parent
     * @param json, a QJsonObject for a given user
     * @param scoreNum, the player's score.
     * @param gameId, a QString representing game Id. "game1" means Battleships and "game2" means Shooting Discs
     */
    explicit gameLost(QWidget *parent, QJsonObject json,int scoreNum, QString gameId);

private:

    QJsonObject userJson;//updated json object
    QLabel *title;//Game Over header
    QLabel* lost;//Defeat text
    QLabel* score_ach;//score text
    int score;//user score
    QString ID;

    QPushButton* again;//play again button
    QPushButton* exit;//exit button

    QHBoxLayout* hbox;
    QVBoxLayout* mainVbox;
    jsonhandler *jh = new jsonhandler();

    QString g; //which game we are dealing with


    /**
     * @brief sets the widgets of a horizontal box layout
     * @param hbox, a pointer to a QHBoxLayout.
     */
    void setHBoxLayout(QHBoxLayout* hbox);
    /**
     * @brief sets the widgets of a vertical box layout
     * @param hbox, a pointer to a QVBoxLayout.
     */
    void setVBoxLayout(QVBoxLayout* vbox);
    /**
     * @brief Initializes the bg of the widget
     */
    void initBg();
    /**
     * @brief setMessage, sets the message to be displayed.
     * @param gameId
     */
    void setMessage(QString gameId);
    /**
     * @brief computeBonus, computes the bonus points a user gets in game 2
     * @return an integer, the bonus points. If bonus points is a negative number, it returns 0.
     */
    int computeBonus();

private slots:
    /**
     * @brief if gameId = game1, onAgain() creates and shows a new instance of g1_setup.
     * Else, if gameId = game2, it creates and shows a new instance of g2_setup
     */
    void onAgain();
    /**
     * @brief if gameId = game1, onExit() creates and shows a new instance of g1_startmenu.
     * Else, if gameId = game2, it creates and shows a new instance of g2_startmenu.
     */
    void onExit();

signals:

};

#endif // GAMELOST_H
