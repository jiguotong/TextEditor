#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QShortcut>
#include <QTextCodec>       //
#include "mainwindow.h"
#include "aboutDialog.h"
//#include "FindWidget.h"

QString GetCorrectUnicode(const QByteArray& text, QString& code);
Mainwindow::Mainwindow(char* filePath,QWidget *parent)
    : currentFile(filePath),QMainWindow(parent){
    ui.setupUi(this);
    
    InitializeWindow();
}
Mainwindow::~Mainwindow(){
    if (textEditor) {
        delete textEditor;
        textEditor = NULL;
    }
}
        
void Mainwindow::InitializeWindow(){
    //设置窗口外观
    setWindowIcon(QIcon(":/textEditor/res/text.png"));
    setWindowTitle("Text Editor");
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->showMaximized();

    //菜单栏、工具栏、状态栏
    bar_menu = QMainWindow::menuBar();
    bar_tool = QMainWindow::addToolBar("Tool bar");
    bar_status = QMainWindow::statusBar();

    //菜单栏编辑
    menu_file = menuBar()->addMenu("File");
    menu_edit = menuBar()->addMenu("Edit");
    menu_help = menuBar()->addMenu("Help");
    menu_about = menuBar()->addMenu(QStringLiteral("关于"));

    //功能编辑
    action_new = menu_file->addAction("New");
    action_open = menu_file->addAction("Open");
    action_save = menu_file->addAction("Save     (ctrl+s)");
    action_save_as = menu_file->addAction("Save as");
    action_about = menu_about->addAction("About");
    
    action_find = menu_edit->addAction("Find");
    
    action_new->setIcon(QIcon(":/textEditor/res/create.png"));
    action_open->setIcon(QIcon(":/textEditor/res/open.png"));
    action_save->setIcon(QIcon(":/textEditor/res/save.png"));


    //工具栏编辑
    bar_tool->addAction(action_new);
    bar_tool->addAction(action_open);
    bar_tool->addAction(action_save);

    
    // 设置快捷键
    action_find->setShortcut(tr("Ctrl+F"));

    //设置快捷键
    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(QKeySequence("Ctrl+S"));
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(OnActionSaveFile()));

    //设置中心窗口属性
    textEditor = new QTextEdit(this);
    setCentralWidget(textEditor);

    //判断当前是否有文档打开
    if (!currentFile.isEmpty()){
        QFile file(currentFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Warning", "Fail to open file: " + file.errorString());
            return;
        }
        QByteArray buf = file.readAll();
        textEditor->setText(GetCorrectUnicode(buf, this->currentCode));
        file.close();
    }
    
    //连接信号和槽
    connect(action_about, SIGNAL(triggered()), this, SLOT(OnActionAboutDialog()));
    connect(action_new, SIGNAL(triggered()), this, SLOT(OnActionNewFile()));
    connect(action_open, SIGNAL(triggered()), this, SLOT(OnActionOpenFile()));
    connect(action_save, SIGNAL(triggered()), this, SLOT(OnActionSaveFile()));
    connect(action_save_as, SIGNAL(triggered()), this, SLOT(OnActionSaveasFile()));
    connect(action_find, SIGNAL(triggered()), this, SLOT(OnShowFindWidget()));
}

bool Mainwindow::OnActionNewFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "new file dialog", "D:", "text files(*.txt);;my files(*.jgt)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to create file: " + file.errorString());
        return false;
    }
    this->SetCurrentFile(fileName);
    return true;
}

bool Mainwindow::OnActionOpenFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "open file dialog", "D:", "text files(*.txt);;my files(*.jgt)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to open file: " + file.errorString());
        return false;
    }
    
    QByteArray buf = file.readAll();
    this->SetCurrentFile(fileName);
    textEditor->setText(GetCorrectUnicode(buf, this->currentCode));
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
    out.setCodec(currentCode.toLatin1().data());
    QString text = textEditor->toPlainText();
    out << text;
    file.close();
    return true;
}

bool Mainwindow::OnActionSaveasFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "save file dialog", "D:", "text files(*.txt);;my files(*.jgt)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Fail to open file: " + file.errorString());
        return false;
    }

    QTextStream out(&file);
    out.setCodec(currentCode.toLatin1().data());
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
bool Mainwindow::OnShowFindWidget() {
    findWidget = new FindWidget(this);
    findWidget->move(this->width() - 500, 100);
    findWidget->show();
    connect(findWidget, &FindWidget::SendText, this, &Mainwindow::recText);
    connect(findWidget, &FindWidget::SendFindPreSignal, this, &Mainwindow::OnFindPreStr);
    connect(findWidget, &FindWidget::SendFindNextSignal, this, &Mainwindow::OnFindNextStr);
    connect(findWidget, &FindWidget::SendCloseSignal, this, &Mainwindow::ClearHighlight);
    return true;
}

bool Mainwindow::OnFindString()
{
    // 清空全部高亮
    QTextDocument* document = textEditor->document();
    QTextCursor cursor(document);
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setBackground(QBrush());
    cursor.mergeCharFormat(format);
    textEditor->mergeCurrentCharFormat(format);

    
    // 搜索全部高亮
    bool found = false;
    QTextCursor highlight_cursor(document);

    // 设置高亮
    cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
    cursor.beginEditBlock();
    QTextCharFormat color_format=highlight_cursor.charFormat();
    //color_format.setForeground(Qt::red);
    color_format.setBackground(Qt::yellow);
    bool isFirstStr = true;
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本
        //highlight_cursor = document->find(m_findText, highlight_cursor, QTextDocument::FindWholeWords);//整字查找，匹配整个单词
        highlight_cursor = document->find(m_findText, highlight_cursor);

        if (!highlight_cursor.isNull()) {
            if (!found)
                found = true;
            color_format.setBackground(Qt::yellow);
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    return true;
}

bool Mainwindow::OnFindPreStr() {
    if (m_findText.isEmpty())
        return false;
    //// debugg_test
    //QMessageBox::information(this, "Warning", "Find previous!", QMessageBox::Ok);
    // 查找上一个
    if (textEditor->find(m_findText, QTextDocument::FindBackward)) {
        // 查找到后高亮显示
        QPalette palette = textEditor->palette();
        palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
        textEditor->setPalette(palette);
    }
    else {
        QMessageBox::information(this, "Warning", "Already reached the top!", QMessageBox::Ok);
        return false;
    }
    return true;
}

bool Mainwindow::OnFindNextStr() {
    if (m_findText.isEmpty())
        return false;
    // 查找下一个
    if (textEditor->find(m_findText)) {
        // 查找到后高亮显示
        QPalette palette = textEditor->palette();
        palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
        textEditor->setPalette(palette);
    }
    else {
        QMessageBox::information(this, "Warning", "Already reached the bottom!", QMessageBox::Ok);
        return false;
    }

    return true;
}

void Mainwindow::recText(QString str) {
    // 高亮显示所有
    m_findText = str;
    OnFindString();     //开始查找

    // 重置光标
    QTextCursor tmpCursor = textEditor->textCursor();
    tmpCursor.movePosition(QTextCursor::Start);
    textEditor->setTextCursor(tmpCursor);

    // 高亮显示第一个串
    OnFindNextStr();
}
void Mainwindow::ClearHighlight(){
    // 清空高亮
    QTextDocument* document = textEditor->document();
    QTextCursor cursor(document);
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setBackground(QBrush());
    cursor.mergeCharFormat(format);
    textEditor->mergeCurrentCharFormat(format);

    // 销毁搜索对话框
    m_findText.clear();
    findWidget->destroyed();
    delete findWidget;
    findWidget = NULL;

    // 重置光标
    QTextCursor tmpCursor = textEditor->textCursor();
    tmpCursor.movePosition(QTextCursor::Start);
    textEditor->setTextCursor(tmpCursor);
}
// 非成员函数
//得到正确转码之后的文本
QString GetCorrectUnicode(const QByteArray& text, QString& code)
{
    QTextCodec::ConverterState state;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QString strtext = codec->toUnicode(text.constData(), text.size(), &state);
    if (state.invalidChars > 0){
        code = "GBK";
        strtext = QTextCodec::codecForName("GBK")->toUnicode(text);
    }
    else{
        code = "UTF-8";
        strtext = text;
    }

    return strtext;
}
