project('arsenal1930', 'cpp',
  version: '0.1.3.5',
  license: 'GPLv3'
)

src = [
  'src/init.cpp', 
  'src/Engine/Engine.cpp', 
  'src/Engine/Math/GameMath.cpp',
  'src/Engine/Filesystem/Filesystem.cpp', 
  'src/Engine/Base/Object.cpp', 
  'src/Engine/Base/Camera.cpp'

]

sfml_dep = dependency('sfml')

executable('arsenal1930', src, dependencies: sfml_dep)

img_src = join_paths(meson.source_root(), 'images')
img_dest = join_paths(meson.build_root(), './')
message('copying @0@ to @1@ ...'.format(img_src, img_dest))
run_command('cp', '-r', img_src, img_dest)

txt_src = join_paths(meson.source_root(), 'texts')
txt_dest = join_paths(meson.build_root(), './')
message('copying @0@ to @1@ ...'.format(txt_src, txt_dest))
run_command('cp', '-r', txt_src, txt_dest)

