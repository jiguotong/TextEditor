#include "FindWidget.h"
FindWidget::FindWidget(QWidget*parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 快捷键
	QKeySequence keyUp(Qt::Key_Up);
	QKeySequence keyDown(Qt::Key_Down);

	ui.btnPreString->setShortcut(keyUp);
	ui.btnNextString->setShortcut(keyDown);

	this->resize(600, 60);
	m_switchReplace = false;

	ui.btnOpenReplace->setIcon(QIcon(":/textEditor/res/replace.png"));

	// 连接
	connect(ui.editorFind, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));
	connect(ui.btnReplace, &QPushButton::clicked, this, &FindWidget::OnBtnReplaceClicked);
	connect(ui.btnReplaceAll, &QPushButton::clicked, this, &FindWidget::OnBtnReplaceAllClicked);
	connect(ui.btnPreString, &QPushButton::clicked, this, &FindWidget::OnBtnFindPre);
	connect(ui.btnNextString, &QPushButton::clicked, this, &FindWidget::OnBtnFindNext);
	connect(ui.btnClose, &QPushButton::clicked, this, &FindWidget::OnBtnCloseWidget);
	connect(ui.btnOpenReplace , &QPushButton::clicked, this, &FindWidget::OnBtnSwitchReplace);

}
bool FindWidget::GetText(QString& findText) {
	findText =  ui.editorFind->toPlainText();
	if (findText.isEmpty())
		return false;
	return true;
}
FindWidget::~FindWidget()
{}

// 内容变化时发送信号
void FindWidget::OnTextChanged() {
	emit SendText(ui.editorFind->toPlainText());
}
void FindWidget::OnBtnFindPre() {
	emit SendFindPreSignal();
}
void FindWidget::OnBtnFindNext() {
	emit SendFindNextSignal();
}
void FindWidget::OnBtnCloseWidget() {
	this->close();
	emit SendCloseSignal();
}
void FindWidget::OnBtnReplaceClicked() {
	emit SendReplaceText(ui.editorReplace->toPlainText(), ReplaceType::one);
}
void FindWidget::OnBtnReplaceAllClicked(){
	emit SendReplaceText(ui.editorReplace->toPlainText(), ReplaceType::all);
}

void FindWidget::OnBtnSwitchReplace()
{
	if (m_switchReplace) {
		m_switchReplace = false;
		this->resize(600, 60);
	}
	else {
		m_switchReplace = true;
		this->resize(600, 120);
	}
		
}

void FindWidget::closeEvent(QCloseEvent* e) {
	// 想要实现的操作
	emit SendCloseSignal();
	this->close();
}
