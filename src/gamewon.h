/**
  * \file gameWon.h
  * \brief The game won popup that shows when the user wins the game.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */

#ifndef GAMEWON_H
#define GAMEWON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "g1_setup.h"
#include "g1_startmenu.h"
#include "centering.h"
#include "jsonhandler.h"

class gameWon : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief gameWon constructor
     * @param parent, a pointer to a QWidget parent
     * @param json, a QJsonObject for a given user
     * @param scoreNum, the player's score.
     * @param gameId, a QString representing game Id. "game1" means Battleships and "game2" means Shooting Discs
     */
    explicit gameWon(QWidget *parent, QJsonObject json, int scoreNum, QString gameId);

private:
    int score; // user score
    QString ID; //game ID
    QJsonObject userJson;//updated json object
    QLabel *title;//Game won header
    QLabel* score_ach;//text displaying the score
    QLabel* congrats;//text displaying victory message
    QPushButton* again;//play again button
    QPushButton* exit;//exit button
    QHBoxLayout* hbox;
    QVBoxLayout* mainVbox;
    jsonhandler *jh = new jsonhandler();

    /**
     * @brief sets the widgets of a horizontal box layout
     * @param hbox, a pointer to a QHBoxLayout.
     */
    void setHBoxLayout(QHBoxLayout* hbox);
    /**
     * @brief sets the widgets of a vertical box layout
     * @param vbox, a pointer to a QVBoxLayout.
     */
    void setVBoxLayout(QVBoxLayout* vbox);
    /**
     * @brief Initializes the bg of the widget
     */
    void initBg();
    /**
     * @brief sets the text for congrats QLabel according to which game the user is playing.
     * @param gameId, QString which specifies the game we are in.
     */
    void setMessage(QString gameId);

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

};

#endif // GAMEWON_H
