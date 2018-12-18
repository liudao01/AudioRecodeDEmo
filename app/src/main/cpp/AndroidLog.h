//
// Created by liuml on 2018/12/18.
//
//#pragma once  表示只编译一次
#pragma once
#ifndef AUDIORECORD_ANDROIDLOG_H
#define AUDIORECORD_ANDROIDLOG_H

#include <android/log.h>
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"ywl5320",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"ywl5320",FORMAT,##__VA_ARGS__);

#define LOG_DEBUG false
#endif //AUDIORECORD_ANDROIDLOG_H
