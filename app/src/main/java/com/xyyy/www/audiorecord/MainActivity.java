package com.xyyy.www.audiorecord;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }


    private AudioRecordUtil audioRecordUtil;


    public native void startRecord(String path);

    public native void stopRecord();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
    }

    public void audiorecord(View view) {
        LogUtil.d("audiorecord 录制");
        if (audioRecordUtil == null) {
            audioRecordUtil = new AudioRecordUtil();
            audioRecordUtil.setOnRecordListener(new AudioRecordUtil.OnRecordListener() {
                @Override
                public void recordByte(byte[] audioData, int readSize) {
                    LogUtil.d("readSize = " + readSize);
                }
            });
            audioRecordUtil.startRecord();
        } else {
            audioRecordUtil.stopRecord();
            audioRecordUtil = null;
        }
    }

    public void stop(View view) {
        audioRecordUtil.stopRecord();

    }

    public void OpenSLRecord(View view) {
        LogUtil.d("opensl es 录制");
        startRecord(Environment.getExternalStorageDirectory().getAbsolutePath() + "/opensl_record.pcm");
    }

    public void OpenSLStop(View view) {
        stopRecord();
    }
}
