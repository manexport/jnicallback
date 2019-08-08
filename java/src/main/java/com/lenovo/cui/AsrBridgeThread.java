package com.lenovo.cui;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

public class AsrBridgeThread extends Thread {
	private Thread t;
	private String threadName;
	private String fileName;

	AsrBridgeThread(String name, String _fileName) {
		threadName = name;
		this.fileName = _fileName;
		System.out.println("Creating " + threadName + fileName);
	}

	public void run() {
		Listener listen1 = new TestListener();
		// Listener listen2=new TestListener();

		AsrBridge objAsr1 = new AsrBridge();
		objAsr1.PreLoad("/home/heyongxin/asr.log");//设置日志路径；
		long handle = objAsr1.Init("BD::Asr");//入参写死不变；
		objAsr1.SetListener(handle, listen1);

		BaseMessage message = new ConfigMessage("ASRBRIDGE_CMD_CONFIG","10555002", "jhRA15uv8Lvd4r9qbtmOODMv",
				"f0a12f8261e1121861a1cd3f4ed02f68", "15362", "1", "1",
				"/home/appadmin/asr-bridge/resources/asr_resource/bds_easr_mfe_dnn.dat",
				"/home/appadmin/asr-bridge/resources/asr_resource/bds_easr_mfe_cmvn.dat", "5", "0000");
		objAsr1.Post(handle, message, 10002);
		BaseMessage message2 = new StartMessage("ASRBRIDGE_CMD_START","YourOwnName", "linux", "LINUX TEST");
		objAsr1.Post(handle, message2, 10001);

		byte[] audio_data = new byte[320];
		InputStream input = null;
		try {
			input = new FileInputStream(fileName);

			while (input.read(audio_data) != -1) {
				BaseMessage audio_message = new AudioMessage("ASRBRIDGE_CMD_DATA_CHUNK", audio_data, 320);
				objAsr1.Post(handle, audio_message, 10003);
				LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(10));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
		}
		BaseMessage stop_message = new StopMessage("ASRBRIDGE_CMD_STOP");
		objAsr1.Post(handle, stop_message, 10004);

		objAsr1.UnInit(handle);
		objAsr1.UnLoad(handle);
	}

	public void start() {
		System.out.println("Starting " + threadName);
		if (t == null) {
			t = new Thread(this, threadName);
			t.start();
		}
	}
}
