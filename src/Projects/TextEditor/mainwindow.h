#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
public:
    void InitializeWindow();

public slots:
    void popAboutDialog();
private:
    Ui::MainwindowClass ui;

    //À¸
    QMenuBar* bar_menu;
    QToolBar* bar_tool;
    QStatusBar* bar_status;
    
    // menu
    QMenu* menu_file;
    QMenu* menu_help;
    QMenu* menu_about;
    // Actions
    QAction* action_new;
    QAction* action_open;
    QAction* action_save;
    QAction* action_save_as;

    QAction* action_about;
};
