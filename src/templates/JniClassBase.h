#include <jni.h>
#include "JniHelper.h"
#include "Settings.h"
#include "StringHelper.h"
#include "ITextMeasurer.h"
#include "WordToDisplay.h"
#include "TextDefinitionMode.h"
#include "ITextFormatStore.h"


#ifndef _Included_hu_lexa_reader_engine2_BaseJNI
#define _Included_hu_lexa_reader_engine2_BaseJNI

using namespace tw;

namespace AndroidNativeEngine
{

	class BaseJNI
	{
	protected:
		BaseJNI(JNIEnv * env )
		{
			int ret = env->GetJavaVM(&jvm);
			if( ret != JNI_OK )
			{
				LOGE("Could not get JavaVM: %d", ret);
				throw;
			}
		}

		JNIEnv * GetEnv()
		{
		    JNIEnv * env;
		    // double check it's all ok
		    int ret = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
		    if (ret == JNI_OK)
		    	return env;

		    if (ret == JNI_EDETACHED)
		    {
		    	LOGE("GetEnv WARNING: This is not supposed to happen, every worker thread should attach itself.");
		    	LOGI("GetEnv: thread is not attached, trying to attach");
		        ret = jvm->AttachCurrentThread( &env, nullptr);
		        if( ret == JNI_OK )
		        {
			    	LOGI("GetEnv: attach successful");
		        	return env;
		        }

		        LOGE("Cannot attach JNI to current thread: %d", ret);
		        return nullptr;
		    }

		    LOGE("could not get JNI ENV: %d", ret);
		    return nullptr;
		}

	protected:
		JavaVM *jvm;

	};
}
#endif