#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopServices>
#include<QLabel>
#include<QDir>
#include<algorithm>
#include<QTimer>
#include <memory>
#include <random>
#include <iostream>
#include <fstream>
#include <QAudioOutput>
#include "run_thread.h"
#include "record_source.h"
#include "json.hpp"
#include "choosedialog.h"
#include "judgmentquestion.h"
#include "singlequestion.h"
#include "ImportExcleDialog.h"
#include "ExcleImport.h"
#include "sqlinputdialog.h"
using nlohmann::json;

//TODO 按钮样式
void setBtnStartStyle(QPushButton *btn){
    if(btn!= nullptr){
        btn->setStyleSheet(R"(

QPushButton {
                                border: 1px solid #c7d4d4;
        image: url(:/开始.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;
                                }
 QPushButton:hover {

                                border: 1px solid #3498db;
                                }
QPushButton:pressed {
                                border: 1px solid #db7734;
                                }

       )");
    }
}
void setBtnPauseStyle(QPushButton *btn){
    if(btn!=nullptr){

        btn->setStyleSheet(R"(
QPushButton {
                                border: 1px solid #c7d4d4;
image: url(:/暂停.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;
                                }
 QPushButton:hover {

                                border: 1px solid #3498db;
                                }
QPushButton:pressed {
                                border: 1px solid #db7734;
                                }

)");
    }
}


//TODO 对话框选项复用
int getChooseState(int sum_judge=0,int sum_single=0,int sum_muti=0){
    auto c = ChooseDialog::getInstance();
    if(sum_judge>0){
        c->setJugeNum(sum_judge);
    }
    if(sum_single>0){
        c->setSingleNum(sum_single);
    }
    if(sum_muti>0){
        c->setMutiNum(sum_muti);
    }
    c->exec();
    return c->getCurState();
}

QPair<int,QString> getImportPath(){//TODO 在内部已经把列信息给赋值了，故只需根据状态看路径即可
    auto c = ImportExcleDialog::getInstance();
    c->exec();
    QString str;
    int state = c->getCurState();
    switch (state) {
        case 1:
        case 2:
        case 3:
            str = c->getExclePath();
            break;
    }
    return {state,str};
}


//TODO 错题的存储转化
int getIdFromQString(QString const& qString){
    int sz = qString.size();
    int i = sz-1;
    while (i>=0&&qString[i]!='=')i--;
    if(i==-1)//not find '='
        return -1;
    //find '=' ,and get the number in the QString's end
    i += 1;
    int answer = 0;
    while (i<sz) {
        answer = answer*10 + (qString[i].toLatin1()-'0');
        i++;
    }
    if(answer<0) //the number overflow
        return -1;
    return answer;
}

template<typename T>
QString getQStringFromQuestion(BaseQ<T>* Question,int times){
    QString mainQ = Question->getQuestion().trimmed().left(20);//TODO 只取20个字作概述
    int id = Question->getId();

    return "题目："+mainQ+"..."+QString(6,' ')+
    "错误次数："+QString::number(times)+QString(20,' ')+"id="+QString::number(id);
}


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), flag_AvaterChoose(0)
        ,one_judgmentQ(1),one_singleChoiceQ(1),one_mutiChoiceQ(1){
    ui->setupUi(this);
    srand(time(nullptr));
    setWindowTitle("练习系统——made by L_B__");
    setWindowIcon(QIcon(":/Icon.png"));

     sub_thread = std::make_shared<run_thread>( [&]{
         //TODO 读取题目
         judgmentQ = SqlSession<JudgmentQ>::getAllQ();
         singleChoiceQ = SqlSession<SingleChoiceQ>::getAllQ();
         mutiChoiceQ = SqlSession<MutiChoiceQ>::getAllQ();

         //TODO 读取题目的错误记录初始化内存
         if(std::ifstream ifs(Judgment_Json_File_Path);ifs){
             json j;
             ifs>>j;
             if(!j.empty())
                judgment_error_record = j["error_id"].get<std::unordered_map<int,int>>();
         }
         if(std::ifstream ifs(SingleChoice_Json_File_Path);ifs){
             json j;
             ifs>>j;
             if(!j.empty())
                singleChoice_error_record = j["error_id"].get<std::unordered_map<int,int>>();
         }
         if(std::ifstream ifs(MutiChoice_Json_File_Path);ifs){
             json j;
             ifs>>j;
             if(!j.empty())
                mutiChoice_error_record = j["error_id"].get<std::unordered_map<int,int>>();
         }
         //TODO 更新id到索引的mapper
         updateIndexMapper();
     });
     sub_thread->start();

    errorNode = new ErrorNoteDialog(); //TODO errorNote的内存申请并连接对应的信号
    connect(errorNode,&ErrorNoteDialog::activatedQ,this,&MainWindow::solveNoteBookActivatedQ);
    connect(errorNode,&ErrorNoteDialog::itemPressedId,this,&MainWindow::solveNoteBookitemPressedId);
    connect(this,&MainWindow::updateNoteBookList,errorNode,&ErrorNoteDialog::setListToWidget);
    QLabel *text = new QLabel(this);
    text->setText("有没有好心人赏口饭吃啊(┬┬﹏┬┬)");
    text->setStyleSheet("color:gray;font-size:9px;");
    text->setGeometry(50, 80, 180, 20);


    ui->title->setFont(QFont("楷体", 25));

    QLabel *label = new QLabel(this);
    label->setGeometry(50, 100, 117, 111);
    label->setStyleSheet("image:url(:/收款码.png)");

    QLabel *issue = new QLabel(this);
    issue->setGeometry(560, 70, 200, 20);
    issue->setText("练累了？来点计算机八股");
    issue->setStyleSheet("color:red;font-size:15px;");

    init_mappers();

    QLabel *question = new QLabel(this);
    question->setGeometry(530, 100, 250, 12);
    question->setOpenExternalLinks(true);
    long long id = rand() % links_mapper.size();
    qDebug() << QString(R"(<html>    <style>
                              a {
                                  color:#ff8ca0;
                              }
                          </style><head/><body><p><a href="%2">%1</a></p></body></html>)").arg(links_mapper[id].first,
                                                                                               links_mapper[id].second);
    question->setText(QString(R"(<html>    <style>
                          a {
                              color:#ff8ca0;
                          }
                      </style><head/><body><p><a href="%2">%1</a></p></body></html>)").arg(links_mapper[id].first,
                                                                                           links_mapper[id].second));
    question->setStyleSheet("font-size:10px;");
    question->adjustSize();

    //TODO 多线程不断换图片
    init_ImgsPath();

    imgs_tip = new QLabel(this);
    imgs_tip->setGeometry(328, 155, 90, 100);
    showImgToSwitch();
    timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &MainWindow::showImgToSwitch);
    timer->start();

    avater = new QLabel(this);
    avater->setGeometry(570, 150, 60, 100);
    showAvaterSwitch();
    timer2 = new QTimer();
    timer2->setInterval(80);
    connect(timer2, &QTimer::timeout, this, &MainWindow::showAvaterSwitch);
    timer2->start();

    QLabel *text_tip = new QLabel(this);
    text_tip->setText("点击按钮暂停选头像(●'◡'●)");
    text_tip->setGeometry(650, 205, 200, 15);
    text_tip->setStyleSheet("font-size:10px;");

    choose_avater = new QPushButton(ui->widget_top);
    choose_avater->setGeometry(690, 230, 25, 25);
    pause_style();
    connect(choose_avater, &QPushButton::clicked, this, &MainWindow::on_choose_avater_clicked);

    //TODO 背景音乐播放模块
    m_musicButton = new QPushButton(this);
    m_musicButton->setGeometry(385,470,25,25);
    setBtnStartStyle(m_musicButton);
    connect(m_musicButton,&QPushButton::clicked,this,&MainWindow::on_m_musicButton_clicked);
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_mediaPlayer->setAudioOutput(m_audioOutput);
    //TODO 连接播放长度信号到对应的设置slider状态的函数
    connect(m_mediaPlayer,&QMediaPlayer::durationChanged,this,&MainWindow::on_durationChanged);
    connect(m_mediaPlayer,&QMediaPlayer::positionChanged,this,&MainWindow::on_positionChanged);
    //TODO 连接播放信号到对应的播放槽函数
    connect(this, &MainWindow::play, m_mediaPlayer, &QMediaPlayer::play);
    connect(this, &MainWindow::pause, m_mediaPlayer, &QMediaPlayer::pause);
    connect(this, &MainWindow::stop, m_mediaPlayer, &QMediaPlayer::stop);
    //TODO 根据当前的播放状态发送对应的播放信号
    connect(m_mediaPlayer,&QMediaPlayer::playbackStateChanged,this,&MainWindow::changed_PlayState);
    connect(m_mediaPlayer,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::on_media_change);

    init_musicPath();
    m_mediaPlayer->setSource(QUrl::fromLocalFile(QString(R"(qrc:/music_list/%1)").arg(music_name[index3])));

    //TODO 下一曲和前一曲按钮
    auto next_Music_btn = new QPushButton(this);
    next_Music_btn->setGeometry(420,470,25,25);
    connect(next_Music_btn,&QPushButton::clicked,this, &MainWindow::next_musicBtn);
    next_Music_btn->setStyleSheet(R"(
QPushButton {
                                border: 1px solid #c7d4d4;
        image: url(:/下一曲.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;
                                }
 QPushButton:hover {

                                border: 1px solid #3498db;
                                }
QPushButton:pressed {
                                border: 1px solid #db7734;
                                }
)");
    auto pre_Music_btn = new QPushButton(this);
    pre_Music_btn->setGeometry(350,470,25,25);
    pre_Music_btn->setStyleSheet(R"(
QPushButton {
                                border: 1px solid #c7d4d4;
       image: url(:/上一曲.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;
                                }
 QPushButton:hover {

                                border: 1px solid #3498db;
                                }
QPushButton:pressed {
                                border: 1px solid #db7734;
                                }
)");
    connect(pre_Music_btn,&QPushButton::clicked,this, &MainWindow::pre_musicBtn);
}

MainWindow::~MainWindow() {
    //TODO 在退出的时候，保存错误的题目状态以json格式保存
    if(!judgment_error_record.empty()){
        if(std::ofstream ofs(Judgment_Json_File_Path);ofs){
            json j;
            j["error_id"] = judgment_error_record;
            ofs<<j.dump(4);
        }
    }

    if(!singleChoice_error_record.empty()){
        if(std::ofstream ofs(SingleChoice_Json_File_Path);ofs){
            json j;
            j["error_id"] = singleChoice_error_record;
            ofs<<j.dump(4);
        }
    }

    if(!mutiChoice_error_record.empty()){
        if(std::ofstream ofs(MutiChoice_Json_File_Path);ofs){
            json j;
            j["error_id"] = mutiChoice_error_record;
            ofs<<j.dump(4);
        }
    }
    delete errorNode;
    delete ui;
}

void MainWindow::init_mappers() {
    //TODO Java相关的问题
    links_mapper.push_back({"还记得Java I/O 的知识吗？", "https://www.acking-you.xyz/posts/java-io/"});
    links_mapper.push_back({"还记得Java多线程的知识吗？", "https://www.acking-you.xyz/posts/java%E5%A4%9A%E7%BA%BF%E7%A8%8B/"});
    links_mapper.push_back({"Java动态代理的原理你清楚吗？(反射+泛型的典型应用)",
                            "https://www.acking-you.xyz/posts/java%E5%8A%A8%E6%80%81%E4%BB%A3%E7%90%86%E8%AF%A6%E8%A7%A3/"});

    //TODO 计算机网络相关的问题
    links_mapper.push_back({"请你说说TCP协议三次握手的过程中用到了哪些系统调用",
                            "https://www.acking-you.xyz/posts/tcp%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B%E4%B8%ADconnectlistenaccept%E4%B8%89%E8%80%85%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB/"});
    links_mapper.push_back(
            {"请说出TCP协议和UDP协议的区别", "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/"});
    links_mapper.push_back({"请描述TCP协议三次握手和四次挥手的过程",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"请说出TCP协议中服务器和客户端通信的状态转移",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"请描述TCP协议中TIME_WAIT状态产生的原因和危害",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"请描述TCP协议中TIME_WAIT状态持续2MSL的原因",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"描述下TCP协议中复位报文段的发送时机",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"请对比TCP协议中交互数据流和成块数据流的区别",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E7%9A%84%E5%BB%BA%E7%AB%8B%E5%92%8C%E5%85%B3%E9%97%AD"});
    links_mapper.push_back({"请描述TCP协议中使用延迟确认和Nagle算法",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E6%95%B0%E6%8D%AE%E6%B5%81%E7%9A%84%E6%8E%A7%E5%88%B6%E6%8B%A5%E5%A1%9E%E6%8E%A7%E5%88%B6"});
    links_mapper.push_back({"请说出TCP协议中数据流的控制(拥塞控制)",
                            "https://www.acking-you.xyz/posts/tcp%E5%8D%8F%E8%AE%AE%E8%AF%A6%E8%A7%A3/#tcp%E6%95%B0%E6%8D%AE%E6%B5%81%E7%9A%84%E6%8E%A7%E5%88%B6%E6%8B%A5%E5%A1%9E%E6%8E%A7%E5%88%B6"});

    //TODO C++相关的问题
    links_mapper.push_back(
            {"请描述下c++和Java中泛型的区别", "https://www.bilibili.com/video/BV1YU4y1Z7WL?spm_id_from=333.999.0.0"});
    links_mapper.push_back({"请问C++中的动态多态和静态多态指的是哪些", ""});
    links_mapper.push_back({"说说C++虚函数实现多态的原理", ""});
    links_mapper.push_back({"请问线程安全是什么，以及C++中如何去实现线程安全",
                            "https://blog.csdn.net/m0_50945504/article/details/123242104?spm=1001.2014.3001.5501"});
    links_mapper.push_back({"请问C++中三个mutex的装饰器以及他们的区别和应用场景",
                            "https://blog.csdn.net/m0_50945504/article/details/123242104?spm=1001.2014.3001.5501"});
    links_mapper.push_back(
            {"为什么会发生死锁？", "https://blog.csdn.net/m0_50945504/article/details/123242104?spm=1001.2014.3001.5501"});
    links_mapper.push_back({"说说C/C++中static关键字的异同", ""});
    links_mapper.push_back({"描述下C++中的字符串应该如何优化才能得到较好的性能？", ""});


    std::shuffle(links_mapper.begin(), links_mapper.end(), std::mt19937(std::random_device()()));
}

void MainWindow::init_ImgsPath() {
    //设置要遍历的目录
    QDir dir1(":/表情包"), dir2(":/头像");
    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.png";
    //将过滤后的文件名称存入到files列表中
    imgs_path = dir1.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    avaters_path = dir2.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    std::shuffle(imgs_path.begin(), imgs_path.end(), std::mt19937(std::random_device()()));
    std::shuffle(avaters_path.begin(), avaters_path.end(), std::mt19937(std::random_device()()));
}

void MainWindow::start_style() {
    choose_avater->setStyleSheet(R"(image: url(:/开始.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;)");

}

void MainWindow::pause_style() {
    choose_avater->setStyleSheet(R"(image: url(:/暂停.png);
            background-color: rgb(255, 255, 255);
            border-radius:12px;
            padding-top:4px;
            padding-bottom:4px;)");
}



void MainWindow::showImgToSwitch() {
    const auto &img_name = imgs_path[(index1++) % imgs_path.size()];
    qDebug() << QString("image:url(:/表情包/%1)").arg(img_name) << '\n';
    imgs_tip->setStyleSheet(QString("image:url(:/表情包/%1)").arg(img_name));
}

void MainWindow::showAvaterSwitch() {
    const auto &img_name = avaters_path[(index2++) % avaters_path.size()];
    qDebug() << QString("image:url(:/头像/%1)").arg(img_name) << '\n';
    avater->setStyleSheet(QString("image:url(:/头像/%1)").arg(img_name));
}

void MainWindow::on_choose_avater_clicked() {
    if (flag_AvaterChoose == 0) {//TODO 处于暂停图标，被按下就是停止
        timer2->stop();
        start_style();
        flag_AvaterChoose = 1;
    } else if (flag_AvaterChoose == 1) {//TODO 处于开始图标，被按下就是开始
        timer2->start();
        pause_style();
        flag_AvaterChoose = 0;
    }
}



//github: https://github.com/ACking-you

//bilibili: "https://space.bilibili.com/24264499?spm_id_from=333.1007.0.0"

//leetcode: https://leetcode-cn.com/u/whu_future/

void MainWindow::on_pushButton_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/ACking-you"));
}


void MainWindow::on_pushButton_2_clicked() {
    QDesktopServices::openUrl(QUrl("https://space.bilibili.com/24264499?spm_id_from=333.1007.0.0"));
}


void MainWindow::on_pushButton_3_clicked() {
    QDesktopServices::openUrl(QUrl("https://leetcode-cn.com/u/whu_future/"));
}


void MainWindow::on_practice_ordered_clicked()
{
    initQuestion();

    int state = getChooseState(judgmentQ.size(),singleChoiceQ.size());
    if(state==0)
        return;
    if(state==1){
        if(judge&&(judge->resetQSum(judgmentQ.size(),1)==0))
            judge->show();
    }else if(state==2){
        if(single&&(single->resetQSum(singleChoiceQ.size(),1)==0))
            single->show();
    }
}


void MainWindow::on_practice_random_clicked()
{
    initQuestion();

    int state =  getChooseState(judgmentQ.size(),singleChoiceQ.size());
    if(state==0)
        return;
    //TODO 先进行一次随机的洗牌算法，然后通过judgement内部的reset设置长度为50
    randomOperation();
    if(state == 1){
        if(judge&&(judge->resetQSum(50)==0))
            judge->show();
    }else if(state==2){
        if(single&&(single->resetQSum(50)==0))
            single->show();
    }
}

void MainWindow::initQuestion() {
    if(judge==nullptr){
        if(!judgmentQ.empty())
            judge = std::shared_ptr<JudgmentQuestion>(new JudgmentQuestion(&judgmentQ));
    }
    if(single== nullptr){
        if(!singleChoiceQ.empty())
            single = std::shared_ptr<SingleQuestion>(new SingleQuestion(&singleChoiceQ));
    }
}

void MainWindow::randomOperation() {
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle (judgmentQ.begin(), judgmentQ.end(), std::default_random_engine(seed));
    std::shuffle(singleChoiceQ.begin(),singleChoiceQ.end(),std::default_random_engine(seed));

    //TODO 每次随机需要重新更新索引mapper
    updateIndexMapper();
}


void MainWindow::on_import_excle_clicked()
{
    auto import_info = getImportPath();
    if(!QFile(import_info.second).exists()){
        return;
    }
    int s = import_info.first;
    int ret;
    switch (s) {//TODO 三个状态分别对应导入判断题，单选题，多选题，导入的同时更新下当前的题库
        case 1:
            ret = ExcleImport<JudgmentQ>::importExcle(import_info.second);
            if(ret == -1)//TODO 错误码直接跳过
                break;
            else{//TODO 否则提示导入成功行数
                QMessageBox::information(nullptr,"提示","成功导入"+QString::number(ret)+"行数据");
            }
            judgmentQ = SqlSession<JudgmentQ>::getAllQ();
            break;
        case 2:
            ret = ExcleImport<SingleChoiceQ>::importExcle(import_info.second);
            if(ret==-1)//TODO 错误码直接跳过
                break;
            else{
                QMessageBox::information(nullptr,"提示","成功导入"+QString::number(ret)+"行数据");
            }
            singleChoiceQ = SqlSession<SingleChoiceQ>::getAllQ();
            break;
        //case 3:
        //    ExcleImport<JudgmentQ>::importExcle(import_info.second);
        //    break;
    }
}

void MainWindow::changed_PlayState(QMediaPlayer::PlaybackState status) {
    m_playerState = status;
}

void MainWindow::on_m_musicButton_clicked() {
    switch (m_playerState) {
        case QMediaPlayer::StoppedState:
        case QMediaPlayer::PausedState:
            emit play();
            setBtnPauseStyle(m_musicButton);
            break;
        case QMediaPlayer::PlayingState:
            emit pause();
            setBtnStartStyle(m_musicButton);
            break;
    }
}

void MainWindow::init_musicPath() {
    //设置要遍历的目录
    QDir dir1(":/music_list");
    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.mp3"<<"*.flac";
    //将过滤后的文件名称存入到files列表中
    music_name = dir1.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (music_name.begin(), music_name.end(), std::default_random_engine(seed));
}

//TODO 确保接收到播放完后的信号继续往下播放
void MainWindow::on_media_change(QMediaPlayer::MediaStatus s) {
    if(s==QMediaPlayer::EndOfMedia){
        next_musicBtn();
        qDebug()<<"test!";
    }else{
        return;
    }
}

void MainWindow::next_musicBtn() {
    m_mediaPlayer->setSource(QUrl::fromLocalFile(QString("qrc:/music_list/%1").arg(music_name[(++index3%music_name.size())])));
    emit play();
}

void MainWindow::pre_musicBtn() {
    if(index3>0)
        --index3;
    else
        index3 = music_name.size()-1;
    m_mediaPlayer->setSource(QUrl::fromLocalFile(QString("qrc:/music_list/%1").arg(music_name[(index3%music_name.size())])));
    emit play();
}


void MainWindow::on_music_slider_sliderMoved(int position)
{
    m_mediaPlayer->setPosition(position);
}

void MainWindow::on_durationChanged(qint64 v) {
    ui->music_slider->setMaximum(v);
}

void MainWindow::on_positionChanged(qint64 v) {
    if (!ui->music_slider->isSliderDown())
        ui->music_slider->setValue(v);
}


void MainWindow::on_sql_btn_clicked()
{
auto dialog = SqlInputDialog::getSqlInputDialog();
    dialog->exec();
    int cnt;
    if(dialog->getCurState()==1){
        cnt = SqlSession<>::execSql(dialog->getSql());
        if(cnt == -1){
            QMessageBox::warning(nullptr,"提示","sql语句执行失败");
        }
        else{
            QMessageBox::information(nullptr,"提示","成功执行sql语句");
        }
    }
}

void MainWindow::updateIndexMapper() {
    int i;
    int id;
    for(i=0;i<judgmentQ.size();i++){
        id = judgmentQ[i]->getId();
        index_fromJudgmentId[id] = i;
    }
    for(i=0;i<singleChoiceQ.size();i++){
        id = singleChoiceQ[i]->getId();
        index_fromSingleId[id] = i;
    }
    for(i=0;i<mutiChoiceQ.size();i++){
        id = mutiChoiceQ[i]->getId();
        index_fromMutiId[id] = i;
    }
}

void MainWindow::solveNoteBookActivatedQ(int index) {
    //TODO 0表示显示判断题，1表示显示单选题，2表示显示多选题
    if(index==0||index==1||index==2){
        auto list = getNoteBookList(index);
        cur_noteChoice = index;
        emit updateNoteBookList(list);
    }
}

void MainWindow::solveNoteBookitemPressedId(int id) {
    decltype(index_fromJudgmentId.begin()) f;
    switch (cur_noteChoice) {
        case 0:
            f = index_fromJudgmentId.find(id);
            if(f!=index_fromJudgmentId.end()){
                one_judgmentQ[0] = judgmentQ[f->second];
                auto w = JudgmentQuestion::getOneJudgementWidget(&one_judgmentQ);
                w->show();
            }
            break;
        case 1:
            f = index_fromSingleId.find(id);
            if(f!=index_fromSingleId.end()){
                one_singleChoiceQ[0] = singleChoiceQ[f->second];
                auto w = SingleQuestion::getOneSingleQuestionWidget(&one_singleChoiceQ);
                w->show();
            }
            break;
        case 2:
            break;
    }
}

void MainWindow::updateRetHelper(std::unordered_map<int,int>&record,std::unordered_map<int,int>&index_mapper,
                     QList<QString>& ret,int state){
    int index;
    for(auto &[k,v]:record){
        auto it = index_mapper.find(k);
        if(it==index_mapper.end())continue;
        index = it->second;
        switch (state) {
            case 0:
                if(index<judgmentQ.size())
                    ret.emplace_back(getQStringFromQuestion<JudgmentQ>(judgmentQ[index].get(),v));
                break;
            case 1:
                if(index<singleChoiceQ.size())
                    ret.emplace_back(getQStringFromQuestion<SingleChoiceQ>(singleChoiceQ[index].get(),v));
                break;
            case 2:
                if(index<mutiChoiceQ.size())
                    ret.emplace_back(getQStringFromQuestion<MutiChoiceQ>(mutiChoiceQ[index].get(),v));
                break;
        }
    }
}

QList<QString> *MainWindow::getNoteBookList(int state) {
    static QList<QString> ret; //static local
    ret.clear();
    switch (state) {
        case 0:
            updateRetHelper(judgment_error_record, index_fromJudgmentId, ret,state);
            break;
        case 1:
            updateRetHelper(singleChoice_error_record,index_fromSingleId,ret,state);
            break;
        case 2:
            updateRetHelper(mutiChoice_error_record,index_fromMutiId,ret,state);
            break;
    }
    return &ret;
}

void MainWindow::on_errorNote_btn_clicked() {
    if(errorNode){
        errorNode->setVisible(true);
        solveNoteBookActivatedQ(cur_noteChoice);
    }
}

