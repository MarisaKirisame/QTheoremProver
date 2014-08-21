#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <vector>
namespace Ui { class MainWindow; }
class QPushButton;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow( );
	std::vector< QPushButton * > buttons;
signals:
private slots:
	void GiveFocus( );
	void on_pushButton_pressed();
	void on_lineEdit_returnPressed();
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
