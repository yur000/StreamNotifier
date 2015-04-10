#include "core.h"
#include "json.h"

core::core() :
    settings("Yuri_Babinets", "StreamNotifier")
{
    localVersion    = 0.2;
    channelList     = new QStringList;
    channelOnlineList=new QStringList;
    settingsWindow  = new dialogSettings;
    web             = new NetworkRequests;
    checkTimer      = new QTimer;
    notifySoundPlayer=new QMediaPlayer;
    currentChannel  = 0;
    setTrayMenu();
    setTray();
    if(!loadSettings())
    {
        settingsWindow->show();
        trayIcon->showMessage("Twitch Steam Notifier приветствует Вас!",
                              "Добавьте свои любимые каналы, а я оповещу Вас о начале трансляций!",
                              QSystemTrayIcon::Information);
    }
    connect(settingsWindow, SIGNAL(modified(QStringList*, settingsContainer*)), SLOT(commitChanges(QStringList*, settingsContainer*)));
    connect(web, SIGNAL(ready(QByteArray)), SLOT(parseData(QByteArray)));
    connect(checkTimer, SIGNAL(timeout()), SLOT(timeToCheck()));
    connect(trayIcon, SIGNAL(messageClicked()), SLOT(openLastURL()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    checkTimer->start(timerInterval);
    QTimer::singleShot(3 * 60 * 1000, this, SLOT(checkUpdates()));
    notifySoundPlayer->setMedia(QUrl(QFileInfo(pathToSound).absoluteFilePath()));
}

core::~core()
{
    saveSettings();
    trayIcon->deleteLater();
    trayMenu->deleteLater();
    web->deleteLater();
    settingsWindow->deleteLater();
    checkTimer->deleteLater();
    notifySoundPlayer->deleteLater();
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

void core::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            settingsTriggered();
            break;
        default:
            break;
    }
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
    settings.beginGroup("/Settings");
    isSound = settings.value("isSound", true).toBool();
    timerInterval = settings.value("timerInterval", 10*60*1000).toInt();
    pathToSound.append(settings.value("pathToSound", "/ICQ.mp3").toString());
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
    settings.beginGroup("/Settings");
    settings.setValue("isSound", isSound);
    settings.setValue("timerInterval", timerInterval);
    settings.setValue("pathToSound", pathToSound);
    settings.endGroup();
}

void core::commitChanges(QStringList *channels, settingsContainer *notifySettings)
{
    channelList->clear();
    pathToSound.clear();
    channelList->append(*channels);
    pathToSound.append(notifySettings->soundPath);
    timerInterval = notifySettings->timeToCheck;
    isSound = notifySettings->isSound;
    notifySoundPlayer->setMedia(QUrl(QFileInfo(pathToSound).absoluteFilePath()));
}

void core::settingsTriggered()
{
    settingsContainer *notifySettings = new settingsContainer;
    notifySettings->isSound = isSound;
    notifySettings->soundPath = pathToSound;
    notifySettings->timeToCheck = timerInterval;
    settingsWindow->showSettings(channelList, notifySettings);
}

void core::parseData(QByteArray json)
{
    QString json_string(json);
    bool ok;
    QtJson::JsonObject parsed = QtJson::parse(json_string, ok).toMap();
    QtJson::JsonObject tmp;
    if(ok)
    {
        if(isCheckingUpdate & !parsed["stream"].toString().count())
        {
            float version(parsed["version"].toFloat());
            isCheckingUpdate = false;
            if(localVersion < version)
            {
                lastURL.setUrl(parsed["updateurl"].toString());
                notifyUpdate(version);
            }
        }
        else if(parsed["stream"].toMap().contains("channel"))
            {
                tmp = parsed["stream"].toMap();
                tmp = tmp["channel"].toMap();
                if(!channelOnlineList->contains(tmp["name"].toString()))
                {
                    lastURL.setUrl("http://www.twitch.tv/" + tmp["name"].toString());
                    notifyStream(tmp["display_name"].toString(), tmp["game"].toString());
                    channelOnlineList->append(tmp["name"].toString());
                }
            }
            else
            {
                QString broadcasterName(parsed["self"].toString());
                channelOnlineList->removeOne(broadcasterName.remove("https://api.twitch.tv/kraken/streams/"));
            }
    }
}

void core::timeToCheck()
{
    if(currentChannel < channelList->count())
    {
        web->sendRequest(QUrl("https://api.twitch.tv/kraken/streams/" + channelList->at(currentChannel)));
        currentChannel++;
        checkTimer->start(30 * 1000);
    }
    else {
        currentChannel = 0;
        checkTimer->start(timerInterval);
    }
}

void core::notifyStream(QString user, QString game)
{
    if(isSound) notifySoundPlayer->play();
    trayIcon->showMessage(user + " начал трансляцию!",
                          user +" играет в " + game + "! Нажми сюда, чтобы начать смотреть стрим!",
                          QSystemTrayIcon::Information);
}

void core::openLastURL()
{
    QDesktopServices::openUrl(lastURL);
}

void core::checkUpdates()
{
    isCheckingUpdate = true;
    web->sendRequest(QUrl("http://vkupdate.cosmostv.tv/streamnotifier.version"));
}

void core::notifyUpdate(float version)
{
    if(isSound) notifySoundPlayer->play();
    trayIcon->showMessage("Доступна " + QString::number(version) + " версия Twitch Steam Notifier!",
                          "У Вас установлена " + QString::number(localVersion) + " версия. Рекомендуем обновиться! Подробную информацию о обновлении можно узнать кликнув по этому окну.",
                          QSystemTrayIcon::Information);
}


