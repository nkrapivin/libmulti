# libmulti

## What is it?

A library to create and manage multiple windows from GameMaker.

## Which GameMaker?

Basically GameMaker: Studio 1.4 and everything newer.

*(there's some hacky GM8.1 support but don't count on it! better switch to Studio asap!)*

The Windows x64 Runtime introduced in 2.3.1 is supported too.

## Can I get it?

Yes, for free!

Latest release is here: https://github.com/nkrapivin/libmulti/releases/latest

Documentation is here (trust me you'll need it): https://github.com/nkrapivin/libmulti/wiki

## Can I build it myself?

Sure, you'll need Visual Studio 2015 or above with installed C++ support.

Each time you build the extension it will invoke GmxGen (see `postbuild.bat`) to update all the sample projects in the repo directory.

When you build the extension in `Debug` configuration, it will replace the extension DLL with debug ones.

If you're building for `Release`, Release DLLs will be copied.

Please build it in the x86 configuration first at least once, and then the x64 one.

Oh and be sure to not screw up the main header file (`libmulti.h`) or any of the sample projects, or else bad things will happen.

*(inability to build the whole thing for example)*

## Any obligations, etc?

Not really, you don't even need to credit me. I don't care. Feel free to steal the code lol.

## How can I ask for support?

- Discord: nik#5351
- VK (russian facebook, for those who don't know): https://vk.com/nkrapivindev
- Twitter: @nkrapivindev
- Email: who's still using email lmfao?! it's in the github profile btw.

## Credits
- [YellowAfterlife](https://yal.cc "His website") for creating an awesome tool [GmxGen](https://github.com/YAL-GameMaker-Tools/GmxGen "The tool's repo").
- Microsoft and their (somewhat easy to understand) Direct2D examples.

