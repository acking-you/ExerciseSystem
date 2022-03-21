//
// Created by Alone on 2022-3-11.
//

#ifndef EXCLE_TEST_RECORD_SOURCE_H
#define EXCLE_TEST_RECORD_SOURCE_H
#include <unordered_map>
#define Judgment_Json_File_Path "./judgment.json"
#define SingleChoice_Json_File_Path "./single_choice.json"
#define MutiChoice_Json_File_Path "./muti_choice.json"
//TODO 用于供给全局项目，记录对应的错误
extern std::unordered_map<int,int> judgment_error_record;
extern std::unordered_map<int,int> singleChoice_error_record;
extern std::unordered_map<int,int> mutiChoice_error_record;


#endif //EXCLE_TEST_RECORD_SOURCE_H
