#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addChannel_clicked();
    void changeEvent(QEvent*);
    void on_deleteChannel_clicked();

private:
    Ui::MainWindow  *ui;
    QListWidgetItem *currentItem;
    QSystemTrayIcon *trayIcon;
    QSettings        settings;
};

#endif // MAINWINDOW_H
