//
// Created by Alone on 2022-3-9.
//

#include "JudgmentQ.h"

QString JudgmentQ::getSelectSql() {
    //指明表名即可
    return op_select_all.arg("judgment");
}

QString JudgmentQ::getInsertSql() {
    //初始化这个insert语句前，请确保每个字段已经被初始化
    return insert_one.arg("judgment").arg(chapter).arg(question).arg(answer_to_string(answer));
}

JudgmentQ &JudgmentQ::setId(int num) {
    id = num;
    return *this;
}

QString JudgmentQ::answer_to_string(int answer) {
    if (answer == 1)
        return "Y";
    else if (answer == 0)
        return "N";
    else
        throw std::exception();
}

int JudgmentQ::string_to_answer(const QString &answer) {
    if (answer.contains('Y')) {
        return 1;
    } else if (answer.contains('N')) {
        return 0;
    } else {
        throw std::exception();
    }
}

JudgmentQ &JudgmentQ::setChapter(int c) {
    chapter = c;
    return *this;
}

JudgmentQ &JudgmentQ::setQuestion(const QString &text) {
    question = text;
    return *this;
}

JudgmentQ &JudgmentQ::setAnswer(const QString &text) {
    answer = string_to_answer(text);
    return *this;
}

int JudgmentQ::getChapter() {
    return chapter;
}

int JudgmentQ::getId() {
    return id;
}

QString JudgmentQ::getQuestion() {
    return question;
}

int JudgmentQ::getAnswer() {
    return answer;
}
