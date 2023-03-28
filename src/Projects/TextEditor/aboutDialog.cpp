#include "aboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{
    //ui.setupUi(this);
    InitializeDialog();
}

void AboutDialog::InitializeDialog()
{
    this->resize(400, 200);
    this->setWindowTitle("About TextEditor");

    QPixmap pix = QPixmap(":/textEditor/res/cat.jpg");
    label_img = new QLabel(this); 
    label_img->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));     //��������
    label_img->move((this->width() - label_img->width()) / 2, (this->height() - label_img->width()) / 2);   //label������ʾ


    label_text = new QLabel(this);
    label_text->setText("Welcome to use this text editor which is developed by Taibai.Li!\nI sincerely hope that you could have a nice day");
    //label_text->move((this->width() - label_text->width()) / 2, 0);
    //label_introduction->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label_text->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

AboutDialog::~AboutDialog()
{}