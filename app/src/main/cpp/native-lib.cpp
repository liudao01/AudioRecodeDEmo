#include <jni.h>
#include <string>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "RecordBuffer.h"
#include "AndroidLog.h"
SLObjectItf slObjectEngine = NULL;
SLEngineItf engineItf = NULL;

SLObjectItf recordObj = NULL;
SLRecordItf recordItf = NULL;

SLAndroidSimpleBufferQueueItf recorderBufferQueue = NULL;
RecordBuffer *recordBuffer;
int buffersize = 4096;

FILE *pcmFile = NULL;

bool finish = false;

void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
    LOGE("开始写入")
    fwrite(recordBuffer->getNowBuffer(), 1, buffersize, pcmFile);
    if (finish) {
        LOGE("录制完成")
        (*recordItf)->SetRecordState(recordItf, SL_RECORDSTATE_STOPPED);//声明当前录制状态
    } else {
        LOGE("正在录制")
        (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recordBuffer->getRecordBuffer(),
                                        buffersize);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_xyyy_www_audiorecord_MainActivity_startRecord(JNIEnv *env, jobject instance,
                                                       jstring path_) {
    LOGE("进入了开始方法")
    if (finish) {
        return;
    }
    const char *path = env->GetStringUTFChars(path_, 0);

    finish = false;
    pcmFile = fopen(path, "w");
    recordBuffer = new RecordBuffer(buffersize);

    slCreateEngine(&slObjectEngine, 0, NULL, 0, NULL, NULL);
    (*slObjectEngine)->Realize(slObjectEngine, SL_BOOLEAN_TRUE);
    (*slObjectEngine)->GetInterface(slObjectEngine, SL_IID_ENGINE, &engineItf);

    LOGE("初始化")
    //设备麦克风等参数
    SLDataLocator_IODevice loc_dev = {SL_DATALOCATOR_IODEVICE,
                                      SL_IODEVICE_AUDIOINPUT,
                                      SL_DEFAULTDEVICEID_AUDIOINPUT,
                                      NULL};
    //把参数设置到数据源中
    SLDataSource audioSrc = {&loc_dev, NULL};

    SLDataLocator_AndroidSimpleBufferQueue loc_bq = {
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,
            2
    };

    /**
     * SLuint32 		formatType;  格式
	SLuint32 		numChannels; 声道
	SLuint32 		samplesPerSec; 采样率
	SLuint32 		bitsPerSample; 位数
	SLuint32 		containerSize; 和上面一样就行
	SLuint32 		channelMask;  通道布局 立体声
	SLuint32		endianness; 对齐方式 小端对齐 (内存的排序方式)
     */
    SLDataFormat_PCM format_pcm = {
            SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN
    };


    SLDataSink audioSnk = {&loc_bq, &format_pcm};


    //属性 可以多个, 比如声道控制,音量控制,均衡器 等 现在只用到了队列
    const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};

    (*engineItf)->CreateAudioRecorder(engineItf, &recordObj, &audioSrc, &audioSnk, 1, id, req);

    (*recordObj)->Realize(recordObj, SL_BOOLEAN_FALSE);
    (*recordObj)->GetInterface(recordObj, SL_IID_ENGINE, &recordItf);

    (*recordObj)->GetInterface(recordObj, SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &recorderBufferQueue);


    (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recordBuffer->getRecordBuffer(),
                                    buffersize);

    LOGE("注册回调完成")
    //注册回调
    (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, bqRecorderCallback, NULL);

    LOGE("修改状态")
    (*recordItf)->SetRecordState(recordItf, SL_RECORDSTATE_RECORDING);//声明当前录制状态

    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_xyyy_www_audiorecord_MainActivity_stopRecord(JNIEnv *env, jobject instance) {

    // TODO

}