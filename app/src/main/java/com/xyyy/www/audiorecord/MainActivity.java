package com.xyyy.www.audiorecord;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }


    private AudioRecordUtil audioRecordUtil;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
    }

    public void audiorecord(View view) {
        if (audioRecordUtil == null) {


            audioRecordUtil = new AudioRecordUtil();
            audioRecordUtil.setOnRecordListener(new AudioRecordUtil.OnRecordListener() {
                @Override
                public void recordByte(byte[] audioData, int readSize) {
                    LogUtil.d("readSize = " + readSize);
                }
            });
            audioRecordUtil.startRecord();
        }else{
            audioRecordUtil.stopRecord();
            audioRecordUtil = null;
        }
    }

    public void stop(View view) {
        audioRecordUtil.stopRecord();

    }
}
