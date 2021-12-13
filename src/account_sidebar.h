/**
* \file account_sidebar.h
* \brief This widget constructs the sidebar of the account widget
*
* The sidebar includes information about the user.
* It also includes navigation buttons.
*/

#ifndef ACCOUNT_SIDEBAR_H
#define ACCOUNT_SIDEBAR_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QJsonObject>

class account_sidebar : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief account_sidebar constructor
      * \param parent, a pointer to a parent QWidget. Initialized to nullptr
      * \param userobj, a QJsonObject. Initialized to an empty QJsonObject.
      */
    explicit account_sidebar(QWidget *parent = nullptr, QJsonObject userobj = {});

private:
    QLabel *profilePic;
    QLabel *user;
    QLabel *flag;
    QLabel *name;
    QPushButton *game1Btn;
    QPushButton *game2Btn;
    QPushButton *backBtn;
    QVBoxLayout *mainBoxLayout;
    QJsonObject json;

    /**
     * \brief sets the country flag of the player based on their country code
     * \param number, a QString that contains the player's phone number in the following format: '+code-number'
     */
    void setFlag(QString number);
    /**
     * \brief Sets the player's profile pic
     * \param picPath, a QString which stores the absolute path to the selected picture
     */
    void setProfilePic(QString picPath);

signals:

private slots:
    /**
     * \brief navigates to the previous window.
     */
    void goToBack();
    /**
     * \brief navigates to Battleships game.
     */
    void goToGame1();
    /**
     * \brief navigates to Shooting Discs game.
     */
    void goToGame2();
};

#endif // ACCOUNT_SIDEBAR_H
