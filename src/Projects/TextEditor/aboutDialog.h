#ifndef _ABOUTDIALOG_H
#define _ABOUTDIALOG_H
#include <QDialog>
#include <QLabel>
class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* parent = nullptr);
	~AboutDialog();
public:
	void InitializeDialog();

private:
	QLabel* label_text;
	QLabel* label_version;
	QLabel* label_img;
public:
};


#endif
