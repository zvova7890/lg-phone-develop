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
;**     FileName: t9names2.h                                                  **
;**                                                                           **
;**  Description: Compatibility Header File defining new names by old         **
;**                                                                           **
;**  Version:	  7.3                                                         **
;*******************************************************************************
;******************************************************************************/
#ifndef T9NAMES2_H
#define T9NAMES2_H 1
#if !defined(T9CTRLSETWORDCOMPLETION)
#define T9CTRLSETWORDCOMPLETION T9CTRLSETUDBCOMPLETION
#endif
#if !defined(T9CTRLCLRWORDCOMPLETION)
#define T9CTRLCLRWORDCOMPLETION T9CTRLCLRUDBCOMPLETION
#endif
#if !defined(T9REQSPELLSYM)
#define T9REQSPELLSYM T9REQMULTITAPSYM
#endif
#if !defined(T9STATESPELL)
#define T9STATESPELL T9STATEMULTITAP
#endif
#if !defined(T9STATEEXTSPELL)
#define T9STATEEXTSPELL T9STATEEXTMULTITAP
#endif
#if !defined(T9STATESPELLMASK)
#define T9STATESPELLMASK T9STATEMULTITAPMASK
#endif
#if !defined(T9STATEEXTSPELLMASK)
#define T9STATEEXTSPELLMASK T9STATEEXTMULTITAPMASK
#endif
#if !defined(SPELL_MODE)
#define SPELL_MODE T9MULTITAPMODE
#endif
#if !defined(EXTSPELL_MODE)
#define EXTSPELL_MODE T9EXTMULTITAPMODE
#endif
#if !defined(T9RDB_ON)
#define T9RDB_ON T9AWRDBON
#endif
#if !defined(AMBIG_MODE)
#define AMBIG_MODE T9AMBIGMODE
#endif
#if !defined(SHIFT_MODE)
#define SHIFT_MODE T9SHIFTMODE
#endif
#if !defined(CAPSLOCK_MODE)
#define CAPSLOCK_MODE T9CAPSLOCKMODE
#endif
#if !defined(INSERT_MODE)
#define INSERT_MODE T9INSERTMODE
#endif
#if !defined(T9AUX_KEYNUM)
#define T9AUX_KEYNUM T9AUXKEYNUM
#endif
#if !defined(T9AUX_SHIFTED)
#define T9AUX_SHIFTED T9AUXSHIFTED
#endif
#if !defined(sSpellSymbol)
#define sSpellSymbol sMultitapSymbol
#endif
#if !defined(T9SNUM) && defined(T9INT)
#define T9SNUM T9INT
#endif
#if !defined(T9NUM) && defined(T9UINT)
#define T9NUM T9UINT
#endif
#if !defined(CHINESE_T9) && defined(T9CHINESE)
#define CHINESE_T9 T9CHINESE
#endif
#if !defined(KOREAN_T9) && defined(T9KOREAN)
#define KOREAN_T9 T9KOREAN
#endif
#if !defined(JAPANESE_T9) && defined(T9JAPANESE)
#define JAPANESE_T9 T9JAPANESE
#endif
#if !defined(WORD_API) && defined(T9WORDAPI)
#define WORD_API T9WORDAPI
#endif
#if !defined(TXTFILLSYM) && defined(T9TXTFILLSYM)
#define TXTFILLSYM T9TXTFILLSYM
#endif
#if !defined(KOREAN_T9) && defined(T9KOREAN)
#define KOREAN_T9 T9KOREAN
#endif
#if !defined(FARCALL) && defined(T9FARCALL)
#define FARCALL T9FARCALL
#endif
#if !defined(FARDATA) && defined(T9FARDATA)
#define FARDATA T9FARDATA
#endif
#if !defined(NEARCALL) && defined(T9NEARCALL)
#define NEARCALL T9NEARCALL
#endif
#if !defined(NEARDATA) && defined(T9NEARDATA)
#define NEARDATA T9NEARDATA
#endif
#if !defined(T9_MAX_DB_KEYS) && defined(T9MAXDBKEYS)
#define T9_MAX_DB_KEYS T9MAXDBKEYS
#endif
#if !defined(T9_MAX_TAP_KEYS) && defined(T9MAXTAPKEYS)
#define T9_MAX_TAP_KEYS T9MAXTAPKEYS
#endif
#if !defined(T9_MAX_TREES) && defined(T9MAXTREES)
#define T9_MAX_TREES T9MAXTREES
#endif
#if !defined(COLLATING_SEQUENCE_LATIN1) && defined(T9CSLatin1)
#define COLLATING_SEQUENCE_LATIN1 T9CSLatin1
#endif
#if !defined(COLLATING_SEQUENCE_GSM) && defined(T9CSGSM)
#define COLLATING_SEQUENCE_GSM T9CSGSM
#endif
#if !defined(COLLATING_SEQUENCE_LATINA) && defined(T9CSLatinA)
#define COLLATING_SEQUENCE_LATINA T9CSLatinA
#endif
#if !defined(COLLATING_SEQUENCE_LATINB) && defined(T9CSLatinB)
#define COLLATING_SEQUENCE_LATINB T9CSLatinB
#endif
#if !defined(COLLATING_SEQUENCE_DIACRITICS) && defined(T9CSDiacritics)
#define COLLATING_SEQUENCE_DIACRITICS T9CSDiacritics
#endif
#if !defined(COLLATING_SEQUENCE_HEBREW) && defined(T9CSHebrew)
#define COLLATING_SEQUENCE_HEBREW T9CSHebrew
#endif
#if !defined(COLLATING_SEQUENCE_GENERAL_PUNCTUATION) && defined(T9CSGeneralPunctuation)
#define COLLATING_SEQUENCE_GENERAL_PUNCTUATION T9CSGeneralPunctuation
#endif
#if !defined(COLLATING_SEQUENCE_CURRENCY_SYMBOLS) && defined(T9CSCurrencySymbols)
#define COLLATING_SEQUENCE_CURRENCY_SYMBOLS T9CSCurrencySymbols
#endif
#if !defined(COLLATING_SEQUENCE_ARABIC_ALTERNATE) && defined(T9CSArabicAlternate)
#define COLLATING_SEQUENCE_ARABIC_ALTERNATE T9CSArabicAlternate
#endif
#if !defined(COLLATING_SEQUENCE_CYRILLIC_EVEN) && defined(T9CSCyrillicEven)
#define COLLATING_SEQUENCE_CYRILLIC_EVEN T9CSCyrillicEven
#endif
#if !defined(COLLATING_SEQUENCE_GREEK_ALPHABETIC) && defined(T9CSGreekAlphabetic)
#define COLLATING_SEQUENCE_GREEK_ALPHABETIC T9CSGreekAlphabetic
#endif
#if !defined(COLLATING_SEQUENCE_THAI_AIS) && defined(T9CSThaiAIS)
#define COLLATING_SEQUENCE_THAI_AIS T9CSThaiAIS
#endif
#if !defined(COLLATING_SEQUENCE_THAI_ALTERNATE) && defined(T9CSThaiAlternate)
#define COLLATING_SEQUENCE_THAI_ALTERNATE T9CSThaiAlternate
#endif
#if !defined(COLLATING_SEQUENCE_THAI_HUTCHISON) && defined(T9CSThaiHutchison)
#define COLLATING_SEQUENCE_THAI_HUTCHISON T9CSThaiHutchison
#endif
#if !defined(COLLATING_SEQUENCE_DEVANAGARI_ALTERNATE) && defined(T9CSDevanagariAlternate)
#define COLLATING_SEQUENCE_DEVANAGARI_ALTERNATE T9CSDevanagariAlternate
#endif
#if !defined(COLLATING_SEQUENCE_ARABIC) && defined(T9CSArabic)
#define COLLATING_SEQUENCE_ARABIC T9CSArabic
#endif
#if !defined(COLLATING_SEQUENCE_CYRILLIC) && defined(T9CSCyrillic)
#define COLLATING_SEQUENCE_CYRILLIC T9CSCyrillic
#endif
#if !defined(COLLATING_SEQUENCE_GREEK) && defined(T9CSGreek)
#define COLLATING_SEQUENCE_GREEK T9CSGreek
#endif
#if !defined(COLLATING_SEQUENCE_THAI) && defined(T9CSThai)
#define COLLATING_SEQUENCE_THAI T9CSThai
#endif
#if !defined(COLLATING_SEQUENCE_DEVANAGARI) && defined(T9CSDevanagari)
#define COLLATING_SEQUENCE_DEVANAGARI T9CSDevanagari
#endif
#if !defined(COLLATING_SEQUENCE_KOREAN_CHUN) && defined(T9CSKoreanChun)
#define COLLATING_SEQUENCE_KOREAN_CHUN T9CSKoreanChun
#endif
#if !defined(FARUDBPOINTER) && defined(T9FARUDBPOINTER)
#define FARUDBPOINTER T9FARUDBPOINTER
#endif
#if !defined(PLDBID_MASK) && defined(T9PIDMASK)
#define PLDBID_MASK T9PIDMASK
#endif
#if !defined(PLDBID_NONE) && defined(T9PIDNone)
#define PLDBID_NONE T9PIDNone
#endif
#if !defined(PLDBID_Arabic) && defined(T9PIDArabic)
#define PLDBID_Arabic T9PIDArabic
#endif
#if !defined(PLDBID_Bulgarian) && defined(T9PIDBulgarian)
#define PLDBID_Bulgarian T9PIDBulgarian
#endif
#if !defined(PLDBID_Catalan) && defined(T9PIDCatalan)
#define PLDBID_Catalan T9PIDCatalan
#endif
#if !defined(PLDBID_Chinese) && defined(T9PIDChinese)
#define PLDBID_Chinese T9PIDChinese
#endif
#if !defined(PLDBID_Czech) && defined(T9PIDCzech)
#define PLDBID_Czech T9PIDCzech
#endif
#if !defined(PLDBID_Danish) && defined(T9PIDDanish)
#define PLDBID_Danish T9PIDDanish
#endif
#if !defined(PLDBID_German) && defined(T9PIDGerman)
#define PLDBID_German T9PIDGerman
#endif
#if !defined(PLDBID_Greek) && defined(T9PIDGreek)
#define PLDBID_Greek T9PIDGreek
#endif
#if !defined(PLDBID_English) && defined(T9PIDEnglish)
#define PLDBID_English T9PIDEnglish
#endif
#if !defined(PLDBID_Spanish) && defined(T9PIDSpanish)
#define PLDBID_Spanish T9PIDSpanish
#endif
#if !defined(PLDBID_Finnish) && defined(T9PIDFinnish)
#define PLDBID_Finnish T9PIDFinnish
#endif
#if !defined(PLDBID_French) && defined(T9PIDFrench)
#define PLDBID_French T9PIDFrench
#endif
#if !defined(PLDBID_Hebrew) && defined(T9PIDHebrew)
#define PLDBID_Hebrew T9PIDHebrew
#endif
#if !defined(PLDBID_Hungarian) && defined(T9PIDHungarian)
#define PLDBID_Hungarian T9PIDHungarian
#endif
#if !defined(PLDBID_Icelandic) && defined(T9PIDIcelandic)
#define PLDBID_Icelandic T9PIDIcelandic
#endif
#if !defined(PLDBID_Italian) && defined(T9PIDItalian)
#define PLDBID_Italian T9PIDItalian
#endif
#if !defined(PLDBID_Japanese) && defined(T9PIDJapanese)
#define PLDBID_Japanese T9PIDJapanese
#endif
#if !defined(PLDBID_Korean) && defined(T9PIDKorean)
#define PLDBID_Korean T9PIDKorean
#endif
#if !defined(PLDBID_Dutch) && defined(T9PIDDutch)
#define PLDBID_Dutch T9PIDDutch
#endif
#if !defined(PLDBID_Norwegian) && defined(T9PIDNorwegian)
#define PLDBID_Norwegian T9PIDNorwegian
#endif
#if !defined(PLDBID_Polish) && defined(T9PIDPolish)
#define PLDBID_Polish T9PIDPolish
#endif
#if !defined(PLDBID_Portuguese) && defined(T9PIDPortuguese)
#define PLDBID_Portuguese T9PIDPortuguese
#endif
#if !defined(PLDBID_RhaetoRomance) && defined(T9PIDRhaetoRomance)
#define PLDBID_RhaetoRomance T9PIDRhaetoRomance
#endif
#if !defined(PLDBID_Romanian) && defined(T9PIDRomanian)
#define PLDBID_Romanian T9PIDRomanian
#endif
#if !defined(PLDBID_Russian) && defined(T9PIDRussian)
#define PLDBID_Russian T9PIDRussian
#endif
#if !defined(PLDBID_SerboCroatian) && defined(T9PIDSerboCroatian)
#define PLDBID_SerboCroatian T9PIDSerboCroatian
#endif
#if !defined(PLDBID_Slovak) && defined(T9PIDSlovak)
#define PLDBID_Slovak T9PIDSlovak
#endif
#if !defined(PLDBID_Albanian) && defined(T9PIDAlbanian)
#define PLDBID_Albanian T9PIDAlbanian
#endif
#if !defined(PLDBID_Swedish) && defined(T9PIDSwedish)
#define PLDBID_Swedish T9PIDSwedish
#endif
#if !defined(PLDBID_Thai) && defined(T9PIDThai)
#define PLDBID_Thai T9PIDThai
#endif
#if !defined(PLDBID_Turkish) && defined(T9PIDTurkish)
#define PLDBID_Turkish T9PIDTurkish
#endif
#if !defined(PLDBID_Urdu) && defined(T9PIDUrdu)
#define PLDBID_Urdu T9PIDUrdu
#endif
#if !defined(PLDBID_Indonesian) && defined(T9PIDIndonesian)
#define PLDBID_Indonesian T9PIDIndonesian
#endif
#if !defined(PLDBID_Ukrainian) && defined(T9PIDUkrainian)
#define PLDBID_Ukrainian T9PIDUkrainian
#endif
#if !defined(PLDBID_Byelorussian) && defined(T9PIDByelorussian)
#define PLDBID_Byelorussian T9PIDByelorussian
#endif
#if !defined(PLDBID_Slovenian) && defined(T9PIDSlovenian)
#define PLDBID_Slovenian T9PIDSlovenian
#endif
#if !defined(PLDBID_Estonian) && defined(T9PIDEstonian)
#define PLDBID_Estonian T9PIDEstonian
#endif
#if !defined(PLDBID_Latvian) && defined(T9PIDLatvian)
#define PLDBID_Latvian T9PIDLatvian
#endif
#if !defined(PLDBID_Lithuanian) && defined(T9PIDLithuanian)
#define PLDBID_Lithuanian T9PIDLithuanian
#endif
#if !defined(PLDBID_Maori) && defined(T9PIDMaori)
#define PLDBID_Maori T9PIDMaori
#endif
#if !defined(PLDBID_Farsi) && defined(T9PIDFarsi)
#define PLDBID_Farsi T9PIDFarsi
#endif
#if !defined(PLDBID_Vietnamese) && defined(T9PIDVietnamese)
#define PLDBID_Vietnamese T9PIDVietnamese
#endif
#if !defined(PLDBID_Laotian) && defined(T9PIDLaotian)
#define PLDBID_Laotian T9PIDLaotian
#endif
#if !defined(PLDBID_Kampuchean) && defined(T9PIDKampuchean)
#define PLDBID_Kampuchean T9PIDKampuchean
#endif
#if !defined(PLDBID_Basque) && defined(T9PIDBasque)
#define PLDBID_Basque T9PIDBasque
#endif
#if !defined(PLDBID_Sorbian) && defined(T9PIDSorbian)
#define PLDBID_Sorbian T9PIDSorbian
#endif
#if !defined(PLDBID_Macedonian) && defined(T9PIDMacedonian)
#define PLDBID_Macedonian T9PIDMacedonian
#endif
#if !defined(PLDBID_Sutu) && defined(T9PIDSutu)
#define PLDBID_Sutu T9PIDSutu
#endif
#if !defined(PLDBID_Tsonga) && defined(T9PIDTsonga)
#define PLDBID_Tsonga T9PIDTsonga
#endif
#if !defined(PLDBID_Tswana) && defined(T9PIDTswana)
#define PLDBID_Tswana T9PIDTswana
#endif
#if !defined(PLDBID_Venda) && defined(T9PIDVenda)
#define PLDBID_Venda T9PIDVenda
#endif
#if !defined(PLDBID_Xhosa) && defined(T9PIDXhosa)
#define PLDBID_Xhosa T9PIDXhosa
#endif
#if !defined(PLDBID_Zulu) && defined(T9PIDZulu)
#define PLDBID_Zulu T9PIDZulu
#endif
#if !defined(PLDBID_Afrikaans) && defined(T9PIDAfrikaans)
#define PLDBID_Afrikaans T9PIDAfrikaans
#endif
#if !defined(PLDBID_Faeroese) && defined(T9PIDFaeroese)
#define PLDBID_Faeroese T9PIDFaeroese
#endif
#if !defined(PLDBID_Hindi) && defined(T9PIDHindi)
#define PLDBID_Hindi T9PIDHindi
#endif
#if !defined(PLDBID_Maltese) && defined(T9PIDMaltese)
#define PLDBID_Maltese T9PIDMaltese
#endif
#if !defined(PLDBID_Sami) && defined(T9PIDSami)
#define PLDBID_Sami T9PIDSami
#endif
#if !defined(PLDBID_ScotsGaelic) && defined(T9PIDScotsGaelic)
#define PLDBID_ScotsGaelic T9PIDScotsGaelic
#endif
#if !defined(PLDBID_Malay) && defined(T9PIDMalay)
#define PLDBID_Malay T9PIDMalay
#endif
#if !defined(PLDBID_Swahili) && defined(T9PIDSwahili)
#define PLDBID_Swahili T9PIDSwahili
#endif
#if !defined(PLDBID_Afar) && defined(T9PIDAfar)
#define PLDBID_Afar T9PIDAfar
#endif
#if !defined(PLDBID_Abkhazian) && defined(T9PIDAbkhazian)
#define PLDBID_Abkhazian T9PIDAbkhazian
#endif
#if !defined(PLDBID_Amharic) && defined(T9PIDAmharic)
#define PLDBID_Amharic T9PIDAmharic
#endif
#if !defined(PLDBID_Assamese) && defined(T9PIDAssamese)
#define PLDBID_Assamese T9PIDAssamese
#endif
#if !defined(PLDBID_Aymara) && defined(T9PIDAymara)
#define PLDBID_Aymara T9PIDAymara
#endif
#if !defined(PLDBID_Azerbaijani) && defined(T9PIDAzerbaijani)
#define PLDBID_Azerbaijani T9PIDAzerbaijani
#endif
#if !defined(PLDBID_Bashkir) && defined(T9PIDBashkir)
#define PLDBID_Bashkir T9PIDBashkir
#endif
#if !defined(PLDBID_Bihari) && defined(T9PIDBihari)
#define PLDBID_Bihari T9PIDBihari
#endif
#if !defined(PLDBID_Bislama) && defined(T9PIDBislama)
#define PLDBID_Bislama T9PIDBislama
#endif
#if !defined(PLDBID_Bengali) && defined(T9PIDBengali)
#define PLDBID_Bengali T9PIDBengali
#endif
#if !defined(PLDBID_Tibetan) && defined(T9PIDTibetan)
#define PLDBID_Tibetan T9PIDTibetan
#endif
#if !defined(PLDBID_Breton) && defined(T9PIDBreton)
#define PLDBID_Breton T9PIDBreton
#endif
#if !defined(PLDBID_Corsican) && defined(T9PIDCorsican)
#define PLDBID_Corsican T9PIDCorsican
#endif
#if !defined(PLDBID_Welsh) && defined(T9PIDWelsh)
#define PLDBID_Welsh T9PIDWelsh
#endif
#if !defined(PLDBID_Bhutani) && defined(T9PIDBhutani)
#define PLDBID_Bhutani T9PIDBhutani
#endif
#if !defined(PLDBID_Esperanto) && defined(T9PIDEsperanto)
#define PLDBID_Esperanto T9PIDEsperanto
#endif
#if !defined(PLDBID_Fiji) && defined(T9PIDFiji)
#define PLDBID_Fiji T9PIDFiji
#endif
#if !defined(PLDBID_Frisian) && defined(T9PIDFrisian)
#define PLDBID_Frisian T9PIDFrisian
#endif
#if !defined(PLDBID_Irish) && defined(T9PIDIrish)
#define PLDBID_Irish T9PIDIrish
#endif
#if !defined(PLDBID_Galician) && defined(T9PIDGalician)
#define PLDBID_Galician T9PIDGalician
#endif
#if !defined(PLDBID_Guarani) && defined(T9PIDGuarani)
#define PLDBID_Guarani T9PIDGuarani
#endif
#if !defined(PLDBID_Gujarati) && defined(T9PIDGujarati)
#define PLDBID_Gujarati T9PIDGujarati
#endif
#if !defined(PLDBID_Hausa) && defined(T9PIDHausa)
#define PLDBID_Hausa T9PIDHausa
#endif
#if !defined(PLDBID_Croatian) && defined(T9PIDCroatian)
#define PLDBID_Croatian T9PIDCroatian
#endif
#if !defined(PLDBID_Armenian) && defined(T9PIDArmenian)
#define PLDBID_Armenian T9PIDArmenian
#endif
#if !defined(PLDBID_Interlingua) && defined(T9PIDInterlingua)
#define PLDBID_Interlingua T9PIDInterlingua
#endif
#if !defined(PLDBID_Interlingue) && defined(T9PIDInterlingue)
#define PLDBID_Interlingue T9PIDInterlingue
#endif
#if !defined(PLDBID_Inupiak) && defined(T9PIDInupiak)
#define PLDBID_Inupiak T9PIDInupiak
#endif
#if !defined(PLDBID_Inuktitut) && defined(T9PIDInuktitut)
#define PLDBID_Inuktitut T9PIDInuktitut
#endif
#if !defined(PLDBID_Javanese) && defined(T9PIDJavanese)
#define PLDBID_Javanese T9PIDJavanese
#endif
#if !defined(PLDBID_Georgian) && defined(T9PIDGeorgian)
#define PLDBID_Georgian T9PIDGeorgian
#endif
#if !defined(PLDBID_Kazakh) && defined(T9PIDKazakh)
#define PLDBID_Kazakh T9PIDKazakh
#endif
#if !defined(PLDBID_Greenlandic) && defined(T9PIDGreenlandic)
#define PLDBID_Greenlandic T9PIDGreenlandic
#endif
#if !defined(PLDBID_Kannada) && defined(T9PIDKannada)
#define PLDBID_Kannada T9PIDKannada
#endif
#if !defined(PLDBID_Kashmiri) && defined(T9PIDKashmiri)
#define PLDBID_Kashmiri T9PIDKashmiri
#endif
#if !defined(PLDBID_Kurdish) && defined(T9PIDKurdish)
#define PLDBID_Kurdish T9PIDKurdish
#endif
#if !defined(PLDBID_Kirghiz) && defined(T9PIDKirghiz)
#define PLDBID_Kirghiz T9PIDKirghiz
#endif
#if !defined(PLDBID_Latin) && defined(T9PIDLatin)
#define PLDBID_Latin T9PIDLatin
#endif
#if !defined(PLDBID_Lingala) && defined(T9PIDLingala)
#define PLDBID_Lingala T9PIDLingala
#endif
#if !defined(PLDBID_Malagasy) && defined(T9PIDMalagasy)
#define PLDBID_Malagasy T9PIDMalagasy
#endif
#if !defined(PLDBID_Malayalam) && defined(T9PIDMalayalam)
#define PLDBID_Malayalam T9PIDMalayalam
#endif
#if !defined(PLDBID_Mongolian) && defined(T9PIDMongolian)
#define PLDBID_Mongolian T9PIDMongolian
#endif
#if !defined(PLDBID_Moldavian) && defined(T9PIDMoldavian)
#define PLDBID_Moldavian T9PIDMoldavian
#endif
#if !defined(PLDBID_Marathi) && defined(T9PIDMarathi)
#define PLDBID_Marathi T9PIDMarathi
#endif
#if !defined(PLDBID_Burmese) && defined(T9PIDBurmese)
#define PLDBID_Burmese T9PIDBurmese
#endif
#if !defined(PLDBID_Nauru) && defined(T9PIDNauru)
#define PLDBID_Nauru T9PIDNauru
#endif
#if !defined(PLDBID_Nepali) && defined(T9PIDNepali)
#define PLDBID_Nepali T9PIDNepali
#endif
#if !defined(PLDBID_Occitan) && defined(T9PIDOccitan)
#define PLDBID_Occitan T9PIDOccitan
#endif
#if !defined(PLDBID_Oromo) && defined(T9PIDOromo)
#define PLDBID_Oromo T9PIDOromo
#endif
#if !defined(PLDBID_Oriya) && defined(T9PIDOriya)
#define PLDBID_Oriya T9PIDOriya
#endif
#if !defined(PLDBID_Punjabi) && defined(T9PIDPunjabi)
#define PLDBID_Punjabi T9PIDPunjabi
#endif
#if !defined(PLDBID_Pashto) && defined(T9PIDPashto)
#define PLDBID_Pashto T9PIDPashto
#endif
#if !defined(PLDBID_Quechua) && defined(T9PIDQuechua)
#define PLDBID_Quechua T9PIDQuechua
#endif
#if !defined(PLDBID_Kirundi) && defined(T9PIDKirundi)
#define PLDBID_Kirundi T9PIDKirundi
#endif
#if !defined(PLDBID_Kiyarwanda) && defined(T9PIDKiyarwanda)
#define PLDBID_Kiyarwanda T9PIDKiyarwanda
#endif
#if !defined(PLDBID_Sanskrit) && defined(T9PIDSanskrit)
#define PLDBID_Sanskrit T9PIDSanskrit
#endif
#if !defined(PLDBID_Sindhi) && defined(T9PIDSindhi)
#define PLDBID_Sindhi T9PIDSindhi
#endif
#if !defined(PLDBID_Sangho) && defined(T9PIDSangho)
#define PLDBID_Sangho T9PIDSangho
#endif
#if !defined(PLDBID_Singhalese) && defined(T9PIDSinghalese)
#define PLDBID_Singhalese T9PIDSinghalese
#endif
#if !defined(PLDBID_Samoan) && defined(T9PIDSamoan)
#define PLDBID_Samoan T9PIDSamoan
#endif
#if !defined(PLDBID_Shona) && defined(T9PIDShona)
#define PLDBID_Shona T9PIDShona
#endif
#if !defined(PLDBID_Somali) && defined(T9PIDSomali)
#define PLDBID_Somali T9PIDSomali
#endif
#if !defined(PLDBID_Serbian) && defined(T9PIDSerbian)
#define PLDBID_Serbian T9PIDSerbian
#endif
#if !defined(PLDBID_Siswati) && defined(T9PIDSiswati)
#define PLDBID_Siswati T9PIDSiswati
#endif
#if !defined(PLDBID_Sesotho) && defined(T9PIDSesotho)
#define PLDBID_Sesotho T9PIDSesotho
#endif
#if !defined(PLDBID_Sudanese) && defined(T9PIDSudanese)
#define PLDBID_Sudanese T9PIDSudanese
#endif
#if !defined(PLDBID_Tamil) && defined(T9PIDTamil)
#define PLDBID_Tamil T9PIDTamil
#endif
#if !defined(PLDBID_Telugu) && defined(T9PIDTelugu)
#define PLDBID_Telugu T9PIDTelugu
#endif
#if !defined(PLDBID_Tajik) && defined(T9PIDTajik)
#define PLDBID_Tajik T9PIDTajik
#endif
#if !defined(PLDBID_Tigrinya) && defined(T9PIDTigrinya)
#define PLDBID_Tigrinya T9PIDTigrinya
#endif
#if !defined(PLDBID_Turkmen) && defined(T9PIDTurkmen)
#define PLDBID_Turkmen T9PIDTurkmen
#endif
#if !defined(PLDBID_Tagalog) && defined(T9PIDTagalog)
#define PLDBID_Tagalog T9PIDTagalog
#endif
#if !defined(PLDBID_Setswana) && defined(T9PIDSetswana)
#define PLDBID_Setswana T9PIDSetswana
#endif
#if !defined(PLDBID_Tonga) && defined(T9PIDTonga)
#define PLDBID_Tonga T9PIDTonga
#endif
#if !defined(PLDBID_Tatar) && defined(T9PIDTatar)
#define PLDBID_Tatar T9PIDTatar
#endif
#if !defined(PLDBID_Twi) && defined(T9PIDTwi)
#define PLDBID_Twi T9PIDTwi
#endif
#if !defined(PLDBID_Uigur) && defined(T9PIDUigur)
#define PLDBID_Uigur T9PIDUigur
#endif
#if !defined(PLDBID_Uzbek) && defined(T9PIDUzbek)
#define PLDBID_Uzbek T9PIDUzbek
#endif
#if !defined(PLDBID_Volapuk) && defined(T9PIDVolapuk)
#define PLDBID_Volapuk T9PIDVolapuk
#endif
#if !defined(PLDBID_Wolof) && defined(T9PIDWolof)
#define PLDBID_Wolof T9PIDWolof
#endif
#if !defined(PLDBID_Yiddish) && defined(T9PIDYiddish)
#define PLDBID_Yiddish T9PIDYiddish
#endif
#if !defined(PLDBID_Yorouba) && defined(T9PIDYorouba)
#define PLDBID_Yorouba T9PIDYorouba
#endif
#if !defined(PLDBID_Zhuang) && defined(T9PIDZhuang)
#define PLDBID_Zhuang T9PIDZhuang
#endif
#if !defined(PLDBID_Null) && defined(T9PIDNull)
#define PLDBID_Null T9PIDNull
#endif
#if !defined(SLDBID_MASK) && defined(T9SIDMASK)
#define SLDBID_MASK T9SIDMASK
#endif
#if !defined(SLDBID_NONE) && defined(T9SIDNone)
#define SLDBID_NONE T9SIDNone
#endif
#if !defined(SLDBID_DEFAULT) && defined(T9SIDDEFAULT)
#define SLDBID_DEFAULT T9SIDDEFAULT
#endif
#if !defined(SLDBID_ChineseTraditional)
#define SLDBID_ChineseTraditional T9SIDChineseTraditional
#endif
#if !defined(SLDBID_ChineseSimplified)
#define SLDBID_ChineseSimplified T9SIDChineseSimplified
#endif
#if !defined(SLDBID_KoreanSyllable)
#define SLDBID_KoreanSyllable T9SIDKoreanSyllable
#endif
#if !defined(SLDBID_KoreanCHUN)
#define SLDBID_KoreanCHUN T9SIDKoreanChun
#endif
#if !defined(SC_ISO_Latin1)
#define SC_ISO_Latin1 T9SCLatin1
#endif
#if !defined(SC_ISO_Latin2)
#define SC_ISO_Latin2 T9SCLatin2
#endif
#if !defined(SC_ISO_Latin3)
#define SC_ISO_Latin3 T9SCLatin3
#endif
#if !defined(SC_ISO_Latin4)
#define SC_ISO_Latin4 T9SCLatin4
#endif
#if !defined(SC_ISO_Cyrillic)
#define SC_ISO_Cyrillic T9SCCyrillic
#endif
#if !defined(SC_ISO_Arabic)
#define SC_ISO_Arabic T9SCArabic
#endif
#if !defined(SC_ISO_Modern_Greek)
#define SC_ISO_Modern_Greek T9SCModernGreek
#endif
#if !defined(SC_ISO_Hebrew)
#define SC_ISO_Hebrew T9SCHebrew
#endif
#if !defined(SC_ISO_Latin5)
#define SC_ISO_Latin5 T9SCLatin5
#endif
#if !defined(SC_ISO_Latin6)
#define SC_ISO_Latin6 T9SCLatin6
#endif
#if !defined(SC_XX11)
#define SC_XX11 T9SCXX11
#endif
#if !defined(SC_XX12)
#define SC_XX12 T9SCXX12
#endif
#if !defined(SC_XX13)
#define SC_XX13 T9SCXX13
#endif
#if !defined(SC_XX14)
#define SC_XX14 T9SCXX14
#endif
#if !defined(SC_Unicode)
#define SC_Unicode T9SCUnicode
#endif
#if !defined(SC_XX16)
#define SC_XX16 T9SCXX16
#endif
#if !defined(SC_XX17)
#define SC_XX17 T9SCXX17
#endif
#if !defined(SC_XX18)
#define SC_XX18 T9SCXX18
#endif
#if !defined(SC_Japanese_JIS_H)
#define SC_Japanese_JIS_H T9SCJapaneseJISH
#endif
#if !defined(SC_Japanese_JIS_K)
#define SC_Japanese_JIS_K T9SCJapaneseJISK
#endif
#if !defined(SC_Japanese_SJIS_H)
#define SC_Japanese_SJIS_H T9SCJapaneseSJISH
#endif
#if !defined(SC_Japanese_SJIS_K)
#define SC_Japanese_SJIS_K T9SCJapaneseSJISK
#endif
#if !defined(SC_XX23)
#define SC_XX23 T9SCXX23
#endif
#if !defined(SC_XX24)
#define SC_XX24 T9SCXX24
#endif
#if !defined(SC_XX25)
#define SC_XX25 T9SCXX25
#endif
#if !defined(SC_XX26)
#define SC_XX26 T9SCXX26
#endif
#if !defined(SC_XX27)
#define SC_XX27 T9SCXX27
#endif
#if !defined(SC_XX28)
#define SC_XX28 T9SCXX28
#endif
#if !defined(SC_XX29)
#define SC_XX29 T9SCXX29
#endif
#if !defined(SC_XX30)
#define SC_XX30 T9SCXX30
#endif
#if !defined(SC_XX31)
#define SC_XX31 T9SCXX31
#endif
#if !defined(SC_XX32)
#define SC_XX32 T9SCXX32
#endif
#if !defined(SC_XX33)
#define SC_XX33 T9SCXX33
#endif
#if !defined(SC_XX34)
#define SC_XX34 T9SCXX34
#endif
#if !defined(SC_XX35)
#define SC_XX35 T9SCXX35
#endif
#if !defined(SC_XX36)
#define SC_XX36 T9SCXX36
#endif
#if !defined(SC_GSM)
#define SC_GSM T9SCGSM
#endif
#if !defined(SC_ARABIC_WINDOWS)
#define SC_ARABIC_WINDOWS T9SCArabicWindows
#endif
#if !defined(SC_ISCII)
#define SC_ISCII T9SCISCII
#endif
#if !defined(SC_THAI_WINDOWS)
#define SC_THAI_WINDOWS T9SCThaiWindows
#endif
#if !defined(SC_BOUNDS)
#define SC_BOUNDS T9SCBOUNDS
#endif
#if !defined(T9UdbInfo)
#define T9UdbInfo T9AWUdbInfo
#endif
#if !defined(T9MdbInfo)
#define T9MdbInfo T9AWMdbInfo
#endif
#if !defined(T9DEFAULTUDBFENCE) && defined(T9AWDEFAULTUDBFENCE)
#define T9DEFAULTUDBFENCE T9AWDEFAULTUDBFENCE
#endif
#if !defined(T9MAXLDBOBJECTS) && defined(T9AWMAXLDBOBJECTS)
#define T9MAXLDBOBJECTS T9AWMAXLDBOBJECTS
#endif
#if !defined(T9MAXSELECTIONOBJECT) && defined(T9AWMAXSELECTIONOBJECT)
#define T9MAXSELECTIONOBJECT T9AWMAXSELECTIONOBJECT
#endif
#if !defined(T9MAXWORDSIZE) && defined(T9AWMAXWORDSIZE)
#define T9MAXWORDSIZE T9AWMAXWORDSIZE
#endif
#if !defined(MDBGETEXACTWORD)
#define MDBGETEXACTWORD T9AWMDBGETEXACTWORD
#endif
#if !defined(MDBGETSTEMWORD)
#define MDBGETSTEMWORD T9AWMDBGETSTEMWORD
#endif
#if !defined(T9AUX_KEYNUM) && defined(T9AWAUXKEYNUM)
#define T9AUX_KEYNUM T9AWAUXKEYNUM
#endif
#if !defined(T9AUX_SHIFTED) && defined(T9AWAUXSHIFTED)
#define T9AUX_SHIFTED T9AWAUXSHIFTED
#endif
#if !defined(T9MDBCALLBACK)
#define T9MDBCALLBACK T9AWMDBCALLBACK
#endif
#if !defined(CHeaderOffsetBlockOffset)
#define CHeaderOffsetBlockOffset T9CCHeaderOffsetBlockOffset
#endif
#if !defined(T9CudbInfo)
#define T9CudbInfo T9CCUdbInfo
#endif
#if !defined(T9CudbObj)
#define T9CudbObj T9CCUdbObj
#endif
#if !defined(T9GetCUDB)
#define T9GetCUDB T9CCUdbGet
#endif
#if !defined(T9AuxChineseInfo)
#define T9AuxChineseInfo T9CCFieldInfo
#endif
#if !defined(T9SPELLBUFSIZE) && defined(T9CCSPELLBUFMAXSIZE)
#define T9SPELLBUFSIZE T9CCSPELLBUFMAXSIZE
#endif
#if !defined(T9MINCUDBSIZE) && defined(T9CCUDBMINSIZE)
#define T9MINCUDBSIZE T9CCUDBMINSIZE
#endif
#if !defined(T9DEFAULTPHRASECOMPFENCE) && defined(T9CCDEFAULTPHRASECOMPFENCE)
#define T9DEFAULTPHRASECOMPFENCE T9CCDEFAULTPHRASECOMPFENCE
#endif
#if !defined(T9CUDB_ACRONYM_MAXSIZE) && defined(T9CCUDBACRONYMMAXSIZE)
#define T9CUDB_ACRONYM_MAXSIZE T9CCUDBACRONYMMAXSIZE
#endif
#if !defined(T9CUDB_PHRASE_MAXSIZE) && defined(T9CCUDBPHRASEMAXSIZE)
#define T9CUDB_PHRASE_MAXSIZE T9CCUDBPHRASEMAXSIZE
#endif
#if !defined(T9CSTATEMORE) && defined(T9CCSTATEMORE)
#define T9CSTATEMORE T9CCSTATEMORE
#endif
#if !defined(T9CSTATESTROKE) && defined(T9CCSTATESTROKE)
#define T9CSTATESTROKE T9CCSTATESTROKE
#endif
#if !defined(T9CSTATEPHAMBIG) && defined(T9CCSTATEPHAMBIG)
#define T9CSTATEPHAMBIG T9CCSTATEPHAMBIG
#endif
#if !defined(T9CSTATEPHMULTI) && defined(T9CCSTATEPHMULTI)
#define T9CSTATEPHMULTI T9CCSTATEPHMULTI
#endif
#if !defined(T9CSTATEAUTOSPELL) && defined(T9CCSTATEAUTOSPELL)
#define T9CSTATEAUTOSPELL T9CCSTATEAUTOSPELL
#endif
#if !defined(T9CSTATEPHMTUPDATE) && defined(T9CCSTATEPHMTUPDATE)
#define T9CSTATEPHMTUPDATE T9CCSTATEPHMTUPDATE
#endif
#if !defined(T9CSTATECOMPONENTS) && defined(T9CCSTATECOMPONENT)
#define T9CSTATECOMPONENTS T9CCSTATECOMPONENT
#endif
#if !defined(T9CSTATECUDBSEARCHONLY) && defined(T9CCSTATESEARCHUDBONLY)
#define T9CSTATECUDBSEARCHONLY T9CCSTATESEARCHUDBONLY
#endif
#if !defined(T9CSTATEFUZZYPINYIN) && defined(T9CCSTATEFUZZYPINYIN)
#define T9CSTATEFUZZYPINYIN T9CCSTATEFUZZYPINYIN
#endif
#if !defined(T9CHINESE_SEARCH_ACRONYM) && defined(T9CCUDBSEARCHACRONYM)
#define T9CHINESE_SEARCH_ACRONYM T9CCUDBSEARCHACRONYM
#endif
#if !defined(T9CHINESE_SEARCH_PHRASE) && defined(T9CCUDBSEARCHPHRASE)
#define T9CHINESE_SEARCH_PHRASE T9CCUDBSEARCHPHRASE
#endif
#if !defined(T9CHINESE_SEARCH_STROKE) && defined(T9CCUDBSEARCHSTROKE)
#define T9CHINESE_SEARCH_STROKE T9CCUDBSEARCHSTROKE
#endif
#if !defined(T9CUDB_FORCEADD) && defined(T9CCUDBFORCEADD)
#define T9CUDB_FORCEADD T9CCUDBFORCEADD
#endif
#if !defined(T9CUDB_NORMALADD) && defined(T9CCUDBNORMALADD)
#define T9CUDB_NORMALADD T9CCUDBNORMALADD
#endif
#if !defined(T9CPREFSTATEMASK) && defined(T9CCPREFMASK)
#define T9CPREFSTATEMASK T9CCPREFMASK
#endif
#if !defined(T9CSTATEPHBITS) && defined(T9CCSTATEPHBITS)
#define T9CSTATEPHBITS T9CCSTATEPHBITS
#endif
#if !defined(T9CSTATEMODEBITS) && defined(T9CCSTATEMODEBITS)
#define T9CSTATEMODEBITS T9CCSTATEMODEBITS
#endif
#if !defined(T9CHINESEDBVERSIONLENGTH) && defined(T9CCLDBVERSIONLENGTH)
#define T9CHINESEDBVERSIONLENGTH T9CCLDBVERSIONLENGTH
#endif
#if !defined(T9CHINESEDATABLOCKS) && defined(T9CCLDBBLOCKCOUNT)
#define T9CHINESEDATABLOCKS T9CCLDBBLOCKCOUNT
#endif
#if !defined(T9CDBSTROKE) && defined(T9CCLDBSTROKE)
#define T9CDBSTROKE T9CCLDBSTROKE
#endif
#if !defined(T9CDBCOMPONENT) && defined(T9CCLDBCOMPONENT)
#define T9CDBCOMPONENT T9CCLDBCOMPONENT
#endif
#if !defined(T9CDBPINYIN) && defined(T9CCLDBPINYIN)
#define T9CDBPINYIN T9CCLDBPINYIN
#endif
#if !defined(T9CDBBPMF) && defined(T9CCLDBBPMF)
#define T9CDBBPMF T9CCLDBBPMF
#endif
#if !defined(T9CDBCONTEXT40) && defined(T9CCLDBCONTEXT40)
#define T9CDBCONTEXT40 T9CCLDBCONTEXT40
#endif
#if !defined(T9CDBCONTEXT20) && defined(T9CCLDBCONTEXT20)
#define T9CDBCONTEXT20 T9CCLDBCONTEXT20
#endif
#if !defined(T9CHN_HASMODULE) && defined(T9CCLDBHASMODULE)
#define T9CHN_HASMODULE T9CCLDBHASMODULE
#endif
#if !defined(CUDB_CTXTSEARCH_DEPTH_HIGH) && defined(T9CCDYNCTXTSEARCHMAXDEPTH)
#define CUDB_CTXTSEARCH_DEPTH_HIGH T9CCDYNCTXTSEARCHMAXDEPTH
#endif
#if !defined(T9CAUdbInfo)
#define T9CAUdbInfo T9CCAudbInfo
#endif
#if !defined(T9AuxJapaneseInfo)
#define T9AuxJapaneseInfo T9JWFieldInfo
#endif
#if !defined(T9GetJUDB_s)
#define T9GetJUDB_s T9JWUdbGet_s
#endif
#if !defined(T9JKEYDIACRITIC) && defined(T9JWKEYDIACRITIC)
#define T9JKEYDIACRITIC T9JWKEYDIACRITIC
#endif
#if !defined(T9JKEYSELECTNEXT) && defined(T9JWKEYSELECTNEXT)
#define T9JKEYSELECTNEXT T9JWKEYSELECTNEXT
#endif
#if !defined(T9JKEYSELECTPREV) && defined(T9JWKEYSELECTPREV)
#define T9JKEYSELECTPREV T9JWKEYSELECTPREV
#endif
#if !defined(T9JKEYCONVERTNEXT) && defined(T9JWKEYCONVERTNEXT)
#define T9JKEYCONVERTNEXT T9JWKEYCONVERTNEXT
#endif
#if !defined(T9JKEYCONVERTPREV) && defined(T9JWKEYCONVERTPREV)
#define T9JKEYCONVERTPREV T9JWKEYCONVERTPREV
#endif
#if !defined(T9JKEYCANCEL) && defined(T9JWKEYCANCEL)
#define T9JKEYCANCEL T9JWKEYCANCEL
#endif
#if !defined(T9JKEYOK) && defined(T9JWKEYOK)
#define T9JKEYOK T9JWKEYOK
#endif
#if !defined(T9JSTATEIDLE) && defined(T9JWSTATEIDLE)
#define T9JSTATEIDLE T9JWSTATEIDLE
#endif
#if !defined(T9JSTATEADDING) && defined(T9JWSTATEADDING)
#define T9JSTATEADDING T9JWSTATEADDING
#endif
#if !defined(T9JSTATESELECT) && defined(T9JWSTATESELECT)
#define T9JSTATESELECT T9JWSTATESELECT
#endif
#if !defined(T9JSTATECONVERT) && defined(T9JWSTATECONVERT)
#define T9JSTATECONVERT T9JWSTATECONVERT
#endif
#if !defined(T9JSTATESPECIFIC) && defined(T9JWSTATESPECIFIC)
#define T9JSTATESPECIFIC T9JWSTATESPECIFIC
#endif
#if !defined(T9JSTATERESPELL) && defined(T9JWSTATERESPELL)
#define T9JSTATERESPELL T9JWSTATERESPELL
#endif
#if !defined(T9JSTATECONVPAGE) && defined(T9JWSTATECONVPAGE)
#define T9JSTATECONVPAGE T9JWSTATECONVPAGE
#endif
#if !defined(J_IDLE_STATE) && defined(T9JWIDLESTATE)
#define J_IDLE_STATE T9JWIDLESTATE
#endif
#if !defined(J_ADDING_STATE) && defined(T9JWADDINGSTATE)
#define J_ADDING_STATE T9JWADDINGSTATE
#endif
#if !defined(J_SELECT_STATE) && defined(T9JWSELECTSTATE)
#define J_SELECT_STATE T9JWSELECTSTATE
#endif
#if !defined(J_CONVERT_STATE) && defined(T9JWCONVERTSTATE)
#define J_CONVERT_STATE T9JWCONVERTSTATE
#endif
#if !defined(J_SPECIFIC_STATE) && defined(T9JWSPECIFICSTATE)
#define J_SPECIFIC_STATE T9JWSPECIFICSTATE
#endif
#if !defined(J_RESPELL_STATE) && defined(T9JWRESPELLSTATE)
#define J_RESPELL_STATE T9JWRESPELLSTATE
#endif
#if !defined(J_CONVPAGE_STATE) && defined(T9JWCONVPAGESTATE)
#define J_CONVPAGE_STATE T9JWCONVPAGESTATE
#endif
#if !defined(J_QSTN_1D) && defined(T9JWQSTN1D)
#define J_QSTN_1D T9JWQSTN1D
#endif
#if !defined(J_QSTN_2D) && defined(T9JWQSTN2D)
#define J_QSTN_2D T9JWQSTN2D
#endif
#if !defined(JF_KATAKANA) && defined(T9JWFKATAKANA)
#define JF_KATAKANA T9JWFKATAKANA
#endif
#if !defined(JF_JUDB_NO_GC) && defined(T9JWFJUDBNOGC)
#define JF_JUDB_NO_GC T9JWFJUDBNOGC
#endif
#if !defined(JKEY_EXPLICIT) && defined(T9JWKEYEXPLICIT)
#define JKEY_EXPLICIT T9JWKEYEXPLICIT
#endif
#if !defined(JKEY_AMBIG) && defined(T9JWKEYAMBIG)
#define JKEY_AMBIG T9JWKEYAMBIG
#endif
#if !defined(JKEY_VAL) && defined(T9JWKEYVAL)
#define JKEY_VAL T9JWKEYVAL
#endif
#if !defined(JKEY_T9_VAL) && defined(T9JWKEYT9VAL)
#define JKEY_T9_VAL T9JWKEYT9VAL
#endif
#if !defined(ADDMID_IDLE) && defined(T9JWADDMIDIDLE)
#define ADDMID_IDLE T9JWADDMIDIDLE
#endif
#if !defined(ADDMID_YOMI_MODE) && defined(T9JWADDMIDYOMIMODE)
#define ADDMID_YOMI_MODE T9JWADDMIDYOMIMODE
#endif
#if !defined(ADDMID_MIDASHIGO_MODE) && defined(T9JWADDMIDMIDASHIGOMODE)
#define ADDMID_MIDASHIGO_MODE T9JWADDMIDMIDASHIGOMODE
#endif
#if !defined(ADDMID_DELETE) && defined(T9JWADDMIDDELETE)
#define ADDMID_DELETE T9JWADDMIDDELETE
#endif
#if !defined(ADDMID_DELETEALL) && defined(T9JWADDMIDDELETEALL)
#define ADDMID_DELETEALL T9JWADDMIDDELETEALL
#endif
#if !defined(EMI_ROMAJI_LAST) && defined(T9JWEMIROMAJILAST)
#define EMI_ROMAJI_LAST T9JWEMIROMAJILAST
#endif
#if !defined(EMI_ROMAJI_2ND_LAST) && defined(T9JWEMIROMAJI2NDLAST)
#define EMI_ROMAJI_2ND_LAST T9JWEMIROMAJI2NDLAST
#endif
#if !defined(EMI_ROMAJI_3RD_LAST) && defined(T9JWEMIROMAJI3RDLAST)
#define EMI_ROMAJI_3RD_LAST T9JWEMIROMAJI3RDLAST
#endif
#if !defined(EMI_ZENK_LAST) && defined(T9JWEMIZENKLAST)
#define EMI_ZENK_LAST T9JWEMIZENKLAST
#endif
#if !defined(EMI_ZENK_2ND_LAST) && defined(T9JWEMIZENK2NDLAST)
#define EMI_ZENK_2ND_LAST T9JWEMIZENK2NDLAST
#endif
#if !defined(EMI_ZENK_3RD_LAST) && defined(T9JWEMIZENK3RDLAST)
#define EMI_ZENK_3RD_LAST T9JWEMIZENK3RDLAST
#endif
#if !defined(EMI_HANK_LAST) && defined(T9JWEMIHANKLAST)
#define EMI_HANK_LAST T9JWEMIHANKLAST
#endif
#if !defined(EMI_HANK_2ND_LAST) && defined(T9JWEMIHANK2NDLAST)
#define EMI_HANK_2ND_LAST T9JWEMIHANK2NDLAST
#endif
#if !defined(EMI_HANK_3RD_LAST) && defined(T9JWEMIHANK3RDLAST)
#define EMI_HANK_3RD_LAST T9JWEMIHANK3RDLAST
#endif
#if !defined(EMI_DEFAULTS) && defined(T9JWEMIDEFAULTS)
#define EMI_DEFAULTS T9JWEMIDEFAULTS
#endif
#if !defined(EMI_NONE) && defined(T9JWEMINONE)
#define EMI_NONE T9JWEMINONE
#endif
#if !defined(T9EXPLKEY1) && defined(T9JWEXPLKEY1)
#define T9EXPLKEY1 T9JWEXPLKEY1
#endif
#if !defined(T9EXPLKEY2) && defined(T9JWEXPLKEY2)
#define T9EXPLKEY2 T9JWEXPLKEY2
#endif
#if !defined(T9EXPLKEY3) && defined(T9JWEXPLKEY3)
#define T9EXPLKEY3 T9JWEXPLKEY3
#endif
#if !defined(T9EXPLKEY4) && defined(T9JWEXPLKEY4)
#define T9EXPLKEY4 T9JWEXPLKEY4
#endif
#if !defined(T9EXPLKEY5) && defined(T9JWEXPLKEY5)
#define T9EXPLKEY5 T9JWEXPLKEY5
#endif
#if !defined(T9EXPLKEY6) && defined(T9JWEXPLKEY6)
#define T9EXPLKEY6 T9JWEXPLKEY6
#endif
#if !defined(T9EXPLKEY7) && defined(T9JWEXPLKEY7)
#define T9EXPLKEY7 T9JWEXPLKEY7
#endif
#if !defined(T9EXPLKEY8) && defined(T9JWEXPLKEY8)
#define T9EXPLKEY8 T9JWEXPLKEY8
#endif
#if !defined(T9EXPLKEY9) && defined(T9JWEXPLKEY9)
#define T9EXPLKEY9 T9JWEXPLKEY9
#endif
#if !defined(T9EXPLKEY0) && defined(T9JWEXPLKEY0)
#define T9EXPLKEY0 T9JWEXPLKEY0
#endif
#if !defined(T9EXPLKEY1_SM_VOWELS) && defined(T9JWEXPLKEY1SMVOWELS)
#define T9EXPLKEY1_SM_VOWELS T9JWEXPLKEY1SMVOWELS
#endif
#if !defined(T9EXPLKEY1_1D) && defined(T9JWEXPLKEY11D)
#define T9EXPLKEY1_1D T9JWEXPLKEY11D
#endif
#if !defined(T9EXPLKEY2_1D) && defined(T9JWEXPLKEY21D)
#define T9EXPLKEY2_1D T9JWEXPLKEY21D
#endif
#if !defined(T9EXPLKEY3_1D) && defined(T9JWEXPLKEY31D)
#define T9EXPLKEY3_1D T9JWEXPLKEY31D
#endif
#if !defined(T9EXPLKEY4_1D) && defined(T9JWEXPLKEY41D)
#define T9EXPLKEY4_1D T9JWEXPLKEY41D
#endif
#if !defined(T9EXPLKEY6_1D) && defined(T9JWEXPLKEY61D)
#define T9EXPLKEY6_1D T9JWEXPLKEY61D
#endif
#if !defined(T9EXPLKEY6_2D) && defined(T9JWEXPLKEY62D)
#define T9EXPLKEY6_2D T9JWEXPLKEY62D
#endif
#endif /* #ifndef T9NAMES2_H */
