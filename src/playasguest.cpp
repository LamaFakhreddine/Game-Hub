/**
* \file PlayAsGuest.cpp
* \brief The play as guest widget
*
* This class allows a temporary user to access the platform.
* The user json object created in this class is only temporary, and it is not stored in the data.json file
*/

#include "playasguest.h"
#include "scene1.h"
#include "account.h"
#include <QFont>
#include "centering.h"

/**
 * \brief playasguest constructor
 * \param parent, a pointer to the parent widget
 */
playasguest::playasguest(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background-color: #fff}");

    next = new QPushButton("Next");
    back = new QPushButton("Back");
    username = new QLabel("Username");
    usrtxt = new QLineEdit();
    comment = new QLabel("This is a temporary username");
    comment->setStyleSheet("font-style: italic;");

    QGridLayout *Grid = new QGridLayout();
    setGridLayout(Grid);
    setLayout(Grid);

    QObject :: connect(back, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject :: connect(next, SIGNAL(clicked()), this, SLOT(goNext()));
}

/**
* \brief Sets the widget of the grid layout
* \param *Grid, a pointer to a grid layout
*/
void playasguest ::  setGridLayout(QGridLayout *grid){
    grid->addWidget(username, 0, 0);
    grid->addWidget(usrtxt, 0, 1);

    grid->addWidget(comment, 1, 0, 1, 0);
    grid->addWidget(back, 2, 0);
    grid->addWidget(next, 2, 2);
}

/**
 * \brief returns to the previous window. In this case, it is Scene1.cpp
 */
void playasguest :: goBack(){
    hide();
    scene1 *intro = new scene1();
    Centering::centerWidget(intro);
    intro->show();

}

/**
* \brief Constructs a user QJsonObject
* \return QJsonObject, the constructed json object. The constructed QJsonObject is empty in case of invalid entries
*
* This function takes the inputs of the play as guest form and checks whether the username is taken or not.
* In case the the username is taken, the function returns an empty QJsonObject.
* Otherwise, it returns a QJsonObject with reduced features.
* (the reduced features only include username, game1, and game2)
*/
QJsonObject playasguest :: storeinfo(){

    QString un = usrtxt->text(); //username

    if(jh->checkUser(un)){
        QMessageBox :: information(this, "Sign in Failed", "Username already taken");
        return {};
    }

    QJsonObject settings {
        {"difficulty", 0},
        {"topic", 0},
        {"bg", 0}
    };

    QJsonObject game1 {
        {"settings", settings},
        {"scores" , QJsonArray {}},
        {"highscore", 0}
    };

    QJsonObject game2 {
        {"settings", settings},
        {"scores" , QJsonArray {}},
        {"highscore", 0}
    };

    QJsonObject userobj {
        {"username" , un},
        {"game1", game1},
        {"game2", game2}
     };
    return userobj;
}

/**
 * \brief navigates to the next window. In this case, it is Account.cpp
 */
void playasguest::goNext(){
    QJsonObject userjson = storeinfo();
    if(!userjson.isEmpty()){
        account *acc = new account(nullptr, userjson);
        Centering::centerWidget(acc);
        acc->show();
        this->hide();
    }
}


