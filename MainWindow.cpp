#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QGraphicsView>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFrame *status_frame = new QFrame();
    status_frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    // Create layout objects
    scene = new QGraphicsScene(this);
    layout = new QHBoxLayout(status_frame);
    layout->setContentsMargins(0,0,0,0);

    // create labels
    StatLabel = new QLabel(this);
    Stat = new QLabel(this);
    MemLoc = new QLabel(this);
    Mem = new QLabel(this);
    Species = new QLabel(this);
    Spec = new QLabel(this);
    Generation = new QLabel(this);
    Gen = new QLabel(this);
    keypad = new QtKeypad(this);

    // create timers
    tick = new QTimer();
    cycle = new QTimer();

    // connect timers to slots
    connect(tick,SIGNAL(timeout()),this,SLOT(tickSlot()));
    connect(cycle,SIGNAL(timeout()),this,SLOT(cycleSlot()));

    // set the objects
    ui->graphicsView->setScene(scene);
    StatLabel->setText("Status:");
    MemLoc->setText("Memory Location:");
    Species->setText("Species:");
    Generation->setText("Generation:");

    // add objects to layout
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
          auto block = new QGraphicsRectItem(x,y,wScale,hScale);
          scene->addItem(block);
          block->setBrush(QBrush(Qt::black));
        }

}

void MainWindow::resizeEvent(QResizeEvent *) {
    QRectF bounds = scene->itemsBoundingRect();
    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearDisplay()
{
}

void MainWindow::drawPixel(std::size_t x, std::size_t y, std::uint8_t color)
{
}

void MainWindow::tickSlot()
{
    vm->tick();
}

void MainWindow::cycleSlot()
{
    vm->cycle();
}

void MainWindow::on_action_Open_Program_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QMessageBox::information(this,"..",file_name);

    std::ifstream input(file_name.toStdString(), std::ios::binary);

    vm.reset(new VirtualMachine(*keypad, input));
    vm->clearCallback = [&]()
    {
        clearDisplay();
    };

    vm->drawCallback = [&](std::size_t x, std::size_t y, std::uint8_t color)
    {
       drawPixel(x,y,color);
    };

    // start timers
}
