#include "aboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{
    //ui.setupUi(this);
    InitializeDialog();
}

void AboutDialog::InitializeDialog()
{
    this->setFixedSize(500, 200);
    this->setWindowTitle("About TextEditor");

    QPixmap pix = QPixmap(":/textEditor/res/cat.jpg");
    label_img = new QLabel(this); 
    label_img->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));     //控制缩放
    label_img->move((this->width() - label_img->width()) / 2, (this->height() - label_img->width()) / 2);   //label居中显示


    label_text = new QLabel(this);
    label_text->setText("Welcome to use this text editor which is developed by Taibai.Li!\nI sincerely hope that you could have a nice day!");
    label_text->setFont(QFont("STKaiti",14));
    label_text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

AboutDialog::~AboutDialog()
{}