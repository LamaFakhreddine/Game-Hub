/**
 * \file g1_info.h
 * \brief this class is a widget that informs the player on how to play Battleships.
 */
#ifndef G1_INFO_H
#define G1_INFO_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "jsonhandler.h"
#include "g1_setup.h"

class g1_info : public QWidget
{
    Q_OBJECT
public:
    /**
      * \brief g1_info constructor
      * \param parent, a pointer to a QWidget parent
      * \param json, the QJsonObject for a given user
      */
    explicit g1_info(QWidget *parent = nullptr, QJsonObject json = {});

private:

    QJsonObject userJson;
    jsonhandler *jh = new jsonhandler();
    QLabel* hi;//text displaying "Hello <username>"
    QLabel* info;//Battleships information
    QPushButton* start;//start button
    QVBoxLayout* vbox;

    /**
     * @brief sets the widgets of a vertical box layout
     * @param vbox, a pointer to a QVBoxLayout.
     */
    void setVBoxLayout(QVBoxLayout* vbox);
    /**
     * @brief initializes the background color of the widget
     */
    void initBg();

private slots:
    /**
     * @brief Navigates to g1_setup
     */
    void onStart();


signals:

};

#endif // G1_INFO_H
