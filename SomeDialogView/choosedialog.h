#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseDialog;
}

class ChooseDialog : public QDialog
{
    Q_OBJECT
    explicit ChooseDialog(QWidget *parent = nullptr);
public:
    ~ChooseDialog() override;

    void setJugeNum(int num);
    void setSingleNum(int num);
    void setMutiNum(int num);

    int getCurState();
    static ChooseDialog* getInstance();
private slots:
    void on_judge_clicked();
    void on_single_clicked();
    void on_muti_clicked();
private:
    static ChooseDialog* m_dialog;
    int state;  //1表示选择了判断题、2表示单选、3表示多选
    Ui::ChooseDialog *ui;
};

#endif // CHOOSEDIALOG_H
