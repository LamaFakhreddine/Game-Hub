/**
  * \file Centering.h
  * \brief A class that centers a widget
  *
  */
#ifndef CENTERING_H
#define CENTERING_H

#include <QObject>
#include <QtWidgets>

class Centering : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Centering constructor
     * \param parent, a pointer to parent QObject. Initialized to a nullptr
     */
    explicit Centering(QObject *parent = nullptr);
    /**
     * \brief a function that centers a widget
     * \param w, a pointer to the QWidget to be centered
     */
    static void centerWidget(QWidget *w);
    static void centerScene(QGraphicsView *s);

signals:

};

#endif // CENTERING_H
