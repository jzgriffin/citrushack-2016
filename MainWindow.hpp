#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "VirtualMachine.hpp"
#include <QMainWindow>
#include <QtCore>
#include <QtKeypad.h>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <memory>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void on_action_Open_Program_triggered();
    void tickSlot();
    void cycleSlot();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<VirtualMachine> vm;

    QLabel *StatLabel, *Stat;

    QLabel *MemLoc, *Mem;
    QLabel *Species, *Generation;
    QLabel *Spec, *Gen;
    QHBoxLayout *layout;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsRectItem *Pixels[32*64];
    QGraphicsRectItem *block;
    qreal ar1 = 2;
    qreal ar2 = 2;
    qreal hScale = 4.7;
    qreal wScale = hScale*(ar1/ar2);
    QTimer *cycle;
    QTimer *tick;

    QtKeypad *keypad;

    void clearDisplay();
    void drawPixel(std::size_t x, std::size_t y, std::uint8_t color);
};

#endif // MAINWINDOW_HPP
