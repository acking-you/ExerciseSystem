/********************************************************************************
** Form generated from reading UI file 'errornotedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORNOTEDIALOG_H
#define UI_ERRORNOTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorNoteDialog
{
public:
    QGridLayout *gridLayout;
    QListWidget *q_list;
    QComboBox *question_c;

    void setupUi(QWidget *ErrorNoteDialog)
    {
        if (ErrorNoteDialog->objectName().isEmpty())
            ErrorNoteDialog->setObjectName(QString::fromUtf8("ErrorNoteDialog"));
        ErrorNoteDialog->resize(580, 592);
        ErrorNoteDialog->setMinimumSize(QSize(580, 0));
        ErrorNoteDialog->setMaximumSize(QSize(580, 16777215));
        gridLayout = new QGridLayout(ErrorNoteDialog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        q_list = new QListWidget(ErrorNoteDialog);
        new QListWidgetItem(q_list);
        q_list->setObjectName(QString::fromUtf8("q_list"));
        q_list->setStyleSheet(QString::fromUtf8("QListWidget::item{\n"
"	height:60px;\n"
"}\n"
"QListView {\n"
"	font: 25 12pt \"Microsoft YaHei\";\n"
"	border: 15px solid white; /* \350\256\276\347\275\256\350\276\271\346\241\206\347\232\204\345\244\247\345\260\217\357\274\214\346\240\267\345\274\217\357\274\214\351\242\234\350\211\262 */\n"
"	border-radius: 10px;\n"
"}\n"
"QListView::item:hover {\n"
"	background-color: transparent;\n"
"	padding: 10px;\n"
"	border-left: 3px solid rgb(130, 130, 130);\n"
"}\n"
"QListView::item:selected {\n"
"	background-color: transparent;\n"
"	color: black;\n"
"	padding: 10px;\n"
"	border-left: 3px solid black;\n"
"}"));

        gridLayout->addWidget(q_list, 2, 1, 1, 1);

        question_c = new QComboBox(ErrorNoteDialog);
        question_c->addItem(QString());
        question_c->addItem(QString());
        question_c->addItem(QString());
        question_c->setObjectName(QString::fromUtf8("question_c"));
        QFont font;
        font.setBold(true);
        question_c->setFont(font);
        question_c->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    font-size: 22px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    min-height:50px;\n"
"	padding-left:260px;\n"
"	background-color: rgb(26, 140, 255);\n"
"}\n"
"/*QComboBox::drop-down {\n"
"    border: 1px solid red;\n"
"}*/\n"
"QComboBox QAbstractItemView\n"
"{\n"
"   font-size: 22px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    min-height:50px;\n"
"	background-color: #74aefd;\n"
"}\n"
"QComboBox QAbstractItemView:hover\n"
"{\n"
"   font-size: 22px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    min-height:50px;\n"
"	background-color: #b4d1fe;\n"
"}\n"
""));
        question_c->setEditable(false);

        gridLayout->addWidget(question_c, 1, 1, 1, 1);


        retranslateUi(ErrorNoteDialog);

        QMetaObject::connectSlotsByName(ErrorNoteDialog);
    } // setupUi

    void retranslateUi(QWidget *ErrorNoteDialog)
    {
        ErrorNoteDialog->setWindowTitle(QCoreApplication::translate("ErrorNoteDialog", "ErrorNoteDialog", nullptr));

        const bool __sortingEnabled = q_list->isSortingEnabled();
        q_list->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = q_list->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ErrorNoteDialog", "\346\265\213\350\257\225\344\272\214", nullptr));
        q_list->setSortingEnabled(__sortingEnabled);

        question_c->setItemText(0, QCoreApplication::translate("ErrorNoteDialog", "\345\210\244\346\226\255\351\242\230", nullptr));
        question_c->setItemText(1, QCoreApplication::translate("ErrorNoteDialog", "\345\215\225\351\200\211\351\242\230", nullptr));
        question_c->setItemText(2, QCoreApplication::translate("ErrorNoteDialog", "\345\244\232\351\200\211\351\242\230", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ErrorNoteDialog: public Ui_ErrorNoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORNOTEDIALOG_H
