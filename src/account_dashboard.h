/**
  * \file account_dashboard.h
  * \brief the account_dashboard widget
  *
  * This widget displays a game stats.
  * The stats include user highscore, global highscore, user rank, and a performance plot based on the user scores.
*/

#ifndef ACCOUNT_DASHBOARD_H
#define ACCOUNT_DASHBOARD_H

#include <QWidget>
#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "jsonhandler.h"

using namespace QtCharts;

class account_dashboard : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief account_dashboard constructor
      * \param parent, a pointer to a parent QWidget. Initially equal to a nullptr
      * \param json, a user QJsonObject passed by the calling class. Initialized to an empty object.
      * \param gameID, a QString with the game's ID to differeniate between stats of different games. Initialized to an empty string.
      */
    explicit account_dashboard(QWidget *parent = nullptr, QJsonObject json = {}, QString gameID = "");

private:
    QString ID; //game ID extracted from json
    QChart *chart; //scores plot
    QChartView *chartView; //a chart view to display the chart in
    QLineSeries *series;//a line series that stores the scores
    QLabel *globalHsLabel;
    QLabel *HsLabel;
    QLabel *globalRankLabel;
    QLabel *hs; //user highscore
    QLabel *globalHs;//global highscore
    QLabel *rank;//user rank
    QGridLayout *grid;
    QHBoxLayout *mainBoxLayout;
    jsonhandler *jh = new jsonhandler();

    /**
     * \brief sets the widgets of the internal grid layout
     */
    void setInternalLayout();
    /**
     * \brief sets the main vertical layout of the widget
     */
    void setMainLayout();
    /**
     * \brief Plots the scores of the user in a specific game
     * \param scores, a QJsonarray with the scores of a specific game
     */
    void plotScores(QJsonArray scores);
    /**
     * \brief styles the scores chart
     */
    void styleChart();
    /**
     * \brief gets the ordinal of the rank. For example, if the rank is 1, the function returns "st".
     *  If the rank is 2, the function returns "nd", and so on.
     * \param x, an int indicating the rank of the user.
     * \return QString, the ordinal of x
     */
    QString getOrdinal(int x);

signals:

};

#endif // ACCOUNT_DASHBOARD_H
