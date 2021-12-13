/**
  * \file account.h
  * \brief the account widget
  *
  * This widget includes two main widgets: the account_sidebar and the account_dashboard
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "account_sidebar.h"
#include "account_dashboard.h"

class account : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief account constructor
      * \param parent, a pointer to a parent widget
      * \param QJsonObject, the user json object returned from signin, signup, or playasguest
     */
    explicit account(QWidget *parent = nullptr, QJsonObject json = {});

private:
    QHBoxLayout *hbLayout;
    QVBoxLayout *vbLayout;
    account_sidebar *acctSidebar; //account_sidebar
    account_dashboard *g1Dashboard; //account_dashboard for Battleships
    account_dashboard *g2Dashboard; //account_dashboard for Shooting Discs
    QLabel *date; //today's date
    QLabel *g1title;
    QLabel *g2title;



signals:

};

#endif // ACCOUNT_H
