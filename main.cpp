#include "MainWindow.hpp"
#include <QApplication>
#include "first_order_logic_prover/first_order_logic.hpp"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
