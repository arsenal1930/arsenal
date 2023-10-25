project('arsenal1930', 'cpp',
  version: '0.1.1',
  license: 'GPLv3'
)

src = [
  'src/init.cpp', 
  'src/Engine/Engine.cpp', 
  'src/Engine/Base/Denizen.cpp', 
  'src/Engine/Base/ITextureable.cpp',
  'src/Engine/Math/GameMath.cpp'
]

sfml_dep = dependency('sfml')

executable('arsenal1930', src, dependencies: sfml_dep)

img_src = join_paths(meson.source_root(), 'images')
img_dest = join_paths(meson.build_root(), './')
message('copying @0@ to @1@ ...'.format(img_src, img_dest))
run_command('cp', '-r', img_src, img_dest)

