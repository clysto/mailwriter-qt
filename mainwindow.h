#ifndef MAILWRITER_QT_MAINWINDOW_H
#define MAILWRITER_QT_MAINWINDOW_H

#include <QMainWindow>
#include "api.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public slots:

    void sendMail();

public:
    MainWindow(Api *api, QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Api *api;
};

#endif //MAILWRITER_QT_MAINWINDOW_H
