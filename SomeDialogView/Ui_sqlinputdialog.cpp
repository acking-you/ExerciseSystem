/********************************************************************************
** Form generated from reading UI file 'sqlinputdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLINPUTDIALOG_H
#define UI_SQLINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sqlInputDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *input_sql;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QPushButton *ack_btn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *w1;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;

    void setupUi(QDialog *sqlInputDialog)
    {
        if (sqlInputDialog->objectName().isEmpty())
            sqlInputDialog->setObjectName(QString::fromUtf8("sqlInputDialog"));
        sqlInputDialog->resize(370, 300);
        sqlInputDialog->setMaximumSize(QSize(400, 300));
        sqlInputDialog->setStyleSheet(QString::fromUtf8("/* \350\276\223\345\205\245\346\241\206\347\232\204\345\270\203\345\261\200\345\222\214\351\242\234\350\211\262\357\274\214\344\273\245\345\217\212\345\256\203\347\232\204hover\347\212\266\346\200\201 */\n"
"QLineEdit {\n"
"    border-radius: 6px;\n"
"    padding: 8px 12px;\n"
"    padding-top: 8px;\n"
"    padding-right: 12px;\n"
"    padding-bottom: 8px;\n"
"    padding-left: 12px;\n"
"    color: #34495e;\n"
"\n"
"}\n"
"QLineEdit:focus{\n"
"    border: 1px solid #bdc3c7;\n"
"}\n"
"QPushButton {\n"
"	\n"
"	image: url(:/\346\211\247\350\241\214.png);\n"
"    border: none;\n"
"    font-size: 14px;\n"
"    font-weight: normal;\n"
"    min-width: 50px;\n"
"    width:50;\n"
"    line-height: 1.4;\n"
"    min-height: 20;\n"
"    border-radius: 8px;\n"
"    padding: 5px 7px;\n"
"    color: white;\n"
"    background-color: white;\n"
"\n"
"} \n"
"QPushButton:hover {\n"
"	\n"
"    background-color: #6ab3e4;\n"
"}\n"
"QPushButton:pressed {\n"
"    border: 1px solid #138496;\n"
"    background-color:#2c81ba;\n"
"}\n"
""));
        gridLayout = new QGridLayout(sqlInputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        input_sql = new QLineEdit(sqlInputDialog);
        input_sql->setObjectName(QString::fromUtf8("input_sql"));
        input_sql->setMaximumSize(QSize(250, 100000));

        gridLayout->addWidget(input_sql, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        ack_btn = new QPushButton(sqlInputDialog);
        ack_btn->setObjectName(QString::fromUtf8("ack_btn"));
        ack_btn->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(ack_btn, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        w1 = new QWidget(sqlInputDialog);
        w1->setObjectName(QString::fromUtf8("w1"));
        w1->setStyleSheet(QString::fromUtf8("#w1{background-color: #1a8cff;}\n"
"#w1 QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        gridLayout_2 = new QGridLayout(w1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(w1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setOpenExternalLinks(true);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(w1);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setOpenExternalLinks(true);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(w1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setOpenExternalLinks(true);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);


        gridLayout->addWidget(w1, 0, 0, 1, 4);


        retranslateUi(sqlInputDialog);

        QMetaObject::connectSlotsByName(sqlInputDialog);
    } // setupUi

    void retranslateUi(QDialog *sqlInputDialog)
    {
        sqlInputDialog->setWindowTitle(QCoreApplication::translate("sqlInputDialog", "Dialog", nullptr));
        ack_btn->setText(QString());
        label_2->setText(QCoreApplication::translate("sqlInputDialog", "\346\234\254\351\242\230\345\272\223\345\220\253\346\234\211\344\273\245\344\270\213\344\270\211\345\274\240\350\241\250\357\274\232<br/>judgment\343\200\201single_choice\343\200\201muti_choice<br/>\344\270\276\344\270\252\344\276\213\345\255\220(\346\270\205\347\251\272\345\210\244\346\226\255\351\242\230\345\272\223)\357\274\232delete from judgment<br/>\351\273\230\350\256\244\344\275\240\350\276\223\345\205\245\347\232\204\344\270\200\345\217\245sql\350\257\255\345\217\245\344\270\272\347\273\223\346\235\237\350\257\255\345\217\245(\344\274\232\350\207\252\345\212\250\346\267\273\345\212\240';'\345\270\256\344\275\240\347\273\223\346\235\237)", nullptr));
        label->setText(QCoreApplication::translate("sqlInputDialog", "\346\234\254\351\242\230\345\272\223\347\232\204\346\225\260\346\215\256\345\272\223\351\207\207\345\217\226\346\234\254\345\234\260\346\226\207\344\273\266io\347\232\204sqlite\346\225\260\346\215\256\345\272\223<br/>\345\237\272\346\234\254\347\232\204sql\350\257\255\345\217\245\344\275\277\347\224\250\345\217\257\344\273\245\346\237\245\347\234\213\350\277\231\344\270\252<a href=\"https://acking-you.gitee.io/posts/%E6%95%B0%E6%8D%AE%E5%BA%93%E5%9F%BA%E7%A1%80/\">\347\275\221\351\241\265</a><br/>\345\275\223\347\204\266\350\277\230\346\230\257\345\217\257\350\203\275\345\255\230\345\234\250\344\270\200\344\272\233sql\346\226\271\350\250\200\347\232\204\351\227\256\351\242\230(\342\227\217'\342\227\241'\342\227\217)", nullptr));
        label_3->setText(QCoreApplication::translate("sqlInputDialog", "\346\270\251\351\246\250\346\217\220\347\244\272\357\274\232<br>\350\207\252\345\267\261\345\210\240\347\232\204\345\272\223\357\274\214\350\207\252\345\267\261\350\264\237\350\264\243(\357\277\243\342\226\275\357\277\243)\"(\357\277\243\342\226\275\357\277\243)\"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sqlInputDialog: public Ui_sqlInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLINPUTDIALOG_H
