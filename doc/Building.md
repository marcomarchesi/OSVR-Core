# Building the Libraries {#Building}

See the OSVR Wiki page on [Getting Started with Core Development][wiki-getting-started] for more step-by-step instructions, including links to pre-compiled Windows binary dependencies.

[wiki-getting-started]:http://wiki.osvr.com/doku.php?id=startingcore

The rest of the page you're currently reading is targeted at those interested in in-depth development (particularly across platforms), so it leaves a lot of blanks that it assumes you can fill in.

You'll need:

- CMake, fairly recent (2.8.12 or newer, 3.0.2 most tested, that or the latest preferred.)
- A relatively recent version of Boost (1.44 or newer, 1.57.0 on Windows the most tested, the latest is usually preferred barring any weird bugs which will be noted here if discovered.)
- [libfunctionality][] compiled
- [jsoncpp][] compiled, with the `JSONCPP_WITH_CMAKE_PACKAGE` option turned on, and the `JSONCPP_LIB_BUILD_SHARED` option turned off on Windows and on for other platforms.
- A C++11 capable compiler: VS 2013 is the main one used in development. (VS 2012 doesn't support enough C++11 to build the core currently.) GCC in the nuwen distro of MinGW also works, at least as of some time in the recent past. CI builds regularly on Linux using GCC and Clang, so ideally GCC in MinGW should also stay working, or at least not very broken.

For Linux:

- The above (any reasonably recent Clang or GCC is fine), plus `libusb-1.0-0-dev`

[libfunctionality]:https://github.com/OSVR/libfunctionality
[jsoncpp]:https://github.com/VRPN/jsoncpp
