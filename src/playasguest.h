/**
* \file PlayAsGuest.h
* \brief The play as guest widget
*
* This class allows a temporary user to access the platform.
* The user json object created in this class is only temporary, and it is not stored in the data.json file
*/

#ifndef PLAYASGUEST_H
#define PLAYASGUEST_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"

class playasguest : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief playasguest constructor
     * \param parent, a pointer to the parent widget
     */
    explicit playasguest(QWidget *parent = nullptr);

signals:
private:
    QPushButton *next;
    QPushButton *back;
    QLabel *username;
    QLineEdit *usrtxt;
    QLabel *comment;
    jsonhandler *jh = new jsonhandler();

    /**
    * \brief Sets the widget of the grid layout
    * \param *Grid, a pointer to a grid layout
    */
    void setGridLayout(QGridLayout *grid);

private slots:
    /**
     * \brief returns to the previous window. In this case, it is Scene1.cpp
     */
    void goBack();
    /**
    * \brief Constructs a user QJsonObject
    * \return QJsonObject, the constructed json object. The constructed QJsonObject is empty in case of invalid entries
    *
    * This function takes the inputs of the play as guest form and checks whether the username is taken or not.
    * In case the the username is taken, the function returns an empty QJsonObject.
    * Otherwise, it returns a QJsonObject with reduced features.
    * (the reduced features only include username, game1, and game2)
    */
    QJsonObject storeinfo();
    /**
     * \brief navigates to the next window. In this case, it is Account.cpp
     */
    void goNext();

};

#endif // PLAYASGUEST_H
