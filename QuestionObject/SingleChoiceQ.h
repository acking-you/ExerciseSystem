//
// Created by Alone on 2022-3-8.
//

#ifndef EXCLE_TEST_SINGLECHOICEQ_H
#define EXCLE_TEST_SINGLECHOICEQ_H

#include "BaseQ.h"

class SingleChoiceQ : public BaseQ<SingleChoiceQ> {
    int answer;
public:
    SingleChoiceQ() : answer(-1) {}//TODO 初始化answer为-1代表没有被设置值

    QString getSelectSql() override;

    static QString answer_to_string(int answer);

    static int string_to_answer(const QString &answer);

    QString getInsertSql() override;

    SingleChoiceQ &setId(int) override;

    SingleChoiceQ &setChapter(int) override;

    SingleChoiceQ &setQuestion(const QString &) override;

    SingleChoiceQ &setA(const QString &) override;

    SingleChoiceQ &setB(const QString &) override;

    SingleChoiceQ &setC(const QString &) override;

    SingleChoiceQ &setD(const QString &) override;

    SingleChoiceQ &setAnswer(const QString &) override;

    int getChapter();

    int getId();

    QString getQuestion();

    QString getA();

    QString getB();

    QString getC();

    QString getD();

    int getAnswer();
};


#endif //EXCLE_TEST_SINGLECHOICEQ_H
