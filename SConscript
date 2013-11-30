Import ('env')

name = "fud"
inc = env.Dir('.'), env.Dir('fud/client'), env.Dir('fud/common'), env.Dir('fud/server'), env.Dir('fud/middlewares/ana/server'), env.Dir('fud/middlewares/ana/client')

deps = ['mili', 'boost_system', 'boost_thread']
src = env.Glob('src/client/*.cpp'), env.Glob('src/server/*.cpp'), env.Glob('fud/middlewares/ana/server/*.cpp'), env.Glob('fud/middlewares/ana/server/*.cpp')

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)
