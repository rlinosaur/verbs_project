#ifndef QLINEEDITWITHFOCUS_H
#define QLINEEDITWITHFOCUS_H

#include <QLineEdit>

class LineEditForVerbs : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditForVerbs(QWidget *parent = 0);
    QString dataId;//id of text, yeah
    int pronoun;
signals:
  void inFocus();
protected:
  virtual void focusInEvent(QFocusEvent *e);
public slots:    
};

#endif // QLINEEDITWITHFOCUS_H
