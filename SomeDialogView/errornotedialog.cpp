//
// Created by Alone on 2022-3-20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ErrorNoteDialog.h" resolved

#include "errornotedialog.h"
#include "Ui_errornotedialog.h"

static int getIdFromQString(QString const& qString){
    int sz = qString.size();
    int i = sz-1;
    while (i>=0&&qString[i]!='=')i--;
    if(i==-1)//not find '='
        return -1;
    //find '=' ,and get the number in the QString's end
    i += 1;
    int answer = 0;
    while (i<sz) {
        answer = answer*10 + (qString[i].toLatin1()-'0');
        i++;
    }
    if(answer<0) //the number overflow
        return -1;
    return answer;
}

ErrorNoteDialog::ErrorNoteDialog(QWidget *parent) :
        QWidget(parent), ui(new Ui::ErrorNoteDialog) {
    ui->setupUi(this);
    setWindowTitle("错题本——made by L_B__");
    setWindowIcon(QIcon(":/Icon.png"));
    connect(ui->question_c,&QComboBox::activated,this,&ErrorNoteDialog::on_activated);
    connect(ui->q_list,&QListWidget::itemPressed, this,&ErrorNoteDialog::on_pressed);
}

ErrorNoteDialog::~ErrorNoteDialog() {
    delete ui;
}

void ErrorNoteDialog::on_pressed(QListWidgetItem *item) {
    int qid = getIdFromQString(item->text());
    emit itemPressedId(qid);
}

void ErrorNoteDialog::on_activated(int index) {
    emit activatedQ(index);
}

void ErrorNoteDialog::setListToWidget(QList<QString>* list) {
    ui->q_list->clear();
    for (auto &text: *list) {
        ui->q_list->addItem(text);
    }
}

void ErrorNoteDialog::show() {
    QWidget::show();
    emit activatedQ(0);
}


