#include "qlineeditwithfocus.h"

QLineEditWithFocus::QLineEditWithFocus(QWidget *parent) :
    QLineEdit(parent)
{
}
void QLineEditWithFocus::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    Q_EMIT inFocus();
}
