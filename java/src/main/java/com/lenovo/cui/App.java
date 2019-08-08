package com.lenovo.cui;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

/**
 * Hello world!
 *
 */
public class App {

	public static void main(String[] args) throws IOException, InterruptedException {
		//System.out.println("Hello World!");
		//System.out.println(System.getProperty("java.library.path"));

//		Listener listen1 = new TestListener();
//		// Listener listen2=new TestListener();
//
//		AsrBridge objAsr1 = new AsrBridge();
//		objAsr1.PreLoad("sss");
//		long handle = objAsr1.Init("ssss");
//		objAsr1.SetListener(handle, listen1);
//
//		BaseMessage message = new ConfigMessage("10555002", "jhRA15uv8Lvd4r9qbtmOODMv",
//				"f0a12f8261e1121861a1cd3f4ed02f68", "15362", "1", "1",
//				"/home/appadmin/asr-bridge/resources/asr_resource/bds_easr_mfe_dnn.dat",
//				"/home/appadmin/asr-bridge/resources/asr_resource/bds_easr_mfe_cmvn.dat", "5", "0000");
//		objAsr1.Post(handle, message, 10002);
//		BaseMessage message2 = new StartMessage("YourOwnName", "linux", "LINUX TEST");
//		objAsr1.Post(handle, message2, 10001);
//
//		byte[] audio_data = new byte[3200];
//		InputStream input = null;
//		try {
//			input = new FileInputStream("/home/appadmin/asr-bridge/16k-1.pcm");
//
//			while (input.read(audio_data) !=-1) {
//				BaseMessage audio_message = new AudioMessage("ASRBRIDGE_CMD_DATA_CHUNK", audio_data, 3200);
//				objAsr1.Post(handle, audio_message, 10003);
//				LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(10));
//			}
//		} catch (Exception e) {
//			e.printStackTrace();
//		} finally {
//			if (input != null) {
//				input.close();
//			}
//		}
//		BaseMessage stop_message = new StopMessage("ASRBRIDGE_CMD_STOP");
//		objAsr1.Post(handle, stop_message, 10004);
//
//		objAsr1.UnInit(handle);
//		objAsr1.UnLoad(handle);
//		
		
		AsrBridgeThread T1 = new AsrBridgeThread( "Thread-1","/home/appadmin/AsrBridge/deploy/16k-1.pcm");
		T1.start(); 
		AsrBridgeThread T2 = new AsrBridgeThread( "Thread-2","/home/appadmin/AsrBridge/deploy/16k-2.pcm");
		T2.start();	
		AsrBridgeThread T3 = new AsrBridgeThread( "Thread-3","/home/appadmin/AsrBridge/deploy/16k-3.pcm");
		T3.start();	
		AsrBridgeThread T4 = new AsrBridgeThread( "Thread-3","/home/appadmin/AsrBridge/deploy/16k-4.pcm");
		T4.start();	
		AsrBridgeThread T5 = new AsrBridgeThread( "Thread-3","/home/appadmin/AsrBridge/deploy/16k-5.pcm");
		T5.start();	
		Thread.sleep(6000000);
		
	}
}
