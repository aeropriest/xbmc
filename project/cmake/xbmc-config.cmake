SET(XBMC_INCLUDE_DIR /Users/Shared/xbmc-depends/macosx10.9_i386-target/include)
LIST(APPEND CMAKE_MODULE_PATH /Users/Shared/xbmc-depends/macosx10.9_i386-target/lib/xbmc)
ADD_DEFINITIONS(-DTARGET_POSIX -DTARGET_DARWIN -DTARGET_DARWIN_OSX -D_LINUX)

include(xbmc-addon-helpers)
