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
Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent){
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
    //���ô������
    setWindowIcon(QIcon(":/textEditor/res/text.png"));
    setWindowTitle("Text Editor");
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    this->showMaximized();

    //�˵�������������״̬��
    bar_menu = QMainWindow::menuBar();
    bar_tool = QMainWindow::addToolBar("Tool bar");
    bar_status = QMainWindow::statusBar();

    //�˵����༭
    menu_file = menuBar()->addMenu("File");
    menu_edit = menuBar()->addMenu("Edit");
    menu_help = menuBar()->addMenu("Help");
    menu_about = menuBar()->addMenu(QStringLiteral("����"));

    //���ܱ༭
    action_new = menu_file->addAction("New");
    action_open = menu_file->addAction("Open");
    action_save = menu_file->addAction("Save     (ctrl+s)");
    action_save_as = menu_file->addAction("Save as");
    action_about = menu_about->addAction("About");
    
    action_find = menu_edit->addAction("Find");
    
    action_new->setIcon(QIcon(":/textEditor/res/create.png"));
    action_open->setIcon(QIcon(":/textEditor/res/open.png"));
    action_save->setIcon(QIcon(":/textEditor/res/save.png"));


    //�������༭
    bar_tool->addAction(action_new);
    bar_tool->addAction(action_open);
    bar_tool->addAction(action_save);

    
    // ���ÿ�ݼ�
    action_find->setShortcut(tr("Ctrl+F"));

    //���ÿ�ݼ�
    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(QKeySequence("Ctrl+S"));
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(OnActionSaveFile()));

    //�������Ĵ�������
    textEditor = new QTextEdit(this);
    setCentralWidget(textEditor);

    //�����źźͲ�
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
    // ���ȫ������
    QTextDocument* document = textEditor->document();
    QTextCursor cursor(document);
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setBackground(QBrush());
    cursor.mergeCharFormat(format);
    textEditor->mergeCurrentCharFormat(format);

    
    // ����ȫ������
    bool found = false;
    QTextCursor highlight_cursor(document);

    // ���ø���
    cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
    cursor.beginEditBlock();
    QTextCharFormat color_format=highlight_cursor.charFormat();
    //color_format.setForeground(Qt::red);
    color_format.setBackground(Qt::yellow);
    bool isFirstStr = true;
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //����ָ�����ı�
        //highlight_cursor = document->find(m_findText, highlight_cursor, QTextDocument::FindWholeWords);//���ֲ��ң�ƥ����������
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
    // ������һ��
    if (textEditor->find(m_findText, QTextDocument::FindBackward)) {
        // ���ҵ��������ʾ
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
    // ������һ��
    if (textEditor->find(m_findText)) {
        // ���ҵ��������ʾ
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
    // ������ʾ����
    m_findText = str;
    OnFindString();     //��ʼ����

    // ���ù��
    QTextCursor tmpCursor = textEditor->textCursor();
    tmpCursor.movePosition(QTextCursor::Start);
    textEditor->setTextCursor(tmpCursor);

    // ������ʾ��һ����
    OnFindNextStr();
}
void Mainwindow::ClearHighlight(){
    // ��ո���
    QTextDocument* document = textEditor->document();
    QTextCursor cursor(document);
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setBackground(QBrush());
    cursor.mergeCharFormat(format);
    textEditor->mergeCurrentCharFormat(format);

    // ���������Ի���
    m_findText.clear();
    findWidget->destroyed();
    delete findWidget;
    findWidget = NULL;

    // ���ù��
    QTextCursor tmpCursor = textEditor->textCursor();
    tmpCursor.movePosition(QTextCursor::Start);
    textEditor->setTextCursor(tmpCursor);
}
// �ǳ�Ա����
//�õ���ȷת��֮����ı�
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
