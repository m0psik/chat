#include "chatwindow.h"
#include "ui_chatwindow.h"

QString ChatWindow::getTime() {
        time_t now = time(nullptr);
        struct tm timeStruct;
        timeStruct = *localtime(&now);
        char res[256];
        strftime(res, sizeof(res), "%H:%M:%S", &timeStruct);
        return res;
    }

ChatWindow::ChatWindow(QString user_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    userId = currentRecvId = user_id;
    ui->setupUi(this);
    ui->userIdLabel->setText(ui->userIdLabel->text() + userId);
    ui->recvIdLabel->setText(ui->recvIdLabel->text() + currentRecvId);
    chat = new UdpChat(userId.toShort(), 5554);
    settingWindow = new SettingWindow();

    connect(chat,
            SIGNAL(sendDataToIncoming(QString)),
            this,
            SLOT(receiveDataFromIncoming(QString)));

    connect(chat,
            SIGNAL(sendDataToOutcoming(QString)),
            this,
            SLOT(receiveDataFromOutcoming(QString)));

    connect(settingWindow,
            SIGNAL(setChatSizeSettings(int&)),
            this,
            SLOT(receiveSizeSettings(int&)));

    connect(settingWindow,
            SIGNAL(cancel()),
            this,
            SLOT(receiveCancelSettings()));
}

ChatWindow::~ChatWindow()
{
    delete settingWindow;
    delete ui;
    delete chat;
}

void ChatWindow::on_signOutButton_clicked()
{
    QMessageBox::StandardButton rep = QMessageBox::question(this, "Sign Out", "Are you really want to sign out?",
                                                            QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::No){
        return;
    }
    emit signOutSignal();
}

void ChatWindow::on_sendButton_clicked()
{
    QString msg = ui->msgLineEdit->text();
    if (msg.isEmpty()){
        return;
    }
    chat->sendMessage(msg,currentRecvId.toInt());
    ui->msgLineEdit->clear();
}


void ChatWindow::receiveDataFromIncoming(QString msg){
    ui->incomingMessage->append("-------------\n" + getTime() +"\n" + msg);
}

void ChatWindow::receiveDataFromOutcoming(QString msg){
    ui->outcomingMessages->append("-------------\n" + getTime() +"\n" + msg);
}

void ChatWindow::on_settingButton_clicked()
{
    this->hide();
    settingWindow->show();
}

void ChatWindow::receiveSizeSettings(int &currentSizeSettings){
    settingWindow->hide();
    this->show();
    chat->calculateDataSize(currentSizeSettings);
}

void ChatWindow::receiveCancelSettings(){
    this->show();
    settingWindow->hide();
}

void ChatWindow::on_addContactButton_clicked()
{
    addContactWindow = new AddContactWindow();

    connect(addContactWindow,
            SIGNAL(addNewContact(QString,QString)),
            this,
            SLOT(receiveNewContact(QString,QString)));

    connect(addContactWindow,
            SIGNAL(cancel()),
            this,
            SLOT(receiveCancelContact()));

    this->hide();
    addContactWindow->show();
}

void ChatWindow::receiveNewContact(QString _id, QString _name){
    delete addContactWindow;
    this->show();
    //добавление контакта
}
void ChatWindow::receiveCancelContact(){
    delete addContactWindow;
    this->show();
}


