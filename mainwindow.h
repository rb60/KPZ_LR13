#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stockexchange.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent *event) override;
    ~MainWindow();

private:
    StockExchange* stock;
    Brocker* brockers[3];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
