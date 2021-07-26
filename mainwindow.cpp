#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
    //delete chatWindow;
}

void MainWindow::on_pushButton_2_clicked(){
    QString user_id = ui->idLabel->text();
    const std::regex check_id(R"(^\d{3}$)");
    if (!std::regex_match(user_id.toStdString().c_str(), check_id)){
        QMessageBox::warning(this,"Error", "Incorrect ID");
        return;
    }
    this->hide();
    chatWindow = new ChatWindow(user_id);
    connect(chatWindow,
            SIGNAL(signOutSignal()),
            this,
            SLOT(signOutSlot()));
    chatWindow->show();
    ui->idLabel->clear();
}

void MainWindow::on_exitButton_clicked(){
    QMessageBox::StandardButton rep = QMessageBox::question(this, "Quit", "Are you really want to quit?",
                                                            QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::No){
        return;
    }
    //this->close();
    QApplication::quit();
}

void MainWindow::signOutSlot(){
    delete chatWindow;
    this->show();
}
