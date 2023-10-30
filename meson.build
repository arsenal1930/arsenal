project('arsenal1930', 'cpp',
  version: files('./VERSION'),
  license: 'GPLv3'
)

add_project_arguments('-march=core2', language: 'cpp')

src = [
  'src/init.cpp', 
  'src/Engine/Engine.cpp', 
  'src/Engine/Math/GameMath.cpp',
  'src/Engine/Base/Object.cpp',
  'src/Engine/Base/Denizen.cpp', 
  'src/Engine/Base/ITextureable.cpp'
]

sfml_dep = dependency('sfml-all', fallback: ['sfml', 'sfml_dep'])

executable('arsenal1930', src, dependencies: sfml_dep)
