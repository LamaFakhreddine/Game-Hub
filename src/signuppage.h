/**
  * \file SignUpPage.h
  * \brief The sign up widget
  *
  * This class allows the user to register in the platform.
  * It creates a user QJsonObject and stores it in the data.json file.
  */

#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "account.h"
#include "jsonhandler.h"


class signupPage : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief signupPage constructor
     * \param parent, a pointer to the parent widget
     */
    explicit signupPage(QWidget *parent = nullptr);

signals:
private:
    QLabel *firstName;
    QLabel *lastName;
    QLabel *username;
    QLabel *pass;
    QLabel *passConfirm;
    QLabel *dob;
    QLabel *gender;
    QLabel *phone;
    QLabel *profilePic;
    QPushButton *changepicBtn;
    QRadioButton *maleRB;
    QRadioButton *femaleRB;
    QRadioButton *otherRB;
    QGroupBox *groupBox;
    QVBoxLayout *box;

    QPushButton *signup; //sign up button
    QPushButton *back;  //back button

    QLineEdit *fntxt;
    QLineEdit *lntxt;
    QLineEdit *usernametxt;
    QLineEdit *passtxt;
    QLineEdit *passConftxt;
    QComboBox *code;
    QLineEdit *number;
    QDateEdit *date;

    QString *code_nb; //stores country code and phone number in the following format: +code-phonenumber
    QString *picPath; //stores path to selected profile picture
    account *acc;
    jsonhandler *json;


private:
    /**
    * \brief Sets the widget of the grid layout
    * \param *Grid, a pointer to a grid layout
    */
    void setGridLayout(QGridLayout *grid);
    /**
    * \brief Sets the QRadioButtons in a VBoxLayout
    * \param *box, a pointer to a vertical box layout
    * \param *groupBox, a pointer to a group of buttons
    */
    void setGroupLayout(QVBoxLayout *box, QGroupBox *groupBox);
    /**
    * \brief Checks if the password passes the all necessary conditions.
    * \param pass, password in string format
    * \return bool, returns true if the password passes all the conditions. Returns false otherwise.
    */
    bool checkPass(QString pass);
    /**
    * \brief Checks if any of the input fields are left empty.
    * \return bool, returns true if all the fields are filled correctly. Returns false otherwise.
    */
    bool notEmpty();


private slots:
    /**
    * \brief Allows the user to select a custom profile picture
    *
    * This function stores the local path to the selected profile picture in the user QJsonObject
    */
    void uploadPic();
    /**
    * \brief Constructs a user QJsonObject and stores it in data.json
    * \return QJsonObject, the constructed json object
    *
    * This function takes the inputs of the sign up form and checks whether they are valid.
    * In case the inputs pass the validation checks, the function fills in a user json object with the corresponding inputs.
    */
    QJsonObject storeinfo();
    /**
    * \brief Displays the Account widget in case the user json object is not empty
    */
    void onSubmit();
    /**
     * \brief returns to the previous window. In this case, it is Scene1.cpp
     */
    void goBack();
};

#endif // SIGNUPPAGE_H
