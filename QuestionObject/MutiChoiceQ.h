//
// Created by Alone on 2022-3-8.
//

#ifndef EXCLE_TEST_MUTICHOICEQ_H
#define EXCLE_TEST_MUTICHOICEQ_H
#include "BaseQ.h"

class MutiChoiceQ :public BaseQ<MutiChoiceQ>{
    int answer;
public:
    static bool isA(int);
    static bool isB(int);
    static bool isC(int);
    static bool isD(int);
    MutiChoiceQ() : answer(0) {}//TODO 初始化answer为-1代表没有被设置值

    QString getSelectSql() override;

    static QString answer_to_string(int answer);

    static int string_to_answer(const QString &answer);

    QString getInsertSql() override;

    MutiChoiceQ &setId(int) override;

    MutiChoiceQ &setChapter(int) override;

    MutiChoiceQ &setQuestion(const QString &) override;

    MutiChoiceQ &setA(const QString &) override;

    MutiChoiceQ &setB(const QString &) override;

    MutiChoiceQ &setC(const QString &) override;

    MutiChoiceQ &setD(const QString &) override;

    MutiChoiceQ &setAnswer(const QString &) override;

    int getChapter();

    int getId() override;

    QString getQuestion() override;

    QString getA();

    QString getB();

    QString getC();

    QString getD();

    int getAnswer();
};


#endif //EXCLE_TEST_MUTICHOICEQ_H
