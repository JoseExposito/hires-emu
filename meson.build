project('hires-emu', 'c')

libevdev = dependency('libevdev')


cc = meson.get_compiler('c')
cflags = [
    '-Wno-unused-parameter',
    '-fvisibility=hidden',
    '-Wmissing-prototypes',
    '-Wstrict-prototypes'
]

add_project_arguments(cflags, language: 'c')
add_project_arguments(cflags, language: 'cpp')

executable('hires-emu',
    'main.c',
    dependencies: [libevdev]
)
