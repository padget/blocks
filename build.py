from pyaml import yaml
import sys
import subprocess
from os import path

yamld = ''
with open('build.yml', 'r') as content_file:
    yamld = content_file.read()

def build_object(compiler, clfags, name, source, target):
  print('compiling {} ...'.format(name))
  
  args = [compiler, '-o', target, '-c', source]
  args.extend(cflags.split(' '))
  
  subprocess.run(args)


def build_shared(compiler, cflags, lib):
  name   = str(lib.get('name', ''))
  target = str(lib.get('target', ''))
  source = str(lib.get('source', ''))
  build_object(compiler, cflags, name, source, target)



def build_lib(compiler, cflags, lib, sources):
  name   = str(lib.get('name'))
  target = str(lib.get('target'))
  source = '{}/{}'.format(sources, str(lib.get('source', '')))
  build_object(compiler, cflags, name, source, target)


def verify_lib(libname):
  if not path.exists(libname):
    raise OSError()


def build_program(compiler, cflags, prog):
  name    = str(prog.get('name', ''))
  target  = str(prog.get('target', ''))
  libs    = list(prog.get('libs', []))
  shared  = list(prog.get('shared', []))

  libs = [dict(lib).get('target') for lib in libs]

  args = [compiler, '-o', target]
  args.extend(libs)
  args.extend(shared)
  args.extend(cflags.split(' '))
  
  print('compiling program {}'.format(name))
  subprocess.run(args)



obj = dict(yaml.safe_load(yamld))

compiler = str(obj.get('compiler', ''))
cflags   = str(obj.get('cflags', ''))
shared   = list(obj.get('shared', []))
programs = list(obj.get('programs', []))
purge    = list(obj.get('purge', []))

if not compiler:
  print('no compiler defined')
  sys.exit(-1)

# il y a des shared libs à compiler
if len(shared) > 0:
  for lib in shared:
    build_shared(compiler, cflags, lib)


if len(programs) > 0:
  for prog in programs:
    
    name = str(prog.get('name', ''))
    sources = str(prog.get('sources', ''))
    target = str(prog.get('target', ''))
    libs = list(prog.get('libs', []))
    shared = list(prog.get('shared', []))

    print('building programm {}'.format(name))

    for lib in libs: 
      build_lib(compiler, cflags, lib, sources)
    
    for libname in shared: 
      verify_lib(libname)

    build_program(compiler, cflags, prog)

if len(purge) > 0:
  for p in purge:
    import glob, os
    for f in glob.glob(p):
      os.remove(f)