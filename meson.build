project('AaDS', 'cpp',
  version : '1.0',
  default_options : [
    'warning_level=3',
    'buildtype=custom',
    'werror=true',
    'optimization=3'
  ])

compiler = meson.get_compiler('cpp')

if compiler.get_id() == 'gcc'
    message('Compiler: GCC')
elif compiler.get_id() == 'clang'
    message('Compiler: LLVM/clang')
endif

add_global_arguments('-Wmissing-declarations',
                     '-Wno-unused',
                     language: 'cpp')

executable('AaDS',
           'main.cpp')

executable('gen_rand_int',
           'gen_rand_int.cpp')