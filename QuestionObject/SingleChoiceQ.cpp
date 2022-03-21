//
// Created by Alone on 2022-3-8.
//

#include "SingleChoiceQ.h"

QString SingleChoiceQ::getSelectSql() {
    return op_select_all.arg("single_choice");
}

QString SingleChoiceQ::answer_to_string(int answer) {
    QString ret;
    switch (answer) {
        case 1:
            ret = "A";
            break;
        case 2:
            ret = "B";
            break;
        case 3:
            ret = "C";
            break;
        case 4:
            ret = "D";
            break;
        default:
            ret = "?";
    }
    return ret;
}

int SingleChoiceQ::string_to_answer(const QString &answer) {
    int ret = -1;
    if (answer.contains('A')) {
        ret = 1;
    } else if (answer.contains('B')) {
        ret = 2;
    } else if (answer.contains('C')) {
        ret = 3;
    } else if (answer.contains('D')) {
        ret = 4;
    }
    return ret;
}

QString SingleChoiceQ::getInsertSql() {
    return insert_one.arg("single_choice").arg(chapter).arg(question)
            .arg(op_a).arg(op_b).arg(op_c).arg(op_d).arg(answer_to_string(answer));
}

SingleChoiceQ &SingleChoiceQ::setId(int num) {
    id = num;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setChapter(int c) {
    chapter = c;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setQuestion(const QString &q) {
    question = q;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setAnswer(const QString &a) {
    answer = string_to_answer(a);
    return *this;
}

int SingleChoiceQ::getChapter() {
    return chapter;
}

int SingleChoiceQ::getId() {
    return id;
}

QString SingleChoiceQ::getQuestion() {
    return question;
}

QString SingleChoiceQ::getA() {
    return op_a;
}

QString SingleChoiceQ::getB() {
    return op_b;
}

QString SingleChoiceQ::getC() {
    return op_c;
}

QString SingleChoiceQ::getD() {
    return op_d;
}

int SingleChoiceQ::getAnswer() {
    return answer;
}

SingleChoiceQ &SingleChoiceQ::setA(const QString &a) {
    op_a = a;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setB(const QString &b) {
    op_b = b;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setC(const QString &c) {
    op_c = c;
    return *this;
}

SingleChoiceQ &SingleChoiceQ::setD(const QString &d) {
    op_d = d;
    return *this;
}
