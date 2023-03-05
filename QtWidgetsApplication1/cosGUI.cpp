#include "cosGUI.h"

void CosGui::initCosGui()
{	
	//PARTEA STANGA
	this->setLayout(lyCosMain);

	QWidget* stg = new QWidget;
	QVBoxLayout* lystg = new QVBoxLayout;
	stg->setLayout(lystg);

	lst = new QListWidget();
	lystg->addWidget(lst);

	QWidget* Form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	Form->setLayout(lyForm);

	txtgenre = new QLineEdit;
	lyForm->addRow(new QLabel{ "Cate sa se genereze" }, txtgenre);

	btnGenre = new QPushButton("Genereaza");
	lyForm->addWidget(btnGenre);

	lystg->addWidget(Form);

	lyCosMain->addWidget(stg);

	//PARTEA DREAPTA
	QWidget* dr = new QWidget;
	QVBoxLayout* lydr = new QVBoxLayout;
	dr->setLayout(lydr);

	QWidget* formdr = new QWidget;
	QFormLayout* lyformdr = new QFormLayout;
	formdr->setLayout(lyformdr);

	txt1 = new QLineEdit;
	txt2 = new QLineEdit;
	txt3 = new QLineEdit;
	txt4 = new QLineEdit;

	lyformdr->addRow(new QLabel{ "titlu" }, txt1);
	lyformdr->addRow(new QLabel{ "gen" }, txt2);
	lyformdr->addRow(new QLabel{ "autor" }, txt3);
	lyformdr->addRow(new QLabel{ "an" }, txt4);

	btnadd = new QPushButton("adauga");
	lyformdr->addWidget(btnadd);

	lydr->addWidget(formdr);

	btngoleste = new QPushButton("goleste");
	lydr->addWidget(btngoleste);

	btnexport = new QPushButton("exporta");
	lydr->addWidget(btnexport);



	lyCosMain->addWidget(dr);


}

void CosGui::conectSignal()
{
	wishlist.addObserver(this);
	QObject::connect(btnGenre, &QPushButton::clicked, this, &CosGui::genre);
	QObject::connect(btnadd, &QPushButton::clicked, this, &CosGui::add_film);
	QObject::connect(btngoleste, &QPushButton::clicked, this, &CosGui::goleste);
}

void CosGui::reloadGui(vector<Film> filme)
{
	lst->clear();
	for (auto& film : filme)
	{
		
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(film.get_titlu()) };
		lst->addItem(item);
	}

}

void CosGui::add_film()
{
	try {
		wishlist.adauga_film_wishlist(txt1->text().toStdString(), txt2->text().toStdString(), txt3->text().toStdString(), txt4->text().toDouble());
		reloadGui(wishlist.get_lista_cos());
	}
	catch (MyException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
	}
}

void CosGui::genre()
{
	wishlist.genereaza_filme(serv.get_lista_srv(), txtgenre->text().toDouble());
	reloadGui(wishlist.get_lista_cos());
}

void CosGui::goleste()
{
	wishlist.goleste_cos();
	reloadGui(wishlist.get_lista_cos());
}


