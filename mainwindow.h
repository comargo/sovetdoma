#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HouseCouncil;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool setCouncil(HouseCouncil *newCouncil);

private slots:
    void onActionNewTriggered();
    void onActionOpenTriggered();

private:
    Ui::MainWindow *ui;
    HouseCouncil *council;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
