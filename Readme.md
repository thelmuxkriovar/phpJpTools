# PHP JP Tools

Various utility functions which become of great use to anyone that needs to use  japanese in their php scripts. The tools include things such as `isHiragana()`, `isKatakana()` as well as `getFurigana()`. 

Those functions are built with speed in mind (think about having to call them thousands of times per file) and because of that they've been written as a php extension. PHP extensions are written in pure C (or C++ in this case) and most of the time perform 10-20 times as fast as php-userland implementations (even when using the same code).

## Building phpJpTools

Those instructions aren't perfected yet and may or may not result in issues with your computer/linux distro. I apologize for this, I'm working on fixing it, but as of now it has only been tested on Fedora 25.

- Install the php development tools: `sudo dnf install php-devel`
- Install mecab and the mecab.h headers: `sudo dnf install mecab mecab-devel` (you might want to add a custom dictionary as well)
- Compile [PHP-C++](http://www.php-cpp.com/documentation/install) which allows this library to exist while,
- `git clone https://github.com/thelmuxkriovar/phpJpTools.git`
- `make all`
- `sudo make install`

## Documentation & usage of the functions
coming soon
