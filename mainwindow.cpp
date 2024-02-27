#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stock = new StockExchange(100, 50);

    brockers[0] = new Brocker1;
    brockers[1] = new Brocker2;
    brockers[2] = new Brocker3;

    for(int i = 0; i < 3; i++)
    {
        stock->addSubscriber(brockers[i]);
    }

    ui->widget->setStock(stock);
    startTimer(500);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    stock->update();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stock;
    for(int i = 0; i < 3; i++)
    {
        delete brockers[i];
    }
}
