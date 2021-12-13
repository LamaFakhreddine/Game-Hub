/**
  * \file g1_startmenu.h
  * \brief the start menu of Battleships
  */
#ifndef G1_STARTMENU_H
#define G1_STARTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>
#include "jsonhandler.h"
#include "account.h"
#include "g1_info.h"

class g1_startmenu : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g1_startmenu constructor
      * \param parent, a pointer to a parent QWidget, initialized to a nullptr
      * \param json, the player's QJsonObject, initialized to an empty json object
      */
    explicit g1_startmenu(QWidget *parent = nullptr, QJsonObject json = {});
    QPushButton *playBtn;
    QPushButton *settingsBtn;
    QPushButton *exitBtn;
    QLabel *gameLogo;
    QVBoxLayout *vLayout;
    QJsonObject userJson;
    jsonhandler *jh = new jsonhandler();

    /**
     * \brief initializes the background color of the QWidget
     * as specified in userJson.
     */
    void initBg();

signals:

private slots:
    /**
     * \brief Proceeds to gameplay when player presses F1 key
     * \param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * \brief Navigates to gameplay when player clicks play button
     */
    void onPlay();
    /**
     * \brief Navigates to game settings
     */
    void onSettings();
    /**
     * \brief navigates back to account
     */
    void onExit();

};

#endif // STARTMENU_H
