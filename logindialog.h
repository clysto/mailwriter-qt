#ifndef MAILWRITER_QT_LOGINDIALOG_H
#define MAILWRITER_QT_LOGINDIALOG_H

#include <QDialog>
#include "api.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    LoginDialog(Api *api, QWidget *parent = nullptr);

    ~LoginDialog();

    QString getEmail();

    QString getPass();

    void accept();

private:
    Ui::Dialog *ui;
    Api *api;
};

#endif //MAILWRITER_QT_LOGINDIALOG_H
