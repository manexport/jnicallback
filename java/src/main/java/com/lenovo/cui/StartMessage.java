package com.lenovo.cui;

public class StartMessage extends BaseMessage {
	String message_name;
	String asr_param_key_app;
	String asr_param_key_platform;
	String asr_param_key_sdk_version;
	
	public StartMessage(String _message_name,String _asr_param_key_app,String _asr_param_key_platform,String _asr_param_key_sdk_version) 
	{
		message_name=_message_name;
		asr_param_key_app=_asr_param_key_app;
		asr_param_key_platform=_asr_param_key_platform;
		asr_param_key_sdk_version=_asr_param_key_sdk_version;
	}
}
