bool isHiragana(std::string chraracter);
bool isKatakana(std::string character, bool shouldCountSeparatorAndLine);
bool isKanji(std::string character);
std::string katakanaToHiragana(std::string text);
std::string hiraganaToKatakana(std::string text);
std::string kanjiToRb(std::string kanji, std::string reading);
std::string getFurigana(std::string text);
void setMecabDictionaryPath(std::string dicPath);