#include <phpcpp.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <mecab.h>
#include "utf8Utils.h"

#define hiraganaStart 0x3041
#define hiraganaEnd 0x3096
#define katakanaStart 0x30A1
#define katakanaEnd 0x30FA
#define katakanaSpecialEnd 0x30FD
#define kanjiStart 0x4e00
#define kanjiEnd 0x9faf

using namespace std;

class jpUtils {
	public:
		static bool isHiragana(string chraracter) {
			int chr = charPoint(chraracter);
			if(chr < hiraganaStart)
				return false;
			if(chr > hiraganaEnd) // hiragana upper limit. Following, are dakuten, handakuten and other characters, we shall NOT consider those as proper hiragana
				return false;
			return true;
		}
		static bool isKatakana(string character, bool shouldCountSeparatorAndLine) {
			int chr = charPoint(character);
			if(chr < katakanaStart) // 0x30A0 is technically in the range of katakana, but it's not a valid katakana character
				return false;
			if(chr > katakanaEnd) { // katakana upper limit.
				if(shouldCountSeparatorAndLine && chr < katakanaSpecialEnd)
					return true;
				return false;
			}
			return true;
		}

		static bool isKanji(string character) {
			int chr = charPoint(character);
			if(chr < kanjiStart)
				return false;
			if(chr > kanjiEnd)
				return false;
			return true;
		}
		static string katakanaToHiragana(string text) {
			string ret = "";
			for(int i = 0; i < utf8len(text); i++) {
				string chr = utf8substr(text, i, 1);
				if(jpUtils::isKatakana(chr, true)) {
					if(chr == "ー") { // e.g.: ホントー -> ほんとう
						string prevChr = utf8substr(text, i - 1, 1);
						if(prevChr == "ア" || prevChr == "イ" || prevChr == "エ")
							appendUnicode(ret, hiraganaStart + charPoint(prevChr) - katakanaStart);
						else if(prevChr == "オ" || prevChr == "ウ")
							ret += "う";
						else if(prevChr == "カ" || prevChr == "ガ" || prevChr == "サ" || prevChr == "ザ" || prevChr == "タ" || prevChr == "ダ" || prevChr == "ナ" || prevChr == "ハ" || prevChr == "バ" || prevChr == "パ" || prevChr == "マ" || prevChr == "ヤ" || prevChr == "ラ" || prevChr == "ワ")
							ret += "あ";
						else if(prevChr == "キ" || prevChr == "ギ" || prevChr == "シ" || prevChr == "ジ" || prevChr == "チ" || prevChr == "ヂ" || prevChr == "ニ" || prevChr == "ヒ" || prevChr == "ビ" || prevChr == "ピ" || prevChr == "ミ" || prevChr == "リ" || prevChr == "ヰ")
							ret += "い";
						else if(prevChr == "ク" || prevChr == "グ" || prevChr == "ス" || prevChr == "ズ" || prevChr == "ツ" || prevChr == "ズ" || prevChr == "ヌ" || prevChr == "フ" || prevChr == "ブ" || prevChr == "プ" || prevChr == "ム" || prevChr == "ル" || prevChr == "コ" || prevChr == "ゴ" || prevChr == "ソ" || prevChr == "ゾ" || prevChr == "ト" || prevChr == "ド" || prevChr == "ノ" || prevChr == "ホ" || prevChr == "ボ" || prevChr == "ポ" || prevChr == "モ" || prevChr == "ロ" || prevChr == "ヲ")
							ret += "う";
						else if(prevChr == "ケ" || prevChr == "ゲ" || prevChr == "セ" || prevChr == "ゼ" || prevChr == "テ" || prevChr == "デ" || prevChr == "ネ" || prevChr == "ヘ" || prevChr == "ベ" || prevChr == "ペ" || prevChr == "メ" || prevChr == "レ" || prevChr == "ヱ")
							ret += "え";
						else
							ret += "ー";
					}else
						appendUnicode(ret, hiraganaStart + charPoint(chr) - katakanaStart);
				} else
					ret += chr;
			}
			return ret;
		}
		static string kanjiToRb(string kanji, string reading) {
			if (kanji == reading)
				return reading;
			if(reading == "かおもじ" && kanji != "顔文字")
				return kanji;
			string furigana = "";
			int placeLeft = 0, placeRight = 0;
			int lastKanji = utf8len(kanji);
			int lastReading = utf8len(reading);
			int j = 0;
			for(int i = 0; i < utf8len(kanji); i++) {
				placeRight = i;
				j = i + 1;
				if(utf8substr(kanji, lastKanji - j, 1) != utf8substr(reading, lastReading - j, 1))
					break;
			}
			for(int i = 0; i < utf8len(kanji); i++) {
				placeLeft = i;
				if(utf8substr(kanji, i, 1) != utf8substr(reading, i, 1))
					break;
			}
			string before = "", after = "", ruby = "", rt = "";
			if(placeLeft == 0) {
				if(placeRight == 0) {
					ruby = kanji;
					rt = reading;
				}else{
					ruby = utf8substr(kanji, 0, lastKanji - placeRight);
					rt = utf8substr(reading, 0, lastReading - placeRight);
					after = utf8substr(reading, lastReading - placeRight, 2147483647);
				}
			}else{
				if(placeRight == 0) {
					before = utf8substr(reading, 0, placeLeft);
					ruby = utf8substr(kanji, placeLeft, 2147483647);
					rt = utf8substr(reading, placeLeft, 2147483647);
				} else {
					before = utf8substr(reading, 0, placeLeft);
					ruby = utf8substr(kanji, placeLeft, lastKanji - placeRight);
					rt = utf8substr(reading, placeLeft, lastReading - placeRight);
					after = utf8substr(reading, lastReading - placeRight, 2147483647);
				}
			}
			return before + "<ruby><rb>"+ruby+"</rb><rt>"+rt+"</rt></ruby>"+after;
		}
		static string getFurigana(string text) {
			string out = "";
			const char *input = text.c_str();
			char *token;
			MeCab::Tagger *tagger = MeCab::createTagger("");

			const MeCab::Node* node = tagger->parseToNode(input);
			for (; node; node = node->next) {
				if (node->stat == MECAB_BOS_NODE || node->stat == MECAB_EOS_NODE) // skip BOS and EOS
					continue;
				int position = 0;

				string word = string(node->surface).substr(0, node->length);
				string mecabResponse = string(node->feature);

				if(jpUtils::isKanji(word)) {
					token = strtok((char *)mecabResponse.c_str(), ","); // is this ok? there must be a better way, typecasting sounds sketchy
					while (token != NULL) {
						if(position == 8) {
							out += kanjiToRb(word, jpUtils::katakanaToHiragana(token));
							break;
						}

						token = strtok (NULL, ",");
						position++;
					}
				}else
					out += word;
			}
			return out;
		}
		static string hiraganaToKatakana(string text) {
			string ret = "";
			for(int i = 0; i < utf8len(text); i++) {
				string chr = utf8substr(text, i, 1);
				if(jpUtils::isHiragana(chr))
					appendUnicode(ret, katakanaStart + charPoint(chr) - hiraganaStart);
				else
					ret += chr;
			}
			return ret;
		}
};

Php::Value phpGetFurigana(Php::Parameters &parameters) {
	return jpUtils::getFurigana(parameters[0]);
}

Php::Value phpKatakanaToHiragana(Php::Parameters &parameters) {
	return jpUtils::katakanaToHiragana(parameters[0]);
}

Php::Value phpIsHiragana(Php::Parameters &parameters) {
	return jpUtils::isHiragana(utf8substr(parameters[0], 0, 1));
}

Php::Value phpIsKatakana(Php::Parameters &parameters) {
	string firstChar = utf8substr(parameters[0], 0, 1);
	bool shouldCountSeparatorAndLine;
	if(parameters.size() == 1)
		shouldCountSeparatorAndLine = false;
	else
		shouldCountSeparatorAndLine = parameters[1];
	return jpUtils::isKatakana(firstChar, shouldCountSeparatorAndLine);
}

Php::Value phpHiraganaToKatakana(Php::Parameters &parameters) {
	return jpUtils::hiraganaToKatakana(parameters[0]);
}

extern "C" {
	PHPCPP_EXPORT void *get_module() {
		static Php::Extension extension("jpTools", "1.0");
		extension.add<phpIsHiragana>("isHiragana", {
			Php::ByVal("character", Php::Type::String, true)
		});
		extension.add<phpIsKatakana>("isKatakana", {
			Php::ByVal("character", Php::Type::String, true),
			Php::ByVal("shouldCountSeparatorAndLine", Php::Type::Bool, false)
		});
		extension.add<phpHiraganaToKatakana>("hiraganaToKatakana", {
			Php::ByVal("string", Php::Type::String, true)
		});
		extension.add<phpKatakanaToHiragana>("katakanaToHiragana", {
			Php::ByVal("string", Php::Type::String, true)
		});
		extension.add<phpGetFurigana>("getFurigana", {
			Php::ByVal("string", Php::Type::String, true)
		});
		return extension;
	}
}
