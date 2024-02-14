project('crpn', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

executable('crpn',
  'src/main.c',
  install : true,
  dependencies : m_dep)
