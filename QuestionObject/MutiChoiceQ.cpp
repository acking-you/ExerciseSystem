//
// Created by Alone on 2022-3-8.
//

#include "MutiChoiceQ.h"

QString MutiChoiceQ::getSelectSql() {
    return op_select_all.arg("muti_choice");
}

QString MutiChoiceQ::getInsertSql() {
    return  insert_one.arg("muti_choice").arg(chapter).arg(question)
            .arg(op_a).arg(op_b).arg(op_c).arg(op_d).arg(answer_to_string(answer));
}

QString MutiChoiceQ::answer_to_string(int answer) {
    QString ret;
    if(isA(answer))
        ret += "A";
    if(isB(answer))
        ret += "B";
    if(isC(answer))
        ret += "C";
    if(isD(answer))
        ret += "D";
    if(ret.isEmpty())
        throw std::exception();
    return ret;
}

bool MutiChoiceQ::isA(int answer) {
    return answer&1;
}

bool MutiChoiceQ::isB(int answer) {
    return answer&(1<<1);
}

bool MutiChoiceQ::isC(int answer) {
    return answer&(1<<2);
}

bool MutiChoiceQ::isD(int answer) {
    return answer&(1<<3);
}

int MutiChoiceQ::string_to_answer(const QString &answer) {
    int ret = 0;
    if(answer.contains('A'))
        ret |= (1<<0);
    if(answer.contains('B'))
        ret |= (1<<1);
    if(answer.contains('C'))
        ret |= (1<<2);
    if(answer.contains('D'))
        ret |= (1<<3);
    if(ret==0)
        throw std::exception();
    return ret;
}

MutiChoiceQ &MutiChoiceQ::setId(int num) {
    id = num;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setChapter(int c) {
    chapter = c;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setQuestion(const QString &q) {
    question = q;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setAnswer(const QString &a) {
    answer = string_to_answer(a);
    return *this;
}

int MutiChoiceQ::getChapter() {
    return chapter;
}

int MutiChoiceQ::getId() {
    return id;
}

QString MutiChoiceQ::getQuestion() {
    return question;
}

QString MutiChoiceQ::getA() {
    return op_a;
}

QString MutiChoiceQ::getB() {
    return op_b;
}

QString MutiChoiceQ::getC() {
    return op_c;
}

QString MutiChoiceQ::getD() {
    return op_d;
}

int MutiChoiceQ::getAnswer() {
    return answer;
}

MutiChoiceQ &MutiChoiceQ::setA(const QString &a) {
    op_a = a;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setB(const QString &b) {
    op_b = b;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setC(const QString &c) {
    op_c = c;
    return *this;
}

MutiChoiceQ &MutiChoiceQ::setD(const QString &d) {
    op_d = d;
    return *this;
}
