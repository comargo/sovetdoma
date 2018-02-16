#include "newhousedialog.h"
#include "ui_newhousedialog.h"

#include <QFileDialog>
#include <QSettings>
#include <QStringBuilder>

NewHouseDialog::NewHouseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewHouseDialog),
    basePath(QSettings().value("DefaultPath", QDir::homePath() + QStringLiteral("/SovetDoma")).toString())
{
    ui->setupUi(this);
    FillSavingPath();
    connect(ui->addressLineEdit, &QLineEdit::textChanged, this, &NewHouseDialog::onAddressLineEditTextChanged);
    connect(ui->savingPathBrowse, &QPushButton::clicked, this, &NewHouseDialog::onSavingPathBrowseClicked);
}

NewHouseDialog::~NewHouseDialog()
{
    delete ui;
}

QString NewHouseDialog::getPath() const
{
    return QDir::fromNativeSeparators(ui->savingPathLineEdit->text());
}

QString NewHouseDialog::getAddress() const
{
    return ui->addressLineEdit->text();
}

void NewHouseDialog::FillSavingPath()
{
    QString sanitizedPathName = ui->addressLineEdit->text();
    sanitizedPathName.replace(QRegExp("[/\\:*?\"<>|]+"),"-");
    sanitizedPathName = sanitizedPathName.simplified();
    ui->savingPathLineEdit->setText(QDir::toNativeSeparators(basePath % "/" % sanitizedPathName));

    bool isAddressValid = !sanitizedPathName.isEmpty();
    ui->addressIcon->setVisible(!isAddressValid);

    bool isPathValid = !QFileInfo::exists(ui->savingPathLineEdit->text());
    ui->savingPathIcon->setVisible(!isPathValid);

    ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(isAddressValid && isPathValid);
}

void NewHouseDialog::onSavingPathBrowseClicked()
{
    QString newBasePath = QFileDialog::getExistingDirectory(this, tr("Parent directory"), basePath);
    if(newBasePath.isEmpty())
        return;
    basePath = newBasePath;
    FillSavingPath();
}

void NewHouseDialog::onAddressLineEditTextChanged(const QString &/*arg1*/)
{
    FillSavingPath();
}



void NewHouseDialog::accept()
{
    QDialog::accept();
    QSettings().setValue("DefaultPath", basePath);
}
