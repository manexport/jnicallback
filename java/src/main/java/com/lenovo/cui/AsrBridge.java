/**
 * 
 */
package com.lenovo.cui;

public class AsrBridge {

	
	public AsrBridge() {
	}
	public native int PreLoad(String logPath);
	public native long Init(String enginetype);
	public native int UnInit(long lhandle);
	public native int Post(long lhandle,BaseMessage message,int msgtype);
	public native long UnLoad(long lhandle);
	public native int SetListener(long lhandle,Listener listener);
	static {
		System.loadLibrary("AsrBridge");
	}
	
}

