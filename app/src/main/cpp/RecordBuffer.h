//
// Created by liuml on 2018/12/18.
//

#ifndef AUDIORECORD_RECORDBUFFER_H
#define AUDIORECORD_RECORDBUFFER_H

class RecordBuffer {

public:
    //二级指针是个数组
    short **buffer;
    int index = -1;

public:
    RecordBuffer(int buffersize);

    ~RecordBuffer();

    short *getRecordBuffer();

    short *getNowBuffer();


};

#endif //AUDIORECORD_RECORDBUFFER_H
