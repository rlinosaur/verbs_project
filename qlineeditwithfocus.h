#ifndef QLINEEDITWITHFOCUS_H
#define QLINEEDITWITHFOCUS_H

#include <QLineEdit>

class QLineEditWithFocus : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditWithFocus(QWidget *parent = 0);
signals:
  void inFocus();
protected:
  virtual void focusInEvent(QFocusEvent *e);
public slots:    
};

#endif // QLINEEDITWITHFOCUS_H
