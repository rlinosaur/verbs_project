#ifndef VERBFUNCTIONS_H
#define VERBFUNCTIONS_H

#include <QStringList>
#include <QString>


//Spanish verb Tenses
#define TENSE_NINGUNO                                   0
#define TENSE_PRESENTE                                  1
#define TENSE_PRETERITO_PERFECTO_COMPUESTO              2
#define TENSE_PRETERITO_IMPERFECTO                      3
#define TENSE_PRETERITO_PERFECTO_SIMPLE                 4
#define TENSE_PRETERITO_PLUSCAMPERFECTO                 5
#define TENSE_FUTURO                                    6
#define TENSE_FUTURO_PERFECTO                           7
#define TENSE_CONDICIONAL                               8
#define TENSE_CONDICIONAL_PERFECTO                      9
#define TENSE_PRETERITO_ANTERIOR                        10
#define TENSE_SUBJUNCTIVO_PRESENTE                      11
#define TENSE_SUBJUNCTIVO_PRETERITO_PERFECTO            12
#define TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO          13
#define TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO_2        14
#define TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO    15
#define TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO_2  16
#define TENSE_SUBJUNCTIVO_FUTURO                        17
#define TENSE_SUBJUNCTIVO_FUTURO_PERFECTO               18
#define TENSE_IMPERATIVO                                19
#define TENSE_IMPERATIVO_NEGATIVO                       20

/*
 case TENSE_PRESENTE:
        break;
    case TENSE_PRETERITO_PERFECTO_COMPUESTO:
        break;
    case TENSE_PRETERITO_IMPERFECTO:
        break;
    case TENSE_PRETERITO_PERFECTO_SIMPLE:
        break;
    case TENSE_PRETERITO_PLUSCAMPERFECTO:
        break;
    case TENSE_FUTURO:
        break;
    case TENSE_FUTURO_PERFECTO:
        break;
    case TENSE_CONDICIONAL:
        break;
    case TENSE_CONDICIONAL_PERFECTO:
        break;
    case TENSE_PRETERITO_PERFECTO:
        break;
    case TENSE_SUBJUNCTIVO_PRESENTE:
        break;
    case TENSE_SUBJUNCTIVO_PRETERITO_PERFECTO:
        break;
    case TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO:
        break;
    case TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO_2:
        break;
    case TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO:
        break;
    case TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO_2:
        break;
    case TENSE_SUBJUNCTIVO_FUTURO:
        break;
    case TENSE_SUBJUNCTIVO_FUTURO_PERFECTO:
        break;
 **/

#define VERBFORM_INFINITIVO_PRESENTE                101
#define VERBFORM_INFINITIVO_COMPUESTO               102
#define VERBFORM_GERUNDIO_PRESENTE                  103
#define VERBFORM_GERUNDIO_COMPUESTO                 104
#define VERBFORM_PARTICIPIO                         105

//Spanish pronouns for verb forms
#define PRONOUN_NINGUNO     0
#define PRONOUN_YO          1
#define PRONOUN_TU          2
#define PRONOUN_EL          3
#define PRONOUN_NOSOTROS    4
#define PRONOUN_VOSOTROS    5
#define PRONOUN_ELLOS       6

class VerbFunctions
{
public:
    VerbFunctions();

    static QStringList verbSplit(QString verb);
    static QString getRegularVerbForm(QString verb, int tense, int pronoun=PRONOUN_NINGUNO);

    static QString getVerbTensePresente(QString verb,int pronoun);
    static QString getVerbTensePreteritoPerfectoCompuesto(QString verb,int pronoun);
    static QString getVerbTensePreteritoImperfecto(QString verb,int pronoun);
    static QString getVerbTensePreteritoPerfectoSimple(QString verb,int pronoun);
    static QString getVerbTensePreteritoPluscamperfecto(QString verb,int pronoun);
    static QString getVerbTenseFuturo(QString verb,int pronoun);
    static QString getVerbTenseFuturoPerfecto(QString verb,int pronoun);
    static QString getVerbTenseCondicional(QString verb,int pronoun);
    static QString getVerbTenseCondicionalPerfecto(QString verb,int pronoun);
    static QString getVerbTensePreteritoAnterior(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPresente(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPreteritoPerfecto(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPreteritoImperfecto(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPreteritoImperfecto2(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPreteritoPluscamperfecto(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoPreteritoPluscamperfecto2(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoFuturo(QString verb,int pronoun);
    static QString getVerbTenseSubjunctivoFuturoPerfecto(QString verb,int pronoun);
    static QString getVerbTenseImperativo(QString verb,int pronoun);
    static QString getVerbTenseImperativoNegativo(QString verb,int pronoun);


};

#endif // VERBFUNCTIONS_H
