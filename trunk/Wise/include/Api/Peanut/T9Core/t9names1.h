/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 2003-2005 TEGIC COMMUNICATIONS                 **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: t9names1.h                                                  **
;**                                                                           **
;**  Description: Compatibility Header File defining new names by old         **
;**                                                                           **
;**  Version:	  7.3                                                         **
;*******************************************************************************
;******************************************************************************/
#ifndef T9NAMES1_H
#define T9NAMES1_H 1
#if defined(T9CTRLSETWORDCOMPLETION) && !defined(T9CTRLSETUDBCOMPLETION)
#define T9CTRLSETUDBCOMPLETION T9CTRLSETWORDCOMPLETION
#endif
#if defined(T9CTRLCLRWORDCOMPLETION) && !defined(T9CTRLCLRUDBCOMPLETION)
#define T9CTRLCLRUDBCOMPLETION T9CTRLCLRWORDCOMPLETION
#endif
#if defined(T9REQSPELLSYM) && !defined(T9REQMULTITAPSYM)
#define T9REQMULTITAPSYM T9REQSPELLSYM
#endif
#if defined(T9STATESPELL) && !defined(T9STATEMULTITAP)
#define T9STATEMULTITAP T9STATESPELL
#endif
#if defined(T9STATEEXTSPELL) && !defined(T9STATEEXTMULTITAP)
#define T9STATEEXTMULTITAP T9STATEEXTSPELL
#endif
#if defined(T9STATESPELLMASK) && !defined(T9STATEMULTITAPMASK)
#define T9STATEMULTITAPMASK T9STATESPELLMASK
#endif
#if defined(T9STATEEXTSPELLMASK) && !defined(T9STATEEXTMULTITAPMASK)
#define T9STATEEXTMULTITAPMASK T9STATEEXTSPELLMASK
#endif
#if defined(SPELL_MODE) && !defined(T9MULTITAPMODE)
#define T9MULTITAPMODE SPELL_MODE
#endif
#if defined(EXTSPELL_MODE) && !defined(T9EXTMULTITAPMODE)
#define T9EXTMULTITAPMODE EXTSPELL_MODE
#endif
#if defined(T9RDB_ON) && !defined(T9AWRDBON)
#define T9AWRDBON T9RDB_ON
#endif
#if defined(AMBIG_MODE) && !defined(T9AMBIGMODE)
#define T9AMBIGMODE AMBIG_MODE
#endif
#if defined(SHIFT_MODE) && !defined(T9SHIFTMODE)
#define T9SHIFTMODE SHIFT_MODE
#endif
#if defined(CAPSLOCK_MODE) && !defined(T9CAPSLOCKMODE)
#define T9CAPSLOCKMODE CAPSLOCK_MODE
#endif
#if defined(INSERT_MODE) && !defined(T9INSERTMODE)
#define T9INSERTMODE INSERT_MODE
#endif
#if defined(T9AUX_KEYNUM) && !defined(T9AUXKEYNUM)
#define T9AUXKEYNUM T9AUX_KEYNUM
#endif
#if defined(T9AUX_SHIFTED) && !defined(T9AUXSHIFTED)
#define T9AUXSHIFTED T9AUX_SHIFTED
#endif
#if defined(sSpellSymbol) && !defined(sMultitapSymbol)
#define sMultitapSymbol sSpellSymbol
#endif
#if defined(T9SNUM) && !defined(T9INT)
#define T9INT T9SNUM
#endif
#if defined(T9NUM) && !defined(T9UINT)
#define T9UINT T9NUM
#endif
#if defined(CHINESE_T9) && !defined(T9CHINESE)
#define T9CHINESE CHINESE_T9
#endif
#if defined(KOREAN_T9) && !defined(T9KOREAN)
#define T9KOREAN KOREAN_T9
#endif
#if defined(JAPANESE_T9) && !defined(T9JAPANESE)
#define T9JAPANESE JAPANESE_T9
#endif
#if defined(WORD_API) && !defined(T9WORDAPI)
#define T9WORDAPI WORD_API
#endif
#if defined(TXTFILLSYM) && !defined(T9TXTFILLSYM)
#define T9TXTFILLSYM TXTFILLSYM
#endif
#if defined(KOREAN_T9) && !defined(T9KOREAN)
#define T9KOREAN KOREAN_T9
#endif
#if defined(FARCALL) && !defined(T9FARCALL)
#define T9FARCALL FARCALL
#endif
#if defined(FARDATA) && !defined(T9FARDATA)
#define T9FARDATA FARDATA
#endif
#if defined(NEARCALL) && !defined(T9NEARCALL)
#define T9NEARCALL NEARCALL
#endif
#if defined(NEARDATA) && !defined(T9NEARDATA)
#define T9NEARDATA NEARDATA
#endif
#if defined(T9_MAX_DB_KEYS) && !defined(T9MAXDBKEYS)
#define T9MAXDBKEYS T9_MAX_DB_KEYS
#endif
#if defined(T9_MAX_TAP_KEYS) && !defined(T9MAXTAPKEYS)
#define T9MAXTAPKEYS T9_MAX_TAP_KEYS
#endif
#if defined(T9_MAX_TREES) && !defined(T9MAXTREES)
#define T9MAXTREES T9_MAX_TREES
#endif
#if defined(COLLATING_SEQUENCE_LATIN1) && !defined(T9CSLatin1)
#define T9CSLatin1 COLLATING_SEQUENCE_LATIN1
#endif
#if defined(COLLATING_SEQUENCE_GSM) && !defined(T9CSGSM)
#define T9CSGSM COLLATING_SEQUENCE_GSM
#endif
#if defined(COLLATING_SEQUENCE_LATINA) && !defined(T9CSLatinA)
#define T9CSLatinA COLLATING_SEQUENCE_LATINA
#endif
#if defined(COLLATING_SEQUENCE_LATINB) && !defined(T9CSLatinB)
#define T9CSLatinB COLLATING_SEQUENCE_LATINB
#endif
#if defined(COLLATING_SEQUENCE_DIACRITICS) && !defined(T9CSDiacritics)
#define T9CSDiacritics COLLATING_SEQUENCE_DIACRITICS
#endif
#if defined(COLLATING_SEQUENCE_HEBREW) && !defined(T9CSHebrew)
#define T9CSHebrew COLLATING_SEQUENCE_HEBREW
#endif
#if defined(COLLATING_SEQUENCE_GENERAL_PUNCTUATION) && !defined(T9CSGeneralPunctuation)
#define T9CSGeneralPunctuation COLLATING_SEQUENCE_GENERAL_PUNCTUATION
#endif
#if defined(COLLATING_SEQUENCE_CURRENCY_SYMBOLS) && !defined(T9CSCurrencySymbols)
#define T9CSCurrencySymbols COLLATING_SEQUENCE_CURRENCY_SYMBOLS
#endif
#if defined(COLLATING_SEQUENCE_ARABIC_ALTERNATE) && !defined(T9CSArabicAlternate)
#define T9CSArabicAlternate COLLATING_SEQUENCE_ARABIC_ALTERNATE
#endif
#if defined(COLLATING_SEQUENCE_CYRILLIC_EVEN) && !defined(T9CSCyrillicEven)
#define T9CSCyrillicEven COLLATING_SEQUENCE_CYRILLIC_EVEN
#endif
#if defined(COLLATING_SEQUENCE_GREEK_ALPHABETIC) && !defined(T9CSGreekAlphabetic)
#define T9CSGreekAlphabetic COLLATING_SEQUENCE_GREEK_ALPHABETIC
#endif
#if defined(COLLATING_SEQUENCE_THAI_AIS) && !defined(T9CSThaiAIS)
#define T9CSThaiAIS COLLATING_SEQUENCE_THAI_AIS
#endif
#if defined(COLLATING_SEQUENCE_THAI_ALTERNATE) && !defined(T9CSThaiAlternate)
#define T9CSThaiAlternate COLLATING_SEQUENCE_THAI_ALTERNATE
#endif
#if defined(COLLATING_SEQUENCE_THAI_HUTCHISON) && !defined(T9CSThaiHutchison)
#define T9CSThaiHutchison COLLATING_SEQUENCE_THAI_HUTCHISON
#endif
#if defined(COLLATING_SEQUENCE_DEVANAGARI_ALTERNATE) && !defined(T9CSDevanagariAlternate)
#define T9CSDevanagariAlternate COLLATING_SEQUENCE_DEVANAGARI_ALTERNATE
#endif
#if defined(COLLATING_SEQUENCE_ARABIC) && !defined(T9CSArabic)
#define T9CSArabic COLLATING_SEQUENCE_ARABIC
#endif
#if defined(COLLATING_SEQUENCE_CYRILLIC) && !defined(T9CSCyrillic)
#define T9CSCyrillic COLLATING_SEQUENCE_CYRILLIC
#endif
#if defined(COLLATING_SEQUENCE_GREEK) && !defined(T9CSGreek)
#define T9CSGreek COLLATING_SEQUENCE_GREEK
#endif
#if defined(COLLATING_SEQUENCE_THAI) && !defined(T9CSThai)
#define T9CSThai COLLATING_SEQUENCE_THAI
#endif
#if defined(COLLATING_SEQUENCE_DEVANAGARI) && !defined(T9CSDevanagari)
#define T9CSDevanagari COLLATING_SEQUENCE_DEVANAGARI
#endif
#if defined(COLLATING_SEQUENCE_KOREAN_CHUN) && !defined(T9CSKoreanChun)
#define T9CSKoreanChun COLLATING_SEQUENCE_KOREAN_CHUN
#endif
#if defined(FARUDBPOINTER) && !defined(T9FARUDBPOINTER)
#define T9FARUDBPOINTER FARUDBPOINTER
#endif
#if defined(PLDBID_MASK) && !defined(T9PIDMASK)
#define T9PIDMASK PLDBID_MASK
#endif
#if defined(PLDBID_NONE) && !defined(T9PIDNone)
#define T9PIDNone PLDBID_NONE
#endif
#if defined(PLDBID_Arabic) && !defined(T9PIDArabic)
#define T9PIDArabic PLDBID_Arabic
#endif
#if defined(PLDBID_Bulgarian) && !defined(T9PIDBulgarian)
#define T9PIDBulgarian PLDBID_Bulgarian
#endif
#if defined(PLDBID_Catalan) && !defined(T9PIDCatalan)
#define T9PIDCatalan PLDBID_Catalan
#endif
#if defined(PLDBID_Chinese) && !defined(T9PIDChinese)
#define T9PIDChinese PLDBID_Chinese
#endif
#if defined(PLDBID_Czech) && !defined(T9PIDCzech)
#define T9PIDCzech PLDBID_Czech
#endif
#if defined(PLDBID_Danish) && !defined(T9PIDDanish)
#define T9PIDDanish PLDBID_Danish
#endif
#if defined(PLDBID_German) && !defined(T9PIDGerman)
#define T9PIDGerman PLDBID_German
#endif
#if defined(PLDBID_Greek) && !defined(T9PIDGreek)
#define T9PIDGreek PLDBID_Greek
#endif
#if defined(PLDBID_English) && !defined(T9PIDEnglish)
#define T9PIDEnglish PLDBID_English
#endif
#if defined(PLDBID_Spanish) && !defined(T9PIDSpanish)
#define T9PIDSpanish PLDBID_Spanish
#endif
#if defined(PLDBID_Finnish) && !defined(T9PIDFinnish)
#define T9PIDFinnish PLDBID_Finnish
#endif
#if defined(PLDBID_French) && !defined(T9PIDFrench)
#define T9PIDFrench PLDBID_French
#endif
#if defined(PLDBID_Hebrew) && !defined(T9PIDHebrew)
#define T9PIDHebrew PLDBID_Hebrew
#endif
#if defined(PLDBID_Hungarian) && !defined(T9PIDHungarian)
#define T9PIDHungarian PLDBID_Hungarian
#endif
#if defined(PLDBID_Icelandic) && !defined(T9PIDIcelandic)
#define T9PIDIcelandic PLDBID_Icelandic
#endif
#if defined(PLDBID_Italian) && !defined(T9PIDItalian)
#define T9PIDItalian PLDBID_Italian
#endif
#if defined(PLDBID_Japanese) && !defined(T9PIDJapanese)
#define T9PIDJapanese PLDBID_Japanese
#endif
#if defined(PLDBID_Korean) && !defined(T9PIDKorean)
#define T9PIDKorean PLDBID_Korean
#endif
#if defined(PLDBID_Dutch) && !defined(T9PIDDutch)
#define T9PIDDutch PLDBID_Dutch
#endif
#if defined(PLDBID_Norwegian) && !defined(T9PIDNorwegian)
#define T9PIDNorwegian PLDBID_Norwegian
#endif
#if defined(PLDBID_Polish) && !defined(T9PIDPolish)
#define T9PIDPolish PLDBID_Polish
#endif
#if defined(PLDBID_Portuguese) && !defined(T9PIDPortuguese)
#define T9PIDPortuguese PLDBID_Portuguese
#endif
#if defined(PLDBID_RhaetoRomance) && !defined(T9PIDRhaetoRomance)
#define T9PIDRhaetoRomance PLDBID_RhaetoRomance
#endif
#if defined(PLDBID_Romanian) && !defined(T9PIDRomanian)
#define T9PIDRomanian PLDBID_Romanian
#endif
#if defined(PLDBID_Russian) && !defined(T9PIDRussian)
#define T9PIDRussian PLDBID_Russian
#endif
#if defined(PLDBID_SerboCroatian) && !defined(T9PIDSerboCroatian)
#define T9PIDSerboCroatian PLDBID_SerboCroatian
#endif
#if defined(PLDBID_Slovak) && !defined(T9PIDSlovak)
#define T9PIDSlovak PLDBID_Slovak
#endif
#if defined(PLDBID_Albanian) && !defined(T9PIDAlbanian)
#define T9PIDAlbanian PLDBID_Albanian
#endif
#if defined(PLDBID_Swedish) && !defined(T9PIDSwedish)
#define T9PIDSwedish PLDBID_Swedish
#endif
#if defined(PLDBID_Thai) && !defined(T9PIDThai)
#define T9PIDThai PLDBID_Thai
#endif
#if defined(PLDBID_Turkish) && !defined(T9PIDTurkish)
#define T9PIDTurkish PLDBID_Turkish
#endif
#if defined(PLDBID_Urdu) && !defined(T9PIDUrdu)
#define T9PIDUrdu PLDBID_Urdu
#endif
#if defined(PLDBID_Indonesian) && !defined(T9PIDIndonesian)
#define T9PIDIndonesian PLDBID_Indonesian
#endif
#if defined(PLDBID_Ukrainian) && !defined(T9PIDUkrainian)
#define T9PIDUkrainian PLDBID_Ukrainian
#endif
#if defined(PLDBID_Byelorussian) && !defined(T9PIDByelorussian)
#define T9PIDByelorussian PLDBID_Byelorussian
#endif
#if defined(PLDBID_Slovenian) && !defined(T9PIDSlovenian)
#define T9PIDSlovenian PLDBID_Slovenian
#endif
#if defined(PLDBID_Estonian) && !defined(T9PIDEstonian)
#define T9PIDEstonian PLDBID_Estonian
#endif
#if defined(PLDBID_Latvian) && !defined(T9PIDLatvian)
#define T9PIDLatvian PLDBID_Latvian
#endif
#if defined(PLDBID_Lithuanian) && !defined(T9PIDLithuanian)
#define T9PIDLithuanian PLDBID_Lithuanian
#endif
#if defined(PLDBID_Maori) && !defined(T9PIDMaori)
#define T9PIDMaori PLDBID_Maori
#endif
#if defined(PLDBID_Farsi) && !defined(T9PIDFarsi)
#define T9PIDFarsi PLDBID_Farsi
#endif
#if defined(PLDBID_Vietnamese) && !defined(T9PIDVietnamese)
#define T9PIDVietnamese PLDBID_Vietnamese
#endif
#if defined(PLDBID_Laotian) && !defined(T9PIDLaotian)
#define T9PIDLaotian PLDBID_Laotian
#endif
#if defined(PLDBID_Kampuchean) && !defined(T9PIDKampuchean)
#define T9PIDKampuchean PLDBID_Kampuchean
#endif
#if defined(PLDBID_Basque) && !defined(T9PIDBasque)
#define T9PIDBasque PLDBID_Basque
#endif
#if defined(PLDBID_Sorbian) && !defined(T9PIDSorbian)
#define T9PIDSorbian PLDBID_Sorbian
#endif
#if defined(PLDBID_Macedonian) && !defined(T9PIDMacedonian)
#define T9PIDMacedonian PLDBID_Macedonian
#endif
#if defined(PLDBID_Sutu) && !defined(T9PIDSutu)
#define T9PIDSutu PLDBID_Sutu
#endif
#if defined(PLDBID_Tsonga) && !defined(T9PIDTsonga)
#define T9PIDTsonga PLDBID_Tsonga
#endif
#if defined(PLDBID_Tswana) && !defined(T9PIDTswana)
#define T9PIDTswana PLDBID_Tswana
#endif
#if defined(PLDBID_Venda) && !defined(T9PIDVenda)
#define T9PIDVenda PLDBID_Venda
#endif
#if defined(PLDBID_Xhosa) && !defined(T9PIDXhosa)
#define T9PIDXhosa PLDBID_Xhosa
#endif
#if defined(PLDBID_Zulu) && !defined(T9PIDZulu)
#define T9PIDZulu PLDBID_Zulu
#endif
#if defined(PLDBID_Afrikaans) && !defined(T9PIDAfrikaans)
#define T9PIDAfrikaans PLDBID_Afrikaans
#endif
#if defined(PLDBID_Faeroese) && !defined(T9PIDFaeroese)
#define T9PIDFaeroese PLDBID_Faeroese
#endif
#if defined(PLDBID_Hindi) && !defined(T9PIDHindi)
#define T9PIDHindi PLDBID_Hindi
#endif
#if defined(PLDBID_Maltese) && !defined(T9PIDMaltese)
#define T9PIDMaltese PLDBID_Maltese
#endif
#if defined(PLDBID_Sami) && !defined(T9PIDSami)
#define T9PIDSami PLDBID_Sami
#endif
#if defined(PLDBID_ScotsGaelic) && !defined(T9PIDScotsGaelic)
#define T9PIDScotsGaelic PLDBID_ScotsGaelic
#endif
#if defined(PLDBID_Malay) && !defined(T9PIDMalay)
#define T9PIDMalay PLDBID_Malay
#endif
#if defined(PLDBID_Swahili) && !defined(T9PIDSwahili)
#define T9PIDSwahili PLDBID_Swahili
#endif
#if defined(PLDBID_Afar) && !defined(T9PIDAfar)
#define T9PIDAfar PLDBID_Afar
#endif
#if defined(PLDBID_Abkhazian) && !defined(T9PIDAbkhazian)
#define T9PIDAbkhazian PLDBID_Abkhazian
#endif
#if defined(PLDBID_Amharic) && !defined(T9PIDAmharic)
#define T9PIDAmharic PLDBID_Amharic
#endif
#if defined(PLDBID_Assamese) && !defined(T9PIDAssamese)
#define T9PIDAssamese PLDBID_Assamese
#endif
#if defined(PLDBID_Aymara) && !defined(T9PIDAymara)
#define T9PIDAymara PLDBID_Aymara
#endif
#if defined(PLDBID_Azerbaijani) && !defined(T9PIDAzerbaijani)
#define T9PIDAzerbaijani PLDBID_Azerbaijani
#endif
#if defined(PLDBID_Bashkir) && !defined(T9PIDBashkir)
#define T9PIDBashkir PLDBID_Bashkir
#endif
#if defined(PLDBID_Bihari) && !defined(T9PIDBihari)
#define T9PIDBihari PLDBID_Bihari
#endif
#if defined(PLDBID_Bislama) && !defined(T9PIDBislama)
#define T9PIDBislama PLDBID_Bislama
#endif
#if defined(PLDBID_Bengali) && !defined(T9PIDBengali)
#define T9PIDBengali PLDBID_Bengali
#endif
#if defined(PLDBID_Tibetan) && !defined(T9PIDTibetan)
#define T9PIDTibetan PLDBID_Tibetan
#endif
#if defined(PLDBID_Breton) && !defined(T9PIDBreton)
#define T9PIDBreton PLDBID_Breton
#endif
#if defined(PLDBID_Corsican) && !defined(T9PIDCorsican)
#define T9PIDCorsican PLDBID_Corsican
#endif
#if defined(PLDBID_Welsh) && !defined(T9PIDWelsh)
#define T9PIDWelsh PLDBID_Welsh
#endif
#if defined(PLDBID_Bhutani) && !defined(T9PIDBhutani)
#define T9PIDBhutani PLDBID_Bhutani
#endif
#if defined(PLDBID_Esperanto) && !defined(T9PIDEsperanto)
#define T9PIDEsperanto PLDBID_Esperanto
#endif
#if defined(PLDBID_Fiji) && !defined(T9PIDFiji)
#define T9PIDFiji PLDBID_Fiji
#endif
#if defined(PLDBID_Frisian) && !defined(T9PIDFrisian)
#define T9PIDFrisian PLDBID_Frisian
#endif
#if defined(PLDBID_Irish) && !defined(T9PIDIrish)
#define T9PIDIrish PLDBID_Irish
#endif
#if defined(PLDBID_Galician) && !defined(T9PIDGalician)
#define T9PIDGalician PLDBID_Galician
#endif
#if defined(PLDBID_Guarani) && !defined(T9PIDGuarani)
#define T9PIDGuarani PLDBID_Guarani
#endif
#if defined(PLDBID_Gujarati) && !defined(T9PIDGujarati)
#define T9PIDGujarati PLDBID_Gujarati
#endif
#if defined(PLDBID_Hausa) && !defined(T9PIDHausa)
#define T9PIDHausa PLDBID_Hausa
#endif
#if defined(PLDBID_Croatian) && !defined(T9PIDCroatian)
#define T9PIDCroatian PLDBID_Croatian
#endif
#if defined(PLDBID_Armenian) && !defined(T9PIDArmenian)
#define T9PIDArmenian PLDBID_Armenian
#endif
#if defined(PLDBID_Interlingua) && !defined(T9PIDInterlingua)
#define T9PIDInterlingua PLDBID_Interlingua
#endif
#if defined(PLDBID_Interlingue) && !defined(T9PIDInterlingue)
#define T9PIDInterlingue PLDBID_Interlingue
#endif
#if defined(PLDBID_Inupiak) && !defined(T9PIDInupiak)
#define T9PIDInupiak PLDBID_Inupiak
#endif
#if defined(PLDBID_Inuktitut) && !defined(T9PIDInuktitut)
#define T9PIDInuktitut PLDBID_Inuktitut
#endif
#if defined(PLDBID_Javanese) && !defined(T9PIDJavanese)
#define T9PIDJavanese PLDBID_Javanese
#endif
#if defined(PLDBID_Georgian) && !defined(T9PIDGeorgian)
#define T9PIDGeorgian PLDBID_Georgian
#endif
#if defined(PLDBID_Kazakh) && !defined(T9PIDKazakh)
#define T9PIDKazakh PLDBID_Kazakh
#endif
#if defined(PLDBID_Greenlandic) && !defined(T9PIDGreenlandic)
#define T9PIDGreenlandic PLDBID_Greenlandic
#endif
#if defined(PLDBID_Kannada) && !defined(T9PIDKannada)
#define T9PIDKannada PLDBID_Kannada
#endif
#if defined(PLDBID_Kashmiri) && !defined(T9PIDKashmiri)
#define T9PIDKashmiri PLDBID_Kashmiri
#endif
#if defined(PLDBID_Kurdish) && !defined(T9PIDKurdish)
#define T9PIDKurdish PLDBID_Kurdish
#endif
#if defined(PLDBID_Kirghiz) && !defined(T9PIDKirghiz)
#define T9PIDKirghiz PLDBID_Kirghiz
#endif
#if defined(PLDBID_Latin) && !defined(T9PIDLatin)
#define T9PIDLatin PLDBID_Latin
#endif
#if defined(PLDBID_Lingala) && !defined(T9PIDLingala)
#define T9PIDLingala PLDBID_Lingala
#endif
#if defined(PLDBID_Malagasy) && !defined(T9PIDMalagasy)
#define T9PIDMalagasy PLDBID_Malagasy
#endif
#if defined(PLDBID_Malayalam) && !defined(T9PIDMalayalam)
#define T9PIDMalayalam PLDBID_Malayalam
#endif
#if defined(PLDBID_Mongolian) && !defined(T9PIDMongolian)
#define T9PIDMongolian PLDBID_Mongolian
#endif
#if defined(PLDBID_Moldavian) && !defined(T9PIDMoldavian)
#define T9PIDMoldavian PLDBID_Moldavian
#endif
#if defined(PLDBID_Marathi) && !defined(T9PIDMarathi)
#define T9PIDMarathi PLDBID_Marathi
#endif
#if defined(PLDBID_Burmese) && !defined(T9PIDBurmese)
#define T9PIDBurmese PLDBID_Burmese
#endif
#if defined(PLDBID_Nauru) && !defined(T9PIDNauru)
#define T9PIDNauru PLDBID_Nauru
#endif
#if defined(PLDBID_Nepali) && !defined(T9PIDNepali)
#define T9PIDNepali PLDBID_Nepali
#endif
#if defined(PLDBID_Occitan) && !defined(T9PIDOccitan)
#define T9PIDOccitan PLDBID_Occitan
#endif
#if defined(PLDBID_Oromo) && !defined(T9PIDOromo)
#define T9PIDOromo PLDBID_Oromo
#endif
#if defined(PLDBID_Oriya) && !defined(T9PIDOriya)
#define T9PIDOriya PLDBID_Oriya
#endif
#if defined(PLDBID_Punjabi) && !defined(T9PIDPunjabi)
#define T9PIDPunjabi PLDBID_Punjabi
#endif
#if defined(PLDBID_Pashto) && !defined(T9PIDPashto)
#define T9PIDPashto PLDBID_Pashto
#endif
#if defined(PLDBID_Quechua) && !defined(T9PIDQuechua)
#define T9PIDQuechua PLDBID_Quechua
#endif
#if defined(PLDBID_Kirundi) && !defined(T9PIDKirundi)
#define T9PIDKirundi PLDBID_Kirundi
#endif
#if defined(PLDBID_Kiyarwanda) && !defined(T9PIDKiyarwanda)
#define T9PIDKiyarwanda PLDBID_Kiyarwanda
#endif
#if defined(PLDBID_Sanskrit) && !defined(T9PIDSanskrit)
#define T9PIDSanskrit PLDBID_Sanskrit
#endif
#if defined(PLDBID_Sindhi) && !defined(T9PIDSindhi)
#define T9PIDSindhi PLDBID_Sindhi
#endif
#if defined(PLDBID_Sangho) && !defined(T9PIDSangho)
#define T9PIDSangho PLDBID_Sangho
#endif
#if defined(PLDBID_Singhalese) && !defined(T9PIDSinghalese)
#define T9PIDSinghalese PLDBID_Singhalese
#endif
#if defined(PLDBID_Samoan) && !defined(T9PIDSamoan)
#define T9PIDSamoan PLDBID_Samoan
#endif
#if defined(PLDBID_Shona) && !defined(T9PIDShona)
#define T9PIDShona PLDBID_Shona
#endif
#if defined(PLDBID_Somali) && !defined(T9PIDSomali)
#define T9PIDSomali PLDBID_Somali
#endif
#if defined(PLDBID_Serbian) && !defined(T9PIDSerbian)
#define T9PIDSerbian PLDBID_Serbian
#endif
#if defined(PLDBID_Siswati) && !defined(T9PIDSiswati)
#define T9PIDSiswati PLDBID_Siswati
#endif
#if defined(PLDBID_Sesotho) && !defined(T9PIDSesotho)
#define T9PIDSesotho PLDBID_Sesotho
#endif
#if defined(PLDBID_Sudanese) && !defined(T9PIDSudanese)
#define T9PIDSudanese PLDBID_Sudanese
#endif
#if defined(PLDBID_Tamil) && !defined(T9PIDTamil)
#define T9PIDTamil PLDBID_Tamil
#endif
#if defined(PLDBID_Telugu) && !defined(T9PIDTelugu)
#define T9PIDTelugu PLDBID_Telugu
#endif
#if defined(PLDBID_Tajik) && !defined(T9PIDTajik)
#define T9PIDTajik PLDBID_Tajik
#endif
#if defined(PLDBID_Tigrinya) && !defined(T9PIDTigrinya)
#define T9PIDTigrinya PLDBID_Tigrinya
#endif
#if defined(PLDBID_Turkmen) && !defined(T9PIDTurkmen)
#define T9PIDTurkmen PLDBID_Turkmen
#endif
#if defined(PLDBID_Tagalog) && !defined(T9PIDTagalog)
#define T9PIDTagalog PLDBID_Tagalog
#endif
#if defined(PLDBID_Setswana) && !defined(T9PIDSetswana)
#define T9PIDSetswana PLDBID_Setswana
#endif
#if defined(PLDBID_Tonga) && !defined(T9PIDTonga)
#define T9PIDTonga PLDBID_Tonga
#endif
#if defined(PLDBID_Tatar) && !defined(T9PIDTatar)
#define T9PIDTatar PLDBID_Tatar
#endif
#if defined(PLDBID_Twi) && !defined(T9PIDTwi)
#define T9PIDTwi PLDBID_Twi
#endif
#if defined(PLDBID_Uigur) && !defined(T9PIDUigur)
#define T9PIDUigur PLDBID_Uigur
#endif
#if defined(PLDBID_Uzbek) && !defined(T9PIDUzbek)
#define T9PIDUzbek PLDBID_Uzbek
#endif
#if defined(PLDBID_Volapuk) && !defined(T9PIDVolapuk)
#define T9PIDVolapuk PLDBID_Volapuk
#endif
#if defined(PLDBID_Wolof) && !defined(T9PIDWolof)
#define T9PIDWolof PLDBID_Wolof
#endif
#if defined(PLDBID_Yiddish) && !defined(T9PIDYiddish)
#define T9PIDYiddish PLDBID_Yiddish
#endif
#if defined(PLDBID_Yorouba) && !defined(T9PIDYorouba)
#define T9PIDYorouba PLDBID_Yorouba
#endif
#if defined(PLDBID_Zhuang) && !defined(T9PIDZhuang)
#define T9PIDZhuang PLDBID_Zhuang
#endif
#if defined(PLDBID_Null) && !defined(T9PIDNull)
#define T9PIDNull PLDBID_Null
#endif
#if defined(SLDBID_MASK) && !defined(T9SIDMASK)
#define T9SIDMASK SLDBID_MASK
#endif
#if defined(SLDBID_NONE) && !defined(T9SIDNone)
#define T9SIDNone SLDBID_NONE
#endif
#if defined(SLDBID_DEFAULT) && !defined(T9SIDDEFAULT)
#define T9SIDDEFAULT SLDBID_DEFAULT
#endif
#if defined(SLDBID_ChineseTraditional) && !defined(T9SIDChineseTraditional)
#define T9SIDChineseTraditional SLDBID_ChineseTraditional
#endif
#if defined(SLDBID_ChineseSimplified) && !defined(T9SIDChineseSimplified)
#define T9SIDChineseSimplified SLDBID_ChineseSimplified
#endif
#if defined(SLDBID_KoreanSyllable) && !defined(T9SIDKoreanSyllable)
#define T9SIDKoreanSyllable SLDBID_KoreanSyllable
#endif
#if defined(SLDBID_KoreanCHUN) && !defined(T9SIDKoreanChun)
#define T9SIDKoreanChun SLDBID_KoreanCHUN
#endif
#if defined(SC_ISO_Latin1) && !defined(T9SCLatin1)
#define T9SCLatin1 SC_ISO_Latin1
#endif
#if defined(SC_ISO_Latin2) && !defined(T9SCLatin2)
#define T9SCLatin2 SC_ISO_Latin2
#endif
#if defined(SC_ISO_Latin3) && !defined(T9SCLatin3)
#define T9SCLatin3 SC_ISO_Latin3
#endif
#if defined(SC_ISO_Latin4) && !defined(T9SCLatin4)
#define T9SCLatin4 SC_ISO_Latin4
#endif
#if defined(SC_ISO_Cyrillic) && !defined(T9SCCyrillic)
#define T9SCCyrillic SC_ISO_Cyrillic
#endif
#if defined(SC_ISO_Arabic) && !defined(T9SCArabic)
#define T9SCArabic SC_ISO_Arabic
#endif
#if defined(SC_ISO_Modern_Greek) && !defined(T9SCModernGreek)
#define T9SCModernGreek SC_ISO_Modern_Greek
#endif
#if defined(SC_ISO_Hebrew) && !defined(T9SCHebrew)
#define T9SCHebrew SC_ISO_Hebrew
#endif
#if defined(SC_ISO_Latin5) && !defined(T9SCLatin5)
#define T9SCLatin5 SC_ISO_Latin5
#endif
#if defined(SC_ISO_Latin6) && !defined(T9SCLatin6)
#define T9SCLatin6 SC_ISO_Latin6
#endif
#if defined(SC_XX11) && !defined(T9SCXX11)
#define T9SCXX11 SC_XX11
#endif
#if defined(SC_XX12) && !defined(T9SCXX12)
#define T9SCXX12 SC_XX12
#endif
#if defined(SC_XX13) && !defined(T9SCXX13)
#define T9SCXX13 SC_XX13
#endif
#if defined(SC_XX14) && !defined(T9SCXX14)
#define T9SCXX14 SC_XX14
#endif
#if defined(SC_Unicode) && !defined(T9SCUnicode)
#define T9SCUnicode SC_Unicode
#endif
#if defined(SC_XX16) && !defined(T9SCXX16)
#define T9SCXX16 SC_XX16
#endif
#if defined(SC_XX17) && !defined(T9SCXX17)
#define T9SCXX17 SC_XX17
#endif
#if defined(SC_XX18) && !defined(T9SCXX18)
#define T9SCXX18 SC_XX18
#endif
#if defined(SC_Japanese_JIS_H) && !defined(T9SCJapaneseJISH)
#define T9SCJapaneseJISH SC_Japanese_JIS_H
#endif
#if defined(SC_Japanese_JIS_K) && !defined(T9SCJapaneseJISK)
#define T9SCJapaneseJISK SC_Japanese_JIS_K
#endif
#if defined(SC_Japanese_SJIS_H) && !defined(T9SCJapaneseSJISH)
#define T9SCJapaneseSJISH SC_Japanese_SJIS_H
#endif
#if defined(SC_Japanese_SJIS_K) && !defined(T9SCJapaneseSJISK)
#define T9SCJapaneseSJISK SC_Japanese_SJIS_K
#endif
#if defined(SC_XX23) && !defined(T9SCXX23)
#define T9SCXX23 SC_XX23
#endif
#if defined(SC_XX24) && !defined(T9SCXX24)
#define T9SCXX24 SC_XX24
#endif
#if defined(SC_XX25) && !defined(T9SCXX25)
#define T9SCXX25 SC_XX25
#endif
#if defined(SC_XX26) && !defined(T9SCXX26)
#define T9SCXX26 SC_XX26
#endif
#if defined(SC_XX27) && !defined(T9SCXX27)
#define T9SCXX27 SC_XX27
#endif
#if defined(SC_XX28) && !defined(T9SCXX28)
#define T9SCXX28 SC_XX28
#endif
#if defined(SC_XX29) && !defined(T9SCXX29)
#define T9SCXX29 SC_XX29
#endif
#if defined(SC_XX30) && !defined(T9SCXX30)
#define T9SCXX30 SC_XX30
#endif
#if defined(SC_XX31) && !defined(T9SCXX31)
#define T9SCXX31 SC_XX31
#endif
#if defined(SC_XX32) && !defined(T9SCXX32)
#define T9SCXX32 SC_XX32
#endif
#if defined(SC_XX33) && !defined(T9SCXX33)
#define T9SCXX33 SC_XX33
#endif
#if defined(SC_XX34) && !defined(T9SCXX34)
#define T9SCXX34 SC_XX34
#endif
#if defined(SC_XX35) && !defined(T9SCXX35)
#define T9SCXX35 SC_XX35
#endif
#if defined(SC_XX36) && !defined(T9SCXX36)
#define T9SCXX36 SC_XX36
#endif
#if defined(SC_GSM) && !defined(T9SCGSM)
#define T9SCGSM SC_GSM
#endif
#if defined(SC_ARABIC_WINDOWS) && !defined(T9SCArabicWindows)
#define T9SCArabicWindows SC_ARABIC_WINDOWS
#endif
#if defined(SC_ISCII) && !defined(T9SCISCII)
#define T9SCISCII SC_ISCII
#endif
#if defined(SC_THAI_WINDOWS) && !defined(T9SCThaiWindows)
#define T9SCThaiWindows SC_THAI_WINDOWS
#endif
#if defined(SC_BOUNDS) && !defined(T9SCBOUNDS)
#define T9SCBOUNDS SC_BOUNDS
#endif
#if defined(T9UdbInfo) && !defined(T9AWUdbInfo)
#define T9AWUdbInfo T9UdbInfo
#endif
#if defined(T9MdbInfo) && !defined(T9AWMdbInfo)
#define T9AWMdbInfo T9MdbInfo
#endif
#if defined(T9DEFAULTUDBFENCE) && !defined(T9AWDEFAULTUDBFENCE)
#define T9AWDEFAULTUDBFENCE T9DEFAULTUDBFENCE
#endif
#if defined(T9MAXLDBOBJECTS) && !defined(T9AWMAXLDBOBJECTS)
#define T9AWMAXLDBOBJECTS T9MAXLDBOBJECTS
#endif
#if defined(T9MAXSELECTIONOBJECT) && !defined(T9AWMAXSELECTIONOBJECT)
#define T9AWMAXSELECTIONOBJECT T9MAXSELECTIONOBJECT
#endif
#if defined(T9MAXWORDSIZE) && !defined(T9AWMAXWORDSIZE)
#define T9AWMAXWORDSIZE T9MAXWORDSIZE
#endif
#if defined(MDBGETEXACTWORD) && !defined(T9AWMDBGETEXACTWORD)
#define T9AWMDBGETEXACTWORD MDBGETEXACTWORD
#endif
#if defined(MDBGETSTEMWORD) && !defined(T9AWMDBGETSTEMWORD)
#define T9AWMDBGETSTEMWORD MDBGETSTEMWORD
#endif
#if defined(T9AUX_KEYNUM) && !defined(T9AWAUXKEYNUM)
#define T9AWAUXKEYNUM T9AUX_KEYNUM
#endif
#if defined(T9AUX_SHIFTED) && !defined(T9AWAUXSHIFTED)
#define T9AWAUXSHIFTED T9AUX_SHIFTED
#endif
#if defined(T9MDBCALLBACK) && !defined(T9AWMDBCALLBACK)
#define T9AWMDBCALLBACK T9MDBCALLBACK
#endif
#if defined(T9CudbInfo) && !defined(T9CCUdbInfo)
#define T9CCUdbInfo T9CudbInfo
#endif
#if defined(T9CudbObj) && !defined(T9CCUdbObj)
#define T9CCUdbObj T9CudbObj
#endif
#if defined(T9GetCUDB) && !defined(T9CCUdbGet)
#define T9CCUdbGet T9GetCUDB
#endif
#if defined(T9AuxChineseInfo) && !defined(T9CCFieldInfo)
#define T9CCFieldInfo T9AuxChineseInfo
#endif
#if defined(T9SPELLBUFSIZE) && !defined(T9CCSPELLBUFMAXSIZE)
#define T9CCSPELLBUFMAXSIZE T9SPELLBUFSIZE
#endif
#if defined(T9MINCUDBSIZE) && !defined(T9CCUDBMINSIZE)
#define T9CCUDBMINSIZE T9MINCUDBSIZE
#endif
#if defined(T9DEFAULTPHRASECOMPFENCE) && !defined(T9CCDEFAULTPHRASECOMPFENCE)
#define T9CCDEFAULTPHRASECOMPFENCE T9DEFAULTPHRASECOMPFENCE
#endif
#if defined(T9CUDB_ACRONYM_MAXSIZE) && !defined(T9CCUDBACRONYMMAXSIZE)
#define T9CCUDBACRONYMMAXSIZE T9CUDB_ACRONYM_MAXSIZE
#endif
#if defined(T9CUDB_PHRASE_MAXSIZE) && !defined(T9CCUDBPHRASEMAXSIZE)
#define T9CCUDBPHRASEMAXSIZE T9CUDB_PHRASE_MAXSIZE
#endif
#if defined(T9CSTATEMORE) && !defined(T9CCSTATEMORE)
#define T9CCSTATEMORE T9CSTATEMORE
#endif
#if defined(T9CSTATESTROKE) && !defined(T9CCSTATESTROKE)
#define T9CCSTATESTROKE T9CSTATESTROKE
#endif
#if defined(T9CSTATEPHAMBIG) && !defined(T9CCSTATEPHAMBIG)
#define T9CCSTATEPHAMBIG T9CSTATEPHAMBIG
#endif
#if defined(T9CSTATEPHMULTI) && !defined(T9CCSTATEPHMULTI)
#define T9CCSTATEPHMULTI T9CSTATEPHMULTI
#endif
#if defined(T9CSTATEAUTOSPELL) && !defined(T9CCSTATEAUTOSPELL)
#define T9CCSTATEAUTOSPELL T9CSTATEAUTOSPELL
#endif
#if defined(T9CSTATEPHMTUPDATE) && !defined(T9CCSTATEPHMTUPDATE)
#define T9CCSTATEPHMTUPDATE T9CSTATEPHMTUPDATE
#endif
#if defined(T9CSTATECOMPONENTS) && !defined(T9CCSTATECOMPONENT)
#define T9CCSTATECOMPONENT T9CSTATECOMPONENTS
#endif
#if defined(T9CSTATECUDBSEARCHONLY) && !defined(T9CCSTATESEARCHUDBONLY)
#define T9CCSTATESEARCHUDBONLY T9CSTATECUDBSEARCHONLY
#endif
#if defined(T9CSTATEFUZZYPINYIN) && !defined(T9CCSTATEFUZZYPINYIN)
#define T9CCSTATEFUZZYPINYIN T9CSTATEFUZZYPINYIN
#endif
#if defined(T9CHINESE_SEARCH_ACRONYM) && !defined(T9CCUDBSEARCHACRONYM)
#define T9CCUDBSEARCHACRONYM T9CHINESE_SEARCH_ACRONYM
#endif
#if defined(T9CHINESE_SEARCH_PHRASE) && !defined(T9CCUDBSEARCHPHRASE)
#define T9CCUDBSEARCHPHRASE T9CHINESE_SEARCH_PHRASE
#endif
#if defined(T9CHINESE_SEARCH_STROKE) && !defined(T9CCUDBSEARCHSTROKE)
#define T9CCUDBSEARCHSTROKE T9CHINESE_SEARCH_STROKE
#endif
#if defined(T9CUDB_FORCEADD) && !defined(T9CCUDBFORCEADD)
#define T9CCUDBFORCEADD T9CUDB_FORCEADD
#endif
#if defined(T9CUDB_NORMALADD) && !defined(T9CCUDBNORMALADD)
#define T9CCUDBNORMALADD T9CUDB_NORMALADD
#endif
#if defined(T9CPREFSTATEMASK) && !defined(T9CCPREFMASK)
#define T9CCPREFMASK T9CPREFSTATEMASK
#endif
#if defined(T9CSTATEPHBITS) && !defined(T9CCSTATEPHBITS)
#define T9CCSTATEPHBITS T9CSTATEPHBITS
#endif
#if defined(T9CSTATEMODEBITS) && !defined(T9CCSTATEMODEBITS)
#define T9CCSTATEMODEBITS T9CSTATEMODEBITS
#endif
#if defined(T9CHINESEDBVERSIONLENGTH) && !defined(T9CCLDBVERSIONLENGTH)
#define T9CCLDBVERSIONLENGTH T9CHINESEDBVERSIONLENGTH
#endif
#if defined(T9CHINESEDATABLOCKS) && !defined(T9CCLDBBLOCKCOUNT)
#define T9CCLDBBLOCKCOUNT T9CHINESEDATABLOCKS
#endif
#if defined(T9CDBSTROKE) && !defined(T9CCLDBSTROKE)
#define T9CCLDBSTROKE T9CDBSTROKE
#endif
#if defined(T9CDBCOMPONENT) && !defined(T9CCLDBCOMPONENT)
#define T9CCLDBCOMPONENT T9CDBCOMPONENT
#endif
#if defined(T9CDBPINYIN) && !defined(T9CCLDBPINYIN)
#define T9CCLDBPINYIN T9CDBPINYIN
#endif
#if defined(T9CDBBPMF) && !defined(T9CCLDBBPMF)
#define T9CCLDBBPMF T9CDBBPMF
#endif
#if defined(T9CDBCONTEXT40) && !defined(T9CCLDBCONTEXT40)
#define T9CCLDBCONTEXT40 T9CDBCONTEXT40
#endif
#if defined(T9CDBCONTEXT20) && !defined(T9CCLDBCONTEXT20)
#define T9CCLDBCONTEXT20 T9CDBCONTEXT20
#endif
#if defined(T9CHN_HASMODULE) && !defined(T9CCLDBHASMODULE)
#define T9CCLDBHASMODULE T9CHN_HASMODULE
#endif
#if defined(CUDB_CTXTSEARCH_DEPTH_HIGH) && !defined(T9CCDYNCTXTSEARCHMAXDEPTH)
#define T9CCDYNCTXTSEARCHMAXDEPTH CUDB_CTXTSEARCH_DEPTH_HIGH
#endif
#if defined(T9CAUdbInfo) && !defined(T9CCAudbInfo)
#define T9CCAudbInfo T9CAUdbInfo
#endif
#if defined(T9AuxJapaneseInfo) && !defined(T9JWFieldInfo)
#define T9JWFieldInfo T9AuxJapaneseInfo
#endif
#if defined(T9GetJUDB_s) && !defined(T9JWUdbGet_s)
#define T9JWUdbGet_s T9GetJUDB_s
#endif
#if defined(T9JKEYDIACRITIC) && !defined(T9JWKEYDIACRITIC)
#define T9JWKEYDIACRITIC T9JKEYDIACRITIC
#endif
#if defined(T9JKEYSELECTNEXT) && !defined(T9JWKEYSELECTNEXT)
#define T9JWKEYSELECTNEXT T9JKEYSELECTNEXT
#endif
#if defined(T9JKEYSELECTPREV) && !defined(T9JWKEYSELECTPREV)
#define T9JWKEYSELECTPREV T9JKEYSELECTPREV
#endif
#if defined(T9JKEYCONVERTNEXT) && !defined(T9JWKEYCONVERTNEXT)
#define T9JWKEYCONVERTNEXT T9JKEYCONVERTNEXT
#endif
#if defined(T9JKEYCONVERTPREV) && !defined(T9JWKEYCONVERTPREV)
#define T9JWKEYCONVERTPREV T9JKEYCONVERTPREV
#endif
#if defined(T9JKEYCANCEL) && !defined(T9JWKEYCANCEL)
#define T9JWKEYCANCEL T9JKEYCANCEL
#endif
#if defined(T9JKEYOK) && !defined(T9JWKEYOK)
#define T9JWKEYOK T9JKEYOK
#endif
#if defined(T9JSTATEIDLE) && !defined(T9JWSTATEIDLE)
#define T9JWSTATEIDLE T9JSTATEIDLE
#endif
#if defined(T9JSTATEADDING) && !defined(T9JWSTATEADDING)
#define T9JWSTATEADDING T9JSTATEADDING
#endif
#if defined(T9JSTATESELECT) && !defined(T9JWSTATESELECT)
#define T9JWSTATESELECT T9JSTATESELECT
#endif
#if defined(T9JSTATECONVERT) && !defined(T9JWSTATECONVERT)
#define T9JWSTATECONVERT T9JSTATECONVERT
#endif
#if defined(T9JSTATESPECIFIC) && !defined(T9JWSTATESPECIFIC)
#define T9JWSTATESPECIFIC T9JSTATESPECIFIC
#endif
#if defined(T9JSTATERESPELL) && !defined(T9JWSTATERESPELL)
#define T9JWSTATERESPELL T9JSTATERESPELL
#endif
#if defined(T9JSTATECONVPAGE) && !defined(T9JWSTATECONVPAGE)
#define T9JWSTATECONVPAGE T9JSTATECONVPAGE
#endif
#if defined(J_IDLE_STATE) && !defined(T9JWIDLESTATE)
#define T9JWIDLESTATE J_IDLE_STATE
#endif
#if defined(J_ADDING_STATE) && !defined(T9JWADDINGSTATE)
#define T9JWADDINGSTATE J_ADDING_STATE
#endif
#if defined(J_SELECT_STATE) && !defined(T9JWSELECTSTATE)
#define T9JWSELECTSTATE J_SELECT_STATE
#endif
#if defined(J_CONVERT_STATE) && !defined(T9JWCONVERTSTATE)
#define T9JWCONVERTSTATE J_CONVERT_STATE
#endif
#if defined(J_SPECIFIC_STATE) && !defined(T9JWSPECIFICSTATE)
#define T9JWSPECIFICSTATE J_SPECIFIC_STATE
#endif
#if defined(J_RESPELL_STATE) && !defined(T9JWRESPELLSTATE)
#define T9JWRESPELLSTATE J_RESPELL_STATE
#endif
#if defined(J_CONVPAGE_STATE) && !defined(T9JWCONVPAGESTATE)
#define T9JWCONVPAGESTATE J_CONVPAGE_STATE
#endif
#if defined(J_QSTN_1D) && !defined(T9JWQSTN1D)
#define T9JWQSTN1D J_QSTN_1D
#endif
#if defined(J_QSTN_2D) && !defined(T9JWQSTN2D)
#define T9JWQSTN2D J_QSTN_2D
#endif
#if defined(JF_KATAKANA) && !defined(T9JWFKATAKANA)
#define T9JWFKATAKANA JF_KATAKANA
#endif
#if defined(JF_JUDB_NO_GC) && !defined(T9JWFJUDBNOGC)
#define T9JWFJUDBNOGC JF_JUDB_NO_GC
#endif
#if defined(JKEY_EXPLICIT) && !defined(T9JWKEYEXPLICIT)
#define T9JWKEYEXPLICIT JKEY_EXPLICIT
#endif
#if defined(JKEY_AMBIG) && !defined(T9JWKEYAMBIG)
#define T9JWKEYAMBIG JKEY_AMBIG
#endif
#if defined(JKEY_VAL) && !defined(T9JWKEYVAL)
#define T9JWKEYVAL JKEY_VAL
#endif
#if defined(JKEY_T9_VAL) && !defined(T9JWKEYT9VAL)
#define T9JWKEYT9VAL JKEY_T9_VAL
#endif
#if defined(ADDMID_IDLE) && !defined(T9JWADDMIDIDLE)
#define T9JWADDMIDIDLE ADDMID_IDLE
#endif
#if defined(ADDMID_YOMI_MODE) && !defined(T9JWADDMIDYOMIMODE)
#define T9JWADDMIDYOMIMODE ADDMID_YOMI_MODE
#endif
#if defined(ADDMID_MIDASHIGO_MODE) && !defined(T9JWADDMIDMIDASHIGOMODE)
#define T9JWADDMIDMIDASHIGOMODE ADDMID_MIDASHIGO_MODE
#endif
#if defined(ADDMID_DELETE) && !defined(T9JWADDMIDDELETE)
#define T9JWADDMIDDELETE ADDMID_DELETE
#endif
#if defined(ADDMID_DELETEALL) && !defined(T9JWADDMIDDELETEALL)
#define T9JWADDMIDDELETEALL ADDMID_DELETEALL
#endif
#if defined(EMI_ROMAJI_LAST) && !defined(T9JWEMIROMAJILAST)
#define T9JWEMIROMAJILAST EMI_ROMAJI_LAST
#endif
#if defined(EMI_ROMAJI_2ND_LAST) && !defined(T9JWEMIROMAJI2NDLAST)
#define T9JWEMIROMAJI2NDLAST EMI_ROMAJI_2ND_LAST
#endif
#if defined(EMI_ROMAJI_3RD_LAST) && !defined(T9JWEMIROMAJI3RDLAST)
#define T9JWEMIROMAJI3RDLAST EMI_ROMAJI_3RD_LAST
#endif
#if defined(EMI_ZENK_LAST) && !defined(T9JWEMIZENKLAST)
#define T9JWEMIZENKLAST EMI_ZENK_LAST
#endif
#if defined(EMI_ZENK_2ND_LAST) && !defined(T9JWEMIZENK2NDLAST)
#define T9JWEMIZENK2NDLAST EMI_ZENK_2ND_LAST
#endif
#if defined(EMI_ZENK_3RD_LAST) && !defined(T9JWEMIZENK3RDLAST)
#define T9JWEMIZENK3RDLAST EMI_ZENK_3RD_LAST
#endif
#if defined(EMI_HANK_LAST) && !defined(T9JWEMIHANKLAST)
#define T9JWEMIHANKLAST EMI_HANK_LAST
#endif
#if defined(EMI_HANK_2ND_LAST) && !defined(T9JWEMIHANK2NDLAST)
#define T9JWEMIHANK2NDLAST EMI_HANK_2ND_LAST
#endif
#if defined(EMI_HANK_3RD_LAST) && !defined(T9JWEMIHANK3RDLAST)
#define T9JWEMIHANK3RDLAST EMI_HANK_3RD_LAST
#endif
#if defined(EMI_DEFAULTS) && !defined(T9JWEMIDEFAULTS)
#define T9JWEMIDEFAULTS EMI_DEFAULTS
#endif
#if defined(EMI_NONE) && !defined(T9JWEMINONE)
#define T9JWEMINONE EMI_NONE
#endif
#if defined(T9EXPLKEY1) && !defined(T9JWEXPLKEY1)
#define T9JWEXPLKEY1 T9EXPLKEY1
#endif
#if defined(T9EXPLKEY2) && !defined(T9JWEXPLKEY2)
#define T9JWEXPLKEY2 T9EXPLKEY2
#endif
#if defined(T9EXPLKEY3) && !defined(T9JWEXPLKEY3)
#define T9JWEXPLKEY3 T9EXPLKEY3
#endif
#if defined(T9EXPLKEY4) && !defined(T9JWEXPLKEY4)
#define T9JWEXPLKEY4 T9EXPLKEY4
#endif
#if defined(T9EXPLKEY5) && !defined(T9JWEXPLKEY5)
#define T9JWEXPLKEY5 T9EXPLKEY5
#endif
#if defined(T9EXPLKEY6) && !defined(T9JWEXPLKEY6)
#define T9JWEXPLKEY6 T9EXPLKEY6
#endif
#if defined(T9EXPLKEY7) && !defined(T9JWEXPLKEY7)
#define T9JWEXPLKEY7 T9EXPLKEY7
#endif
#if defined(T9EXPLKEY8) && !defined(T9JWEXPLKEY8)
#define T9JWEXPLKEY8 T9EXPLKEY8
#endif
#if defined(T9EXPLKEY9) && !defined(T9JWEXPLKEY9)
#define T9JWEXPLKEY9 T9EXPLKEY9
#endif
#if defined(T9EXPLKEY0) && !defined(T9JWEXPLKEY0)
#define T9JWEXPLKEY0 T9EXPLKEY0
#endif
#if defined(T9EXPLKEY1_SM_VOWELS) && !defined(T9JWEXPLKEY1SMVOWELS)
#define T9JWEXPLKEY1SMVOWELS T9EXPLKEY1_SM_VOWELS
#endif
#if defined(T9EXPLKEY1_1D) && !defined(T9JWEXPLKEY11D)
#define T9JWEXPLKEY11D T9EXPLKEY1_1D
#endif
#if defined(T9EXPLKEY2_1D) && !defined(T9JWEXPLKEY21D)
#define T9JWEXPLKEY21D T9EXPLKEY2_1D
#endif
#if defined(T9EXPLKEY3_1D) && !defined(T9JWEXPLKEY31D)
#define T9JWEXPLKEY31D T9EXPLKEY3_1D
#endif
#if defined(T9EXPLKEY4_1D) && !defined(T9JWEXPLKEY41D)
#define T9JWEXPLKEY41D T9EXPLKEY4_1D
#endif
#if defined(T9EXPLKEY6_1D) && !defined(T9JWEXPLKEY61D)
#define T9JWEXPLKEY61D T9EXPLKEY6_1D
#endif
#if defined(T9EXPLKEY6_2D) && !defined(T9JWEXPLKEY62D)
#define T9JWEXPLKEY62D T9EXPLKEY6_2D
#endif
#endif /* #ifndef T9NAMES1_H */
