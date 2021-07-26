#include "addcontactwindow.h"
#include "ui_addcontactwindow.h"
#include <regex>
#include <QMessageBox>

AddContactWindow::AddContactWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContactWindow)
{
    ui->setupUi(this);
}

AddContactWindow::~AddContactWindow()
{
    delete ui;
}

void AddContactWindow::on_cancelButton_clicked()
{
    emit cancel();
}

void AddContactWindow::on_addButton_clicked()
{
    QString user_id = ui->userIdLineEdit->text();
    QString user_name = ui->userNameLineEdit->text();
    if (user_id.length() == 0){
        QMessageBox::warning(this,"Error", "Enter user ID");
        return;
    }
    if (user_name.length() == 0){
        QMessageBox::warning(this,"Error", "Enter user name");
        return;
    }
    const std::regex check_id(R"(^\d{3}$)");
    if (!std::regex_match(user_id.toStdString().c_str(), check_id)){
        QMessageBox::warning(this,"Error", "Incorrect ID");
        return;
    }
    emit addNewContact(user_id,user_name);
}
