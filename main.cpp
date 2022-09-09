#include <QApplication>
#include <QFile>
#include <iostream>
#include <nlohmann/json.hpp>

#include "api.h"
#include "logindialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Api api("http://114.214.170.155:8090");
  LoginDialog loginDialog(&api);
  QFile f("session.json");
  if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&f);
    std::string content = in.readAll().toStdString();
    api.setAuth(nlohmann::json::parse(content));
    f.close();
  } else {
    if (loginDialog.exec() == QDialog::Rejected) {
      return 0;
    }
  }
  MainWindow w(&api);
  w.show();
  return QApplication::exec();
}
