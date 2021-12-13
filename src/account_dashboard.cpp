/**
  * \file account_dashboard.cpp
  * \brief the account_dashboard widget
  *
  * This widget displays a game stats.
  * The stats include user highscore, global highscore, user rank, and a performance plot based on the user scores.
*/

#include "account_dashboard.h"

account_dashboard::account_dashboard(QWidget *parent, QJsonObject json, QString gameID) : QWidget(parent)
{
    setStyleSheet("QWidget{background-color: #fff;"
                  "border: 2px solid #d8daeb;"
                  "border-radius: 10px;}"

                  "QLabel{font-size: 13px; border:0px; font-weight:bold; color: #262626}");

    setAttribute(Qt::WA_StyledBackground);

    //sets game ID
    ID = gameID;

    //gets the user highscore from  json and sets it in the corresponding highscore label
    int highscore = json.value("highscore").toInt();
    QJsonArray scores = json.value("scores").toArray();
    HsLabel = new QLabel("Your Highscore:");
    hs = new QLabel(QString::number(highscore) + " XP");

    //gets global highscore rank from data.json, calculates user's rank, and displays both results
    QJsonObject stats = jh->getGlobalHSAndRank(highscore, ID);
    globalHsLabel = new QLabel("Global Highschore:");
    globalHs = new QLabel(QString::number(stats.value("globalHS").toInt()) + " XP");
    globalRankLabel = new QLabel("Global Rank:");
    QString ordinal = getOrdinal(stats.value("rank").toInt());
    rank = new QLabel(QString::number(stats.value("rank").toInt()) + " " + ordinal);

    //plots the scores in a lineChart
    chart = new QChart();
    series = new QLineSeries();
    plotScores(scores);
    chartView = new QChartView(chart);
    chartView->setStyleSheet("border:none");

    //sets the layout of the widget
    grid = new QGridLayout();
    mainBoxLayout = new QHBoxLayout();
    setInternalLayout();
    setMainLayout();
}

/**
 * \brief sets the widgets of the internal grid layout
 */
void account_dashboard::setInternalLayout(){
    grid->setMargin(10);
    grid->setVerticalSpacing(10);
    grid->setHorizontalSpacing(50);
    grid->addWidget(HsLabel, 0, 0, 1, 2);
    grid->addWidget(hs, 0, 2);
    grid->addWidget(globalHsLabel, 1, 0, 1, 2);
    grid->addWidget(globalHs, 1, 2);
    grid->addWidget(globalRankLabel, 2, 0, 1, 2);
    grid->addWidget(rank, 2, 2);
    grid->addWidget(chartView, 3, 0, 2, 6);

}

/**
 * \brief sets the main vertical layout of the widget
 */
void account_dashboard::setMainLayout(){
    mainBoxLayout->addItem(grid);
    mainBoxLayout->addStretch();
    setLayout(mainBoxLayout);
}

/**
 * \brief Plots the scores of the user in a specific game
 * \param scores, a QJsonarray with the scores of a specific game
 */
void account_dashboard::plotScores(QJsonArray scores){
    int size = scores.size();
    for(int i=0; i<size; i++){
        series->append(i,scores.takeAt(i).toInt());
    }
    chart->addSeries(series);
    styleChart();
}

/**
 * \brief styles the scores chart
 */
void account_dashboard::styleChart(){
    //custom chart line
    QPen pen = series->pen();
    pen.setWidth(2);
    series->setPen(pen);
    series->setColor("#ff711f");

    //custom axes
    chart->legend()->hide();
    chart->createDefaultAxes();

    //custom grid
    chart->axes().first()->setGridLineVisible(false);

    //custom title
    chart->setTitle("Scores");
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush("#ff711f"));

    chart->resize(800,800);
}

/**
 * \brief gets the ordinal of the rank. For example, if the rank is 1, the function returns "st".
 *  If the rank is 2, the function returns "nd", and so on.
 * \param x, an int indicating the rank of the user.
 * \return QString, the ordinal of x
 */
QString account_dashboard::getOrdinal(int x){
    //if x is 11, 12, or 13
    if(10 < x && x < 14) return "th";

    switch (x % 10) {
        case 1:
            return "st";
        case 2:
            return "nd";
        case 3:
            return "rd";
        default:
            return "th";
    }
}


