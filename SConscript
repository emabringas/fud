Import ('env')

#env.Append(CXXFLAGS = ['-DRESEND_PENDING_JOBS'])

inc = env.Dir('.'), env.Dir('src/client'), env.Dir('src/common'), env.Dir('src/server'), env.Dir('src/middlewares/ana/server'), env.Dir('src/middlewares/ana/client'), env.Dir('../ana/src/api')
deps = ['mili', 'boost_system', 'boost_thread', 'ana']
src = env.Glob('src/client/*.cpp'), env.Glob('src/server/*.cpp'), env.Glob('src/middlewares/ana/server/*.cpp'), env.Glob('src/middlewares/ana/client/*.cpp')
ext_inc = []

env.CreateSharedLibrary('fud', inc, ext_inc, src, deps)