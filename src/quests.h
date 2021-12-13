/**
  * \file quests.h
  * \brief A class that displays a QDialog of a question in Battleships game
  * This class contains queries to the questions.json file
  */
#ifndef QUESTS_H
#define QUESTS_H

#include <jsonhandler.h>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include "g1_setup.h"

class quests : public QDialog
{
    Q_OBJECT
public:
    /**
      * \brief quests constructor
      * \param parent, a pointer to a parent QWidget, initialized to a nullptr
      * \param json, a QJsonObject of a given user.
      * \param count, an int specificying the index of the question to be set
      */
    explicit quests(QWidget *parent = nullptr, QJsonObject json = {}, int count = 0);

    QLabel *header;
    QLabel *quest;
    QLabel *gameLogo;
    QPushButton *ans1;//stores answer 1
    QPushButton *ans2;//stores answer 2
    QPushButton *ans3;//stores answer 3
    QPushButton *ans4;//stores answer 4
    QVBoxLayout *answers;
    QGroupBox *anslayout;
    QGridLayout *grid;
    QMessageBox *wrng;//QMessageBox displayed in case of a wrong answer.
    QMessageBox *right;//QMessageBox displayed in case of a correct answer.
    QPushButton *cont;//default button of QMessageBox
    int diff;//difficulty extracted from userJson's settings
    int top;//topic extracted from userJson's settings
    QString topstr;//name of topic
    QString diffstr;//name of difficulty level
    bool checkAns = false;//a class attribute to check whether the user answers correctly or not
    jsonhandler *reading;
    QJsonObject topicObj;//A QJsonObject that stores the data of questions.json
    QJsonArray questarr;//a QJsonArray containing the questions of the desired difficulty and topic
    QJsonObject userJson;//the user json object
    QJsonObject toset; //question to set in the QDialog

    /**
     * \brief sets the widget of the answers layout
     */
    void createAnsBox();
    /**
     * \brief sets the widgets of the grid layout
     */
    void setGridLayout();
    /**
     * \brief maps an integer to the corresponding difficulty
     * \param d, An int indicating the difficulty level extracted from userJson
     * \return QString containing the name of the difficulty level
     */
    QString mapdiff(int d);
    /**
     * \brief maps an integer to the corresponding topic
     * \param t, An int indicating the topic extracted from userJson
     * \return QString containing the name of the topic
     */
    QString maptop(int t);
    /**
     * \brief Retrieves array of questions of a difficulty d and topic t.
     * \param d, a QString that specifies the level of difficulty of the questions
     * \param t, a QString that specifies the topic of the questions
     * \return QJsonArray that contains the questions.
     */
    QJsonArray getquest(QString d, QString t); //gets array of questions of difficulty t
    /**
     * \brief Sets the question in the QDialog
     * \param quest, a QJsonObject containing a single question.
     */
    void setquests(QJsonObject quest);
    /**
     * \brief initializes the background color of the QWidget
     * as specified in userJson.
     */
    void initBg();

signals:

public slots:
    /**
     * \brief checks whether the chosen pushbutton contains the correct answer.
     * The function displays wrng QMessageBox in case the answer is incorrect
     * and right QMessageBox otherwise.
     */
    void checkanswer1();
    /**
     * \brief checks whether the chosen pushbutton contains the correct answer.
     * The function displays wrng QMessageBox in case the answer is incorrect
     * and right QMessageBox otherwise.
     */
    void checkanswer2();
    /**
     * \brief checks whether the chosen pushbutton contains the correct answer.
     * The function displays wrng QMessageBox in case the answer is incorrect
     * and right QMessageBox otherwise.
     */
    void checkanswer3();
    /**
     * \brief checks whether the chosen pushbutton contains the correct answer.
     * The function displays wrng QMessageBox in case the answer is incorrect
     * and right QMessageBox otherwise.
     */
    void checkanswer4();
};

#endif // QUESTS_H
