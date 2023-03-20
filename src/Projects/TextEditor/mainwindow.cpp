#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include "mainwindow.h"
#include "aboutDialog.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    InitializeWindow();
}

void Mainwindow::InitializeWindow()
{
    bar_menu = QMainWindow::menuBar();
    bar_tool = QMainWindow::addToolBar("Tool bar");
    bar_status = QMainWindow::statusBar();

    menu_file = menuBar()->addMenu("file");
    menu_help = menuBar()->addMenu("help");
    menu_about = menuBar()->addMenu(QStringLiteral("¹ØÓÚ"));

    action_new = menu_file->addAction("new");
    action_open = menu_file->addAction("open");
    action_save = menu_file->addAction("save");
    action_save_as = menu_file->addAction("save as");

    action_about = menu_about->addAction("About");

    connect(action_about, SIGNAL(triggered()), this, SLOT(popAboutDialog()));
}

void Mainwindow::popAboutDialog()
{
    qDebug() << "trigger about menu";
    AboutDialog* dialog_about = new AboutDialog;
    dialog_about->show();
}

Mainwindow::~Mainwindow()
{}
