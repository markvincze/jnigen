#include <boost/python.hpp>
#include "${include_file}"

<%doc>

using namespace boost::python;

BOOST_PYTHON_MODULE(${module_name})
{
% for c in classes:
    class_<${c.name}>("${c.name}")
    % for f in c.functions:
        % if not "hidden" in f.annotations:
        .def("${f.name}", &${c.name}::${f.name})
        % endif
    % endfor
    ;
% endfor
}

void init_bindings()
{
    Py_Initialize();
    init${module_name}();
}

</%doc>

#include "JniClassBase.h"

#ifndef JNI_ADAPTER
#define JNI_ADAPTER

% if namespace is not UNDEFINED and namespace != '':
namespace ${namespace}
{
%endif

class JniAdapter : JniClassBase
{
% for c in classes:

jobject ToJava${c.name}(const ${c.name}& obj)
{
    JNIEnv* env = GetEnv();
    jobject result = env->CreateObject(${c.name}ClassId);

    % for f in c.fields:
        % if f.typename == 'int':
            env->SetIntField(result, obj.${f.name});
        % elif f.typename == 'double':
            env->SetDoubleField(result, obj.${f.name});
        % endif
    % endfor
}

jobject ToNative${c.name}(jobject obj)
{
    JNIEnv* env = GetEnv();
    ${c.name} result;

    % for f in c.fields:
        % if f.typename == 'int':
            result.${f.name} = env->GetIntField(obj, ${c.name}_${f.name}FieldId);
        % elif f.typename == 'double':
            result.${f.name} = env->GetDoubleField(obj, ${c.name}_${f.name}FieldId);
        % endif
    % endfor

    return result;
}

% endfor

}

% if namespace is not UNDEFINED and namespace != '':
}
%endif

#endif
