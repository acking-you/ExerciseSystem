/********************************************************************************
** Form generated from reading UI file 'ImportExcleDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTEXCLEDIALOG_H
#define UI_IMPORTEXCLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QWidget *w1;
    QGridLayout *gridLayout_3;
    QLabel *title;
    QLabel *info;
    QWidget *w2;
    QGridLayout *gridLayout_2;
    QPushButton *import_judge;
    QPushButton *import_single;
    QPushButton *import_muti;
    QWidget *w3;
    QGridLayout *gridLayout_4;
    QWidget *judge;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    QLineEdit *start_row;
    QLineEdit *answer_c;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *chapter_c;
    QLabel *label_4;
    QLineEdit *question_c;
    QLabel *label_13;
    QLineEdit *end_row;
    QWidget *w4;
    QGridLayout *gridLayout_6;
    QWidget *choose;
    QGridLayout *gridLayout_7;
    QLineEdit *start_row_2;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_9;
    QLineEdit *a_c;
    QLineEdit *answer_c_2;
    QLineEdit *c_c;
    QLineEdit *b_c;
    QLineEdit *chapter_c_2;
    QLabel *label_6;
    QLineEdit *question_c_2;
    QLabel *label_10;
    QLineEdit *d_c;
    QLabel *label_12;
    QLabel *label_14;
    QLineEdit *end_row_2;
    QWidget *w5;
    QGridLayout *gridLayout_8;
    QPushButton *submit_btn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(617, 500);
        Dialog->setMinimumSize(QSize(0, 0));
        Dialog->setMaximumSize(QSize(16777215, 500));
        Dialog->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-size:11pt;\n"
"}\n"
"QLabel#title{\n"
"font-size:15pt;\n"
"}\n"
"#Dialog{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        w1 = new QWidget(Dialog);
        w1->setObjectName(QString::fromUtf8("w1"));
        w1->setStyleSheet(QString::fromUtf8("#w1{\n"
"	background-color: rgb(26, 140, 255);\n"
"}\n"
"QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        gridLayout_3 = new QGridLayout(w1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        title = new QLabel(w1);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(15);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(title, 0, 0, 1, 1);

        info = new QLabel(w1);
        info->setObjectName(QString::fromUtf8("info"));
        QFont font1;
        font1.setPointSize(8);
        info->setFont(font1);
        info->setStyleSheet(QString::fromUtf8("font-size:8pt;"));
        info->setAlignment(Qt::AlignCenter);
        info->setOpenExternalLinks(true);

        gridLayout_3->addWidget(info, 1, 0, 1, 1);


        gridLayout->addWidget(w1, 0, 0, 1, 1);

        w2 = new QWidget(Dialog);
        w2->setObjectName(QString::fromUtf8("w2"));
        w2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-size:12pt;\n"
"max-width:120px;\n"
"min-height:40px;\n"
"border-radius: 20px;\n"
"border: 2px solid #334a59;\n"
"color: rgb(51, 74, 89);\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: #1a8cff;\n"
"	color:white;\n"
"border: 1px solid white;\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: #1768ff;\n"
"	color:white;\n"
"border: 1px solid white;\n"
"}\n"
""));
        gridLayout_2 = new QGridLayout(w2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        import_judge = new QPushButton(w2);
        import_judge->setObjectName(QString::fromUtf8("import_judge"));

        gridLayout_2->addWidget(import_judge, 0, 0, 1, 1);

        import_single = new QPushButton(w2);
        import_single->setObjectName(QString::fromUtf8("import_single"));

        gridLayout_2->addWidget(import_single, 0, 1, 1, 1);

        import_muti = new QPushButton(w2);
        import_muti->setObjectName(QString::fromUtf8("import_muti"));

        gridLayout_2->addWidget(import_muti, 0, 2, 1, 1);


        gridLayout->addWidget(w2, 1, 0, 1, 1);

        w3 = new QWidget(Dialog);
        w3->setObjectName(QString::fromUtf8("w3"));
        w3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"max-height:30px;\n"
"}"));
        gridLayout_4 = new QGridLayout(w3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        judge = new QWidget(w3);
        judge->setObjectName(QString::fromUtf8("judge"));
        judge->setMinimumSize(QSize(0, 110));
        judge->setStyleSheet(QString::fromUtf8("#judge{\n"
"	background-color:#f7f8fa;\n"
"	border-radius: 20px;\n"
"}\n"
"QLabel{\n"
"color: #808080;\n"
"max-width:150px;\n"
"}\n"
"QLineEdit{\n"
"min-height:25px;\n"
"border-radius: 10px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_5 = new QGridLayout(judge);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(2);
        gridLayout_5->setVerticalSpacing(0);
        label_3 = new QLabel(judge);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_3, 0, 2, 1, 1);

        start_row = new QLineEdit(judge);
        start_row->setObjectName(QString::fromUtf8("start_row"));

        gridLayout_5->addWidget(start_row, 1, 3, 1, 1);

        answer_c = new QLineEdit(judge);
        answer_c->setObjectName(QString::fromUtf8("answer_c"));

        gridLayout_5->addWidget(answer_c, 1, 2, 1, 1);

        label = new QLabel(judge);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(judge);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_2, 0, 1, 1, 1);

        chapter_c = new QLineEdit(judge);
        chapter_c->setObjectName(QString::fromUtf8("chapter_c"));
        chapter_c->setMinimumSize(QSize(0, 25));

        gridLayout_5->addWidget(chapter_c, 1, 0, 1, 1);

        label_4 = new QLabel(judge);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_4, 0, 3, 1, 1);

        question_c = new QLineEdit(judge);
        question_c->setObjectName(QString::fromUtf8("question_c"));

        gridLayout_5->addWidget(question_c, 1, 1, 1, 1);

        label_13 = new QLabel(judge);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_13, 0, 4, 1, 1);

        end_row = new QLineEdit(judge);
        end_row->setObjectName(QString::fromUtf8("end_row"));

        gridLayout_5->addWidget(end_row, 1, 4, 1, 1);


        gridLayout_4->addWidget(judge, 0, 0, 1, 1);


        gridLayout->addWidget(w3, 2, 0, 1, 1);

        w4 = new QWidget(Dialog);
        w4->setObjectName(QString::fromUtf8("w4"));
        gridLayout_6 = new QGridLayout(w4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        choose = new QWidget(w4);
        choose->setObjectName(QString::fromUtf8("choose"));
        choose->setMinimumSize(QSize(0, 110));
        choose->setStyleSheet(QString::fromUtf8("#choose{\n"
"	background-color:#f7f8fa;\n"
"	border-radius: 20px;\n"
"}\n"
"QLabel{\n"
"color: #808080;\n"
"max-width:150px;\n"
"}\n"
"QLineEdit{\n"
"min-height:25px;\n"
"border-radius: 10px;\n"
"	background-color: white;\n"
"}"));
        gridLayout_7 = new QGridLayout(choose);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(2);
        gridLayout_7->setVerticalSpacing(0);
        start_row_2 = new QLineEdit(choose);
        start_row_2->setObjectName(QString::fromUtf8("start_row_2"));

        gridLayout_7->addWidget(start_row_2, 1, 10, 1, 1);

        label_7 = new QLabel(choose);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_7, 0, 2, 1, 3);

        label_5 = new QLabel(choose);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_5, 0, 0, 1, 1);

        label_8 = new QLabel(choose);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_8, 0, 5, 1, 1);

        label_11 = new QLabel(choose);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_11, 0, 9, 1, 1);

        label_9 = new QLabel(choose);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_9, 0, 6, 1, 1);

        a_c = new QLineEdit(choose);
        a_c->setObjectName(QString::fromUtf8("a_c"));

        gridLayout_7->addWidget(a_c, 1, 5, 1, 1);

        answer_c_2 = new QLineEdit(choose);
        answer_c_2->setObjectName(QString::fromUtf8("answer_c_2"));

        gridLayout_7->addWidget(answer_c_2, 1, 2, 1, 1);

        c_c = new QLineEdit(choose);
        c_c->setObjectName(QString::fromUtf8("c_c"));

        gridLayout_7->addWidget(c_c, 1, 8, 1, 1);

        b_c = new QLineEdit(choose);
        b_c->setObjectName(QString::fromUtf8("b_c"));

        gridLayout_7->addWidget(b_c, 1, 6, 1, 1);

        chapter_c_2 = new QLineEdit(choose);
        chapter_c_2->setObjectName(QString::fromUtf8("chapter_c_2"));

        gridLayout_7->addWidget(chapter_c_2, 1, 0, 1, 1);

        label_6 = new QLabel(choose);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_6, 0, 1, 1, 1);

        question_c_2 = new QLineEdit(choose);
        question_c_2->setObjectName(QString::fromUtf8("question_c_2"));

        gridLayout_7->addWidget(question_c_2, 1, 1, 1, 1);

        label_10 = new QLabel(choose);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_10, 0, 8, 1, 1);

        d_c = new QLineEdit(choose);
        d_c->setObjectName(QString::fromUtf8("d_c"));

        gridLayout_7->addWidget(d_c, 1, 9, 1, 1);

        label_12 = new QLabel(choose);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_12, 0, 10, 1, 1);

        label_14 = new QLabel(choose);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_7->addWidget(label_14, 0, 11, 1, 1);

        end_row_2 = new QLineEdit(choose);
        end_row_2->setObjectName(QString::fromUtf8("end_row_2"));

        gridLayout_7->addWidget(end_row_2, 1, 11, 1, 1);


        gridLayout_6->addWidget(choose, 0, 0, 1, 1);

        w5 = new QWidget(w4);
        w5->setObjectName(QString::fromUtf8("w5"));
        w5->setMinimumSize(QSize(0, 60));
        w5->setMaximumSize(QSize(16777215, 60));
        gridLayout_8 = new QGridLayout(w5);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        submit_btn = new QPushButton(w5);
        submit_btn->setObjectName(QString::fromUtf8("submit_btn"));
        submit_btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-size:12pt;\n"
"max-width:120px;\n"
"min-height:40px;\n"
"border-radius: 15px;\n"
"border: 2px solid #334a59;\n"
"color: rgb(51, 74, 89);\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(255, 23, 131);\n"
"	color:white;\n"
"border: 1px solid white;\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: #cf1369;\n"
"	color:white;\n"
"border: 1px solid white;\n"
"}\n"
""));

        gridLayout_8->addWidget(submit_btn, 0, 0, 1, 1);


        gridLayout_6->addWidget(w5, 1, 0, 1, 1);


        gridLayout->addWidget(w4, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 4);
        gridLayout->setRowStretch(3, 4);
        QWidget::setTabOrder(import_judge, import_single);
        QWidget::setTabOrder(import_single, import_muti);
        QWidget::setTabOrder(import_muti, chapter_c);
        QWidget::setTabOrder(chapter_c, question_c);
        QWidget::setTabOrder(question_c, answer_c);
        QWidget::setTabOrder(answer_c, start_row);
        QWidget::setTabOrder(start_row, chapter_c_2);
        QWidget::setTabOrder(chapter_c_2, question_c_2);
        QWidget::setTabOrder(question_c_2, answer_c_2);
        QWidget::setTabOrder(answer_c_2, a_c);
        QWidget::setTabOrder(a_c, b_c);
        QWidget::setTabOrder(b_c, c_c);
        QWidget::setTabOrder(c_c, d_c);
        QWidget::setTabOrder(d_c, start_row_2);
        QWidget::setTabOrder(start_row_2, submit_btn);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        title->setText(QCoreApplication::translate("Dialog", "Excle\345\257\274\345\205\245", nullptr));
        info->setText(QCoreApplication::translate("Dialog", "\345\217\252\346\224\257\346\214\201xlsx\346\240\274\345\274\217\347\232\204excle\346\226\207\344\273\266\357\274\214\345\246\202\346\236\234\346\230\257xls\346\226\207\344\273\266\345\217\257\344\273\245\345\210\260<a href=\"https://onlineconvertfree.com/zh/convert-format/xls-to-xlsx/\">\347\275\221\347\253\231</a>\350\277\233\350\241\214\350\275\254\345\214\226<br/>\346\263\250\346\204\217\344\270\215\350\246\201\351\207\215\345\244\215\345\257\274\345\205\245\347\233\270\345\220\214\347\232\204\346\225\260\346\215\256\345\210\260\346\225\260\346\215\256\345\272\223\357\274\214\345\257\274\345\205\245\346\225\260\346\215\256\344\270\215\344\274\232\345\257\271\345\206\205\345\256\271\350\277\233\350\241\214\345\210\244\346\226\255\347\232\204<br/>\n"
"\346\234\200\345\220\216\345\246\202\346\236\234\345\256\236\345\234\250\346\230\257\345\257\274\345\205\245\351\224\231\344\272\206\357\274\214\346\210\221\346\217\220\344\276\233\344\272\206\346\211\247\350\241\214sql\350\257\255\345\217\245\347\232\204\346\226"
                        "\271\345\274\217\345\216\273\347\256\241\347\220\206\346\225\260\346\215\256\345\272\223", nullptr));
        import_judge->setText(QCoreApplication::translate("Dialog", "\345\257\274\345\205\245\345\210\244\346\226\255\351\242\230", nullptr));
        import_single->setText(QCoreApplication::translate("Dialog", "\345\257\274\345\205\245\345\215\225\351\200\211\351\242\230", nullptr));
        import_muti->setText(QCoreApplication::translate("Dialog", "\345\257\274\345\205\245\345\244\232\351\200\211\351\242\230", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\347\255\224\346\241\210\345\234\250\347\254\254\345\207\240\345\210\227\357\274\237", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\347\253\240\350\212\202\345\234\250\347\254\254\345\207\240\345\210\227\357\274\237", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\351\242\230\345\271\262\345\234\250\347\254\254\345\207\240\345\210\227\357\274\237", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\350\265\267\345\247\213\350\241\214\346\225\260", nullptr));
        label_13->setText(QCoreApplication::translate("Dialog", "\347\273\223\346\235\237\350\241\214\346\225\260", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog", "\347\255\224\346\241\210(\345\210\227)", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "\347\253\240\350\212\202(\345\210\227)", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog", "A\351\200\211\351\241\271(\345\210\227)", nullptr));
        label_11->setText(QCoreApplication::translate("Dialog", "D\351\200\211\351\241\271(\345\210\227)", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog", "B\351\200\211\351\241\271(\345\210\227)", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "\351\242\230\345\271\262(\345\210\227)", nullptr));
        label_10->setText(QCoreApplication::translate("Dialog", "C\351\200\211\351\241\271(\345\210\227)", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog", "\350\265\267\345\247\213\350\241\214\346\225\260", nullptr));
        label_14->setText(QCoreApplication::translate("Dialog", "\347\273\223\346\235\237\350\241\214\346\225\260", nullptr));
        submit_btn->setText(QCoreApplication::translate("Dialog", "\346\217\220\344\272\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTEXCLEDIALOG_H
