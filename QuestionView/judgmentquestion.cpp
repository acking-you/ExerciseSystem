#include <fstream>
#include "judgmentquestion.h"
#include "ui_judgmentquestion.h"
#include "json.hpp"
#include "run_thread.h"
#include "record_source.h"
#include <QMessageBox>

using nlohmann::json;

static void btn_stylesheet_init(QPushButton *button) {
    if (button == nullptr)
        return;
    else {
        button->setStyleSheet(R"(QPushButton{
                                background-color:#1a8cff;
                                color:#ffffff;
                               border: 1px solid #0d85ff;
                                 border-radius: 5px;
                                font-size:15px;
                              }
                              QPushButton:hover{
                                 background-color:rgb(97, 175, 255);
                                 border: 1px solid #5554ff;
                              }
                              QPushButton:pressed{
                                background-color:#007fff;
                                }
            )");
    }
}

//TODO 两个选择按钮的状态改变函数
static void set_btn_IconError(QPushButton *button) {
    if (button == nullptr) {
        return;
    } else {
        button->setText("");
        button->setStyleSheet(R"(
                image:url(:/错误.png);
                border-radius:12px;
            )");
    }
}

static void set_btn_IconCorrect(QPushButton *button) {
    if (button == nullptr)
        return;
    else {
        button->setText("");
        button->setStyleSheet(R"(
                image:url(:/正确.png);
                border-radius:12px;
            )");
    }
}

static void set_accept_btn_original_state(QPushButton *button) {
    if (button == nullptr)
        return;
    else {
        button->setText("Y");
        button->setStyleSheet(R"(
            QPushButton{background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:2px;
            padding-bottom:2px;})");
    }
}

static void set_no_btn_original_state(QPushButton *button) {
    if (button == nullptr)
        return;
    else {
        button->setText("N");
        button->setStyleSheet(R"(
            QPushButton{background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:2px;
            padding-bottom:2px;})");
    }
}

//TODO 两个文字内容的状态改变
static void set_label_IconError(QLabel *label) {
    if (label == nullptr) {
        return;
    } else {
        label->setStyleSheet(R"(
                color:#f5222d;
            )");
    }
}

static void set_label_IconCorrect(QLabel *label) {
    if (label == nullptr)
        return;
    else {
        label->setStyleSheet(R"(
                color:#11aa66;
            )");
    }
}

static void set_lable_original_state(QLabel *label) {
    if (label == nullptr)
        return;
    else {
        label->setStyleSheet(R"(
            color:black;)");
    }
}

JudgmentQuestion::JudgmentQuestion(QList<std::shared_ptr<JudgmentQ>>* all_q,QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::JudgmentQuestion) {
    ui->setupUi(this);

    assert(all_q != nullptr);
    this->all_q = all_q;
    sum_page = all_q->size();
    cur_page = 1;
    cur_state.resize(sum_page); //TODO 初始化用于表示当前题目状态的数组，状态：（答/未答）
    cur_mode = 0;
    answers_num = 0;
    correct_num = 0;
    this->setWindowIcon(QIcon(":/Icon.png"));
    this->setWindowTitle("判断题——made By L_B__");
    auto *next_question = new QPushButton(this);
    auto *pre_question = new QPushButton(this);
    nextBtn = next_question;
    preBtn = pre_question;
    //TODO 连接槽函数
    connect(next_question,&QPushButton::clicked,this,&JudgmentQuestion::on_next_question_clicked);
    connect(pre_question,&QPushButton::clicked,this,&JudgmentQuestion::on_pre_question_clicked);
    next_question->setText("下一题");
    pre_question->setText("上一题");
    next_question->setGeometry(550, 400, 100, 40);
    pre_question->setGeometry(550, 350, 100, 40);
    btn_stylesheet_init(next_question);
    btn_stylesheet_init(pre_question);
    setToMode1();
    updateQ();
}

JudgmentQuestion::~JudgmentQuestion() {

    delete ui;
}

void JudgmentQuestion::on_mode1_clicked() {
    cur_mode = 0;
    updateQ();
    setToMode1();
    ActiveBtn(true);
}

void JudgmentQuestion::setToMode1() {
    ui->label_2->setVisible(false);
    ui->answer->setVisible(false);
    set_accept_btn_original_state(ui->accept_btn);
    set_no_btn_original_state(ui->no_btn);
    set_lable_original_state(ui->accpet_text);
    set_lable_original_state(ui->no_text);
}

void JudgmentQuestion::clearTxt()
{
    cur_page = 1;
    cur_mode = 0;
    answers_num = 0;
    correct_num = 0;
    ActiveBtn();
    setToMode1();
    //状态清零
    std::fill(cur_state.begin(),cur_state.end(),0);
}
//TODO 传递参数为true后，可把mode2的设定当作mode1来用，只是能够设定按钮的样式而已
void JudgmentQuestion::setToMode2(bool isChangeToMode1) {
    if(!isChangeToMode1){
        ui->label_2->setVisible(true);
        ui->answer->setVisible(true);
    }

    int cur_answer = (*all_q)[cur_page-1]->getAnswer();

    //TODO 根据当前的答案状态1表示当前答案是Y，0表示是N，得到对应的按钮来设置对应的样式
    auto correct_btn = cur_answer==1?ui->accept_btn:ui->no_btn;
    auto correct_text = cur_answer==1?ui->accpet_text:ui->no_text;
    auto no_btn = cur_answer==1?ui->no_btn:ui->accept_btn;
    auto no_text = cur_answer==1?ui->no_text:ui->accpet_text;

    //TODO 下面根据是否是mode2的情况，或者是否答对的情况看是否给出对应的样式
    if(cur_mode==1||cur_state[cur_page-1]==1||cur_state[cur_page-1]==2){
        set_btn_IconCorrect(correct_btn);
        set_label_IconCorrect(correct_text);
    }
    if(cur_mode==1||cur_state[cur_page-1]==2){
        set_btn_IconError(no_btn);
        set_label_IconError( no_text);
    }
    //TODO 为了保持答对后的一致性，需要判断答案是ok还是no，然后把no的那个设置回普通样式
    if(cur_state[cur_page-1]==1){
        if(correct_btn==ui->accept_btn){
            set_no_btn_original_state(no_btn);
        }else{
            set_accept_btn_original_state(no_btn);
        }
        set_lable_original_state(no_text);
    }
}

void JudgmentQuestion::updateQ(bool isAlready) {
    auto question = (*all_q)[cur_page-1]->getQuestion();
    auto answer = JudgmentQ::answer_to_string((*all_q)[cur_page-1]->getAnswer());
    ui->qu_text->setPlainText(question); //设置题目信息
    if(isAlready){
        InActiveBtn();
    }else{
        //TODO 当状态为1的时候表示作答正确，状态为2的时候表示作答错误，为0表示还未作答
        switch (cur_state[cur_page-1]) {
            case 1:
                answers_num++;
                correct_num++;
                break;
            case 2:
                answers_num++;
                break;
            default:
                break;
        }
    }
    //TODO 统计信息和答案的设定
    ui->answer_times->setText(QString::number(answers_num));
    ui->correct_times->setText(QString::number(correct_num));
    int rate = 0;
    if(answers_num>0)
        rate = int(((double )correct_num/answers_num)*100);
    ui->correct_rate->setText(QString::number(rate)+"%");
    ui->answer->setText(answer);
    //TODO 顶部页面导航栏
    ui->q_numbers->setText(QString::number(cur_page)+"/"+QString::number(sum_page));
}

int JudgmentQuestion::resetQSum(int num,int update)
{
    if(update){ //TODO 如果是更新状态
        cur_state.resize(num+1);
    }
    if(!update&&cur_state.size()<num){//TODO 非更新状态
        QMessageBox::warning(nullptr,"警告","题库数量不够");
        return 1;
    }
    clearTxt();
    //TODO 在外面由洗牌算法打乱数组，这里只需要设置最大的题目数量即可
    sum_page = num;
    updateQ();
    return 0;
}

void JudgmentQuestion::on_mode2_clicked() {
    cur_mode = 1;
    updateQ();
    setToMode2();
    InActiveBtn(true);
}

void JudgmentQuestion::on_next_question_clicked() {
    if(cur_page>=sum_page)
        return;

    cur_page++;
    //TODO 表示已经被选择过，所以传入isAlready，且用之前的样式即可
    if(cur_state[cur_page-1]==1||cur_state[cur_page-1]==2){
        updateQ(true);
        setToMode2();
        return;
    }
    ActiveBtn();

    updateQ();
    if(cur_mode==1){//TODO 当前状态是背题模式，不要让选择按钮可用
        InActiveBtn(true);
        setToMode2();
    }
    else setToMode1();
}

void JudgmentQuestion::on_pre_question_clicked() {
    if(cur_page<=1)
        return;

    cur_page--;
    //TODO 表示已经被选择过，所以传入isAlready，且用之前的样式即可
    if(cur_state[cur_page-1]==1||cur_state[cur_page-1]==2){
        updateQ(true);
        setToMode2();
        return;
    }
    ActiveBtn();
    updateQ();
    if(cur_mode==1){//TODO 当前状态是背题模式，不要让选择按钮可用
        InActiveBtn(true);
        setToMode2();
    }
    else setToMode1();
}

void JudgmentQuestion::on_accept_btn_clicked() {
    int answer = (*all_q)[cur_page-1]->getAnswer();
    //TODO 如果答案是正确的，则当前为答对的状态，否则为答错的状态，答错的题目编号收集到m_record
    int id = (*all_q)[cur_page-1]->getId();
    if(answer==1)
        cur_state[cur_page-1] = 1;
    else{
        cur_state[cur_page-1] = 2;
        judgment_error_record[id]++;//这个值表示这个id题目的错误次数
    }

    updateQ();
    setToMode2();
    InActiveBtn();
}

void JudgmentQuestion::on_no_btn_clicked() {
    int answer = (*all_q)[cur_page-1]->getAnswer();
    //TODO 如果答案是正确的，则当前为答对的状态，否则为答错的状态
    int id = (*all_q)[cur_page-1]->getId();
    if(answer==0)
        cur_state[cur_page-1] = 1;
    else{
        cur_state[cur_page-1] = 2;
        judgment_error_record[id]++;//这个值表示这个id题目的错误次数
    }
    updateQ();
    setToMode2();
    InActiveBtn();
}

void JudgmentQuestion::InActiveBtn(bool isRecite) {
    if(!isRecite){
        ui->mode1->setEnabled(false);
        ui->mode2->setEnabled(false);
    }
    ui->accept_btn->setEnabled(false);
    ui->no_btn->setEnabled(false);
}

void JudgmentQuestion::ActiveBtn(bool isRecite) {
    if(!isRecite){
        ui->mode1->setEnabled(true);
        ui->mode2->setEnabled(true);
    }
    ui->accept_btn->setEnabled(true);
    ui->no_btn->setEnabled(true);
}

JudgmentQuestion *JudgmentQuestion::getOneJudgementWidget(QList<std::shared_ptr<JudgmentQ>>* one_q) {
    assert(one_q!= nullptr&&one_q->size()==1);
    static JudgmentQuestion p_judgment(one_q);//此语句只会执行一次，不必担心
    static bool once = true;//TODO static_local控制语句只执行一次
    if(once){
        once = false;
        p_judgment.ui->label_4->setVisible(false);
        p_judgment.ui->w4->setVisible(false);
        p_judgment.nextBtn->setVisible(false);
        p_judgment.preBtn->setVisible(false);
    }
    p_judgment.clearTxt();
    p_judgment.updateQ();
    return &p_judgment;
}
