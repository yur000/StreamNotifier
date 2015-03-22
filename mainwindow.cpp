#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("Yuri_Babinets", "StreamNotifier")
{
    ui->setupUi(this);
    if(!loadSettings()) show();
    setTrayMenu();
    setTray();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::setTrayMenu()
{
    trayMenu = new QMenu(this);
    trayMenu->addAction("&Настройки", this, SLOT(show()), Qt::CTRL + Qt::Key_S);
    trayMenu->addSeparator();
    trayMenu->addAction("&Выход", this, SLOT(close()), Qt::ALT + Qt::Key_F4);
}

void MainWindow::setTray()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/icon.ico"), this);
    trayIcon->setToolTip("Twitch Stream Notifier");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

bool MainWindow::loadSettings()
{
    settings.beginGroup("/Channels");
    int channelsNum = settings.value("NumberOfChannels", 0).toInt();
    for(int i = 0; i < channelsNum; i++)
    {
        ui->listOfChannels->addItem(settings.value("Channel_" + QString::number(i), "Delete ME").toString());
    }
    settings.endGroup();
    if(channelsNum) return true;
    else return false;
}

void MainWindow::saveSettings()
{
    settings.beginGroup("/Channels");
    int channelsNum = ui->listOfChannels->count();
    settings.setValue("NumberOfChannels", channelsNum);
    for(int i = 0; i < channelsNum; i++)
    {
        settings.setValue("Channel_" + QString::number(i), ui->listOfChannels->item(i)->text());
    }
    settings.endGroup();
}

void MainWindow::on_addChannel_clicked()
{
    ui->listOfChannels->addItem( ui->channelName->text());
    ui->channelName->clear();
}


void MainWindow::on_deleteChannel_clicked()
{
    delete ui->listOfChannels->currentItem();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this -> hide();
        }
    }
}



