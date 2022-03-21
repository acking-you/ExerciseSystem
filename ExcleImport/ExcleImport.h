//
// Created by Alone on 2022-3-10.
//

#ifndef EXCLE_TEST_EXCLEIMPORT_H
#define EXCLE_TEST_EXCLEIMPORT_H
#include "SqlSession.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "col_info.h"
#include <QMessageBox>
//TODO 第一个参数是需要导入的excle类型，后面是对应的excle列
using namespace QXlsx;

template<class T>
class ExcleImport{
    ExcleImport() = delete;
private:
    static QList<T> readExcleToType(Document& xlsxR)  {
        QList<T> ret;
        bool isOk;
        for(int i=col_info::start_row;i<=col_info::end_row;i++){
            T item;
            auto chapter = xlsxR.read(i,col_info::col_chapter).toString().toUInt(&isOk);
            if(isOk){
                item.setChapter(chapter);
            }else{
                item.setChapter(0);
                QMessageBox::information(nullptr,"提示",QString("发生在第%1行\n").arg(i)+"发现excle章节描述非法(不是数字)");
            }

            auto que = xlsxR.read(i,col_info::col_que).toString();
            item.setQuestion(que);

            auto answer = xlsxR.read(i,col_info::col_answer).toString();
            item.setAnswer(answer);

            if constexpr(BaseQ<T>::is_choice){
                auto a = xlsxR.read(i,col_info::col_a);

                    item.setA(a.toString());

                auto b = xlsxR.read(i,col_info::col_b);

                    item.setB(b.toString());

                auto c = xlsxR.read(i,col_info::col_c);

                    item.setC(c.toString());

                auto d = xlsxR.read(i,col_info::col_d);

                    item.setD(d.toString());

            }
            ret.push_back(item);
        }
        return ret;
    }
public:
    static int importExcle(const QString& path){
        Document xlsxR(path);
        int ret;
        if ( xlsxR.load() ) // load excel file
        {
            qDebug() << "[debug] success to load xlsx file.";
            auto list = readExcleToType(xlsxR);
            SqlSession<T>::insertAll(list);
            ret = list.size();
        }
        else
        {
            ret = -1;
            qDebug() << "[debug][error] failed to load xlsx file.";
        }
        return ret;
    }
};
#endif //EXCLE_TEST_EXCLEIMPORT_H
