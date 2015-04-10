#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QListWidgetItem>
#include "settingsstruct.h"

namespace Ui {
class dialogSettings;
}

class dialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dialogSettings(QWidget *parent = 0);
    ~dialogSettings();

public slots:
    void showSettings(QStringList *channels, settingsContainer *notifySettings);

private slots:
    void on_addChannel_clicked();
    void on_deleteChannel_clicked();
    void on_saveButton_clicked();
    void on_isSound_clicked(bool checked);
    void on_minutesToCheck_valueChanged(int arg1);
    void on_callFileDialog_clicked();

signals:
    void modified(QStringList *channels, settingsContainer *notifySettings);

private:
    bool isModified;
    Ui::dialogSettings *ui;
};

#endif // DIALOGSETTINGS_H
