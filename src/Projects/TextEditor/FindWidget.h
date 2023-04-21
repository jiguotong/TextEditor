#pragma once

#include <QMainWindow>
#include "ui_FindWidget.h"

class FindWidget : public QMainWindow
{
	Q_OBJECT

public:
	FindWidget(QWidget *parent = nullptr);
	~FindWidget();
	bool GetText(QString& findText);
signals:
	void SendText(QString str);
	void SendFindPreSignal();
	void SendFindNextSignal();
	void SendCloseSignal();

private slots:
	void OnTextChanged();
	void OnBtnFindPre();
	void OnBtnFindNext();
	void OnBtnCloseWidget();
private:
	Ui::FindWidgetClass ui;
};
