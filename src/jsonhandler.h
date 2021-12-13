/**
  * \file jsonhandler.h
  * \brief A class that allows us to perform queries on the json file or a json object
  */
#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QList>
#include <bits/stdc++.h>
#include <QtAlgorithms>

class jsonhandler : public QObject
{
    Q_OBJECT
public:

    QString userPath = "./data.json";//path to data.json file which includes the registered users
    QString questsPath = "./questions.json"; //path to questions.json which includes the questions for Battleships.
    QJsonArray userarr;//An array that stores all the users of data.json

    /**
     * \brief jsonhandler constructor
     * \param parent, a pointer to a QObject, initally a nullptr.
     *
     * The constructor creates an instance of jsonhandler class and calls the readfile function with userPath passed as an argument.
     * The result of readFile is stored in userarr
     */
    explicit jsonhandler(QObject *parent = nullptr);

public:
    /**
     * \brief a function that opens a file, reads it, and stores its data in a QJSonArray
     * \param path, a QString containing the path to the json file.
     * \return QJsonArray containing the result of readFile.
     */
    QJsonArray readFile(QString path);
    /**
     * \brief a function that writes to a file
     * \param path, a QString containing the path to the json file.
     */
    void writeFile(QString path);
    /**
     * \brief a function that updates a user QJsonObject in jsonhandler::userarr
     * \param userjson, the QJsonObject to be updated.
     */
    void updateUserarr(QJsonObject userjson);
    /**
     * @brief updateBonus, updates the bonus points of a user in game 2
     * @param userjson
     * @param bonus
     * @return the new updated json object
     */
    QJsonObject updateBonus(QJsonObject userjson, int bonus);
    /**
     * \brief a function that checks whether the username and password match the credentials of the registered user
     * \param username (QString).
     * \param password (QString).
     * \return QJsonObject containing the user with matching username and password. Returns an empty object otherwise.
     */
    QJsonObject checkUser(QString username, QString password);
    /**
     * \brief Overloaded checkUser function that checks if the username is taken or not
     * \param username (Qstring)
     * \return bool, true in case the user is taken, false otherwise.
     */
    bool checkUser(QString username);
    /**
     * \brief a function that inserts a new user QJsonObject in jsonhandler::userarr and writes the updated array to data.json
     * \param userjson, the new QJsonObject to be added.
     */
    void insertUser(QJsonObject userjson);
    /**
     * \brief gets the highscore of a user in either Battleships or Shooting Discs.
     * \param userjson, a QJsonObject of a given user.
     * \param gameId, a QString containing game ID.
     * \return int, the highscore
     */
    int getHighscore(QJsonObject userjson, QString gameId);
    /**
     * \brief gets the scores arry of a user in either Battleships or Shooting Discs.
     * \param userjson, a QJsonObject of a given user.
     * \param gameId, a QString containing game ID.
     * \return QJsonArray, the scores array
     */
    QJsonArray getScoresArr(QJsonObject userjson, QString gameId);
    /**
     * \brief adds the new score to the user's scores array in either Battleships or Shooting Discs.
     * \param userjson, a QJsonObject of a given user.
     * \param newScore, int, the new score.
     * \param gameId, a QString containing game ID.
     * \return QJsonArray, the updated scores array
     */
    QJsonObject updateScores(QJsonObject userjson, int newScore, QString gameId);
    /**
     * \brief retrieves the global highscore of a game and computes the rank of the player
     * \param hs, int, the highscore of the player.
     * \param gameID, the ID of the game
     * \return QJsonObject containing the global highscore and player rank.
     */
    QJsonObject getGlobalHSAndRank(int hs, QString gameID);
    /**
     * \brief gets the background color as specified in the game settings in a user's QJsonObject
     * \param userjson, a QJsonObject of a given user
     * \param gameID, the ID of the game
     * \return QString containing the bg color in the following format '#hexrepresentation'
     */
    QString getBgColor(QJsonObject userjson, QString gameID);
    /**
     * @brief getBgImg, retrieves the path to the background image in userjson
     * @param userjson
     * @param gameID
     * @return the path to the bg img
     */
    QString getBgImg(QJsonObject userjson, QString gameID);
    //void updateUserarr(QJsonObject userjson);
    //QJsonObject updateScores(QJsonObject userjson, int newScore, QString gameId);

signals:

};

#endif // JSONHANDLER_H
