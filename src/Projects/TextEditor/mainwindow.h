#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include "ui_mainwindow.h"
#include "FindWidget.h"
//�ļ���������
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
    Mainwindow(char*, QWidget* parent = nullptr);
    ~Mainwindow();
public:
    void InitializeWindow();
    void SetCurrentFile(const QString currentFile);
    QString GetCurrentFile();

private slots:
    void OnActionAboutDialog();
    bool OnShowFindWidget();
    bool OnFindString();
    // �����滻���
    bool OnActionNewFile();
    bool OnFindPreStr();
    bool OnFindNextStr();
    void ClearHighlight();

    bool OnActionOpenFile();
    bool OnActionSaveFile();
    bool OnActionSaveasFile();
    void OnCursorPosChanged();
    void updateStatusBar(const int row, const int col);

    void recText(QString str);

private:
    /*void mousePressEvent(QMouseEvent* ev);*/
private:
    Ui::MainwindowClass ui;

    //��
    QMenuBar* bar_menu;
    QToolBar* bar_tool;
    QStatusBar* bar_status;
    
    // menu
    QMenu* menu_file;
    QMenu* menu_edit;
    QMenu* menu_help;
    QMenu* menu_about;
    // Actions
    QAction* action_new;
    QAction* action_open;
    QAction* action_save;
    QAction* action_save_as;

    QAction* action_find;
    QAction* action_replace;
    QAction* action_about;

    // ״̬����Ϣ
    QLabel* posLabel;
    //���Ĵ���
    QTextEdit* textEditor;

    //���Ҵ���
    FindWidget* findWidget;
    QString m_findText;           // ��Ҫ���ҵ��ַ���
    QString replaceText;          // ��Ҫ�滻Ϊ���ַ���

    //��ǰ���ļ�
    QString currentFile;
    //��ǰ���ļ��ı����ʽ
    QString currentCode;
};
#endif
