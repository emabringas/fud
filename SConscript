Import ('env')

# Implementation options
implementations = ['ana', 'asio']

# Concrete implementation for FuD
AddOption(
    '--implementation',
    dest='implementation',
    action='store',
    type='string',
    default=implementations[0],
    help='Specifies the underlying implementation for FuD. Default is ana.'
)

# Check if implementation option is OK
if not env.GetOption('implementation') in implementations:
    print 'Error: the concrete implementation chosen does not exist !!\nYou have to choose one of these:', implementations

# Object: Ana implementation for FuD client
inc = env.Dir('.')
src = env.Glob('src/middlewares/ana/client/*.cpp')
deps = ['mili', 'boost_thread', 'ana']
env.CreateObject('fud_client_ana', inc, src, deps)

# Object: Ana implementation for FuD server
inc = env.Dir('.')
src = env.Glob('src/middlewares/ana/server/*.cpp')
deps = ['mili', 'ana']
env.CreateObject('fud_server_ana', inc, src, deps)

# Object: Asio implementation for FuD client
inc = env.Dir('.')
src = env.Glob('src/middlewares/asio/client/*.cpp')
deps = ['mili']
env.CreateObject('fud_client_asio', inc, src, deps)

# Object: Asio implementation for FuD server
inc = env.Dir('.')
src = env.Glob('src/middlewares/asio/server/*.cpp')
deps = []
env.CreateObject('fud_server_asio', inc, src, deps)

# Object: Common implementation for FuD client and FuD server
inc = env.Dir('.')
src = env.Glob('src/common/*.cpp')
deps = ['mili']
env.CreateObject('common_fud', inc, src, deps)

# SharedLibrary: FuD client
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/client/*.cpp')
#deps = ['mili', 'boost_system', 'boost_thread', 'ana', 'common_fud', 'fud_client' + env.GetOption('implementation')]
deps = ['mili', 'boost_system', 'boost_thread', 'ana', 'common_fud', 'fud_client_ana']
env.CreateSharedLibrary('fud_client', inc, ext_inc, src, deps)

# SharedLibrary: FuD server
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/server/*.cpp')
#deps = ['mili', 'boost_system', 'boost_thread', 'ana', 'common_fud', 'fud_server' + env.GetOption('implementation')]
deps = ['mili', 'boost_system', 'boost_thread', 'ana', 'common_fud', 'fud_server_ana']
env.CreateSharedLibrary('fud_server', inc, ext_inc, src, deps)


