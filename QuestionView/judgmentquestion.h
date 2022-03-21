#ifndef JUDGMENTQUESTION_H
#define JUDGMENTQUESTION_H

#include <QMainWindow>
#include <iostream>
#include "JudgmentQ.h"
#include <unordered_map>

namespace Ui {
    class JudgmentQuestion;
}

class run_thread;
class QPushButton;
class JudgmentQuestion : public QMainWindow {
Q_OBJECT

public:
    explicit JudgmentQuestion(QList<std::shared_ptr<JudgmentQ>>* all_q,QWidget *parent = nullptr);

static JudgmentQuestion* getOneJudgementWidget(QList<std::shared_ptr<JudgmentQ>>* one_q);
    ~JudgmentQuestion() override;

    void setToMode1();

    void clearTxt();

    void InActiveBtn(bool isRecite = false);

    void ActiveBtn(bool isRecite = false);

    void setToMode2(bool isChangeToMode1 = false);
    void updateQ(bool isAlready=false);

    int resetQSum(int num,int update=0);
private slots:

    void on_mode1_clicked();
    void on_mode2_clicked();
    void on_next_question_clicked();
    void on_pre_question_clicked();
    void on_accept_btn_clicked();
    void on_no_btn_clicked();
private:
    QList<std::shared_ptr<JudgmentQ>>* all_q;
    QPushButton* nextBtn;
    QPushButton* preBtn;
    int cur_mode;
    int cur_page;
    int sum_page;
    int answers_num;
    int correct_num;
    std::vector<int> cur_state;
    Ui::JudgmentQuestion *ui;
};

#endif // JUDGMENTQUESTION_H
