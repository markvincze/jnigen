#include <boost/python.hpp>
#include "dataclass.h"



#include "JniClassBase.h"

#ifndef JNI_ADAPTER
#define JNI_ADAPTER

namespace JniGenTest
{

class JniAdapter : JniClassBase
{

jobject ToJavaMyClass(const MyClass& obj)
{
    JNIEnv* env = GetEnv();
    jobject result = env->CreateObject(MyClassClassId);

            env->SetIntField(result, obj.IntVar);
            env->SetIntField(result, obj.IntVar2);
            env->SetDoubleField(result, obj.DoubleVar);
            env->SetIntField(result, obj.StringVar);
}

jobject ToNativeMyClass(jobject obj)
{
    JNIEnv* env = GetEnv();
    MyClass result;

            result.IntVar = env->GetIntField(obj, MyClass_IntVarFieldId);
            result.IntVar2 = env->GetIntField(obj, MyClass_IntVar2FieldId);
            result.DoubleVar = env->GetDoubleField(obj, MyClass_DoubleVarFieldId);
            result.StringVar = env->GetIntField(obj, MyClass_StringVarFieldId);

    return result;
}


}

}

#endif
