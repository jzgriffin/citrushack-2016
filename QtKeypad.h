#ifndef QTKEYPAD_H
#define QTKEYPAD_H

#include "Keypad.hpp"
#include <QObject>
#include <QtGui>

class QtKeypad:public QObject, public Keypad{
    Q_OBJECT

    public:

        QtKeypad(QObject *parent = 0);

    protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // QTKEYPAD_H
