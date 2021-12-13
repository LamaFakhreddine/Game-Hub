/**
* \file account_sidebar.cpp
* \brief This widget constructs the sidebar of the account widget
*
* The sidebar includes information about the user.
* It also includes navigation buttons.
*/
#include "account_sidebar.h"
#include "account.h"
#include "scene1.h"
#include "g1_startmenu.h"
#include "g2_startmenu.h"
#include "centering.h"

/**
  * \brief account_sidebar constructor
  * \param parent, a pointer to a parent QWidget. Initialized to nullptr
  * \param userobj, a QJsonObject. Initialized to an empty QJsonObject.
  */
account_sidebar::account_sidebar(QWidget *parent, QJsonObject userobj) : QWidget(parent)
{
    //extracts player info from the json object
    json = userobj;
    QString fname = userobj.value("first name").toString();
    QString lname = userobj.value("last name").toString();
    QString picPath = userobj.value("profile pic").toString();
    QString username = userobj.value("username").toString();
    QString phoneNumber = userobj.value("phone number").toString();

    //styles the widget
    setStyleSheet("QWidget{background-color:#fff;"
                  "border: 2px solid #d8daeb;"
                  "border-radius: 10px;}"

                  "QLabel{font-weight: bold; font-size: 14px; border:0px;}"

                  "QPushButton{font-size:14px; "
                  "background-color: #fff;"
                  "color: #7965fc;"
                  "font-weight:bold;"
                  "width:60px;"
                  "height:30px;"
                  "padding:5px, 2px;"
                  "border: 2px solid #692cff;"
                  "border-radius: 5px;}"

                  "QPushButton::hover{"
                  "background-color:#692cff;"
                  "color: #fff;}");

    setAttribute(Qt::WA_StyledBackground);

    //sets the profile picture
    profilePic = new QLabel();
    setProfilePic(picPath);
    profilePic->setAlignment(Qt::AlignCenter);

    //displays player info
    name = new QLabel(fname + " " + lname);
    name->setAlignment(Qt::AlignCenter);
    name->setStyleSheet("color: #ff711f");
    user = new QLabel(username);
    user->setAlignment(Qt::AlignCenter);
    user->setStyleSheet("font-size: 20px; color: #262626;");
    flag = new QLabel();
    setFlag(phoneNumber);

    //sets sidebar navigation buttons
    game1Btn = new QPushButton("Battleships");
    game2Btn = new QPushButton("Shooting Discs");
    backBtn = new QPushButton("Back");

    //sets sidebar main layout
    mainBoxLayout = new QVBoxLayout;
    mainBoxLayout->addSpacing(20);
    mainBoxLayout->addWidget(profilePic, Qt::AlignCenter);
    mainBoxLayout->addSpacing(10);
    mainBoxLayout->addWidget(user);
    mainBoxLayout->addSpacing(-40);
    mainBoxLayout->addWidget(name);
    mainBoxLayout->addSpacing(-40);
    mainBoxLayout->addWidget(flag);
    mainBoxLayout->addSpacing(50);
    mainBoxLayout->addWidget(game1Btn);
    mainBoxLayout->addSpacing(20);
    mainBoxLayout->addWidget(game2Btn);
    mainBoxLayout->addSpacing(20);
    mainBoxLayout->addWidget(backBtn);
    mainBoxLayout->addSpacing(90);
    mainBoxLayout->setAlignment(Qt::AlignHCenter);
    setFixedSize(200,770);

    QObject::connect(backBtn, SIGNAL(clicked()), this, SLOT(goToBack()));
    QObject::connect(game1Btn, SIGNAL(clicked()), this, SLOT(goToGame1()));
    QObject::connect(game2Btn, SIGNAL(clicked()), this, SLOT(goToGame2()));
    setLayout(mainBoxLayout);

}

/**
 * \brief sets the country flag of the player based on their country code
 * \param number, a QString that contains the player's phone number in the following format: '+code-number'
 */
void account_sidebar::setFlag(QString number){
    QString flagImg;

    if(number.contains("+961-")) {
        flagImg = "lebanon-flag.png";
    } else if (number.contains("+962-")){
        flagImg = "jordan-flag.jpeg";
    }else if (number.contains("+20-")){
        flagImg = "egypt-flag.jpeg";
    }else if (number.contains("+1-")){
        flagImg = "us-flag.png";
    }

    QPixmap country (QPixmap(":" + flagImg).scaled(40,27));
    flag->setPixmap(country);//add corresponding country flag
    flag->setAlignment(Qt::AlignCenter);
}
/**
 * \brief Sets the player's profile pic
 * \param picPath, a QString which stores the absolute path to the selected picture
 */
void account_sidebar::setProfilePic(QString picPath){
    QString path = ":acctPic.jpeg";
    if(!picPath.isNull()){
        path = picPath;
    }
    QPixmap bg (QPixmap(path).scaled(125,125));
    profilePic->setPixmap(bg);
    profilePic->setScaledContents(true);
    profilePic->setStyleSheet("border-radius: 4px;");
    profilePic->setFixedSize(140,140);
}

/**
 * \brief navigates to the previous window.
 */
void account_sidebar::goToBack(){
    scene1 *s = new scene1;
    window()->hide();
    Centering::centerWidget(s);
    s->show();
}
/**
 * \brief navigates to Battleships game.
 */
void account_sidebar::goToGame1(){
    g1_startmenu *g1menu = new g1_startmenu(nullptr, json);
    window()->hide();
    Centering::centerWidget(g1menu);
    g1menu->show();
}
/**
 * \brief navigates to Shooting Discs game.
 */
void account_sidebar::goToGame2(){
    g2_startmenu *g2menu = new g2_startmenu(nullptr, json);
    window()->hide();
    Centering::centerWidget(g2menu);
    g2menu->show();
}
