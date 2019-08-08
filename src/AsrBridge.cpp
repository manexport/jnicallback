#include "AsrMessage.h"
#include "AsrBridge.h"
#include "BDSpeechSDK.hpp"
#include "bds_ASRDefines.hpp"
#include "bds_asr_key_definitions.hpp"
#include <pthread.h>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

struct CallBack
{
	unsigned long callbackObj;
	unsigned long onChangedMD;
};


std::map<unsigned long,CallBack> mapCallBack;

static JavaVM *gs_jvm = NULL;
static jobject gs_object = NULL;

int iCounter=0;
pthread_mutex_t lockmap;

void asr_output_callback(bds::BDSSDKMessage &message, void *user_arg) 
{
//	pthread_mutex_lock(&lock);

	//int thread_seq = *(int *)user_arg;;
//	printf("asr_output_callback input arg:%ld\n",user_arg);
	if (message.name != bds::asr_callback_name) 
	{
		return;
	}

	int status = 0;

	if (!message.get_parameter(bds::CALLBACK_ASR_STATUS, status)) 
	{
		return;
	}
	
	JNIEnv *env;
	gs_jvm->AttachCurrentThread((void**)&env, NULL);

	switch (status) 
	{
		case bds::EVoiceRecognitionClientWorkStatusStartWorkIng:
		{
			printf("------------------1----------------\n");
			//env->CallVoidMethod(_callback.callbackObj, _callback.onChangedMD, 10002,0,"sss",0);
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusStart:
		{ 
		printf("----------------2------------------\n");
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusEnd: 
		{ 
		printf("----------------3------------------\n");
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusFlushData: 
		{ 
			printf("------------------%ld--4--------------\n",user_arg);
			std::string json_result;
           message.get_parameter(bds::CALLBACK_ASR_RESULT, json_result);
			jstring json=env->NewStringUTF(json_result.c_str());
			pthread_mutex_lock(&lockmap);
			printf("the mapcallback [%ld].callbackobj=%ld,onChangeMD:%ld\n",user_arg,mapCallBack[(unsigned long)user_arg].callbackObj,mapCallBack[(unsigned long)user_arg].onChangedMD);
			env->CallBooleanMethod((jobject)mapCallBack[(unsigned long)user_arg].callbackObj,(jmethodID)mapCallBack[(unsigned long)user_arg].onChangedMD, (jlong)user_arg,iCounter++,json,0);
			pthread_mutex_unlock(&lockmap);
			env->DeleteLocalRef(json);
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusFinish: 
		{
		         printf("------------------%ld-----5-----------\n",user_arg);
                        std::string json_result2;
           message.get_parameter(bds::CALLBACK_ASR_RESULT, json_result2);
                        jstring json2=env->NewStringUTF(json_result2.c_str());
                        pthread_mutex_lock(&lockmap);
                        printf("the mapcallback [%ld].callbackobj=%ld,onChangeMD:%ld\n",user_arg,mapCallBack[(unsigned long)user_arg].callbackObj,mapCallBack[(unsigned long)user_arg].onChangedMD);
                        env->CallBooleanMethod((jobject)mapCallBack[(unsigned long)user_arg].callbackObj,(jmethodID)mapCallBack[(unsigned long)user_arg].onChangedMD, (jlong)user_arg,iCounter++,json2,0);
                        pthread_mutex_unlock(&lockmap);
                        env->DeleteLocalRef(json2);
                        break;   
		}

		case bds::EVoiceRecognitionClientWorkStatusChunkNlu: 
		{ 
		printf("----------------6------------------\n");
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusLongSpeechEnd: 
		{
		printf("------------------7----------------\n");
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusError:
		{
			printf("---------------8-------------------\n");
			break;
		}

		case bds::EVoiceRecognitionClientWorkStatusCancel: 
		{
			printf("----------------9------------------\n");
			
			break;
		}
		case bds::EVoiceRecognitionClientWorkStatusNewRecordData:
		case bds::EVoiceRecognitionClientWorkStatusMeterLevel:
		{
			//printf("------------------0----------------\n");
			break;
		}
		default: 
		{
			break;
		}
	}
	if (env->ExceptionOccurred() != NULL)
	{
		gs_jvm->DetachCurrentThread();
		return ;
	}
	gs_jvm->DetachCurrentThread();
//	pthread_mutex_unlock(&lock);
}

JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_PreLoad(JNIEnv * env, jobject thiz, jstring logPath)
{
	bds::BDSpeechSDK::open_log_file("asr.log", 25);
	env->GetJavaVM(&gs_jvm); 
	gs_object = env->NewGlobalRef(thiz);
	printf("exit Preload\n");
	return 0;
}


JNIEXPORT jlong JNICALL Java_com_lenovo_cui_AsrBridge_Init(JNIEnv * env, jobject thiz, jstring enginetype)
{
	std::string err_msg;
	bds::BDSpeechSDK *sdk = bds::BDSpeechSDK::get_instance(bds::SDK_TYPE_ASR, err_msg);
	if (!sdk) {
		return NULL;
	}
	pthread_mutex_init(&lockmap, NULL);
	sdk->set_event_listener(&asr_output_callback, (void *)sdk);
	printf("Exit Init the instance id:%ld\n",sdk);
	return(jlong) sdk;
}


JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_UnInit(JNIEnv * env, jobject thiz, jlong lhandle)
{
	printf("Java_com_lenovo_cui_AsrBridge_UnInit the input handle:%ld\n", lhandle);
	bds::BDSpeechSDK::release_instance((bds::BDSpeechSDK *)lhandle);
	printf("Exit UnInit the instance :%ld\n",lhandle);
	return 0;
}

JNIEXPORT jlong JNICALL Java_com_lenovo_cui_AsrBridge_UnLoad(JNIEnv * env, jobject thiz, jlong lhandle)
{
	bds::BDSpeechSDK::close_log_file();
    bds::BDSpeechSDK::do_cleanup();
	gs_jvm->DestroyJavaVM();
	printf("Exit Unload\n");
	return 0;
}


JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_SetListener(JNIEnv * env, jobject thiz, jlong lhandle, jobject listener)
{
	if ((listener == nullptr) || (lhandle == 0))
	{
		printf("--------------------------Set Listennr :%ld------------\n",lhandle);
		return -1;
	}
	pthread_mutex_lock(&lockmap);
	jclass objClass = env->GetObjectClass(listener);
	CallBack _callback; 
	_callback.callbackObj = (unsigned long)env->NewGlobalRef(listener);
	_callback.onChangedMD = (unsigned long)env->GetMethodID(objClass, "onChangedMessage", "(JJLjava/lang/String;[B)Z");
	mapCallBack.insert(std::make_pair((unsigned long)lhandle, _callback));
//	mapCallBack.at((void*)lhandle)=_callback;
	pthread_mutex_unlock(&lockmap);
	printf("Exit SetLister\n");
	return 0;
}

JNIEXPORT jint JNICALL Java_com_lenovo_cui_AsrBridge_Post(JNIEnv * env, jobject thiz, jlong lhandle, jobject message, jint msgtype)
{
	std::string err_msg;
	bds::BDSSDKMessage bdmessage;
	if (msgtype == ASRBRIDGE_CMD_START)
	{
		printf("I hv enter ASRBRIDGE_CMD_START branch\n");
		jclass jclass = env->FindClass("Lcom/lenovo/cui/StartMessage;");
		jfieldID asr_param_key_app_fld = env->GetFieldID(jclass, "asr_param_key_app", "Ljava/lang/String;");
		jfieldID asr_param_key_platform_fld = env->GetFieldID(jclass, "asr_param_key_platform", "Ljava/lang/String;");
		jfieldID asr_param_key_sdk_version_fld = env->GetFieldID(jclass, "asr_param_key_sdk_version", "Ljava/lang/String;");


		jstring asr_param_key_app = (jstring)env->GetObjectField(message, asr_param_key_app_fld);
		jstring asr_param_key_platform =(jstring)env->GetObjectField(message, asr_param_key_platform_fld);
		jstring asr_param_key_sdk_version =(jstring)env->GetObjectField(message, asr_param_key_sdk_version_fld);


		const char*  asr_param_key_app_ =env->GetStringUTFChars(asr_param_key_app, NULL);
		const char*  asr_param_key_platform_ = env->GetStringUTFChars(asr_param_key_platform, NULL);
		const char*  asr_param_key_sdk_version_ = env->GetStringUTFChars(asr_param_key_sdk_version, NULL);

		printf("asr_param_key_app:%s,asr_param_key_platform:%s,asr_param_key_sdk_version:%s\n", asr_param_key_app_, asr_param_key_platform_, asr_param_key_sdk_version_);

		bdmessage.name = bds::ASR_CMD_START;
		
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_APP, asr_param_key_app_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_PLATFORM, asr_param_key_platform_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_SDK_VERSION, asr_param_key_sdk_version_);

		if (!((bds::BDSpeechSDK *)lhandle)->post(bdmessage, err_msg)) {
			printf("------------------post start msg failed---------------------------\n");
			bds::BDSpeechSDK::release_instance((bds::BDSpeechSDK*)lhandle);
			return NULL;
		}

	}
	else if (msgtype == ASRBRIDGE_CMD_CONFIG)
	{
		printf("I hv enter ASRBRIDGE_CMD_CONFIG branch\n");
		jclass jclass = env->FindClass("Lcom/lenovo/cui/ConfigMessage;");
		jfieldID app_id_Field = env->GetFieldID(jclass, "app_id", "Ljava/lang/String;");
		jfieldID chunk_key_Field = env->GetFieldID(jclass, "chunk_key", "Ljava/lang/String;");
		jfieldID secret_key_Field = env->GetFieldID(jclass, "secret_key", "Ljava/lang/String;");
		jfieldID product_id_Field = env->GetFieldID(jclass, "product_id", "Ljava/lang/String;");
		jfieldID enable_long_speech_Field = env->GetFieldID(jclass, "enable_long_speech", "Ljava/lang/String;");
		jfieldID key_chunk_enable_Field = env->GetFieldID(jclass, "key_chunk_enable", "Ljava/lang/String;");
		jfieldID mfe_dnn_dat_file_Field = env->GetFieldID(jclass, "mfe_dnn_dat_file", "Ljava/lang/String;");
		jfieldID mfe_cmvn_dat_file_Field = env->GetFieldID(jclass, "mfe_cmvn_dat_file", "Ljava/lang/String;");
		jfieldID ompression_type_Field = env->GetFieldID(jclass, "ompression_type", "Ljava/lang/String;");
		jfieldID log_level_Field = env->GetFieldID(jclass, "log_level", "Ljava/lang/String;");

		jstring app_id = (jstring)env->GetObjectField(message, app_id_Field);
		jstring chunk_key =(jstring)env->GetObjectField(message, chunk_key_Field);
		jstring secret_key =(jstring)env->GetObjectField(message, secret_key_Field);
		jstring product_id =(jstring)env->GetObjectField(message, product_id_Field);
		jstring enable_long_speech =(jstring)env->GetObjectField(message, enable_long_speech_Field);
		jstring key_chunk_enable =(jstring)env->GetObjectField(message, key_chunk_enable_Field);
		jstring mfe_dnn_dat_file =(jstring)env->GetObjectField(message, mfe_dnn_dat_file_Field);
		jstring mfe_cmvn_dat_file =(jstring)env->GetObjectField(message, mfe_cmvn_dat_file_Field);
		jstring ompression_type =(jstring)env->GetObjectField(message, ompression_type_Field);
		jstring log_level =(jstring)env->GetObjectField(message, log_level_Field);

		const char*  app_id_ =env->GetStringUTFChars(app_id, NULL);
		const char*  chunk_key_ = env->GetStringUTFChars(chunk_key, NULL);
		const char*  secret_key_ = env->GetStringUTFChars(secret_key, NULL);
		const char*  product_id_ = env->GetStringUTFChars(product_id, NULL);
		const char*  enable_long_speech_ = env->GetStringUTFChars(enable_long_speech, NULL);
		const char*  key_chunk_enable_ = env->GetStringUTFChars(key_chunk_enable, NULL);
		const char*  mfe_dnn_dat_file_ = env->GetStringUTFChars(mfe_dnn_dat_file, NULL);
		const char*  mfe_cmvn_dat_file_ = env->GetStringUTFChars(mfe_cmvn_dat_file, NULL);
		const char*  ompression_type_ = env->GetStringUTFChars(ompression_type, NULL);
		const char*  log_level_ = env->GetStringUTFChars(log_level, NULL);
		
		printf("appid:%s,chunk_key:%s,secret_key:%s,product_id:%s,enable_long_speech:%s,key_chunk_enable:%s,mfe_dnn_dat_file:%s,mfe_cmvn_dat_file:%s,ompression_type:%s,log_level:%s\n",
			app_id_, chunk_key_, secret_key_, product_id_, enable_long_speech_, key_chunk_enable_,mfe_dnn_dat_file_,mfe_cmvn_dat_file_,ompression_type_,log_level_);

		bdmessage.name = bds::ASR_CMD_CONFIG;
		
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_APP_ID, app_id_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_CHUNK_KEY, chunk_key_);

		bdmessage.set_parameter(bds::ASR_PARAM_KEY_PRODUCT_ID, product_id_);
		bdmessage.set_parameter(bds::COMMON_PARAM_KEY_DEBUG_LOG_LEVEL, bds::EVRDebugLogLevelOff);

		bdmessage.set_parameter(bds::ASR_PARAM_KEY_ENABLE_LONG_SPEECH, enable_long_speech_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_CHUNK_ENABLE, 1);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_MFE_DNN_DAT_FILE, mfe_dnn_dat_file_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_MFE_CMVN_DAT_FILE, mfe_cmvn_dat_file_);
		bdmessage.set_parameter(bds::ASR_PARAM_KEY_COMPRESSION_TYPE, bds::EVR_AUDIO_COMPRESSION_PCM);

		if (!((bds::BDSpeechSDK *)lhandle)->post(bdmessage, err_msg)) {
			printf("------------------post data msg failed---------------------------\n");
			bds::BDSpeechSDK::release_instance((bds::BDSpeechSDK*)lhandle);
			return NULL;
		}

	}
	else if (msgtype == ASRBRIDGE_CMD_DATA_CHUNK)
	{
	//	printf("I hv enter ASRBRIDGE_CMD_DATA_CHUNK branch\n");
		jclass jclass = env->FindClass("Lcom/lenovo/cui/AudioMessage;");

		jfieldID data_len_fld = env->GetFieldID(jclass, "data_len", "I");
		jfieldID bytedata_fld = env->GetFieldID(jclass, "bytedata", "[B");


		jint data_len = (jint)env->GetIntField(message, data_len_fld);
		jbyteArray bytedata =(jbyteArray)env->GetObjectField(message, bytedata_fld);


		jbyte* dataBuf=NULL;
		dataBuf = env->GetByteArrayElements(bytedata, 0); 
		if(!dataBuf)
		{
			printf ("get audio data failed!\n");
		}

	//	printf("data_buffer:%ld,data_len:%d,\n", dataBuf, data_len);

		bdmessage.name = bds::ASR_CMD_PUSH_AUDIO;
		bdmessage.set_parameter(bds::DATA_CHUNK, (char*)dataBuf, (int) data_len);

		if (!((bds::BDSpeechSDK *)lhandle)->post(bdmessage, err_msg)) 
		{
			printf("------------------post ASRBRIDGE_CMD_DATA_CHUNK msg failed---------------------------\n");
			bds::BDSpeechSDK::release_instance((bds::BDSpeechSDK*)lhandle);
			env->ReleaseByteArrayElements(bytedata, dataBuf, 0);
			return NULL;
		}
		env->ReleaseByteArrayElements(bytedata, dataBuf, 0);

	}
	else if (msgtype == ASRBRIDGE_CMD_STOP)
	{
		printf("I hv enter ASRBRIDGE_CMD_STOP branch\n");
		bdmessage.name = bds::ASR_CMD_STOP;
		if (!((bds::BDSpeechSDK *)lhandle)->post(bdmessage, err_msg)) 
		{
			printf("------------------post ASRBRIDGE_CMD_STOP msg failed---------------------------\n");
			bds::BDSpeechSDK::release_instance((bds::BDSpeechSDK*)lhandle);
			return NULL;
		}

    }
	return 0;
}




