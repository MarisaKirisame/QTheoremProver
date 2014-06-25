#include "QRememberPositionLineEdit.hpp"

QRememberPositionLineEdit::QRememberPositionLineEdit(QWidget *parent) : QLineEdit(parent), position( 0 ) { }

void QRememberPositionLineEdit::focusOutEvent(QFocusEvent *) { position = cursorPosition( ); }

void QRememberPositionLineEdit::focusInEvent(QFocusEvent *) { setCursorPosition( position ); }

void QRememberPositionLineEdit::AppendString( const QString & str )
{
	QString new_str( text( ) );
	new_str.insert( position, str );
	position += str.size( );
	setText( new_str );
}
