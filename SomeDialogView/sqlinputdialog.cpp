#include "sqlinputdialog.h"
#include "ui_sqlinputdialog.h"
#include "QMessageBox"
SqlInputDialog::SqlInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sqlInputDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Icon.png"));
    setWindowTitle("执行任意SQL语句");

}

SqlInputDialog::~SqlInputDialog()
{
    delete ui;
}

SqlInputDialog *SqlInputDialog::getSqlInputDialog() {
    static SqlInputDialog sqlInputDialog;   //TODO 经典static_local处理
    sqlInputDialog.ui->input_sql->setText("");//把输入的数据清除
    sqlInputDialog.state = 0;
    sqlInputDialog.sql.clear();
    return &sqlInputDialog;
}

void SqlInputDialog::on_ack_btn_clicked()
{
    sql = ui->input_sql->text();
    if(isValidSql(sql)){
        state = 1;
        accept();
    }else{
        QMessageBox::information(nullptr,"提示","输入格式非sql语句");
        state = -1;
    }
}

bool SqlInputDialog::isValidSql(QString sql) {
    for(auto& str:sql_keyword){
        if(sql.contains(str))
            return true;
    }
    return false;
}

QString SqlInputDialog::getSql() {
    if(!sql.endsWith(';'))//TODO 保证此条语句执行完
        sql+=";";
    return sql;
}

int SqlInputDialog::getCurState() {
    return state;
}

