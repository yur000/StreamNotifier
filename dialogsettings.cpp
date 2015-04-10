#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QFileDialog>


dialogSettings::dialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSettings)
{
    ui->setupUi(this);
    setWindowTitle("Настройки");
}

void dialogSettings::showSettings(QStringList *channels, settingsContainer *notifySettings)
{
    for(int i = 0; i < channels->count(); i++)
    {
        ui->listOfChannels->addItem(channels->at(i));
    }
    ui->isSound->setChecked(notifySettings->isSound);
    on_isSound_clicked(notifySettings->isSound);
    ui->soundPath->setText(notifySettings->soundPath);
    ui->minutesToCheck->setValue(notifySettings->timeToCheck / 60 / 1000);
    this->show();
    isModified = false;
}

dialogSettings::~dialogSettings()
{
    delete ui;
}

void dialogSettings::on_addChannel_clicked()
{
    if(!ui->channelName->text().isEmpty())
    {
        ui->listOfChannels->addItem( ui->channelName->text());
        ui->channelName->clear();
        isModified = true;
    }
}

void dialogSettings::on_deleteChannel_clicked()
{
    delete ui->listOfChannels->currentItem();
    isModified = true;
}

void dialogSettings::on_saveButton_clicked()
{
    hide();
    if(isModified)
    {
        QStringList *channels = new QStringList;
        settingsContainer *notifySettings = new settingsContainer;
        for(int i = 0; i < ui->listOfChannels->count(); i++)
        {
            channels->append(ui->listOfChannels->item(i)->text());
        }
        ui->listOfChannels->clear();
        notifySettings->isSound = ui->isSound->isChecked();
        notifySettings->soundPath = ui->soundPath->text();
        notifySettings->timeToCheck = ui->minutesToCheck->value() * 60 * 1000;
        emit modified(channels, notifySettings);
    }
}

void dialogSettings::on_isSound_clicked(bool checked)
{
    ui->soundPathText->setEnabled(checked);
    ui->soundPath->setEnabled(checked);
    ui->callFileDialog->setEnabled(checked);
    isModified = true;
}

void dialogSettings::on_minutesToCheck_valueChanged(int arg1)
{
    isModified = true;
}

void dialogSettings::on_callFileDialog_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор звукового оповещения", "", "*.mp3");
    if(!path.isEmpty())
    {
        ui->soundPath->setText(path);
        isModified = true;
    }
}
