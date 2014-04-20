#!/usr/bin/python
# vim: set fileencoding=utf-8
import clang.cindex
import asciitree
import sys
#import pprint

#pp = pprint.PrettyPrinter(indent=4)

def node_children(node):
    #for c in node.get_children():
        #print(c.displayname)
        #print(c)
        #print(c.location)
        #print(type(c.location.file))
        #print(type(c.location.file) is clang.cindex.File)

    return (c for c in node.get_children() if type(c.location.file) is clang.cindex.File and c.location.file.name == sys.argv[1])

def print_node(node):
    #pp.pprint(node)
    text = node.spelling or node.displayname
    kind = str(node.kind)[str(node.kind).index('.')+1:]
    return '{} {}, type: {}'.format(kind, text, node.type.get_canonical().spelling, dir(node)) #node.type.spelling, 
#, properties: {}

if len(sys.argv) != 2:
    print("Usage: dump_ast.py [header file name]")
    sys.exit()

#clang.cindex.Config.set_library_file('/usr/local/lib/libclang.so')
clang.cindex.Config.set_library_file('C:/Python27/DLLs/libclang.dll')
index = clang.cindex.Index.create()
translation_unit = index.parse(sys.argv[1], ['-x', 'c++', '-std=c++11', '-D__CODE_GENERATOR__'])

print(asciitree.draw_tree(translation_unit.cursor, node_children, print_node))

