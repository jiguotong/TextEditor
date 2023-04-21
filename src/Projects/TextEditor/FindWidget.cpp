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

	// 连接
	connect(ui.editor, SIGNAL(textChanged()), this, SLOT(OnTextChanged()));
	connect(ui.btnPreString, &QPushButton::clicked, this, &FindWidget::OnBtnFindPre);
	connect(ui.btnNextString, &QPushButton::clicked, this, &FindWidget::OnBtnFindNext);
	connect(ui.btnClose, &QPushButton::clicked, this, &FindWidget::OnBtnCloseWidget);
}
bool FindWidget::GetText(QString& findText) {
	findText =  ui.editor->toPlainText();
	if (findText.isEmpty())
		return false;
	return true;
}
FindWidget::~FindWidget()
{}

// 内容变化时发送信号
void FindWidget::OnTextChanged() {
	emit SendText(ui.editor->toPlainText());
}
void FindWidget::OnBtnFindPre() {
	emit SendFindPreSignal();
}
void FindWidget::OnBtnFindNext() {
	emit SendFindNextSignal();
}
void FindWidget::OnBtnCloseWidget() {
	emit SendCloseSignal();
}
