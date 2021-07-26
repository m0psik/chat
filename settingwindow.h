#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

private:
    Settings settings;
    Ui::SettingWindow *ui;

signals:
    void setChatSizeSettings(int &currentSizeSettings);
    void cancel();

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();
};

#endif // SETTINGWINDOW_H
