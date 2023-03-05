#include "Filmegui.h"
#include <fstream>
#include <set>


void FilmeStoreGUI::initGUI() {

	this->setLayout(lyMain);
	QLabel* label = new QLabel(this);
	
	label->setText("CINEMA");
	label->setStyleSheet("background-color:orange");
	lyMain->addWidget(label);

	
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lblCate);
	vl->addWidget(lst);
	
	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);

	btnSortByAn = new QPushButton("Sort by an");
	btnSortByAn->setStyleSheet("background-color:turquoise;");
	lyBtnsDr->addWidget(btnSortByAn);
	btnSortByTitlu = new QPushButton("Sort by titlu");
	btnSortByTitlu->setStyleSheet("background-color:turquoise;");
	lyBtnsDr->addWidget(btnSortByTitlu);
	btnDelete = new QPushButton("Delete");
	btnDelete->setStyleSheet("background-color:turquoise;");
	lyBtnsDr->addWidget(btnDelete);

	QWidget* widBtnUndo = new QWidget;
	QHBoxLayout* lyBtnUndo= new QHBoxLayout;
	widBtnUndo->setLayout(lyBtnUndo);

	btnUndo = new QPushButton("UNDO");
	lyBtnUndo->addWidget(btnUndo);

	vl->addWidget(widBtnDreapta);
	vl->addWidget(widBtnUndo);
	lyMain->addWidget(widDreapta);

	//PARTEA DREAPTA*****************************
	
	QWidget* widStanga = new QWidget;
	QVBoxLayout* stanga = new QVBoxLayout;
	widStanga->setLayout(stanga);


	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtTitlu = new QLineEdit;
	formLDetalii->addRow(new QLabel("Titlu:"), txtTitlu);
	txtGen = new QLineEdit;
	formLDetalii->addRow(new QLabel("Gen:"), txtGen);
	txtActor = new QLineEdit;
	formLDetalii->addRow(new QLabel("actor:"), txtActor);
	txtAn = new QLineEdit;
	formLDetalii->addRow(new QLabel("An:"), txtAn);

	QWidget* widBtnStanga = new QWidget;
	QHBoxLayout* lyBtnsSt = new QHBoxLayout;
	widBtnStanga->setLayout(lyBtnsSt);

	btnAdd = new QPushButton("Add film");
	lyBtnsSt->addWidget(btnAdd);
	btnUpdate = new QPushButton("Update");
	lyBtnsSt->addWidget(btnUpdate);

	stanga->addWidget(widDetalii);
	stanga->addWidget(widBtnStanga);


	//filtrare
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);

	editFilterGen = new QLineEdit();
	lyFormFilter->addRow(new QLabel("Gen filtrare"), editFilterGen);
	btnFilter = new QPushButton("Filtreaza");
	lyFormFilter->addWidget(btnFilter);

	stanga->addWidget(formFilter);
	lyMain->addWidget(widStanga);
	

	//partea cu cosul observer

	QWidget* widCos = new QWidget;
	QVBoxLayout* lycos = new QVBoxLayout;
	widCos->setLayout(lycos);

	btnCosCrud = new QPushButton("Creeaza CosCRUD");
	lycos->addWidget(btnCosCrud);
	btnCosRead = new QPushButton("Creeaza CosReadOnly");
	lycos->addWidget(btnCosRead);
	lyMain->addWidget(widCos);





	
}

void FilmeStoreGUI::connectSignalsSlots()
{
	
		
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByAn, &QPushButton::clicked, [&]() {
		
		reloadList(ctr.sortedAn());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByTitlu, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortedTitlu());
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &FilmeStoreGUI::addNewFilm);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &FilmeStoreGUI::deleteFilm);
	QObject::connect(btnUpdate, &QPushButton::clicked, this, &FilmeStoreGUI::UpdateFilm);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &FilmeStoreGUI::UndoFilm);
	QObject::connect(btnFilter, &QPushButton::clicked, this, &FilmeStoreGUI::filter);
	QObject::connect(btnCosCrud, &QPushButton::clicked, this, &FilmeStoreGUI::creeaza_cosCrud);
	QObject::connect(btnCosRead, &QPushButton::clicked, this, &FilmeStoreGUI::creeaza_cosDesenat);

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtGen->setText("");
			txtActor->setText("");
			txtTitlu->setText("");
			txtAn->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto titlu = selItem->text();
			auto gen= selItem->data(Qt::UserRole).toString();
			
			txtTitlu->setText(titlu);
			auto p = ctr.srv_cauta_film(titlu.toStdString());
			txtGen->setText(QString::fromStdString(p.get_gen()));
			txtAn->setText(QString::number(p.get_an()));
			txtActor->setText(QString::fromStdString(p.get_actor()));
		}
		});

}

void FilmeStoreGUI::reloadList(const std::vector<Film>& filme)
{

	lblCate->setText(QString{ "Filme disponibile: " } + QString::number(filme.size()));
	
	lst->clear();
	for (const auto& p : filme) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_titlu()));
		lst->addItem(item);

	}

	
}

void FilmeStoreGUI::addNewFilm()
{
	try {
		ctr.srv_add(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAn->text().toDouble());
		reloadList(ctr.get_lista_srv());
	}
	catch (MyException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
	}
	
}

void FilmeStoreGUI::deleteFilm()
{
	try {
		ctr.srv_delete(txtTitlu->text().toStdString());
		reloadList(ctr.get_lista_srv());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
	}
}

void FilmeStoreGUI::UpdateFilm()
{
	try {
		ctr.srv_update(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAn->text().toDouble());
		reloadList(ctr.get_lista_srv());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
	
	}
}

void FilmeStoreGUI::UndoFilm()
{
	try {
		ctr.undo();
		reloadList(ctr.get_lista_srv());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
	}
}



void FilmeStoreGUI::filter()
{
	reloadList(ctr.gen_filter(editFilterGen->text().toStdString()));

}

void FilmeStoreGUI::creeaza_cosCrud()
{
	auto cosWindow = new CosGui{ ctr,wishlist };
	cosWindow->show();
}

void FilmeStoreGUI::creeaza_cosDesenat()
{
	auto cosDesenat = new HistogramaGUI{ wishlist };
	cosDesenat->show();
}




