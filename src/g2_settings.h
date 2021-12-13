/**
  * \file g2_settings.h
  * \brief This class creates the settings QWidget for Shooting discs.
  * In the settings, the user can change the game difficulty and background image.
  * Changing the difficulty changes the target score and lives.
  * Changing the background updates the image of the gameplay ONLY.
  * (unlike Battleships, the start menu and settings do not change backgrounds).
  */

#ifndef G2_SETTINGS_H
#define G2_SETTINGS_H

#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"

class g2_settings : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g2_settings constructor
      * \param parent, a nullptr to the QWidget parent
      * \param json, the QJsonObject for a given user.
      */
    explicit g2_settings(QWidget *parent = nullptr, QJsonObject json = {});

    QPushButton *backBtn;
    QLabel *title;
    QLabel *diffLabel;
    QLabel *topicLabel;
    QLabel *bgLabel;
    QPushButton *easyBtn;
    QPushButton *mediumBtn;
    QPushButton *hardBtn;
    QGroupBox *difficultyBox;//group of difficulty buttons
    QHBoxLayout *diffBoxLayout;
    QPushButton *bg1Btn;
    QPushButton *bg2Btn;
    QPushButton *bg3Btn;
    QGroupBox *bgBox;//group of background buttons
    QHBoxLayout *bgBoxLayout;
    QGridLayout *grid;

    QJsonObject userJson;
    jsonhandler *jh = new jsonhandler();

    /**
     * @brief setGridLayout, sets the widgets of a grid layout
     */
    void setGridLayout();
    /**
     * @brief createDifficultyBox, creates the box of difficulty buttons
     */
    void createDifficultyBox();
    /**
     * @brief createBgBox, creates the box of bg buttons
     */
    void createBgBox();


signals:

private slots:
    /**
     * @brief changeBg, changes the bg image path in the user json
     * @param bgImg, the path to the image.
     */
    void changeBg(QString bgImg);
    /**
     * @brief changeDifficulty, changes the difficulty of the game in the user json
     * @param d, the difficulty level (easy = 0, medium = 1, hard = 2)
     */
    void changeDifficulty(int d);
    /**
     * @brief goBack, returns to g2_startmenu
     */
    void goBack();
};

#endif // G2_SETTINGS_H
