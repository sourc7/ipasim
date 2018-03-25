# Objective-C runtime

Because the GNUstep runtime used by WinObjC is binary incompatible with the Apple's runtime used on iPhones, we cannot simply use it.
If we did, the runtime couldn't read the structures in the iPhone app binary as they are in Apple's format and the runtime expects them in its own different format.

So, the only option we see here is to recompile WinObjC with a different runtime (and pass clang a parameter to generate the Apple's structures - it can definitely do that since it's the compiler used on Apple for development).

## Existing runtimes

- Apple's runtime
  - Source code: [Official](https://opensource.apple.com/source/objc4/), [Tarballs](https://opensource.apple.com/tarballs/objc4/), [GitHub mirror](https://github.com/opensource-apple/objc4) (not updated so often)
  - Documentation: [Official](https://developer.apple.com/documentation/objectivec/objective_c_runtime?language=objc)
- Modular Objective-C Run-Time Library
  - Source code: [GitHub](https://github.com/charlieMonroe/modular-objc-run-time)
  - Master thesis: [Local copy](../res/modular-objc.pdf), [CUNI repository](https://is.cuni.cz/webapps/zzp/detail/116510/29583005/)
- ObjFW
  - It contains an Objective-C runtime reimplementation.
  - Source code: [Official GitHub mirror](https://github.com/Midar/objfw)
- Magenta project
  - Info: [Official website](http://crna.cc/cat/open-source), [OSnews article](http://www.osnews.com/story/26060/Magenta_implements_Darwin_BSD_on_top_of_the_Linux_kernel), [Maemo.org thread](https://talk.maemo.org/showthread.php?t=84803)
  - Source code: [Archive.org](https://web.archive.org/web/20120625011212/http://crna.cc:80/magenta_source.html)
- mulle-objc
  - Info: [Official website](https://mulle-objc.github.io/)

**TODO: Add more.**

## Porting the Apple's runtime

### Related work

One cool thing to do would be to just take the source code for Apple's Objective-C runtime and compile it for Windows.
Links to projects that try to do that follow.

- [GitHub] [0xxd0's buildable fork](https://github.com/0xxd0/objc4)
- [mailing list] [Building Objc4 on Windows](https://lists.apple.com/archives/darwin-dev/2009/Sep/msg00076.html)
- [SourceForge] [OpenCFLite](https://sourceforge.net/projects/opencflite/)
  - [mailing list] [Building Objc4 on Windows](https://lists.apple.com/archives/darwin-dev/2009/Nov/msg00045.html) (despite the same name, it's a different mailing list from the above)
- [GitHub] [isaacselement's buildable fork](https://github.com/isaacselement/objc4-706)
  - [GitHub] [lanvsblue's buildable fork](https://github.com/lanvsblue/objc4-706) (based on isaacselement's blog post)
- [GitHub] [Jeswang's buildable fork](https://github.com/Jeswang/objc4-532.2)
  - [StackOverflow] [Explanation of the repository](https://stackoverflow.com/questions/23469738/debugging-objc4-532-2-on-os-x-10-9)
- [GitHub] [oneofai's buildable fork](https://github.com/oneofai/objc4)
- [GitHub] [Mirror of objc4 with added comments](https://github.com/xuhong1105/objc4-680)

All of these projects are mostly for building the runtime on macOS, though.
And the others can build only the old runtime for Win32 (which is what even Apple was doing for Safari on Windows, so it is supported in the source code).
But we want the new runtime because that's the one used in iPhones.
So we just take all these projects as merely an inspiration for our own Objective-C runtime written from scratch with only one goal - to be binary compatible with the new Apple's runtime.

### Inspiration

Our code is inspired by the Apple's runtime source code, version 723.
We want it to be binary-compatible with the new runtime, so that's like `__OBJC2__` was defined.