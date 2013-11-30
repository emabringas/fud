Import ('env')

inc = env.Dir('.')
ext_inc = []
deps = ['mili', 'boost_system', 'boost_thread', 'ana']
src = env.Glob('src/client/*.cpp'), env.Glob('fud/middlewares/ana/client/*.cpp'), env.Glob('fud/middlewares/asio/client/*.cpp') 
env.CreateSharedLibrary('fud_client', inc, ext_inc, src, deps)

inc = env.Dir('.')
ext_inc = []
deps = ['mili', 'boost_system', 'boost_thread', 'ana']
src = env.Glob('src/server/*.cpp'), env.Glob('src/common/*.cpp'), env.Glob('fud/middlewares/ana/server/*.cpp'), env.Glob('fud/middlewares/asio/server/*.cpp')
env.CreateSharedLibrary('fud_server', inc, ext_inc, src, deps)