//
// Created by liuml on 2018/12/18.
//

#include "RecordBuffer.h"

#include <cwchar>

RecordBuffer::RecordBuffer(int buffersize) {
    //通过一个数组 循环起来
    buffer = new short *[2];
    for(int i = 0; i < 2; i++)
    {
        buffer[i] = new short[buffersize];
    }
}

short *RecordBuffer::getRecordBuffer() {
    index++;
    if(index > 1)
    {
        index = 1;
    }
    return buffer[index];
}

RecordBuffer::~RecordBuffer() {
    for(int i = 0; i < 2; i++)
    {
        delete  buffer[i];
    }
    delete buffer;
}

short *RecordBuffer::getNowBuffer() {
    return buffer[index];
}