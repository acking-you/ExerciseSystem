//
// Created by Alone on 2022-3-20.
//

#ifndef EXCLE_TEST_ERRORNOTEDIALOG_H
#define EXCLE_TEST_ERRORNOTEDIALOG_H

#include <QWidget>
#include <QListWidgetItem>

/**
 * 此处简述下整个错题的显示过程：\n
 * 1.该类发送activatedQ信号通知主窗口我所需要的错题类型\n
 * 2.通知到位后，在主窗口更新对应的QList然后在主窗口发送信号去传递QList信息\n
 * 3.由于信号槽机制，此时我们到了setListToWidget槽函数内，我们此时只需要把QList信息展示即可\n
 * 4.如果我们点击了对应的错题信息项会发送itemPressedId信号通知到主窗口当前点到的题目id\n
 * 5.主窗口根据传递过来的题目id和之前已经掌握的错题类型信息创建一个新的题目作答窗口
 */

QT_BEGIN_NAMESPACE
namespace Ui { class ErrorNoteDialog; }
QT_END_NAMESPACE

class ErrorNoteDialog : public QWidget {
Q_OBJECT

public:
    explicit ErrorNoteDialog(QWidget *parent = nullptr);
    void show();
    ~ErrorNoteDialog() override;
signals:
    void activatedQ(int index);
    void itemPressedId(int qid);
public slots:
    void setListToWidget(QList<QString>* list);
private slots:
    void on_pressed(QListWidgetItem *item);
    void on_activated(int );

private:
    Ui::ErrorNoteDialog *ui;
};


#endif //EXCLE_TEST_ERRORNOTEDIALOG_H
