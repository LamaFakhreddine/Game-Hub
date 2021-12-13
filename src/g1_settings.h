/**
  * \file g1_settings.h
  * \brief A widget that displays a game settings window.
  */
#ifndef G1_SETTINGS_H
#define G1_SETTINGS_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"

class g1_settings : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g1_settings constructor
      * \param parent, a pointer to a parent QWidget, initialized to a nullptr
      * \param json, the player's QJsonObject, initialized to an empty json object
      */
    explicit g1_settings(QWidget *parent = nullptr, QJsonObject json = {});

    QPushButton *backBtn;
    QLabel *title;
    QLabel *diffLabel;
    QLabel *topicLabel;
    QLabel *bgLabel;
    QPushButton *easyBtn;
    QPushButton *mediumBtn;
    QPushButton *hardBtn;
    QGroupBox *difficultyBox;
    QHBoxLayout *diffBoxLayout;
    QPushButton *t1Btn;
    QPushButton *t2Btn;
    QPushButton *t3Btn;
    QGroupBox *topicBox;
    QHBoxLayout *topicBoxLayout;
    QPushButton *bg1Btn;
    QPushButton *bg2Btn;
    QPushButton *bg3Btn;
    QGroupBox *bgBox;
    QHBoxLayout *bgBoxLayout;
    QGridLayout *grid;

    QJsonObject userJson;
    jsonhandler *jh = new jsonhandler();

    /**
    * \brief Sets the widget of the grid layout
    */
    void setGridLayout();
    /**
     * \brief groups the difficulty buttons
     */
    void createDifficultyBox();
    /**
     * \brief groups the topic buttons
     */
    void createTopicBox();
    /**
     * \brief groups the background buttons
     */
    void createBgBox();
    /**
     * \brief initializes the background color of the QWidget
     * as specified in userJson.
     */
    void initBg();

signals:

private slots:
    /**
     * \brief changes the background color to the option chosen by the player.
     * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
     */
    void changeBg(QString bgColor="#1F4E8D");
    /**
     * \brief changes the difficulty level to the option chosen by the player.
     * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
     */
    void changeDifficulty(int d);
    /**
     * \brief changes Battleships question topic to the option chosen by the player.
     * This function updates the settings of the userJson QJsonObject to store the player's settings and changes
     */
    void changeTopic(int t);
    /**
     * \brief Navigates to the previous screen, the start menu.
     */
    void goBack();

};

#endif // G1_SETTINGS_H
