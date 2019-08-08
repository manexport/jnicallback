package com.lenovo.cui;

public class AudioMessage extends BaseMessage {
	String message_name;
	byte[] bytedata = null;
	int data_len=0;

	public AudioMessage(String _message_name, byte[] data,int _data_len) {
		 this.message_name=_message_name;
         this.bytedata = data;
         this.data_len=_data_len;
	}
}

