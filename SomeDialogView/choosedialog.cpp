#include "choosedialog.h"
#include "ui_choosedialog.h"

ChooseDialog* ChooseDialog::m_dialog = nullptr;

ChooseDialog::ChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDialog),state(0)
{
    ui->setupUi(this);
    setWindowTitle("选择练习题类型——made by L_B__");
    setWindowIcon(QIcon(":/Icon.png"));
}

ChooseDialog::~ChooseDialog()
{
    delete ui;
}

void ChooseDialog::on_judge_clicked()
{
    state = 1;
    this->accept();
}

void ChooseDialog::setJugeNum(int num) {
    ui->num_judge->setText(QString::number(num)+"道");
}

void ChooseDialog::setSingleNum(int num) {
    ui->num_single->setText(QString::number(num)+"道");
}

void ChooseDialog::setMutiNum(int num) {
    ui->num_muti->setText(QString::number(num)+"道");
}

ChooseDialog *ChooseDialog::getInstance() {
    if(m_dialog== nullptr){
        m_dialog = new ChooseDialog;
    }
    m_dialog->state = 0;
    return m_dialog;
}

void ChooseDialog::on_single_clicked() {
    state = 2;
    this->accept();
}

void ChooseDialog::on_muti_clicked() {
    state = 3;
    this->accept();
}

int ChooseDialog::getCurState() {
    return state;
}
