#ifndef DEFINES_H
#define DEFINES_H

#include <QString>

enum MessageType
{
    messageText,
    messageBox
};
enum MessageEmotion
{
    messageWarning,
    messageInformation,
    messageCritical
};

enum languageEnum
{
    languageEspanol,
    languageEnglish,
    languageRussian
};

enum SpanishTense
{
    None = 0,
    Present = 1,
    PresentPerfect =2,
    Imperfect=3,
    Preterite=4,
    Pluperfect=5,
    Future=6,
    FuturePerfect=7,
    Conditional=8,
    ConditionalPerfect=9,
    PreteritePerfect=10,
    subjPresent=11,
    subjPresentPerfect=12,
    subjImperfect=13,
    subjImperfect2=14,
    subjPlurperfect=15,
    subjPlurperfect2=16,
    subjFuture=17,
    subjFuturePerfect=18,
    impAffirmative=19
};

QString getTenseName(SpanishTense tense, languageEnum lang);
QString getTenseNameEn(SpanishTense tense);
QString getTenseNameRu(SpanishTense tense);
QString getTenseNameEs(SpanishTense tense);

//áéíñóúüÁÉÍÑÓÚÜ

#endif // DEFINES_H
