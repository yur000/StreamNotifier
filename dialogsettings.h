#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QListWidgetItem>

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
    void showSettings(QStringList *channels);
private slots:
    void on_addChannel_clicked();
    void on_deleteChannel_clicked();
    void on_saveButton_clicked();

signals:
    void channelListModified(QStringList *channels);

private:
    Ui::dialogSettings *ui;
};

#endif // DIALOGSETTINGS_H
