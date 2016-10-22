#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFrame *status_frame = new QFrame();
    status_frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    layout = new QHBoxLayout(status_frame);
    layout->setContentsMargins(0,0,0,0);

    StatLabel = new QLabel(this);
    Stat = new QLabel(this);
    MemLoc = new QLabel(this);
    Mem = new QLabel(this);
    Species = new QLabel(this);
    Spec = new QLabel(this);
    Generation = new QLabel(this);
    Gen = new QLabel(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    StatLabel->setText("Status:");
    MemLoc->setText("Memory Location:");
    Species->setText("Species:");
    Generation->setText("Generation:");

    layout->addWidget(StatLabel);
    layout->addWidget(Stat);
    layout->addWidget(MemLoc,1);
    layout->addWidget(Mem);
    layout->addWidget(Species,1);
    layout->addWidget(Spec);
    layout->addWidget(Generation,1);
    layout->addWidget(Gen);
    ui->statusBar->insertWidget(0, status_frame);

    for (int x = 0; x < 63; x++)
        for(int y = 0; y < 31; y++)
        {
          auto block = new QGraphicsRectItem(x*wScale,y*hScale,wScale,hScale);
          scene->addItem(block);
          block->setBrush(QBrush(Qt::black));
        }
    ui->graphicsView->fitInView(scene->sceneRect());
}

void MainWindow::resizeEvent(QResizeEvent *) {
    QRectF bounds = scene->itemsBoundingRect();
    bounds.setWidth(bounds.width()*.75);         // to tighten-up margins
    bounds.setHeight(bounds.height()*.75);       // same as above
    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
