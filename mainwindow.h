#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include <QPushButton>
#include "SqlSession.h"
#include "JudgmentQ.h"
#include "SingleChoiceQ.h"
#include "MutiChoiceQ.h"
#include <QMediaPlayer>
#include "errornotedialog.h"
class JudgmentQuestion;
class SingleQuestion;
class run_thread;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void init_mappers();

    void init_ImgsPath();

    void init_musicPath();

    void start_style();

    void pause_style();

    void initQuestion();

    void randomOperation();

    void updateIndexMapper();
    void updateRetHelper(std::unordered_map<int,int>&record,std::unordered_map<int,int>&index_mapper,
            QList<QString>& ret,int state);
    QList<QString>* getNoteBookList(int state);
signals:
    void play();
    void pause();
    void stop();
    void updateNoteBookList(QList<QString>* list);
private slots:

    void showImgToSwitch();

    void showAvaterSwitch();

    void on_choose_avater_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_practice_ordered_clicked();

    void on_practice_random_clicked();

    void on_import_excle_clicked();

    void on_errorNote_btn_clicked();

    void on_durationChanged(qint64);

    void on_positionChanged(qint64);
    //TODO 当播放状态改变的时候进行内部状态的传递
    void changed_PlayState(QMediaPlayer::PlaybackState status);
    void on_media_change(QMediaPlayer::MediaStatus status);
    void on_m_musicButton_clicked();
    void next_musicBtn();
    void pre_musicBtn();
    void on_music_slider_sliderMoved(int position);


    void on_sql_btn_clicked();
    void solveNoteBookActivatedQ(int index);
    void solveNoteBookitemPressedId(int id);
private:
    std::shared_ptr<run_thread> sub_thread;

    std::shared_ptr<JudgmentQuestion> judge;
    std::shared_ptr<SingleQuestion> single;
    ErrorNoteDialog* errorNode = nullptr; //错题本的窗口
    int cur_noteChoice = 0;
    QTimer *timer;
    QTimer *timer2;
    QList<QPair<QString, QString>> links_mapper;

    QLabel *avater;
    QLabel *imgs_tip;

    int flag_AvaterChoose;
    QPushButton *choose_avater;

    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
    QList<QString> avaters_path;
    QList<QString> imgs_path;

    //TODO 以下为播放音乐所需的组件
    QList<QString> music_name;
    //TODO 记录当前的Media状态
    QMediaPlayer::PlaybackState m_playerState = QMediaPlayer::StoppedState;
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* m_audioOutput;
    QPushButton* m_musicButton;


    QList<std::shared_ptr<JudgmentQ>> judgmentQ;
    QList<std::shared_ptr<SingleChoiceQ>> singleChoiceQ;
    QList<std::shared_ptr<MutiChoiceQ>> mutiChoiceQ;
    //TODO 用于快速映射以上题目的数组下标
    std::unordered_map<int,int> index_fromJudgmentId;
    std::unordered_map<int,int> index_fromSingleId;
    std::unordered_map<int,int> index_fromMutiId;
    //TODO 以下为容纳一个题目的list
    QList<std::shared_ptr<JudgmentQ>> one_judgmentQ;
    QList<std::shared_ptr<SingleChoiceQ>> one_singleChoiceQ;
    QList<std::shared_ptr<MutiChoiceQ>> one_mutiChoiceQ;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
