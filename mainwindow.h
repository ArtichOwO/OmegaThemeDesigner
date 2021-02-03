#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QLineEdit>
#include <QSignalMapper>

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "json.hpp"

using namespace std;

using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool loadProject();
    void saveJSON();
    //void testTestTest();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
