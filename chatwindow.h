#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "udpchat.h"
#include "addcontactwindow.h"
#include "settingwindow.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QString user_id, QWidget *_parent = 0);
    void sendMessage(QString &msg);
    ~ChatWindow();

private slots:
    void on_signOutButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::ChatWindow *ui;
    QString userId;
    QString currentRecvId;
    UdpChat *chat;
    AddContactWindow *addContactWindow;
    SettingWindow *settingWindow;

    static QString getTime();

signals:
    void signOutSignal();

private slots:
    void receiveDataFromIncoming(QString message);
    void receiveDataFromOutcoming(QString messages);

    void receiveSizeSettings(int &currentSizeSettings);
    void receiveCancelSettings();

    void receiveNewContact(QString _id, QString _name);
    void receiveCancelContact();

    void on_addContactButton_clicked();
    void on_settingButton_clicked();
};

#endif // CHATWINDOW_H
