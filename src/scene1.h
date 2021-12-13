/**
* \file Scene1.h
* \brief The landing view of the GameHub application
*
* This view includes the following entry options: sign-in, sign-up, and play-as-guest
*/

#ifndef SCENE1_H
#define SCENE1_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class scene1 : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief scene1 constructor
     * \param parent, a pointer to the parent widget
     */
    explicit scene1(QWidget *parent = nullptr);

signals:
private:
    QLabel *hello;
    QLabel *paragraph;  //includes a brief description of the platform
    QPushButton *signup;    //sign up button
    QPushButton *signin;    //sign in button
    QPushButton *playasguest_;  //playasguest button


    /**
    * \brief Sets the widget of the grid layout
    * \param *Grid, a pointer to a grid layout
    */
    void setGridLayout(QGridLayout *Grid);

    private slots:
    /**
    * \brief Creates and displays the sign up window
    */
    void pushsignup();
    /**
    * \brief Creates and displays the sign in window
    */
    void pushsignin();
    /**
    * \brief Creates and displays the play as guest window
    */
    void pag();

};

#endif // SCENE1_H
