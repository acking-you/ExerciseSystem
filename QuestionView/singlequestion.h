#ifndef SINGLEQUESTION_H
#define SINGLEQUESTION_H

#include <QMainWindow>
#include "SingleChoiceQ.h"
namespace Ui {
class SingleQuestion;
}
/**
 * TODO 每个界面的显示和两个状态有关：1.当前处于哪种答题模式。2.当前题目的答题状态\n
 * 总共可以搭配三种显示模式：\n
 * 1.处于答题模式且未进行任何作答。\n
 * 2.处于答题模式且回答正确。\n
 * 3.处于答题模式且回答错误 和 处于背题模式处于同一种显示模式。
 */



class SingleQuestion : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleQuestion(QList<std::shared_ptr<SingleChoiceQ>>*,QWidget *parent = nullptr);
    ~SingleQuestion() override;

    static SingleQuestion* getOneSingleQuestionWidget(QList<std::shared_ptr<SingleChoiceQ>>*);
    void hideAnswer();
    void setBtnInActive();
    void setBtnActive();
    void updateQ();
    void showQ();
    void showAnswer(QString const& answer);

    void setStyleMode1();
    //TODO 状态二和三，需要确认是哪个答案，然后给予对应的样式1,2,3,4分别代表abcd
    void setStyleMode2(int answerId);
    void setStyleMode3(int answerId);

    int resetQSum(int new_sum,int update=0); //TODO 对外提供的按照传入的数量重新开始的接口
    void setCurState(int state);
    int getCurState();
    int getCurAnswer();

    void saveCurQRecord();
private slots:
    void on_mode1_clicked();

    void on_mode2_clicked();

    void on_pre_btn_clicked();

    void on_next_btn_clicked();

    void on_a_btn_clicked();

    void on_b_btn_clicked();

    void on_c_btn_clicked();

    void on_d_btn_clicked();

private:
    QList<std::shared_ptr<SingleChoiceQ>>* all_q;
    /**
     * 最终的更新逻辑：\n
     * 对应的按钮按下后，影响的是下面的这些变量的状态值\n
     * 而对应的显示画面由showQ根据这些状态来调用updateQ和StyleMode更新\n
     * updateQ则负责更新题目的文字等信息，之前的三个StyleMode负责对应的样式
     */
    int cur_page;
    //TODO 0表示答题，1表示背题，表示当前处于背题还是答题
    int cur_mode;
    int page_sum;
    int answers_num;
    int correct_num;

    //TODO 当前的作答情况,1,2表示答对和答错，0表示未答
    std::vector<int>cur_state;
    Ui::SingleQuestion *ui;
};

#endif // SINGLEQUESTION_H
