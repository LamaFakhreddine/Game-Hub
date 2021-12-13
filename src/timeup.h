/**
  * \file timeUp.h
  * \brief The time's up popup that shows when the user wins the game.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */
#ifndef TIMEUP_H
#define TIMEUP_H

#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"


class timeUp : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief timeUp constructor
     * @param parent, a pointer to a QWidget parent
     * @param json, a QJsonObject for a given user
     * @param scoreNum, the player's score.
     * @param gameId, the game's Id.
     */
    explicit timeUp(QWidget *parent = nullptr, QJsonObject json = {}, int scoreNum = 0, QString gameId = "");

    QJsonObject userJson;//updated json object
    QLabel *title;//time's up  header
    QLabel *congrats;//congratulations text in case the score is a highscore
    QLabel *text;//score text
    int score;//user score
    QString ID; //game id
    QPushButton *exitBtn;//exit button

    QVBoxLayout *vLayout;
    jsonhandler *jh = new jsonhandler();

    /**
     * @brief Initializes the bg of the widget
     */
    void initBg();
    /**
     * @brief checks if the score is a new highscore.
     * If the condition is true, display congrats QLabel.
     */
    void checkScore();
    /**
     * @brief computeBonus, computes the bonus points a user gets in game 2
     * @return an integer, the bonus points. If bonus points is a negative number, it returns 0.
     */
    int computeBonus();

signals:
private slots:
    /**
     * @brief if gameId = game1, onExit() creates and shows a new instance of g1_startmenu.
     * Else, if gameId = game2, it creates and shows a new instance of g2_startmenu.
     */
    void onExit();
};

#endif // TIMEUP_H
