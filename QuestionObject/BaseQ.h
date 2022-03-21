//
// Created by Alone on 2022-3-8.
//
/**
 * 定义虚函数接口：基本的设置方法和共同拥有的一些设置属性，答案根据不同类型再进行重写设置
 * 通过is_choice完成编译时的trait判断类型
 */

#ifndef EXCLE_TEST_BASEQ_H
#define EXCLE_TEST_BASEQ_H

#include <QString>

class JudgmentQ;    //防止直接include导致循环导入

template<typename T>
class BaseQ {
protected:
    QString op_select_all = "select * from %1;";
    QString insert_one = "INSERT INTO %1(chapter, question, option_a, option_b, option_c, option_d, answer)"
                         " VALUES(%2,'%3','%4','%5','%6','%7','%8');";
    int id;
    int chapter;
    QString question;
    QString op_a;
    QString op_b;
    QString op_c;
    QString op_d;

    bool isValidSql(const QString &text) {
        return !(text.contains(';') || text.contains(' '));
    }

public:
    static const bool is_choice = true;

    virtual QString getSelectSql() = 0;

    virtual QString getInsertSql() = 0;

    virtual QString getQuestion() = 0;

    virtual int getId() = 0;

    virtual T &setId(int) = 0;

    virtual T &setChapter(int) = 0;

    virtual T &setQuestion(const QString &) = 0;

    virtual T &setA(const QString &) = 0;

    virtual T &setB(const QString &) = 0;

    virtual T &setC(const QString &) = 0;

    virtual T &setD(const QString &) = 0;

    virtual T &setAnswer(const QString &) = 0;
};

template<>
class BaseQ<JudgmentQ> {
protected:
    QString op_select_all = "select * from %1;";
    QString insert_one = "INSERT INTO %1(chapter, question, answer)"
                         " VALUES(%2,'%3','%4');";
    int id;
    int chapter;
    QString question;

    bool isValidSql(const QString &text) {
        return !(text.contains(';') || text.contains(' '));
    }

public:
    static const bool is_choice = false;

    virtual QString getQuestion() = 0;

    virtual int getId() = 0;

    virtual QString getSelectSql() = 0;

    virtual QString getInsertSql() = 0;

    virtual JudgmentQ &setId(int) = 0;

    virtual JudgmentQ &setChapter(int) = 0;

    virtual JudgmentQ &setQuestion(const QString &) = 0;

    virtual JudgmentQ &setAnswer(const QString &) = 0;
};

#endif //EXCLE_TEST_BASEQ_H
