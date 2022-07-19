#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "api.h"
#include <QMessageBox>

MainWindow::MainWindow(Api *api, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->api = api;
    this->ui->statusbar->showMessage("欢迎来到你的信箱 v0.0.1", 1000);
    this->ui->statusbar->showMessage(
            ("current user: " + api->currentUser()).c_str()
    );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendMail() {
    std::string to = ui->lineEdit->text().toStdString();
    std::string subject = ui->lineEdit_2->text().toStdString();
    std::string content = ui->plainTextEdit->toPlainText().toStdString();
    try {
        to = api->getUserId(to);
    } catch (...) {
        QMessageBox::warning(this, "发送失败!", "用户不存在!");
        return;
    }
    try {
        api->createMail(to, subject, content);
    } catch (...) {
        QMessageBox::information(this, "发送失败!", "发送失败!");
        return;
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->plainTextEdit->clear();
    QMessageBox::information(this, "发送成功!", "发送成功!");
}
