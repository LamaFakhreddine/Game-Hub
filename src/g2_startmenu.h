/**
  * \file g2_startmenu.h
  * \brief the start menu of Shooting Disks
  */
#ifndef G2_STARTMENU_H
#define G2_STARTMENU_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"
#include "account.h"
#include "g2_settings.h"
#include "g2_setup.h"
#include "centering.h"

class g2_startmenu : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g2_startmenu constructor
      * \param parent, a pointer to a parent QWidget, initialized to a nullptr
      * \param json, the player's QJsonObject, initialized to an empty json object
      */
    explicit g2_startmenu(QWidget *parent = nullptr, QJsonObject json = {});
    QPushButton *playBtn;
    QPushButton *settingsBtn;
    QPushButton *exitBtn;
    QLabel *gameLogo;
    QVBoxLayout *vLayout;
    QJsonObject userJson;
    jsonhandler *jh = new jsonhandler();
    QGraphicsView *v1;

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

#endif // G2_STARTMENU_H
