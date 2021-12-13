/**
  * \file account.cpp
  * \brief the account widget
  *
  * This widget includes two main widgets: the account_sidebar and the account_dashboard
*/

#include "account.h"

/**
  * \brief account constructor
  * \param parent, a pointer to a parent widget
  * \param QJsonObject, the user json object returned from signin, signup, or playasguest
 */
account::account(QWidget *parent, QJsonObject json) : QWidget(parent)
{
    setStyleSheet("QWidget{ color: #262626;"
                  "margin:0; "
                  "padding:0;"
                  "background-color: #f1f2f9;}");

    hbLayout = new QHBoxLayout();
    vbLayout = new QVBoxLayout();
    vbLayout->setContentsMargins(20,20,20,20);


    //sets date to today's date
    date = new QLabel(QDateTime().currentDateTime().toString("ddd, MMM, d, yyyy"));
    date->setStyleSheet("font-weight: bold; font-size: 18px");

    g1title = new QLabel("Battleship Stats");
    g2title = new QLabel("Shooting Discs Stats");
    g1title->setStyleSheet("padding: 2px; font-weight: bold; font-size: 16px; color: #6a3dd9");
    g2title->setStyleSheet("padding: 2px; font-weight: bold; font-size: 16px; color: #6a3dd9");

    //add the sidebar and dashboards
    acctSidebar = new account_sidebar(parent, json);
    g1Dashboard = new account_dashboard(parent, json.value("game1").toObject(), "game1");
    g2Dashboard = new account_dashboard(parent, json.value("game2").toObject(), "game2");

    //set the widget layout
    vbLayout->addWidget(date);
    vbLayout->setSpacing(20);
    vbLayout->addWidget(g1title);
    vbLayout->addWidget(g1Dashboard);
    vbLayout->addWidget(g2title);
    vbLayout->addWidget(g2Dashboard);

    hbLayout->addWidget(acctSidebar);
    hbLayout->addItem(vbLayout);
    setLayout(hbLayout);
    window()->setFixedSize(1000,825);
}
