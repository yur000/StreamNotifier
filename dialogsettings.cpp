#include "dialogsettings.h"
#include "ui_dialogsettings.h"

dialogSettings::dialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogSettings)
{
    ui->setupUi(this);
    setWindowTitle("Настройки");
}

void dialogSettings::showSettings(QStringList *channels)
{
    for(int i = 0; i < channels->count(); i++)
    {
        ui->listOfChannels->addItem(channels->at(i));
    }
    this->show();
}

dialogSettings::~dialogSettings()
{
    delete ui;
}

void dialogSettings::on_addChannel_clicked()
{
    ui->listOfChannels->addItem( ui->channelName->text());
    ui->channelName->clear();
}

void dialogSettings::on_deleteChannel_clicked()
{
    delete ui->listOfChannels->currentItem();
}

void dialogSettings::on_saveButton_clicked()
{
    hide();
    QStringList *channels = new QStringList;
    for(int i = 0; i < ui->listOfChannels->count(); i++)
    {
        channels->append(ui->listOfChannels->item(i)->text());
    }
    ui->listOfChannels->clear();
    emit channelListModified(channels);
}
