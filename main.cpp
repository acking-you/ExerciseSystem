#include "mainwindow.h"
#include "judgmentquestion.h"
#include <QApplication>
#include "SqlSession.h"
#include "SingleChoiceQ.h"
#include "JudgmentQ.h"
#include "MutiChoiceQ.h"
#include "ExcleImport.h"
#include "choosedialog.h"
#include "singlequestion.h"
#include "ImportExcleDialog.h"
#include "ExcleImport.h"
#include "sqlinputdialog.h"
#include "errornotedialog.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
