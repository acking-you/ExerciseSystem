//
// Created by Alone on 2022-3-13.
//

#include "ImportExcleDialog.h"
#include "Ui_ImportExcleDialog.h"
#include "col_info.h"
#include <QFileDialog>
#include <QMessageBox>
QString openExcleFile(){
    return QFileDialog::getOpenFileName(nullptr,"打开excle文件",".","*.xlsx");
}
ImportExcleDialog* ImportExcleDialog::m_dialog = nullptr;

ImportExcleDialog::ImportExcleDialog(QWidget *parent):
        QDialog(parent),ui(new Ui_Dialog()){
    ui->setupUi(this);
    setWindowTitle("选择导入EXCLE——made by L_B__");
    setWindowIcon(QIcon(":/Icon.png"));
    reset();
}

ImportExcleDialog::~ImportExcleDialog() {
    delete ui;
}

void ImportExcleDialog::setStyleMode1() {
    ui->judge->setVisible(false);
    ui->choose->setVisible(false);
    ui->submit_btn->setVisible(false);
}

void ImportExcleDialog::setStyleMode2() {
    ui->judge->setVisible(true);
    ui->choose->setVisible(false);
    ui->submit_btn->setVisible(true);
}

void ImportExcleDialog::setStyleMode3() {
    ui->judge->setVisible(false);
    ui->choose->setVisible(true);
    ui->submit_btn->setVisible(true);
}

void ImportExcleDialog::on_import_judge_clicked() {
    auto path = openExcleFile();
    if (!QFile(path).exists()) {
        QMessageBox::warning(nullptr,"提示","路径选择错误");
        return;
    }
    excle_path = path;
    setStyleMode2();
    cur_state = 1;
}

void ImportExcleDialog::on_import_single_clicked() {
    auto path = openExcleFile();
    if (!QFile(path).exists()) {
        QMessageBox::warning(nullptr,"提示","路径选择错误");
        return;
    }
    excle_path = path;
    setStyleMode3();
    cur_state = 2;
}

void ImportExcleDialog::on_import_muti_clicked() {
    auto path = openExcleFile();
    if (!QFile(path).exists()) {
        QMessageBox::warning(nullptr,"提示","路径选择错误");
        return;
    }
    excle_path = path;
    setStyleMode3();
    cur_state = 3;
}

void ImportExcleDialog::on_submit_btn_clicked() {
    switch (cur_state) {
        case 1:
            if(isValidParam(1)){
                submit_state = 1;
                updateColInfo();    //TODO 如果输入数据有效，就更新列信息的全局配置变量
                this->accept();
            }
            break;
        case 2:
        case 3:
            if(isValidParam(2)){
                submit_state = 1;
                updateColInfo();
                this->accept();
            }
            break;
    }
}

bool ImportExcleDialog::isValidParam(int page) {
    bool ret = false;
    switch (page) {
        case 1:
            if(isValidMode1())
                ret = true;
            else{
                QMessageBox::warning(nullptr,"提示","请正确输入表格的对应信息");
                ret = false;
            }
            break;
        case 2:
            if(isValidMode2())
                ret = true;
            else{
                QMessageBox::warning(nullptr,"提示","请正确输入表格的对应信息");
                ret = false;
            }
            break;
    }
    return ret;
}

bool ImportExcleDialog::isValidMode1() {
    bool ok;
    auto chapter = ui->chapter_c->text().toInt(&ok);
    if(!ok)return false;
    auto question = ui->question_c->text().toInt(&ok);
    if(!ok)return false;
    auto answer = ui->answer_c->text().toInt(&ok);
    if(!ok)return false;
    auto start_row = ui->start_row->text().toInt(&ok);
    if(!ok)return false;
    auto end_row = ui->end_row->text().toInt(&ok);
    if(!ok)return false;
    this->chapter_c = chapter;
    this->question_c = question;
    this->answer_c = answer;
    this->start_row = start_row;
    this->end_row = end_row;
    return true;
}

bool ImportExcleDialog::isValidMode2() {
    bool ok;
    auto chapter = ui->chapter_c_2->text().toInt(&ok);
    if(!ok)return false;
    auto question = ui->question_c_2->text().toInt(&ok);
    if(!ok)return false;
    auto answer = ui->answer_c_2->text().toInt(&ok);
    if(!ok)return false;
    auto start_row = ui->start_row_2->text().toInt(&ok);
    if(!ok)return false;
    auto end_row = ui->end_row_2->text().toInt(&ok);
    if(!ok)return false;
    auto a = ui->a_c->text().toInt(&ok);
    if(!ok)return false;
    auto b = ui->b_c->text().toInt(&ok );
    if(!ok)return false;
    auto c = ui->c_c->text().toInt(&ok);
    if(!ok)return false;
    auto d = ui->d_c->text().toInt(&ok);
    if(!ok)return false;

    this->chapter_c = chapter;
    this->question_c = question;
    this->answer_c = answer;
    this->start_row = start_row;
    this->end_row = end_row;
    this->opa_c = a;
    this->opb_c = b;
    this->opc_c = c;
    this->opd_c = d;
    return true;
}

int ImportExcleDialog::getCurState() {
    int ret = 0;
    if(submit_state==1) //TODO 必须要正常提交了列信息才给他算当前状态
        ret = cur_state;
    return ret;
}

QString ImportExcleDialog::getExclePath() {
    return excle_path;
}

int ImportExcleDialog::getChapterCol() {
    return chapter_c;
}

int ImportExcleDialog::getAnswerCol() {
    return answer_c;
}

int ImportExcleDialog::getQuestionCol() {
    return question_c;
}

int ImportExcleDialog::getOpaCol() {
    return opa_c;
}

int ImportExcleDialog::getOpcCol() {
    return opc_c;
}

int ImportExcleDialog::getOpbCol() {
    return opb_c;
}

int ImportExcleDialog::getOpdCol() {
    return opd_c;
}

int ImportExcleDialog::getStartRow() {
    return start_row;
}

ImportExcleDialog *ImportExcleDialog::getInstance() {
    if(m_dialog== nullptr){
        m_dialog = new ImportExcleDialog();
    }
    else m_dialog->reset();

    return m_dialog;
}

void ImportExcleDialog::reset() {
    setStyleMode1();
    excle_path.clear();
    cur_state = 0;
    submit_state = 0;
    chapter_c = 0;
    question_c = 0;
    answer_c = 0;
    start_row = 2;
    end_row = start_row;
    opa_c = 0;
    opb_c = 0;
    opc_c = 0;
    opd_c = 0;
}

void ImportExcleDialog::updateColInfo() {
    col_info::col_chapter = chapter_c;
    col_info::col_que = question_c;
    col_info::col_answer = answer_c;
    col_info::col_a = opa_c;
    col_info::col_b = opb_c;
    col_info::col_c = opc_c;
    col_info::col_d = opd_c;
    col_info::start_row = start_row;
    col_info::end_row = end_row;
}
