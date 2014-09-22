#include "MainWindow.hpp"
#include <QApplication>
#include "first_order_logic_prover/first_order_logic.hpp"
#include <QTextCodec>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	MainWindow w;
	w.show();
	return a.exec();
}
