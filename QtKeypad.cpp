#include <QApplication>
#include <QKeyEvent>
#include "QtKeypad.h"

//QtKeypad::QtKeypad(QWidget *parent):QWidget(parent)
//{

//}

void QtKeypad::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        _state.set(0x1);
        break;

    case Qt::Key_2:
        _state.set(0x2);
        break;

    case Qt::Key_3:
        _state.set(0x3);
        break;

    case Qt::Key_C:
        _state.set(0x4);
        break;

    case Qt::Key_4:
        _state.set(0x5);
        break;

    case Qt::Key_5:
        _state.set(0x6);
        break;

    case Qt::Key_6:
        _state.set(0x7);
        break;

    case Qt::Key_D:
        _state.set(0x8);
        break;

    case Qt::Key_7:
        _state.set(0x9);
        break;

    case Qt::Key_8:
        _state.set(0x10);
        break;

    case Qt::Key_9:
        _state.set(0x11);
        break;

    case Qt::Key_E:
        _state.set(0x12);
        break;

    case Qt::Key_A:
        _state.set(0x13);
        break;

    case Qt::Key_0:
        _state.set(0x14);
        break;

    case Qt::Key_B:
        _state.set(0x14);
        break;

    case Qt::Key_F:
        _state.set(0x15);
        break;
    }
}

void QtKeypad::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        _state.reset(0x1);
        break;

    case Qt::Key_2:
        _state.reset(0x2);
        break;

    case Qt::Key_3:
        _state.reset(0x3);
        break;

    case Qt::Key_C:
        _state.reset(0x4);
        break;

    case Qt::Key_4:
        _state.reset(0x5);
        break;

    case Qt::Key_5:
        _state.reset(0x6);
        break;

    case Qt::Key_6:
        _state.reset(0x7);
        break;

    case Qt::Key_D:
        _state.reset(0x8);
        break;

    case Qt::Key_7:
        _state.reset(0x9);
        break;

    case Qt::Key_8:
        _state.reset(0x10);
        break;

    case Qt::Key_9:
        _state.reset(0x11);
        break;

    case Qt::Key_E:
        _state.reset(0x12);
        break;

    case Qt::Key_A:
        _state.reset(0x13);
        break;

    case Qt::Key_0:
        _state.reset(0x14);
        break;

    case Qt::Key_B:
        _state.reset(0x14);
        break;

    case Qt::Key_F:
        _state.reset(0x15);
        break;
    }
}
