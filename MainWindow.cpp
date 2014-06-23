#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QSignalMapper>
#include "theorem_prover/first_order_logic/praser.hpp"
#include "QProofModel.hpp"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	buttons =
	{
		ui->pushButton_2,
		ui->pushButton_3,
		ui->pushButton_4,
		ui->pushButton_5,
		ui->pushButton_6,
		ui->pushButton_7,
		ui->pushButton_8,
		ui->pushButton_9,
		ui->pushButton_10
	};
	QSignalMapper *signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped( const QString & )), this, SIGNAL(AppendString( const QString & )));
	for ( auto i : buttons )
	{
		signalMapper->setMapping( i, i->text( ) );
		connect( i, SIGNAL(clicked()), signalMapper, SLOT(map()));
	}
}

MainWindow::~MainWindow( ) { delete ui; }

void MainWindow::AppendString( const QString & str )
{
	QString new_str( ui->lineEdit->text( ) );
	new_str.insert( ui->lineEdit->cursorPosition( ), str );
	ui->lineEdit->setText( new_str );
}

void MainWindow::on_pushButton_clicked()
{
	auto res = theorem_prover::first_order_logic::prase( ui->lineEdit->text( ).toStdString( ) );
	ui->label->setText( res->is_valid( ) ? "true" : "false" );
//	QProofModel * pm = new QProofModel( res, nullptr );
//	ui->treeView->setModel( pm );
}
