#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <regex>
#include <QMessageBox>

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    ui->udpSizeLineEdit->setText(QString::number(settings.getUdpSize()));
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_applyButton_clicked()
{
    QString udpSizeStr = ui->udpSizeLineEdit->text();
    const std::regex check_size(R"(^\d+$)");
    if (!std::regex_match(udpSizeStr.toStdString().c_str(), check_size)){
        QMessageBox::warning(this,"Error", "Incorrect input");
        return;
    }
    int udpSize = udpSizeStr.toInt();
    if (udpSize < 45){
        udpSize = 45;
    }
    settings.setUdpSize(udpSize);
    ui->udpSizeLineEdit->setText(QString::number(settings.getUdpSize()));
    emit setChatSizeSettings(udpSize);
}

void SettingWindow::on_cancelButton_clicked()
{
    ui->udpSizeLineEdit->setText(QString::number(settings.getUdpSize()));
    emit cancel();
}
