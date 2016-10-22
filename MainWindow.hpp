#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *StatLabel, *Stat;
    QLabel *MemLoc, *Mem;
    QLabel *Species, *Generation;
    QLabel *Spec, *Gen;
    QHBoxLayout *layout;
    QGraphicsScene *scene;
    QGraphicsRectItem *Pixels[32*64];
    QGraphicsRectItem *block;
    qreal ar1 = 2;
    qreal ar2 = 2;
    qreal hScale = 4.7;
    qreal wScale = hScale*(ar1/ar2);
};

#endif // MAINWINDOW_HPP
