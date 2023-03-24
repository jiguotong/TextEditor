#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
//文件编码类型
enum class EncodeFormat {
    ANSI = 0,
    GBK,
    UTF8,
    UTF16LE,
    UTF16BE,
    UTF8BOM,
};
class QTextEdit;
class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
public:
    void InitializeWindow();
    void SetCurrentFile(const QString currentFile);
    QString GetCurrentFile();

private slots:
    void OnActionAboutDialog();
    bool OnActionOpenFile();
    bool OnActionSaveFile();
    bool OnActionSaveasFile();
private:
    Ui::MainwindowClass ui;

    //栏
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

    //中心窗口
    QTextEdit* textEditor;

    //当前打开文件
    QString currentFile;
    //当前打开文件的编码格式
    QString currentCode;
};
#endif
