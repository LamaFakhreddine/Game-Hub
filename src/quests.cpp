/**
  * \file quests.cpp
  * \brief A class that displays a QDialog of a question in Battleships game
  * This class contains queries to the questions.json file
  */

#include "quests.h"
#include <QDebug>
#include <QObject>

/**
  * \brief quests constructor
  * \param parent, a pointer to a parent QWidget, initialized to a nullptr
  * \param json, a QJsonObject of a given user.
  * \param count, an int specificying the index of the question to be set
  */
quests::quests(QWidget *parent, QJsonObject json, int count) : QDialog(parent)
{
    userJson = json;

    setStyleSheet("QLabel{font-size:24px;"
                  "font-weight: bold;"
                  "text-transform: uppercase;"
                  "color: #fff;}"

                  "QPushButton{"
                  "background-color: #fff;"
                  "border: 5px solid #fff;"
                  "border-radius:4px;"
                  "font-size:20px;"
                  "font-weight:bold;"
                  "color: #1F4E8D;"
                  "width:800px;"
                  "height: 50px;}"
                  "QPushButton:hover{"
                  "border-right:5px solid #FF5454;"
                  "border-bottom:5px solid #FF5454;"
                  "border-left:5px solid #73FFFF;"
                  "border-top: 5px solid #73FFFF;}");

    initBg();

    header = new QLabel("Hit your target by answering this question correctly!");

    //creates wrng and right QMessageBoxes
    cont = new QPushButton("Continue");
    cont->setStyleSheet("background-color: #0047AB;" "color: #fff;");

    wrng = new QMessageBox();
    wrng->setText("Incorrect");
    wrng->setInformativeText("Sorry, that's not quite right. Since you answered incorrectly, your shot missed...and your enemy fired back, hitting one of your ships!");
    wrng->setDefaultButton(cont);
    wrng->setStyleSheet("background-color: #fff;"
                        "font-size:20px;"
                        "font-weight:bold;"
                        "color: #1F4E8D;");

    right = new QMessageBox();
    right->setText("Correct");
    right->setInformativeText("Nice work! You answered correctly, so you were able to hit one of your enemy's ships!");
    right->setDefaultButton(cont);
    right->setStyleSheet("background-color: #fff;"
                        "font-size:20px;"
                        "font-weight:bold;"
                        "color: #1F4E8D;");

    //extracts difficulty and topic from game 1 settings
    diff = userJson.value("game1").toObject().value("settings").toObject().value("difficulty").toInt();
    top = userJson.value("game1").toObject().value("settings").toObject().value("topic").toInt();

    diffstr = mapdiff(diff);
    topstr = maptop(top);
    //reads contents of questions.json and extracts the questions that fit the specified difficulty and topic
    reading = new jsonhandler();
    topicObj = reading->readFile(reading->questsPath).at(0).toObject();
    questarr = getquest(diffstr, topstr);
    qDebug() << "questions arr: "<<questarr <<"\n";

    //sets question in popup window
    toset = questarr.at(count).toObject();
    //qDebug() << "toset: " << toset << "\n";
    setquests(toset);

    //submit = new QPushButton("Submit");
    //submit->setStyleSheet("background-color: #800;" "color: #fff");

    gameLogo = new QLabel();
    gameLogo->setPixmap(QPixmap(":/battleship-bg.png").scaled(550,200));
    answers = new QVBoxLayout();
    anslayout = new QGroupBox();
    createAnsBox();

    grid = new QGridLayout();
    setGridLayout();
    setFixedSize(1000,800);

    QObject::connect(ans1, SIGNAL(clicked()) , this, SLOT(checkanswer1()));
    QObject::connect(ans2, SIGNAL(clicked()) , this, SLOT(checkanswer2()));
    QObject::connect(ans3, SIGNAL(clicked()) , this, SLOT(checkanswer3()));
    QObject::connect(ans4, SIGNAL(clicked()) , this, SLOT(checkanswer4()));

}

/**
 * \brief sets the widget of the answers layout
 */
void quests::createAnsBox(){
    answers->addWidget(ans1, 0, Qt::AlignCenter);
    answers->addWidget(ans2, 0, Qt::AlignCenter);
    answers->addWidget(ans3, 0, Qt::AlignCenter);
    answers->addWidget(ans4, 0, Qt::AlignCenter);
    answers->addSpacing(50);
    //answers->addWidget(submit, 0, Qt::AlignCenter);
    anslayout->setLayout(answers);
    anslayout->setFixedWidth(450);
}
/**
 * \brief sets the widgets of the grid layout
 */
void quests::setGridLayout(){
    grid->setMargin(30);
    grid->addWidget(header, 0, 0, 1, 4, Qt::AlignCenter);
    grid->addWidget(quest, 1, 0, 2, 4);
    grid->addWidget(anslayout, 3, 0, 5, 1);
    grid->addWidget(gameLogo, 3, 1, 2, 3);

    setLayout(grid);

}
/**
 * \brief maps an integer to the corresponding difficulty
 * \param d, An int indicating the difficulty level extracted from userJson
 * \return QString containing the name of the difficulty level
 */
QString quests::mapdiff(int d){
    if (d == 0){
        return "easy";
    }
    if (d == 1){
        return "medium";
    }
    else{
        return "hard";
    }
}
/**
 * \brief maps an integer to the corresponding topic
 * \param t, An int indicating the topic extracted from userJson
 * \return QString containing the name of the topic
 */
QString quests::maptop(int t){
    if(t == 0){
        return "arrs&strs";
    }
    if (t == 1){
        return "basics";
    }
    return "structs&funcs";
}
/**
 * \brief Retrieves array of questions of a difficulty d and topic t.
 * \param d, a QString that specifies the level of difficulty of the questions
 * \param t, a QString that specifies the topic of the questions
 * \return QJsonArray that contains the questions.
 */
QJsonArray quests::getquest(QString d, QString t){
    return topicObj.value(t).toObject().value(d).toObject().value("questions").toArray();
}
/**
 * \brief Sets the question in the QDialog
 * \param quest, a QJsonObject containing a single question.
 */
void quests::setquests(QJsonObject q){
    quest = new QLabel(q.value("question").toString());
    //qDebug() <<"question to set in box: " <<  q.value("question").toString() << "\n";
    quest->setStyleSheet("font-size: 20px;" "font-weight: normal");
    quest->setWordWrap(true);

    QJsonArray a = q.value("answers").toArray();
    ans1 = new QPushButton(a.at(0).toString());
    ans1->setStyleSheet("font-size: 12px");
    ans2 = new QPushButton(a.at(1).toString());
    ans2->setStyleSheet("font-size: 12px");
    ans3 = new QPushButton(a.at(2).toString());
    ans3->setStyleSheet("font-size: 12px");
    ans4 = new QPushButton(a.at(3).toString());
    ans4->setStyleSheet("font-size: 12px");
}
/**
 * \brief checks whether the chosen pushbutton contains the correct answer.
 * The function displays wrng QMessageBox in case the answer is incorrect
 * and right QMessageBox otherwise.
 */
void quests::checkanswer1(){
    QString s;
    s = ans1->text();
    if (s == toset.value("answer").toString()){
        checkAns = true;
        right->exec();
        hide();
    }
    else{
        checkAns = false;
        wrng->exec();
        hide();
    }
}
/**
 * \brief checks whether the chosen pushbutton contains the correct answer.
 * The function displays wrng QMessageBox in case the answer is incorrect
 * and right QMessageBox otherwise.
 */
void quests::checkanswer2(){
    QString s;
    s = ans2->text();
    if (s == toset.value("answer").toString()){
        checkAns = true;
        right->exec();
        hide();
    }
    else{
        checkAns = false;
        wrng->exec();
        hide();
    }
}
/**
 * \brief checks whether the chosen pushbutton contains the correct answer.
 * The function displays wrng QMessageBox in case the answer is incorrect
 * and right QMessageBox otherwise.
 */
void quests::checkanswer3(){
    QString s;
    s = ans3->text();
    if (s == toset.value("answer").toString()){
        checkAns = true;
        right->exec();
        hide();
    }
    else{
        checkAns = false;
        wrng->exec();
        hide();
    }
}
/**
 * \brief checks whether the chosen pushbutton contains the correct answer.
 * The function displays wrng QMessageBox in case the answer is incorrect
 * and right QMessageBox otherwise.
 */
void quests::checkanswer4(){
    QString s;
    s = ans4->text();
    if (s == toset.value("answer").toString()){
        checkAns = true;
        right->exec();
        hide();
    }
    else{
        checkAns = false;
        wrng->exec();
        hide();
    }
}
/**
 * \brief initializes the background color of the QWidget
 * as specified in userJson.
 */
void quests::initBg(){
    QString bgColor = reading->getBgColor(userJson, "game1");
    //set bg color
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, bgColor);
    setAutoFillBackground(true);
    setPalette(pal);
}
