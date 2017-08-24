<?php
var_dump(isHiragana("す"));
var_dump(isKatakana("ー"));
var_dump(isKatakana("ー", true));
var_dump(hiraganaToKatakana("カタカナ ひらがな 漢字", true));
var_dump(katakanaToHiragana("カタカナ ひらがな 漢字", true));
echo getFurigana("日本語を話すことは本当に楽しいですよね。");
echo getFurigana("日本に行った時に、僕の人生が変わった。僕は僕の居場所が探した。");
