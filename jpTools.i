%module jpTools
%include "std_string.i"
%include "exception.i"
%{
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <mecab.h>
#include "../utf8Utils.hpp"
#include "../jpTools.hpp"
%}

%exception {
	try {
		$action
	} catch (std::exception& e) {
		SWIG_exception(SWIG_SystemError, e.what());
	}
}

%pragma(php) phpinfo="
  php_info_print_table_start();
  php_info_print_table_header(2, \"Directive\", \"Value\");
  php_info_print_table_row(2, \"Extension enabled\", \"true\");
  php_info_print_table_row(2, \"Github\", \"https://github.com/thelmuxkriovar/phpJpTools\");
  php_info_print_table_end();
"

extern bool isHiragana(std::string character);
extern bool isKatakana(std::string character, bool shouldCountSeparatorAndLine);
extern bool isKanji(std::string character);
extern std::string katakanaToHiragana(std::string text);
extern std::string hiraganaToKatakana(std::string text);
extern std::string kanjiToRb(std::string kanji, std::string reading);
extern std::string getFurigana(std::string text);
extern void setMecabDictionaryPath(std::string dicPath);