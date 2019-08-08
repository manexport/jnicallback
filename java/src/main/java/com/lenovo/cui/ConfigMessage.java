package com.lenovo.cui;

public class ConfigMessage extends BaseMessage {
	String message_name;
	String app_id;
	String chunk_key;
	String secret_key;
	String product_id;
	String enable_long_speech;
	String key_chunk_enable;
	String mfe_dnn_dat_file;
	String mfe_cmvn_dat_file;
	String ompression_type;
	String log_level;
	
	public ConfigMessage(String _message_name,String _app_id,String _chunk_key,String _secret_key,
			String _product_id,String _enable_long_speech,String _key_chunk_enable,
			String _mfe_dnn_dat_file,String _mfe_cmvn_dat_file,String _ompression_type,String _log_level) 
	{
		message_name=_message_name;
		app_id=_app_id;
		chunk_key=_chunk_key;
		secret_key=_secret_key;
		product_id=_product_id;
		enable_long_speech=_enable_long_speech;
		key_chunk_enable=_key_chunk_enable;
		mfe_dnn_dat_file=_mfe_dnn_dat_file;
		mfe_cmvn_dat_file=_mfe_cmvn_dat_file;
		ompression_type=_ompression_type;
		log_level=_log_level;
	}
}
