#include <boost/python.hpp>
#include "dataclass.h"



#include "JniClassBase.h"

#ifndef JNI_ADAPTER
#define JNI_ADAPTER

namespace JniGenTest
{

class JniAdapter : JniClassBase
{

jobject ToJavaGameEngine(const GameEngine& obj)
{
    JNIEnv* env = GetEnv();
    jobject result = env->CreateObject(GameEngineClassId);

            env->SetIntField(result, obj.IntVar);
            env->SetIntField(result, obj.IntVar2);
            env->SetDoubleField(result, obj.DoubleVar);
            env->SetIntField(result, obj.StringVar);
}

jobject ToNativeGameEngine(jobject obj)
{
    JNIEnv* env = GetEnv();
    GameEngine result;

            result.IntVar = env->GetIntField(obj, GameEngine_IntVarFieldId);
            result.IntVar2 = env->GetIntField(obj, GameEngine_IntVar2FieldId);
            result.DoubleVar = env->GetDoubleField(obj, GameEngine_DoubleVarFieldId);
            result.StringVar = env->GetIntField(obj, GameEngine_StringVarFieldId);

    return result;
}


}

}

#endif
