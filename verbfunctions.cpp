#include "verbfunctions.h"

VerbFunctions::VerbFunctions()
{
}

/**
 * @brief VerbFunctions::getRegularVerbForm Function gives standart form of verb
 * @param verb  The verb
 * @param tense A tense of the verb
 * @param pronoun A pronoun which is used with a verb form.
 * @return Returns verb form
 */
QString VerbFunctions::getRegularVerbForm(QString verb,int tense,int pronoun)
{
    //1. Определить тип (ar,ir,er)
    //2. Поискать в словаре регулярностей (хотя...) Надо ли? а вот и нет.
    //3. Сделать выборку для каждого по времени, это слишком много, давай наоборот.


    //1. Определить время.
    //2. Для каждого времени. в зависимости от местоимения и окончания сделать окончание правильное...
    //3. Соединить окончание с глаголом (добавить префикс, если понадобится).

//    QString verbSpliced=VerbFunctions::verbSplit(verb);

    switch(tense)
    {
    case TENSE_PRESENTE:
        //функцию для каждого времени не хотите ли?
        //О-хо-хо...а ведь придётся.
        return getVerbTensePresente(verb,pronoun);
    case TENSE_PRETERITO_PERFECTO_COMPUESTO:
        return getVerbTensePreteritoPerfectoCompuesto(verb,pronoun);
    case TENSE_PRETERITO_IMPERFECTO:
        return getVerbTensePreteritoImperfecto(verb,pronoun);
    case TENSE_PRETERITO_PERFECTO_SIMPLE:
        return getVerbTensePreteritoPerfectoSimple(verb,pronoun);
    case TENSE_PRETERITO_PLUSCAMPERFECTO:
        return getVerbTensePreteritoPluscamperfecto(verb,pronoun);
    case TENSE_FUTURO:
        return getVerbTenseFuturo(verb,pronoun);
    case TENSE_FUTURO_PERFECTO:
        return getVerbTenseFuturoPerfecto(verb,pronoun);
    case TENSE_CONDICIONAL:
        return getVerbTenseCondicional(verb,pronoun);
    case TENSE_CONDICIONAL_PERFECTO:
        return getVerbTenseCondicionalPerfecto(verb,pronoun);
    case TENSE_PRETERITO_ANTERIOR:
        return getVerbTensePreteritoAnterior(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRESENTE:
        return getVerbTenseSubjunctivoPresente(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRETERITO_PERFECTO:
        return getVerbTenseSubjunctivoPreteritoPerfecto(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO:
        return getVerbTenseSubjunctivoPreteritoImperfecto(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRETERITO_IMPERFECTO_2:
        return getVerbTenseSubjunctivoPreteritoImperfecto2(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO:
        return getVerbTenseSubjunctivoPreteritoPluscamperfecto(verb,pronoun);
    case TENSE_SUBJUNCTIVO_PRETERITO_PLUSCUAMPERFECTO_2:
        return getVerbTenseSubjunctivoPreteritoPluscamperfecto2(verb,pronoun);
    case TENSE_SUBJUNCTIVO_FUTURO:
        return getVerbTenseSubjunctivoFuturo(verb,pronoun);
    case TENSE_SUBJUNCTIVO_FUTURO_PERFECTO:
        return getVerbTenseSubjunctivoFuturoPerfecto(verb,pronoun);
    case TENSE_IMPERATIVO:
        return getVerbTenseImperativo(verb,pronoun);
    case TENSE_IMPERATIVO_NEGATIVO:
        return getVerbTenseImperativoNegativo(verb,pronoun);
    default:
        return "";
    break;
    }
}
/**
 * @brief VerbFunctions::verbSplit Function splits verb in two parts: starting and ending
 * @param verb The verb
 * @return Returns spliced verb.
 */
QStringList VerbFunctions::verbSplit(QString verb)
{
    //1. Выделить окончание глагола и часть, над которой проводятся эксперименты. Всё просто.
    QStringList list;
    //тупо оторвать окончание (две буквы в конце).
    //Если буквы не ar,ir,er - в топку.
    if(verb.size()<3) return list;
    QString ending=verb.right(2);
    if(ending!="ar" && ending!="er" && ending!="ir") return list;
    list.append(verb.left(verb.size()-2));
    list.append(ending);
    return list;
}

QString VerbFunctions::getVerbTensePresente(QString verb, int pronoun)
{
     QStringList verbSpliced=VerbFunctions::verbSplit(verb);
     if(verbSpliced.isEmpty()) return QString();
     switch(pronoun)
     {
     case PRONOUN_YO:
         //Ах, три вида окончаний ещё...гм...
         if(verbSpliced[1]!="ir")return verbSpliced[0]+"o";
         else return verbSpliced[0]+"!go";
     case PRONOUN_TU:
         if(verbSpliced[1]=="ar") return verbSpliced[0]+"as";
         else if(verbSpliced[1]=="er") return verbSpliced[0]+"es";
         else return verbSpliced[0]+"es";
     case PRONOUN_EL:
         if(verbSpliced[1]=="ar") return verbSpliced[0]+"a";
         else if(verbSpliced[1]=="er") return verbSpliced[0]+"e";
         else return verbSpliced[0]+"e";
     case PRONOUN_NOSOTROS:
         if(verbSpliced[1]=="ar") return verbSpliced[0]+"amos";
         else if(verbSpliced[1]=="er") return verbSpliced[0]+"emos";
         else return verbSpliced[0]+"imos";
     case PRONOUN_VOSOTROS:
         if(verbSpliced[1]=="ar") return verbSpliced[0]+"áis";
         else if(verbSpliced[1]=="er") return verbSpliced[0]+"éis";
         else return verbSpliced[0]+"ís";
     case PRONOUN_ELLOS:
         if(verbSpliced[1]=="ar") return verbSpliced[0]+"an";
         else if(verbSpliced[1]=="er") return verbSpliced[0]+"en";
         else return verbSpliced[0]+"en";
     }
     return "";
}

QString VerbFunctions::getVerbTensePreteritoPerfectoCompuesto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "he "+verbSpliced[0]+"ado";
        else return "he "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "has "+verbSpliced[0]+"ado";
        else return "has "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "ha "+verbSpliced[0]+"ado";
        else return "ha "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hemos "+verbSpliced[0]+"ado";
        else return "hemos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "habéis "+verbSpliced[0]+"ado";
        else return "habéis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "han "+verbSpliced[0]+"ado";
        else return "han "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTensePreteritoImperfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aba";
       else return verbSpliced[0]+"ía";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"abas";
       else return verbSpliced[0]+"ías";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aba";
       else return verbSpliced[0]+"ía";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ábamos";
       else return verbSpliced[0]+"íamos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"abais";
       else return verbSpliced[0]+"íais";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aban";
       else return verbSpliced[0]+"ían";
    }
    return "";
}

QString VerbFunctions::getVerbTensePreteritoPerfectoSimple(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"é";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"í";
       else return verbSpliced[0]+"é";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aste";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iste";
       else return verbSpliced[0]+"iste";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ó";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ió";
       else return verbSpliced[0]+"ió";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"amos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"imos";
       else return verbSpliced[0]+"imos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"asteis";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"isteis";
       else return verbSpliced[0]+"isteis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aron";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieron";
       else return verbSpliced[0]+"ieron";
    }
    return "";
}

QString VerbFunctions::getVerbTensePreteritoPluscamperfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "había "+verbSpliced[0]+"ado";
        else return "había "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "habías "+verbSpliced[0]+"ado";
        else return "habías "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "había "+verbSpliced[0]+"ado";
        else return "había "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "habíamos "+verbSpliced[0]+"ado";
        else return "habíamos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "habíais "+verbSpliced[0]+"ado";
        else return "habíais "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "habían "+verbSpliced[0]+"ado";
        else return "habían "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseFuturo(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aré";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"eré";
       else return verbSpliced[0]+"dré";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"arás";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"erás";
       else return verbSpliced[0]+"drás";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ará";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"erá";
       else return verbSpliced[0]+"drá";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"jaremos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"eremos";
       else return verbSpliced[0]+"dremos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aréis";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"eréis";
       else return verbSpliced[0]+"dréis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"arán";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"erán";
       else return verbSpliced[0]+"drán";
    }
    return "";
}

QString VerbFunctions::getVerbTenseFuturoPerfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "habré "+verbSpliced[0]+"ado";
        else return "habré "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "habrás "+verbSpliced[0]+"ado";
        else return "habrás "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "habrá "+verbSpliced[0]+"ado";
        else return "habrá "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "habremos "+verbSpliced[0]+"ado";
        else return "habremos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "habréis "+verbSpliced[0]+"ado";
        else return "habréis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "habrán "+verbSpliced[0]+"ado";
        else return "habrán "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseCondicional(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aría";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ería";
       else return verbSpliced[0]+"dría";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"arías";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"erías";
       else return verbSpliced[0]+"drías";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aría";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ería";
       else return verbSpliced[0]+"dría";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aríamos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"eríamos";
       else return verbSpliced[0]+"dríamos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aríais";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"eríais";
       else return verbSpliced[0]+"dríais";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"arían";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"erían";
       else return verbSpliced[0]+"drían";
    }
    return "";
}

QString VerbFunctions::getVerbTenseCondicionalPerfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "habré "+verbSpliced[0]+"ado";
        else return "habré "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "habrás "+verbSpliced[0]+"ado";
        else return "habrás "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "habrá "+verbSpliced[0]+"ado";
        else return "habrá "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "habremos "+verbSpliced[0]+"ado";
        else return "habremos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "habréis "+verbSpliced[0]+"ado";
        else return "habréis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "habrán "+verbSpliced[0]+"ado";
        else return "habrán "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTensePreteritoAnterior(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "hube "+verbSpliced[0]+"ado";
        else return "hube "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "hubiste "+verbSpliced[0]+"ado";
        else return "hubiste "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "hubo "+verbSpliced[0]+"ado";
        else return "hubo "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hubimos "+verbSpliced[0]+"ado";
        else return "hubimos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "hubisteis "+verbSpliced[0]+"ado";
        else return "hubisteis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "hubieron "+verbSpliced[0]+"ado";
        else return "hubieron "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPresente(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"e";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"a";
       else return verbSpliced[0]+"ga";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"es";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"as";
       else return verbSpliced[0]+"gas";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"e";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"a";
       else return verbSpliced[0]+"ga";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"emos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"amos";
       else return verbSpliced[0]+"gamos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"éis";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"áis";
       else return verbSpliced[0]+"gáis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"en";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"an";
       else return verbSpliced[0]+"gan";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPreteritoPerfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "haya "+verbSpliced[0]+"ado";
        else return "haya "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "hayas "+verbSpliced[0]+"ado";
        else return "hayas "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "haya "+verbSpliced[0]+"ado";
        else return "haya "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hayamos "+verbSpliced[0]+"ado";
        else return "hayamos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "hayamos "+verbSpliced[0]+"ado";
        else return "hayamos "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "hayan "+verbSpliced[0]+"ado";
        else return "hayan "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPreteritoImperfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ara";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iera";
       else return verbSpliced[0]+"iera";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aras";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieras";
       else return verbSpliced[0]+"ieras";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ara";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iera";
       else return verbSpliced[0]+"iera";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"áramos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iéramos";
       else return verbSpliced[0]+"iéramos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"arais";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ierais";
       else return verbSpliced[0]+"ierais";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aran";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieran";
       else return verbSpliced[0]+"ieran";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPreteritoImperfecto2(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ase";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iese";
       else return verbSpliced[0]+"iese";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ases";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieses";
       else return verbSpliced[0]+"ieses";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ase";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iese";
       else return verbSpliced[0]+"iese";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ásemos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iésemos";
       else return verbSpliced[0]+"iésemos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aseis";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieseis";
       else return verbSpliced[0]+"ieseis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"asen";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iesen";
       else return verbSpliced[0]+"iesen";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPreteritoPluscamperfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "hubiera "+verbSpliced[0]+"ado";
        else return "hubiera "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "hubieras "+verbSpliced[0]+"ado";
        else return "hubieras "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "hubiera "+verbSpliced[0]+"ado";
        else return "hubiera "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hubiéramos "+verbSpliced[0]+"ado";
        else return "hubiéramos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "hubierais "+verbSpliced[0]+"ado";
        else return "hubierais "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "hubieran "+verbSpliced[0]+"ado";
        else return "hubieran "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoPreteritoPluscamperfecto2(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "hubiese "+verbSpliced[0]+"ado";
        else return "hubiese "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "hubieses "+verbSpliced[0]+"ado";
        else return "hubieses "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "hubiese "+verbSpliced[0]+"ado";
        else return "hubiese "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hubiésemos "+verbSpliced[0]+"ado";
        else return "hubiésemos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "hubieseis "+verbSpliced[0]+"ado";
        else return "hubieseis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "hubiesen "+verbSpliced[0]+"ado";
        else return "hubiesen "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoFuturo(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"are";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iere";
       else return verbSpliced[0]+"iere";
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ares";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieres";
       else return verbSpliced[0]+"ieres";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"are";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iere";
       else return verbSpliced[0]+"iere";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"áremos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iéremos";
       else return verbSpliced[0]+"iéremos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"areis";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"iereis";
       else return verbSpliced[0]+"iereis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"aren";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ieren";
       else return verbSpliced[0]+"ieren";
    }
    return "";
}

QString VerbFunctions::getVerbTenseSubjunctivoFuturoPerfecto(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_YO:
        if(verbSpliced[1]=="ar")return "hubiere "+verbSpliced[0]+"ado";
        else return "hubiere "+verbSpliced[0]+"ido";
    case PRONOUN_TU:
        if(verbSpliced[1]=="ar")return "hubieres "+verbSpliced[0]+"ado";
        else return "hubieres "+verbSpliced[0]+"ido";
    case PRONOUN_EL:
        if(verbSpliced[1]=="ar")return "hubiere "+verbSpliced[0]+"ado";
        else return "hubiere "+verbSpliced[0]+"ido";
    case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar")return "hubiéremos "+verbSpliced[0]+"ado";
        else return "hubiéremos "+verbSpliced[0]+"ido";
    case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar")return "hubiereis "+verbSpliced[0]+"ado";
        else return "hubiereis "+verbSpliced[0]+"ido";
    case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar")return "hubieren "+verbSpliced[0]+"ado";
        else return "hubieren "+verbSpliced[0]+"ido";
    }
    return "";
}

QString VerbFunctions::getVerbTenseImperativo(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"a";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"e";
       else return verbSpliced[0];
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"e";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"a";
       else return verbSpliced[0]+"ga";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"emos";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"amos";
       else return verbSpliced[0]+"gamos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"ad";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"ed";
       else return verbSpliced[0]+"id";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return verbSpliced[0]+"en";
       else if(verbSpliced[1]=="er") return verbSpliced[0]+"an";
       else return verbSpliced[0]+"gan";
    }
    return "";
}

QString VerbFunctions::getVerbTenseImperativoNegativo(QString verb, int pronoun)
{
    QStringList verbSpliced=VerbFunctions::verbSplit(verb);
    if(verbSpliced.isEmpty()) return QString();
    switch(pronoun)
    {
    case PRONOUN_TU:
       if(verbSpliced[1]=="ar") return "no "+verbSpliced[0]+"es";
       else if(verbSpliced[1]=="er") return "no "+verbSpliced[0]+"as";
       else return "no "+verbSpliced[0]+"gas";
    case PRONOUN_EL:
       if(verbSpliced[1]=="ar") return "no "+verbSpliced[0]+"e";
       else if(verbSpliced[1]=="er") return "no "+verbSpliced[0]+"a";
       else return "no "+verbSpliced[0]+"ga";
    case PRONOUN_NOSOTROS:
       if(verbSpliced[1]=="ar") return "no "+verbSpliced[0]+"emos";
       else if(verbSpliced[1]=="er") return "no "+verbSpliced[0]+"amos";
       else return "no "+verbSpliced[0]+"gamos";
    case PRONOUN_VOSOTROS:
       if(verbSpliced[1]=="ar") return "no "+verbSpliced[0]+"éis";
       else if(verbSpliced[1]=="er") return "no "+verbSpliced[0]+"áis";
       else return "no "+verbSpliced[0]+"gáis";
    case PRONOUN_ELLOS:
       if(verbSpliced[1]=="ar") return "no "+verbSpliced[0]+"en";
       else if(verbSpliced[1]=="er") return "no "+verbSpliced[0]+"an";
       else return "no "+verbSpliced[0]+"gamos";
    }
    return "";
}

/*
 *if(verbSpliced[1]=="ar") return;
  else if(verbSpliced[1]=="er") return;
  else return;
     switch(pronoun)
     {
     case PRONOUN_YO:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     case PRONOUN_TU:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     case PRONOUN_EL:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar") return verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return verbSpliced[0]+"";
        else return verbSpliced[0]+"";
     }

     switch(pronoun)
     {
     case PRONOUN_YO:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     case PRONOUN_TU:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     case PRONOUN_EL:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     case PRONOUN_NOSOTROS:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     case PRONOUN_VOSOTROS:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     case PRONOUN_ELLOS:
        if(verbSpliced[1]=="ar") return ""+verbSpliced[0]+"";
        else if(verbSpliced[1]=="er") return ""+verbSpliced[0]+"";
        else return ""+verbSpliced[0]+"";
     }

 **/

