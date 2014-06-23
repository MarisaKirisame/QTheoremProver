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
	void AppendString( const QString & );
private slots:
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
