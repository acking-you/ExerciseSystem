//
// Created by Alone on 2022-3-8.
//

#ifndef EXCLE_TEST_SQLSESSION_H
#define EXCLE_TEST_SQLSESSION_H

#include <QString>
#include <memory>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QApplication>
#include <QSqlRecord>
#include "BaseQ.h"
//TODO db文件的位置
#define DB_PATH R"(C:\Users\Alone\Desktop\马原题目数据库\data.db)"

template<class T=JudgmentQ>
class SqlSession {
    static QList<std::shared_ptr<BaseQ<T>>> base_lists; //TODO 用基类指针做缓存，方便接住任意类型，且能够安全的转型
    static std::shared_ptr<QSqlDatabase> db;

    SqlSession() = delete;

    //TODO 初始化数据库相关索引媒介
    static void init_db() {
        if (QSqlDatabase::drivers().isEmpty()) {
            QMessageBox::warning(nullptr, "没有发现数据库驱动", "执行此程序的功能需要数据库");
            QApplication::exit(-1);
        }
        //得到对应数据库类型的连接媒介，如果之前连接还存在，则不继续连接，否则重新连接
        if (QSqlDatabase::contains("qt_sql_default_connection"))
            db = std::make_shared<QSqlDatabase>(QSqlDatabase::database("qt_sql_default_connection"));
        else {
            db = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
            db->setDatabaseName(DB_PATH);//数据库的所在位置
        }
        if (!db->open()) {//启动数据库失败的提示
            QMessageBox::warning(nullptr, "open error", "数据库启动失败");
            QApplication::exit(-1);
        }
    }

    //TODO 进行一个更新的普适性
    static void update(QList<std::shared_ptr<T>>* ret = nullptr){
        BaseQ<T> *q = nullptr; //通过基类指针操作各种set操作
        auto sql = T().getSelectSql();
        if (db == nullptr) {//开始的时候db未被初始化，进行一次初始化
            init_db();
        }
        QSqlQuery query(*db);
        query.exec(sql); //执行sql语句
        while (query.next()) {
            q = new T();
            //大家公共的部分
            q->setId(query.value(0).toInt());
            q->setChapter(query.value(1).toInt());
            q->setQuestion(query.value(2).toString());
            //TODO 这里必须要用if constexpr，在编译期就确认这段代码不会被经过，所以不会检查这段代码的语法
            if constexpr(BaseQ<T>::is_choice) {//如果是选择题，则还要进行选项的填充,选项注意去除前后空格
                q->setA(query.value(3).toString().trimmed());
                q->setB(query.value(4).toString().trimmed());
                q->setC(query.value(5).toString().trimmed());
                q->setD(query.value(6).toString().trimmed());
                q->setAnswer(query.value(7).toString());
            } else { //否则是判断题
                q->setAnswer(query.value(3).toString());
            }

            //TODO 注意要新建一个shared_ptr再传入到vector中，否则状态不会被共享，会产生内存问题
            std::shared_ptr<T> ptr((T *) q);
            if(ret!= nullptr)
                ret->push_back(std::shared_ptr<T>(ptr));
            base_lists.push_back(std::shared_ptr<BaseQ<T>>(ptr));

            qDebug() << ptr.use_count() << '\n'; //调试看看智能指针的工作是否正常
        }
    }
public:
    //TODO 得到数据库的内容
    static QList<std::shared_ptr<T>> getAllQ() {
        QList<std::shared_ptr<T>> ret; //用于返回的答案
        //TODO 如果base_lists没有缓存，则请求数据库
        if (base_lists.isEmpty()) {
            update(&ret);
        } else {//TODO 否则直接进行强行转型后便可用于返回了
            for (auto &ptr: base_lists) {
                //智能指针的基类向下转型
                ret.push_back(std::static_pointer_cast<T>(ptr));
            }
        }
        return ret;
    }

    //TODO 批量更新数据库的内容
    static bool insertAll(QList<T> &items){
        if(db==nullptr)
            init_db();
        QSqlQuery query(*db);
        db->transaction(); //TODO 执行事务
        for(int i=0;i<items.size();i++){
         QString text = items[i].getInsertSql();
            if(!query.exec(text))
                return false;
        }
        db->commit();
        //TODO 重新刷新缓存
        base_lists.clear();
        update();
        return true;
    }
    /**
     * 效果：执行sql语句\n
     * 返回值：执行成功则返回生效的列数，否则返回-1
     */
     static int execSql(QString sql){
      if(!db)
        init_db();
        QSqlQuery query(*db);
        int ret;
        if(!query.exec(sql)){//TODO 执行失败
            ret = -1;
        }else{
           ret = 0;
        }
        return ret;
     }
};

/**
 * 以下为静态变量的定义
 * 这就是模板的神奇了，定义放在.h文件里面也不会在多个.cpp文件使用的时候产生重复定义
 * 原因是模板的特性，
 * 1.模板只有在用户使用的时候才会进行代码的真正展开
 * 2.每个类型的模板实例化只会进行一次，也就是说相同类型的静态变量只会产生一个定义。
 * 故模板中的静态变量的定义放在.h文件里，也不会产生重复定义问题
 */
template<class T>
QList<std::shared_ptr<BaseQ<T>>> SqlSession<T>::base_lists;

template<class T>
std::shared_ptr<QSqlDatabase> SqlSession<T>::db;

#endif //EXCLE_TEST_SQLSESSION_H
