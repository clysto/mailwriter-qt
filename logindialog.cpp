#include "logindialog.h"
#include "./ui_logindialog.h"

#include <QMessageBox>
#include "api.h"

LoginDialog::LoginDialog(Api *api, QWidget *parent)
        : QDialog(parent), ui(new Ui::Dialog), api(api) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

QString LoginDialog::getEmail() {
    return this->ui->lineEdit->text();
}

QString LoginDialog::getPass() {
    return this->ui->lineEdit_2->text();
}

void LoginDialog::accept() {
    QString mail = this->getEmail();
    QString pass = this->getPass();
    try {
        api->login(mail.toStdString(), pass.toStdString());
    } catch (...) {
        QMessageBox::warning(this, "登录失败!", "密码错误!");
        return;
    }
    QDialog::accept();
}
