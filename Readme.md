# PHP JP Tools

Various utility functions which become of great use to anyone that needs to use  japanese in their php scripts. The tools include things such as `isHiragana()`, `isKatakana()` as well as `getFurigana()`. 

Those functions are built with speed in mind (think about having to call them thousands of times), so they've been written as a php extension. PHP extensions are written in pure C (or C++ in this case) and most of the time perform 10-20 times as fast as php-userland implementations (even when using the same or equivalent code).

## Building phpJpTools

### Ubuntu
 - Install the php development tools: `sudo apt install php-dev`
 - Install mecab and the mecab headers: `sudo apt install mecab mecab-dev`
 - Install swig: `sudo apt install swig`
 - Clone this repository: `git clone https://github.com/thelmuxkriovar/phpJpTools.git`
 - Run make on the cloned repo: `make`
 - Install the extension with: `sudo make install` 

### Fedora
 - Install the php development tools: `sudo dnf install php-devel`
 - Install mecab and the mecab.h headers: `sudo dnf install mecab mecab-devel` (you might want to add a custom dictionary as well)
 - Install swig: `sudo dnf install swig`
 - Clone this repository: `git clone https://github.com/thelmuxkriovar/phpJpTools.git`
 - Run make on the cloned repo: `make`
 - Install the extension with: `sudo make install`

### Arch (& others)

 - Install php and swig 
 - Install mecab and a mecab dictionary from the AUR
 - Clone this repository
 - Run make on the cloned repo
 - Install the extension with `sudo make install`

## Documentation & usage of the functions
coming soon