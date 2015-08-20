#include "lineeditforverbs.h"

LineEditForVerbs::LineEditForVerbs(QWidget *parent) :
    QLineEdit(parent)
{    
}
void LineEditForVerbs::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    Q_EMIT inFocus();
}
