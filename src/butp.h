/**
  * \file butp.h
  * \brief the purple disk in game 2
  */
#ifndef BUTP_H
#define BUTP_H

#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "butblack.h"

class butp : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
      * \brief butp constructor
      * \param parent, a pointer to a parent QObject, initialized to a nullptr
      * \param pos, position by which the button falls
      */
    explicit butp(QObject *parent = nullptr, int pos = 5);
    enum DiskType {Black = UserType + 1, Blue = UserType + 2, Green = UserType + 3, Purple = UserType + 4};
    int type() const override;

private:
    QTimer *timer;
    /**
     * \brief connects button to correct signal depending on the falling speed needed
     */
    void confirmConnect(QTimer* timer, int pos);

signals:
private slots:
    /**
     * \brief button falls slowly
     */
    void buttonfall1();
    /**
     * \brief button falls faster
     */
    void buttonfall2();
    /**
     * \brief button falls faster
     */
    void buttonfall3();
    /**
     * \brief button falls faster
     */
    void buttonfall4();
    /**
     * \brief button falls faster
     */
    void buttonfall5();
};

#endif // BUTP_H
