/**
* \file SignInPage.h
* \brief The sign in widget
*
* This class allows a registered user to enter the platform.
* It also uses jsonhandler.cpp as a helper class to authenticate the user.
*/

#ifndef SIGNINPAGE_H
#define SIGNINPAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "account.h"
#include "jsonhandler.h"

class signinPage : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief signingPage constructor
     * \param parent, a pointer to the parent widget
     */
    explicit signinPage(QWidget *parent = nullptr);

signals:
private:
    QLabel *username;   //User's registered username
    QLabel *pass;       //User's registered password
    QPushButton *back;  //back button
    QPushButton *signin;//sign in button

    QLineEdit *usernametxt; //text edit widget
    QLineEdit *passtxt;     //text edit widget

    account *acc;
    jsonhandler *json;      //jsonhandler instance

private:
    /**
    * \brief Sets the widget of the grid layout
    * \param *Grid, a pointer to a grid layout
    */
    void setGridLayout(QGridLayout *grid);
    /**
    * \brief Checks whether the username or passwords inputs are empty or not
    *
    * notEmpty() displays a "Login Failed" QMessageBox if any of the entries are empty
    */
    bool notEmpty();

private slots:
    /**
     * \brief returns to the previous window. In this case, it is Scene1.cpp
     */
    void goBack();
    /**
    * \brief Validates the user.
    * \return QJsonObject of the user in case of successful validation. Returns an empty json object otherwise.
    *
    * This function checks whether the username and password entries match a registered user
    */
    QJsonObject validateUser();

    /**
     * \brief Displays the account window
     *
     * If the user is valid, this function displays the next window, the Account window.
     */
    void signIn();
};

#endif // SIGNINPAGE_H
