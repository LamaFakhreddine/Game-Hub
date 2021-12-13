/**
  * \file noTurns.h
  * \brief The game over popup that shows when the number of turns reaches zero.
  * This class also adds the new score to the scores array and updates the highscore if necessary in the player's json object.
  */
#ifndef NOTURNS_H
#define NOTURNS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "g1_startmenu.h"
#include "g1_setup.h"
#include "centering.h"
#include "jsonhandler.h"

class noTurns : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief noTurns constructor
     * @param parent, a pointer to a QWidget parent
     * @param json, a QJsonObject for a given user
     * @param scoreNum, the player's score.
     */
    explicit noTurns(QWidget *parent, QJsonObject json,int scoreNum);

private:

    QJsonObject userJson; //The updated user json
    int score;//user score
    QLabel* score_ach;//Text displaying the score.
    QLabel *title; //Game Over header
    QLabel* oops;//Text displaying a message.
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

private slots:
    /**
     * @brief Returns to g1_setup widget
     */
    void onAgain();
    /**
     * @brief Returns to g1_startmenu
     */
    void onExit();

signals:

};

#endif // NOTURNS_H
