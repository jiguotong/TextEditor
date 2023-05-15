#pragma once

#include <QMainWindow>
#include "ui_FindWidget.h"

enum class ReplaceType {
	one,
	all
};
class FindWidget : public QMainWindow
{
	Q_OBJECT

public:
	FindWidget(QWidget *parent = nullptr);
	~FindWidget();
	bool GetText(QString& findText);
signals:
	void SendText(QString str);
	void SendReplaceText(QString str, ReplaceType type);
	void SendFindPreSignal();
	void SendFindNextSignal();
	void SendCloseSignal();

private slots:
	void OnTextChanged();
	void OnBtnFindPre();
	void OnBtnFindNext();
	void OnBtnCloseWidget();
	void OnBtnSwitchReplace();
	void OnBtnReplaceClicked();
	void OnBtnReplaceAllClicked();
private:
	Ui::FindWidgetClass ui;
	bool m_switchReplace;
};
