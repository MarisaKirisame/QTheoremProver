#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QSignalMapper>
#include "first_order_logic_prover/praser.hpp"
#include "QProofModel.hpp"
#include <QtCore>
#include "first_order_logic_prover/gentzen_system.hpp"
#include <QMessageBox>
#include "first_order_logic_prover/first_order_logic.hpp"
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
	connect(signalMapper, SIGNAL(mapped( const QString & )), ui->lineEdit, SLOT(AppendString( const QString & )));
	for ( auto i : buttons )
	{
		signalMapper->setMapping( i, i->text( ) );
		connect( i, SIGNAL(pressed()), signalMapper, SLOT(map()));
		connect( i, SIGNAL(released()), this, SLOT(GiveFocus()) );
	}
	setFocusPolicy( Qt::StrongFocus );
	setFocusProxy( ui->lineEdit );
	connect( ui->pushButton, SIGNAL(released()), this, SLOT(GiveFocus()) );
	ui->lineEdit->setFocus( Qt::OtherFocusReason );
}

MainWindow::~MainWindow( ) { delete ui; }

void MainWindow::GiveFocus( ) { ui->lineEdit->setFocus( Qt::OtherFocusReason ); }

void MainWindow::on_lineEdit_returnPressed( ) { on_pushButton_clicked( ); }

void MainWindow::on_pushButton_clicked()
{
	auto res = first_order_logic::prase( ui->lineEdit->text( ).toStdString( ) );
	if ( ! res )
	{
		QMessageBox msgBox( this );
		msgBox.setText( "Error in parsing formula. Please check input or file an issue." );
		msgBox.exec( );
		return;
	}
	auto ret = first_order_logic::gentzen_system::is_valid( * res );
	ui->label->setText( ret.second ? "valid" : "falsible" );
	QProofModel * pm = new QProofModel( ret.first, nullptr );
	ui->treeView->setModel( pm );
	ui->lineEdit->setText( "" );
}
