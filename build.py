#!/usr/bin/env python3

import subprocess

# generic variables
cc      = 'gcc'
ccflags =  ['-Wall', '-W', '-pedantic', '-Werror', '-std=c11']

# program name variables
blocks_prog         = 'blocks.exe'
blocks_help_prog    = 'blocks-help.exe'
blocks_prepare_prog = 'blocks-prepare.exe'
blocks_compile_prog = 'blocks-compile.exe'
blocks_execute_prog = 'blocks-execute.exe'

# object name variables
blocks_object         = 'blocks.o'
blocks_compile_object = 'blocks-compile.o'
blocks_execute_object = 'blocks-execute.o'
blocks_help_object    = 'blocks-help.o'
blocks_prepare_object = 'blocks-prepare.o'

# experimental variables
argument_object = 'argument.o'
argument_source = 'experimental/argument.c'

# main source name variables
blocks_main = 'blocks/src/main.c'

# dependances variables
blocks_deps = ['argument.o']


def build_blocks_program():
    args = [cc, '-o', argument_object, '-c', argument_source]
    args.extend(ccflags)
    subprocess.run(args=args, shell=True)

    args=[cc, '-o', blocks_object,'-c',  blocks_main]
    args.extend(ccflags)
    subprocess.run(args=args, shell=True)
    
    args=[cc, '-o', blocks_prog, blocks_object]
    args.extend(blocks_deps)
    args.extend(ccflags)
    subprocess.run(args=args, shell=True)


if __name__=='__main__':
    print('building project')
    build_blocks_program()


