//
// Created by Alone on 2022-3-13.
//

#ifndef EXCLE_TEST_IMPORTEXCLEDIALOG_H
#define EXCLE_TEST_IMPORTEXCLEDIALOG_H
#include <QDialog>
class Ui_Dialog;

/**
 * 显示模式分析：\n
 *  1.没有点击任何导入按钮\n
 *  2.点击导入判断题类\n
 *  3.点击导入选择题类
 */

class ImportExcleDialog :public QDialog{
Q_OBJECT
    explicit ImportExcleDialog(QWidget *parent = nullptr);
public:
    static ImportExcleDialog* getInstance();
    ~ImportExcleDialog() override;

    void updateColInfo();

    int getCurState();

    QString getExclePath();

    int getChapterCol();
    int getAnswerCol();
    int getQuestionCol();
    int getOpaCol();
    int getOpcCol();
    int getOpbCol();
    int getOpdCol();
    int getStartRow();
    void setStyleMode1();
    void setStyleMode2();
    void setStyleMode3();
    bool isValidMode1();
    bool isValidMode2();
    bool isValidParam(int page);
private slots:
    void on_import_judge_clicked();
    void on_import_single_clicked();
    void on_import_muti_clicked();
    void on_submit_btn_clicked();
private:
    void reset();

    static ImportExcleDialog* m_dialog;

    QString excle_path;
    int cur_state;
    int submit_state;

    int chapter_c;
    int question_c;
    int answer_c;
    int start_row;
    int end_row;
    int opa_c;
    int opb_c;
    int opc_c;
    int opd_c;
    Ui_Dialog *ui;
};


#endif //EXCLE_TEST_IMPORTEXCLEDIALOG_H
