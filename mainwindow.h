#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <regex>
#include "chatwindow.h"

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
    void on_pushButton_2_clicked();

    void on_exitButton_clicked();

    void signOutSlot();

private:
    Ui::MainWindow *ui;
    ChatWindow *chatWindow;
};

#endif // MAINWINDOW_H
