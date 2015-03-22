#ifndef CORE_H
#define CORE_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include "dialogsettings.h"


class core : public QWidget
{
    Q_OBJECT

public:
    explicit core();
    ~core();

private slots:
    void commitChanges(QStringList *channels);
    void settingsTriggered();

private:
    void            setTrayMenu();
    void            setTray();
    bool            loadSettings();
    void            saveSettings();
    QSystemTrayIcon *trayIcon;
    QSettings        settings;
    QMenu           *trayMenu;
    dialogSettings  *settingsWindow;
    QStringList     *channelList;

};

#endif // CORE_H
