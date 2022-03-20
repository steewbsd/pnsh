project('pnsh', 'c')
src = ['main.c', 'libs/read.c', 'libs/builtins.c', 'libs/types.c']
cc = meson.get_compiler('c')
libedit_dep = cc.find_library('edit', required : true)
executable('pnsh', src, dependencies : [libedit_dep], install : false)