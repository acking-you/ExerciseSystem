#ifndef SQLINPUTDIALOG_H
#define SQLINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class sqlInputDialog;
}

class SqlInputDialog : public QDialog
{
    Q_OBJECT
    explicit SqlInputDialog(QWidget *parent = nullptr);
public:
    bool isValidSql(QString sql);
    static SqlInputDialog* getSqlInputDialog();
    ~SqlInputDialog() override;
    int getCurState();
    QString getSql();
private slots:
    void on_ack_btn_clicked();

private:
    int state = 0;
    QString sql;
    QList<QString> sql_keyword
    {"create","update","select"
    ,"drop","alter","insert","delete"};

    Ui::sqlInputDialog *ui;
};

#endif // SQLINPUTDIALOG_H
