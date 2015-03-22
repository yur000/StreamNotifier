#include "core.h"
#include "ui_mainwindow.h"

core::core() :
    settings("Yuri_Babinets", "StreamNotifier")
{
    channelList = new QStringList;
    settingsWindow = new dialogSettings;
    setTrayMenu();
    setTray();
    if(!loadSettings())
    {
        settingsWindow->show();
        trayIcon->showMessage("Twitch Steam Notifier приветствует Вас!",
                              "Добавьте свои любимые каналы, а я Вас оповещу о начале трансляций!",
                              QSystemTrayIcon::Information);
    }
    connect(settingsWindow, SIGNAL(channelListModified(QStringList*)), SLOT(commitChanges(QStringList*)));
}

core::~core()
{
    saveSettings();
}

void core::setTrayMenu()
{
    trayMenu = new QMenu;
    trayMenu->addAction("&Настройки", this, SLOT(settingsTriggered()), Qt::CTRL + Qt::Key_S);
    trayMenu->addSeparator();
    trayMenu->addAction("&Выход", qApp, SLOT(quit()), Qt::ALT + Qt::Key_F4);
}

void core::setTray()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/icon.ico"), this);
    trayIcon->setToolTip("Twitch Stream Notifier");
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

bool core::loadSettings()
{
    settings.beginGroup("/Channels");
    int channelsNum = settings.value("NumberOfChannels", 0).toInt();
    for(int i = 0; i < channelsNum; i++)
    {
        channelList->append(settings.value("Channel_" + QString::number(i), "Delete ME").toString());
    }
    settings.endGroup();
    if(channelsNum) return true;
    else return false;
}

void core::saveSettings()
{
    settings.beginGroup("/Channels");
    settings.setValue("NumberOfChannels", channelList->count());
    for(int i = 0; i < channelList->count(); i++)
    {
        settings.setValue("Channel_" + QString::number(i), channelList->at(i));
    }
    settings.endGroup();
}

void core::commitChanges(QStringList *channels)
{
    channelList->clear();
    channelList->append(*channels);
}

void core::settingsTriggered()
{
    settingsWindow->showSettings(channelList);
}



