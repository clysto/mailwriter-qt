#include "mainwindow.h"

#include <QMessageBox>
#include <QtWebEngineWidgets>
#include <algorithm>

#include "./ui_mainwindow.h"
#include "api.h"

MainWindow::MainWindow(Api *api, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->api = api;
  this->ui->statusbar->showMessage("欢迎来到你的信箱 v0.0.1", 1000);
  this->ui->statusbar->showMessage(
      ("current user: " + api->currentUser()).c_str());
  webview = new QWebEngineView();
  this->ui->webContainer->addWidget(webview);
  webview->setUrl(QUrl("qrc:/index.html"));
  webview->maximumSize();
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  webview->setSizePolicy(sizePolicy);
  webview->show();
}

MainWindow::~MainWindow() {
  delete ui;
  delete webview;
}

void MainWindow::sendMail() {
  webview->page()->runJavaScript("getContent();", [this](const QVariant &v) {
    std::string to = ui->lineEdit->text().toStdString();
    std::string subject = ui->lineEdit_2->text().toStdString();
    std::string content = v.toString().toStdString();
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
    // clear ckeditor content
    QMessageBox::information(this, "发送成功!", "发送成功!");
  });
}
