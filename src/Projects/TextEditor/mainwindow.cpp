#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>       //
#include "mainwindow.h"
#include "aboutDialog.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent){
    ui.setupUi(this);
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->showMaximized();
    InitializeWindow();
}

void Mainwindow::InitializeWindow(){
    bar_menu = QMainWindow::menuBar();
    bar_tool = QMainWindow::addToolBar("Tool bar");
    bar_status = QMainWindow::statusBar();

    menu_file = menuBar()->addMenu("file");
    menu_help = menuBar()->addMenu("help");
    menu_about = menuBar()->addMenu(QStringLiteral("����"));

    action_new = menu_file->addAction("new");
    action_open = menu_file->addAction("open");
    action_save = menu_file->addAction("save");
    action_save_as = menu_file->addAction("save as");

    action_about = menu_about->addAction("About");

    //�������Ĵ�������
    textEditor = new QTextEdit(this);
    setCentralWidget(textEditor);

    //�����źźͲ�
    connect(action_about, SIGNAL(triggered()), this, SLOT(OnActionAboutDialog()));
    connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpenFile()));
    connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSaveFile()));
    connect(action_save_as, SIGNAL(triggered()), this, SLOT(OnActionSaveasFile()));
}

bool Mainwindow::OnActionOpenFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "open file dialog", "C:/Users/Administrator/desktop", "text files(*.txt);;my files(*.jgt)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to open file: " + file.errorString());
        return false;
    }
    
    this->SetCurrentFile(fileName);
    setWindowTitle(fileName);
    QTextStream textStream(&file);

    QString text = textStream.readAll();
    textEditor->setText(text);
    file.close();

    return true;
}
bool Mainwindow::OnActionSaveFile() {
    QString fileName = this->GetCurrentFile();

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to save file: " + file.errorString());
        return false;
    }

    QTextStream out(&file);
    QString text = textEditor->toPlainText();
    out << text;
    file.close();
    return true;
}
bool Mainwindow::OnActionSaveasFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "save file dialog", "C:/Users/Administrator/desktop", "text files(*.txt);;my files(*.jgt)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to open file: " + file.errorString());
        return false;
    }

    QTextStream out(&file);
    QString text = textEditor->toPlainText();
    out << text;
    file.close();
    return true;
}
void Mainwindow::OnActionAboutDialog(){
    AboutDialog* dialog_about = new AboutDialog;
    dialog_about->show();
}

void Mainwindow::SetCurrentFile(const QString currentFile) {
    this->currentFile = currentFile;
}
QString Mainwindow::GetCurrentFile(){
    return this->currentFile;
}
Mainwindow::~Mainwindow(){
}
