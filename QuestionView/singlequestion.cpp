#include "singlequestion.h"
#include "ui_singlequestion.h"
#include "record_source.h"
#include "QMessageBox"

//TODO 选择按钮的状态改变函数
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

//TODO 题目文字的样式改变
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

//TODO 设置按钮的样式回到原始状态，且附上文字
static void set_btn_original_state(QPushButton *button,QString const& text) {
    if (button == nullptr)
        return;
    else {
        button->setText(text);
        button->setStyleSheet(R"(
            QPushButton{background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:2px;
            padding-bottom:2px;})");
    }
}



SingleQuestion::SingleQuestion(QList<std::shared_ptr<SingleChoiceQ>>* all_q,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingleQuestion)
{
    ui->setupUi(this);
    assert(all_q!= nullptr);
    this->all_q = all_q;
    setWindowTitle("选择题 made By L_B__");
    setWindowIcon(QIcon(":/Icon.png"));
    page_sum = all_q->size();
    cur_page = 1;
    cur_state.resize(page_sum+1);
    cur_mode = 0;
    answers_num = 0;
    correct_num = 0;
    showQ();
}

SingleQuestion::~SingleQuestion()
{
    delete ui;
}

void SingleQuestion::hideAnswer() {
    ui->label_answer->setVisible(false);
    ui->answer->setVisible(false);
}

void SingleQuestion::showAnswer(const QString &answer) {
    ui->answer->setText(answer);
    ui->label_answer->setVisible(true);
    ui->answer->setVisible(true);
}

void SingleQuestion::setStyleMode1() {
    //TODO 确保按钮被激活，且样式都回到原始状态，而且答案的那一块要隐藏
    setBtnActive();
    hideAnswer();
    set_btn_original_state(ui->a_btn,"A");
    set_btn_original_state(ui->b_btn,"B");
    set_btn_original_state(ui->c_btn,"C");
    set_btn_original_state(ui->d_btn,"D");
    set_lable_original_state(ui->a_text);
    set_lable_original_state(ui->b_text);
    set_lable_original_state(ui->c_text);
    set_lable_original_state(ui->d_text);
}

void SingleQuestion::setBtnInActive() {
    ui->a_btn->setEnabled(false);
    ui->b_btn->setEnabled(false);
    ui->c_btn->setEnabled(false);
    ui->d_btn->setEnabled(false);
}

void SingleQuestion::setBtnActive() {
    ui->a_btn->setEnabled(true);
    ui->b_btn->setEnabled(true);
    ui->c_btn->setEnabled(true);
    ui->d_btn->setEnabled(true);
}

void SingleQuestion::setStyleMode2(int answerId) {
    if(answerId>=5||answerId<=0)
        return;
    //TODO 需要保证答案的那一块被显示，以及按钮无法再用
    setBtnInActive();
    showAnswer(SingleChoiceQ::answer_to_string(answerId));
    switch (answerId) {
        case 1:
            set_btn_IconCorrect(ui->a_btn);
            set_label_IconCorrect(ui->a_text);
            set_btn_original_state(ui->b_btn,"B");
            set_btn_original_state(ui->c_btn,"C");
            set_btn_original_state(ui->d_btn,"D");
            set_lable_original_state(ui->c_text);
            set_lable_original_state(ui->b_text);
            set_lable_original_state(ui->d_text);
            break;
        case 2:
            set_btn_IconCorrect(ui->b_btn);
            set_label_IconCorrect(ui->b_text);
            set_btn_original_state(ui->a_btn,"A");
            set_btn_original_state(ui->c_btn,"C");
            set_btn_original_state(ui->d_btn,"D");
            set_lable_original_state(ui->a_text);
            set_lable_original_state(ui->c_text);
            set_lable_original_state(ui->d_text);
            break;
        case 3:
            set_btn_IconCorrect(ui->c_btn);
            set_label_IconCorrect(ui->c_text);
            set_btn_original_state(ui->a_btn,"A");
            set_btn_original_state(ui->b_btn,"B");
            set_btn_original_state(ui->d_btn,"D");
            set_lable_original_state(ui->a_text);
            set_lable_original_state(ui->b_text);
            set_lable_original_state(ui->d_text);
            break;
        case 4:
            set_btn_IconCorrect(ui->d_btn);
            set_label_IconCorrect(ui->d_text);
            set_btn_original_state(ui->a_btn,"A");
            set_btn_original_state(ui->b_btn,"B");
            set_btn_original_state(ui->c_btn,"C");
            set_lable_original_state(ui->a_text);
            set_lable_original_state(ui->b_text);
            set_lable_original_state(ui->c_text);
            break;
    }
}

void SingleQuestion::setStyleMode3(int answerId) {
    if(answerId>=5||answerId<=0)
        return;
    setBtnInActive();
    showAnswer(SingleChoiceQ::answer_to_string(answerId));
    switch (answerId) {
        case 1:
            set_btn_IconCorrect(ui->a_btn);
            set_label_IconCorrect(ui->a_text);
            set_btn_IconError(ui->b_btn);
            set_btn_IconError(ui->c_btn);
            set_btn_IconError(ui->d_btn);
            set_label_IconError(ui->c_text);
            set_label_IconError(ui->b_text);
            set_label_IconError(ui->d_text);
            break;
        case 2:
            set_btn_IconCorrect(ui->b_btn);
            set_label_IconCorrect(ui->b_text);
            set_btn_IconError(ui->a_btn);
            set_btn_IconError(ui->c_btn);
            set_btn_IconError(ui->d_btn);
            set_label_IconError(ui->a_text);
            set_label_IconError(ui->c_text);
            set_label_IconError(ui->d_text);
            break;
        case 3:
            set_btn_IconCorrect(ui->c_btn);
            set_label_IconCorrect(ui->c_text);
            set_btn_IconError(ui->a_btn);
            set_btn_IconError(ui->b_btn);
            set_btn_IconError(ui->d_btn);
            set_label_IconError(ui->a_text);
            set_label_IconError(ui->b_text);
            set_label_IconError(ui->d_text);
            break;
        case 4:
            set_btn_IconCorrect(ui->d_btn);
            set_label_IconCorrect(ui->d_text);
            set_btn_IconError(ui->a_btn);
            set_btn_IconError(ui->b_btn);
            set_btn_IconError(ui->c_btn);
            set_label_IconError(ui->a_text);
            set_label_IconError(ui->b_text);
            set_label_IconError(ui->c_text);
            break;
    }
}

void SingleQuestion::updateQ() {
    //TODO 设置题目信息
    if(page_sum==0){
        QMessageBox::warning(nullptr,"提示","单选题读取错误！");
        return;
    }
    auto const& q = (*all_q)[cur_page-1];
    ui->question->setPlainText(q->getQuestion());
    ui->a_text->setText(q->getA());
    ui->b_text->setText(q->getB());
    ui->c_text->setText(q->getC());
    ui->d_text->setText(q->getD());
    //TODO 设置统计信息
    ui->sum_cnt->setText(QString::number(answers_num));
    ui->correct_cnt->setText(QString::number(correct_num));
    int percent = 0;
    if(answers_num>0)//TODO 只有作答了一次后，才计算percent
        percent = int(((double )correct_num/answers_num)*100);
    ui->correct_chance->setText(QString::number(percent)+"%");

    //TODO 设置最上层页面信息
    ui->cur_page->setText(QString::number(cur_page)+"/"+QString::number(page_sum));
}

void SingleQuestion::showQ() {
    //TODO 更新文字信息
    updateQ();
    //TODO 根据状态设置样式
    int state = getCurState();
    //TODO 得到当前题目的答案
    int answer_id = getCurAnswer();
    //TODO 处理样式设置
    if(cur_mode==0){ //处于答题状态
        switch (state) {
            case 1:
                //回答正确设置为状态1
                setStyleMode2(answer_id);
                break;
            case 2:
                //回答错误，设置为状态3
                setStyleMode3(answer_id);
                break;
            default:
                //题目未回答，应设置为状态1
                setStyleMode1();
        }
    }else if(cur_mode==1) {//处于背题状态
        setStyleMode3(answer_id);
    }
}

void SingleQuestion::on_mode1_clicked()
{
    cur_mode = 0;
    showQ();
}


void SingleQuestion::on_mode2_clicked()
{
    cur_mode = 1;
    showQ();
}


void SingleQuestion::on_pre_btn_clicked()
{
    if(cur_page<=1)
        return;
    --cur_page;
    showQ();
}


void SingleQuestion::on_next_btn_clicked()
{
    if(cur_page>=page_sum)
        return;
    ++cur_page;
    showQ();
}


void SingleQuestion::on_a_btn_clicked()
{
    int answer = getCurAnswer();
    answers_num++;
    if(answer==1){
        correct_num++;
        setCurState(1);
    }else{//TODO 答错需要进行一个记录到全局变量上去
        saveCurQRecord();
        setCurState(2);
    }
    showQ();
}

int SingleQuestion::getCurAnswer() {
    return (*all_q)[cur_page-1]->getAnswer();
}

void SingleQuestion::setCurState(int state) {
    cur_state[cur_page] = state;
}

int SingleQuestion::getCurState() {
    return cur_state[cur_page];
}


void SingleQuestion::on_b_btn_clicked()
{
    int answer = getCurAnswer();
    answers_num++;
    if(answer==2){
        correct_num++;
        setCurState(1);
    }else{
        saveCurQRecord();
        setCurState(2);
    }
    showQ();
}


void SingleQuestion::on_c_btn_clicked()
{
    int answer = getCurAnswer();
    answers_num++;
    if(answer==3){
        correct_num++;
        setCurState(1);
    }else{
        saveCurQRecord();
        setCurState(2);
    }
    showQ();
}


void SingleQuestion::on_d_btn_clicked()
{
    int answer = getCurAnswer();
    answers_num++;
    if(answer==4){
        correct_num++;
        setCurState(1);
    }else{
        saveCurQRecord();
        setCurState(2);
    }
    showQ();
}

void SingleQuestion::saveCurQRecord() {
    auto id = (*all_q)[cur_page-1]->getId();
    singleChoice_error_record[id]++;
}

int SingleQuestion::resetQSum(int new_sum,int update) {
    if(update){
        cur_state.resize(new_sum+1);
    }
    if(!update&&new_sum>page_sum){
        QMessageBox::warning(nullptr,"警告","需要显示的题目数量超出上限！");
        return 1;
    }
    page_sum = new_sum;
    //TODO 初始化所有之前的状态
    std::fill(cur_state.begin(),cur_state.end(),0);
    cur_page = 1;
    cur_mode = 0;
    answers_num = 0;
    correct_num = 0;
    showQ();
    return 0;
}

SingleQuestion *SingleQuestion::getOneSingleQuestionWidget(QList<std::shared_ptr<SingleChoiceQ>>* one_q) {
    static SingleQuestion p_single(one_q);
    static bool once = true;    //TODO 利用static_local控制代码块只执行一次
    if(once){
        p_single.resetQSum(1);
        p_single.ui->w4->setVisible(false);
        p_single.ui->pre_btn->setVisible(false);
        p_single.ui->next_btn->setVisible(false);
        p_single.ui->label_8->setVisible(false);
        once = false;
    }
    p_single.setStyleMode1();
    return &p_single;
}

