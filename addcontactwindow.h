#ifndef ADDCONTACTWINDOW_H
#define ADDCONTACTWINDOW_H

#include <QDialog>

namespace Ui {
class AddContactWindow;
}

class AddContactWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactWindow(QWidget *parent = 0);
    ~AddContactWindow();

private:
    Ui::AddContactWindow *ui;

signals:
    void addNewContact(QString _id, QString _name);
    void cancel();
private slots:
    void on_cancelButton_clicked();
    void on_addButton_clicked();
};

#endif // ADDCONTACTWINDOW_H
