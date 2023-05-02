/********************************************************************************
** Form generated from reading UI file 'FindWidgetOGOCGf.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FINDWIDGETOGOCGF_H
#define FINDWIDGETOGOCGF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindWidgetClass
{
public:
    QWidget *centralWidget;
    QTextEdit *editor;
    QPushButton *btnNextString;
    QPushButton *btnPreString;
    QPushButton *btnClose;

    void setupUi(QMainWindow *FindWidgetClass)
    {
        if (FindWidgetClass->objectName().isEmpty())
            FindWidgetClass->setObjectName(QString::fromUtf8("FindWidgetClass"));
        FindWidgetClass->resize(560, 70);
        FindWidgetClass->setMinimumSize(QSize(560, 70));
        FindWidgetClass->setMaximumSize(QSize(560, 70));
        centralWidget = new QWidget(FindWidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        editor = new QTextEdit(centralWidget);
        editor->setObjectName(QString::fromUtf8("editor"));
        editor->setGeometry(QRect(20, 19, 231, 31));
        btnNextString = new QPushButton(centralWidget);
        btnNextString->setObjectName(QString::fromUtf8("btnNextString"));
        btnNextString->setGeometry(QRect(360, 23, 75, 23));
        btnPreString = new QPushButton(centralWidget);
        btnPreString->setObjectName(QString::fromUtf8("btnPreString"));
        btnPreString->setGeometry(QRect(280, 23, 75, 23));
        btnClose = new QPushButton(centralWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(450, 23, 75, 23));
        FindWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(FindWidgetClass);

        QMetaObject::connectSlotsByName(FindWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *FindWidgetClass)
    {
        FindWidgetClass->setWindowTitle(QCoreApplication::translate("FindWidgetClass", "FindWidget", nullptr));
        btnNextString->setText(QCoreApplication::translate("FindWidgetClass", "\344\270\213\344\270\200\344\270\252", nullptr));
        btnPreString->setText(QCoreApplication::translate("FindWidgetClass", "\344\270\212\344\270\200\344\270\252", nullptr));
        btnClose->setText(QCoreApplication::translate("FindWidgetClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindWidgetClass: public Ui_FindWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FINDWIDGETOGOCGF_H
