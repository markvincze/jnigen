#!/usr/bin/python
# vim: set fileencoding=utf-8

import sys
import os
import clang.cindex
import itertools

from ctypes.util import find_library

from mako.template import Template

def get_annotations(node):
    return [c.displayname for c in node.get_children()
            if c.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]

class Function(object):
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.annotations = get_annotations(cursor)
        self.access = cursor.access_specifier

class Field(object):
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.annotations = get_annotations(cursor)
        self.access = cursor.access_specifier
        self.typename = cursor.type.get_canonical().spelling

class Class(object):
    def __init__(self, cursor):
        self.name = cursor.spelling
        self.functions = []
        self.fields = []
        self.annotations = get_annotations(cursor)

        for c in cursor.get_children():
            if (c.kind == clang.cindex.CursorKind.CXX_METHOD and
                c.access_specifier == clang.cindex.AccessSpecifier.PUBLIC):
                f = Function(c)
                self.functions.append(f)

        for c in cursor.get_children():
            if (c.kind == clang.cindex.CursorKind.FIELD_DECL and
                c.access_specifier == clang.cindex.AccessSpecifier.PUBLIC):
                f = Field(c)
                self.fields.append(f)

def build_classes(cursor):
    result = []
    for c in cursor.get_children():
        if (c.kind == clang.cindex.CursorKind.CLASS_DECL
            and c.location.file.name == sys.argv[1]):
            a_class = Class(c)
            result.append(a_class)
        elif c.kind == clang.cindex.CursorKind.NAMESPACE:
            child_classes = build_classes(c)
            result.extend(child_classes)

    return result

if len(sys.argv) != 2:
    print("Usage: boost_python_gen.py [header file name]")
    sys.exit()

#clang.cindex.Config.set_library_path('C:/Program Files (x86)/LLVM/bin')
print("Setting clang path")
clang.cindex.Config.set_library_file('C:/Python27/DLLs/libclang.dll')
print("Clang path set")

index = clang.cindex.Index.create()
translation_unit = index.parse(sys.argv[1], ['-x', 'c++', '-std=c++11', '-D__CODE_GENERATOR__'])

classes = build_classes(translation_unit.cursor)
tpl = Template(filename='templates/jniadapter.mako')
rendered = tpl.render(
             classes=classes,
             module_name='CodegenExample',
             namespace='JniGenTest',
             include_file=sys.argv[1])

print(rendered)

OUTPUT_DIR = 'generated'

if not os.path.isdir(OUTPUT_DIR): os.mkdir(OUTPUT_DIR)

with open("generated/{}.bind.cc".format(sys.argv[1]), "w") as f:
    f.write(rendered)
