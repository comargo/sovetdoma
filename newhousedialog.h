#ifndef NEWHOUSEDIALOG_H
#define NEWHOUSEDIALOG_H

#include <QDialog>

namespace Ui {
class NewHouseDialog;
}

class NewHouseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewHouseDialog(QWidget *parent = 0);
    ~NewHouseDialog();

    QString getPath() const;
    QString getAddress() const;

protected:
    void FillSavingPath();

private slots:
    void onSavingPathBrowseClicked();
    void onAddressLineEditTextChanged(const QString &arg1);

private:
    Ui::NewHouseDialog *ui;
    QString basePath;

    // QDialog interface
public slots:
    void accept() override;
};

#endif // NEWHOUSEDIALOG_H
