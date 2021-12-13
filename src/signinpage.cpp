/**
* \file SignInPage.cpp
* \brief The sign in widget
*
* This class allows a registered user to enter the platform.
* It also uses jsonhandler.cpp as a helper class to authenticate the user.
*/

#include "centering.h"
#include "signinpage.h"
#include "signuppage.h"
#include "scene1.h"
#include <QMessageBox>
#include <QDebug>

/**
 * \brief signinPage constructor
 * \param parent, a pointer to the parent widget
 */
signinPage::signinPage(QWidget *parent) : QWidget(parent)
{
    json = new jsonhandler();

    username = new QLabel("Username");
    pass = new QLabel("Password");

    back = new QPushButton("Back");
    signin = new QPushButton("Sign in");

    usernametxt = new QLineEdit();
    passtxt = new QLineEdit();
    passtxt-> setEchoMode(QLineEdit::Password);

    QGridLayout *Grid = new QGridLayout();

    setGridLayout(Grid);
    setLayout(Grid);

    setStyleSheet("QWidget{background-color: #fff;}");

    setFixedSize(300,200);
    QObject :: connect(back, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject :: connect(signin, SIGNAL(clicked()), this, SLOT(signIn()));
}

/**
* \brief Sets the widget of the grid layout
* \param *Grid, a pointer to a grid layout
*/
void signinPage ::  setGridLayout(QGridLayout *grid){
    grid->setVerticalSpacing(10);
    grid->addWidget(username, 0, 0);
    grid->addWidget(usernametxt,0, 1, 1, 2);
    grid->addWidget(pass, 1, 0);
    grid->addWidget(passtxt, 1, 1, 1, 2);
    grid->addWidget(back, 2, 1);
    grid->addWidget(signin, 2, 2);
}

/**
* \brief Checks whether the username or passwords inputs are empty or not
*
* notEmpty() displays a "Login Failed" QMessageBox if any of the entries are empty
*/
bool signinPage :: notEmpty(){
    if (usernametxt->text() == nullptr || passtxt->text() == nullptr){
        QMessageBox :: information(this, "Login Failed", "Missing required information.");
        return false;
    }
    return true;
}

/**
 * \brief returns to the previous window. In this case, it is Scene1.cpp
 */
void signinPage :: goBack(){
    hide();
    scene1 *intro = new scene1();
    Centering::centerWidget(intro);
    intro->show();

}
/**
* \brief Validates the user.
* \return QJsonObject of the user in case of successful validation. Returns an empty json object otherwise.
*
* This function checks whether the username and password entries match a registered user
*/
QJsonObject signinPage :: validateUser(){
    QString un = usernametxt->text();
    QString pw = passtxt->text();
    QJsonObject user = {};

    if (notEmpty()){
        //search for user in json file
        //if exists, return it,
        //if not, return an empty object
        user = json->checkUser(un, pw);
        if(user.isEmpty()){
            QMessageBox :: information(this, "Login Failed", "Incorrect username or password");
        }
    }
    return user;
}

/**
 * \brief Displays the account window
 *
 * If the user is valid, this function displays the next window, the Account window.
 */
void signinPage:: signIn(){

    QJsonObject jobj = validateUser();
    if (!jobj.isEmpty()){
        acc = new account(nullptr,jobj);
        hide();
        Centering::centerWidget(acc);
        acc->show();
        // navigate to next page
        return;

    }
}
