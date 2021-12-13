/**
  * \file jsonhandler.cpp
  * \brief A class that allows us to perform queries on the json file or a json object
  */
#include "jsonhandler.h"
#include <QDebug>

/**
 * \brief jsonhandler constructor
 * \param parent, a pointer to a QObject, initally a nullptr.
 *
 * The constructor creates an instance of jsonhandler class and calls the readfile function with userPath passed as an argument.
 * The result of readFile is stored in userarr
 */
jsonhandler::jsonhandler(QObject *parent) : QObject(parent)
{
    userarr = readFile(userPath);
    /*
     * IMPORTANT: the program starts with scene1 > signin or signup
     * both signin and signup classes call readfile function
     * userarr will be used to keep track of all stored json objects
     * userarr will be updated as well
     * the readfile function loads the contents of the json file to userarr
     * so we can assume that at the start of the program, the userarr has all json objects.
    */
}

/**
 * \brief a function that opens a file, reads it, and stores its data in a QJSonArray
 * \param path, a QString containing the path to the json file.
 * \return QJsonArray containing the result of readFile.
 */
QJsonArray jsonhandler::readFile(QString path){
    QFile file(path); //directory
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = file.readAll();
    userarr = QJsonDocument::fromJson(data).array();
    file.close();
    return userarr;
}

/**
 * \brief a function that writes to a file
 * \param path, a QString containing the path to the json file.
 */
void jsonhandler::writeFile(QString path){
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc(userarr);
    //write to file
    file.write(doc.toJson());
    file.close();
}

/**
 * \brief a function that updates a user QJsonObject in jsonhandler::userarr
 * \param userjson, the QJsonObject to be updated.
 */
void jsonhandler::updateUserarr(QJsonObject userjson){
    QString key = userjson.value("username").toString();
    for(int i=0; i<userarr.size(); i++){
        QJsonObject user = userarr.at(i).toObject();
        if(key == user.value("username").toString()){
            userarr.replace(i, userjson);
            break;
        }
    }
}

/**
 * \brief a function that checks whether the username and password match the credentials of the registered user
 * \param username (QString).
 * \param password (QString).
 * \return QJsonObject containing the user with matching username and password. Returns an empty object otherwise.
 */
QJsonObject jsonhandler::checkUser(QString username, QString password){
    for (auto v : userarr) {
        QJsonObject user = v.toObject();
        if (user.value("username").toString() == username && user.value("password").toString() == password){
            return user;
        }
    }
    return {};
}

/**
 * \brief Overloaded checkUser function that checks if the username is taken or not
 * \param username (Qstring)
 * \return bool, true in case the user is taken, false otherwise.
 */
bool jsonhandler::checkUser(QString username){
    for (auto v : userarr) {
        QJsonObject user = v.toObject();
        if (user.value("username").toString() == username){
            return true;
        }
    }
    return false;
}

/**
 * \brief a function that inserts a new user QJsonObject in jsonhandler::userarr and writes the updated array to data.json
 * \param userjson, the new QJsonObject to be added.
 */
void jsonhandler::insertUser(QJsonObject userjson){
    //append json object to userarr
    userarr.append(userjson);
    //write to file
    writeFile(userPath);
}


/**
 * \brief gets the highscore of a user in either Battleships or Shooting Discs.
 * \param userjson, a QJsonObject of a given user.
 * \param gameId, a QString containing game ID.
 * \return int, the highscore
 */int jsonhandler::getHighscore(QJsonObject userjson, QString gameId){
    QJsonObject g = userjson.value(gameId).toObject();
    return g.value("highscore").toInt();
}

/**
 * \brief gets the scores arry of a user in either Battleships or Shooting Discs.
 * \param userjson, a QJsonObject of a given user.
 * \param gameId, a QString containing game ID.
 * \return QJsonArray, the scores array
 */
QJsonArray jsonhandler::getScoresArr(QJsonObject userjson, QString gameId){
    QJsonObject g = userjson.value(gameId).toObject();
    return g.value("scores").toArray();
}

/**
 * \brief adds the new score to the user's scores array in either Battleships or Shooting Discs.
 * \param userjson, a QJsonObject of a given user.
 * \param newScore, int, the new score.
 * \param gameId, a QString containing game ID.
 * \return QJsonArray, the updated scores array
 */
QJsonObject jsonhandler::updateScores(QJsonObject userjson, int newScore, QString gameId){
    QJsonObject g = userjson.value(gameId).toObject();
    QJsonArray scoresArr  = g.value("scores").toArray();

    scoresArr.append(newScore);
    int highscore = g.value("highscore").toInt();
    int newHighscore = (newScore > highscore)? newScore : highscore;

    g.insert("highscore", newHighscore);
    g.insert("scores", scoresArr);
    userjson.insert(gameId, g);

    updateUserarr(userjson);
    writeFile(userPath);
    return userjson;
}

/**
 * \brief retrieves the global highscore of a game and computes the rank of the player
 * \param hs, int, the highscore of the player.
 * \param gameID, the ID of the game
 * \return QJsonObject containing the global highscore and player rank.
 */
QJsonObject jsonhandler::getGlobalHSAndRank(int hs, QString gameID){
    QList<int> highscores;
    for(auto u: userarr){
        QJsonObject user = u.toObject();
        highscores.append(user.value(gameID).toObject().value("highscore").toInt());
    }

    //sort highscores QList in non-increasing order
    qSort(highscores.begin(), highscores.end(),
          [] (int a, int b){
        return a > b;
    });

    //extract global highscore and user rank
    int rank = highscores.indexOf(hs) + 1;
    int globalHS =  highscores.at(0);

    //create a json object from the results
    QJsonObject result{
      {"globalHS", globalHS},
      {"rank", rank}
    };
    return result;
}
/**
 * @brief updateBonus, updates the bonus points of a user in game 2
 * @param userjson
 * @param bonus
 * @return the new updated json object
 */
QJsonObject jsonhandler::updateBonus(QJsonObject userjson, int bonus){
    QJsonObject g = userjson.value("game2").toObject();

    g.insert("bonus", bonus);
    userjson.insert("game2", g);

    updateUserarr(userjson);
    writeFile(userPath);
    return userjson;
}

/**
 * \brief gets the background color as specified in the game settings in a user's QJsonObject
 * \param userjson, a QJsonObject of a given user
 * \param gameID, the ID of the game
 * \return QString containing the bg color in the following format '#hexrepresentation'
 */
QString jsonhandler::getBgColor(QJsonObject userjson, QString gameId){
    //extract bg ID from json object
    QJsonObject g = userjson.value(gameId).toObject();
    QJsonObject s  = g.value("settings").toObject();
    int jsonBgId = s.value("bg").toInt();

    //map id to corresponding color
    QString bgColor = "#1F4E8D";
    if(jsonBgId == 1){
        bgColor = "#7d2727";
    }else if(jsonBgId == 2){
        bgColor = "#102745";
    }
    return bgColor;
}
/**
 * @brief getBgImg, retrieves the path to the background image in userjson
 * @param userjson
 * @param gameID
 * @return the path to the bg img
 */
QString jsonhandler::getBgImg(QJsonObject userjson, QString gameId){
    QJsonObject g = userjson.value(gameId).toObject();
    QJsonObject s  = g.value("settings").toObject();
    return s.value("bg").toString();
}
