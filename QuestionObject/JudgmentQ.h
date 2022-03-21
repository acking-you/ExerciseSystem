//
// Created by Alone on 2022-3-9.
//

#ifndef EXCLE_TEST_JUDGMENTQ_H
#define EXCLE_TEST_JUDGMENTQ_H


#include "BaseQ.h"

class JudgmentQ : public BaseQ<JudgmentQ> {
    int answer;
public:
    JudgmentQ() : answer(-1) {}//TODO 初始化answer为-1代表没有被设置值
    QString getSelectSql() override;

    static QString answer_to_string(int answer);

    static int string_to_answer(const QString &answer);

    QString getInsertSql() override;

    JudgmentQ &setId(int) override;

    JudgmentQ &setChapter(int) override;

    JudgmentQ &setQuestion(const QString &) override;

    JudgmentQ &setAnswer(const QString &) override;

    int getChapter();

    int getId();

    QString getQuestion() override;

    int getAnswer();
};


#endif //EXCLE_TEST_JUDGMENTQ_H
