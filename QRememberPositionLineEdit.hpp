#ifndef QREMEMBERPOSITIONLINEEDIT_HPP
#define QREMEMBERPOSITIONLINEEDIT_HPP

#include <QLineEdit>

class QRememberPositionLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QRememberPositionLineEdit(QWidget * parent = 0);
    void focusOutEvent(QFocusEvent *) override;
    void focusInEvent(QFocusEvent *) override;
    size_t position;
signals:

public slots:
    void AppendString( const QString & );
};

#endif // QREMEMBERPOSITIONLINEEDIT_HPP
