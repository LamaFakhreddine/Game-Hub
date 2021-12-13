#ifndef SIGNUP_SCENE_H
#define SIGNUP_SCENE_H

#include <QObject>
#include <QWidget>

class signup_scene : public QObject
{
    Q_OBJECT
public:
    explicit signup_scene(QObject *parent = nullptr);

signals:

};

#endif // SIGNUP_SCENE_H
