#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("Yuri_Babinets", "StreamNotifier")
{
    ui->setupUi(this);
    QMenu *trayMenu = new QMenu(this);
    trayMenu->addAction("&Настройки", this, SLOT(show()), Qt::CTRL + Qt::Key_S);
    trayMenu->addSeparator();
    trayMenu->addAction("&Выход", this, SLOT(close()), Qt::ALT + Qt::Key_F4);
    trayIcon = new QSystemTrayIcon(QIcon(":/icon.ico"), this);
    trayIcon->setToolTip("Twitch Stream Notifier");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
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



