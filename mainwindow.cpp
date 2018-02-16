#include "mainwindow.h"
#include "newhousedialog.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <qfiledialog.h>

#include "housecouncil.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    council(nullptr)
{
    ui->setupUi(this);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriggered);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::setCouncil(HouseCouncil *newCouncil)
{
    if(council) {
        if(council->isModified()) {
            QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Save changes"), tr("Do you want to save modified data?"), QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if(answer == QMessageBox::Cancel)
                return false;
            if(answer == QMessageBox::Yes) {
                council->save();
            }
        }
        council->deleteLater();
    }
    council = newCouncil;
}

void MainWindow::onActionNewTriggered()
{
    NewHouseDialog dlg(this);
    if(dlg.exec() == QDialog::Rejected) {
        return;
    }
    try {
        HouseCouncil *newCouncil = HouseCouncil::create(dlg.getPath(), dlg.getAddress(), this);
        setCouncil(newCouncil);
    }
    catch(const std::exception &ex) {
        QMessageBox::critical(this, tr("Error"), tr("Can't create new House Owner Council:")+"\n"+QString::fromUtf8(ex.what()));
    }
}

void MainWindow::onActionOpenTriggered()
{
    QString newCouncilPath = QFileDialog::getExistingDirectory(this, tr("Open House Owner Council"), QSettings().value("DefaultPath", QDir::homePath() + QStringLiteral("/SovetDoma")).toString());
    try {
        HouseCouncil *newCouncil = new HouseCouncil(newCouncilPath, this);
        setCouncil(newCouncil);
    }
    catch(const std::exception &ex) {
        QMessageBox::critical(this, tr("Error"), tr("Can't open House Owner Council:")+"\n"+QString::fromUtf8(ex.what()));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(setCouncil(nullptr)) {
        QSettings settings;
        settings.setValue("geometry", saveGeometry());
        settings.setValue("windowState", saveState());
        event->accept();
    }
    else {
        event->ignore();
    }
}
