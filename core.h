#ifndef CORE_H
#define CORE_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QDesktopServices>
#include "dialogsettings.h"
#include "networkrequests.h"


class core : public QWidget
{
    Q_OBJECT

public:
    explicit core();
    ~core();

private slots:
    void commitChanges(QStringList *channels);
    void settingsTriggered();
    void parseData(QByteArray json);
    void timeToCheck();
    void openLastURL();
    void checkUpdates();

private:
    void            setTrayMenu();
    void            setTray();
    bool            loadSettings();
    void            saveSettings();
    void            notifyStream(QString user, QString game);
    void            notifyUpdate(float version);
    QTimer          *checkTimer;
    NetworkRequests *web;
    QSystemTrayIcon *trayIcon;
    QSettings        settings;
    QMenu           *trayMenu;
    dialogSettings  *settingsWindow;
    QStringList     *channelList;
    QStringList     *channelOnlineList;
    QUrl             lastURL;
    int              currentChannel;
    int              timerInterval;
    bool             isCheckingUpdate;
    float            localVersion;

};

#endif // CORE_H
