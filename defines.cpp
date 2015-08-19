#include "defines.h"

QString getTenseName(SpanishTense tense, languageEnum lang)
{
    switch(lang)
    {
    case languageEnglish:
        return getTenseNameEn(tense);
    case languageEspanol:
        return getTenseNameEs(tense);
    case languageRussian:
        return getTenseNameRu(tense);
    }
    return "";
}


QString getTenseNameEn(SpanishTense tense)
{
    switch(tense)
    {
    case None:
        return "";
    case Present:
        return "Present";
    case PresentPerfect:
        return "Present Perfect";
    case Imperfect:
        return "Imperfect";
    case Preterite:
        return "Preterite";
    case Pluperfect:
        return "Plurperfect";
    case Future:
        return "Future";
    case FuturePerfect:
        return "Future Perfect";
    case Conditional:
        return "Conditional";
    case ConditionalPerfect:
        return "Conditional Perfect";
    case PreteritePerfect:
        return "Preterite Perfect";
    case subjPresent:
        return "Subjunctive Present";
    case subjPresentPerfect:
        return "Subjunctive Present Perfect";
    case subjImperfect:
        return "Subjunctive Imperfect";
    case subjPlurperfect:
        return "Subjunctive Plurperfect";
    case subjFuture:
        return "Subjunctive Future";
    case subjFuturePerfect:
        return "Subjunctive Future Perfect";
    case impAffirmative:
        return "Imperative Affirmative";
    }
    return "";
}





QString getTenseNameRu(SpanishTense tense)
{
    switch(tense)
    {
    case None:
        return "";
    case Present:
        return "";
    case PresentPerfect:
        return "";
    case Imperfect:
        return "";
    case Preterite:
        return "";
    case Pluperfect:
        return "";
    case Future:
        return "";
    case FuturePerfect:
        return "";
    case Conditional:
        return "";
    case ConditionalPerfect:
        return "";
    case PreteritePerfect:
        return "";
    case subjPresent:
        return "";
    case subjPresentPerfect:
        return "";
    case subjImperfect:
        return "";
    case subjPlurperfect:
        return "";
    case subjFuture:
        return "";
    case subjFuturePerfect:
        return "";
    case impAffirmative:
        return "";
    }
    return "";
}


QString getTenseNameEs(SpanishTense tense)
{
    switch(tense)
    {
    case None:
        return "";
    case Present:
        return "";
    case PresentPerfect:
        return "";
    case Imperfect:
        return "";
    case Preterite:
        return "";
    case Pluperfect:
        return "";
    case Future:
        return "";
    case FuturePerfect:
        return "";
    case Conditional:
        return "";
    case ConditionalPerfect:
        return "";
    case PreteritePerfect:
        return "";
    case subjPresent:
        return "";
    case subjPresentPerfect:
        return "";
    case subjImperfect:
        return "";
    case subjPlurperfect:
        return "";
    case subjFuture:
        return "";
    case subjFuturePerfect:
        return "";
    case impAffirmative:
        return "";
    }
    return "";
}
