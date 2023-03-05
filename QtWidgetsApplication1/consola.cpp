#include "consola.h"
#include <assert.h>
#include <vector>

using namespace std;



void Consola::show_menu()
{
	cout << "Meniul aplicatiei de gestiune a filmelor:" << endl;
	cout << "Scrieti cifra corespunzatoare comenzii dorite!" << endl;
	cout << "1-adauga film" << endl;
	cout << "2-afiseaza filme" << endl;
	cout << "3-modifica film" << endl;
	cout << "4-sterge film" << endl;
	cout << "5-cauta film" << endl;
	cout << "6-filtrare carti" << endl;
	cout << "7-ordoneaza carti" << endl;
	cout << "8-wish list" << endl;
	cout << "9-undo" << endl;

}
void Consola::show_menu_wishlist()
{
	cout << "1-goleste cos" << endl;
	cout << "2-adauga in cos" << endl;
	cout << "3-genereaza cos" << endl;
	cout << "4-export cos" << endl;
	cout << "5-afiseaza cos" << endl;
	cout << "0-inapoi la meniu principal" << endl;
}

void Consola::afiseaza_filme()
{
	vector<Film> filme = serv.get_lista_srv();

	for (const Film& film : filme)
	{
		cout << film.pretty_print() << endl;
	}
}

void Consola::adauga_film()
{
	int anul;
	std::string titlu{}, gen{}, autor{}, an{};
	cout << "titlu:";
	cin >> titlu;
	cout << "gen:";
	cin >> gen;
	cout << "autor:";
	cin >> autor;
	cout << "an:";
	cin >> an;
	try {
		anul = stoi(an);
		try {
			serv.srv_add(titlu, gen, autor, anul);
			cout << "film adaugat cu succes!" << endl;
		}
		catch (MyException& e) {
			cout << e.what() << endl;
		}
		catch (RepoException& e) {
			cout << e.getErrorMessage() << endl;
		}
	}
	catch (...)
	{
		cout << "anul trebuie sa fie cifra!" << endl;

	}

}
void Consola::sterge_film()
{
	std::string titlu{};
	cout << "titlu film de sters:";
	cin >> titlu;
	try {
		serv.srv_delete(titlu);
		cout << "filmul a fost sters!" << endl;
	}
	catch (...) {
		cout << "Filmul nu exista in lista" << endl;
	}

}
void Consola::modifica_film()
{
	int an;
	std::string titlu{}, gen{}, autor{};
	cout << "titlu:";
	cin >> titlu;
	cout << "gen:";
	cin >> gen;
	cout << "autor:";
	cin >> autor;
	cout << "an:";
	cin >> an;
	try {
		serv.srv_update(titlu, gen, autor, an);
		cout << "film modificat cu succes!" << endl;
	}
	catch (...) {
		cout << "Filmul nu exista in lista" << endl;
	}

}


void Consola::cauta_film()
{
	std::string titlu{};
	cout << "titlu:";
	cin >> titlu;
	try	
	{	
		Film gasit = serv.srv_cauta_film(titlu);
		cout << gasit.pretty_print() << endl;
	}
	catch (...) {
		cout << "Filmul nu exista!" << endl;
	}
}
void Consola::sortare_carti()
{
	cout << "sortare dupa:(titlu,an)";

	std::string tipul{}, titlul{ "titlul" }, anul{ "an" };
	cin >> tipul;

	vector<Film> filme = serv.get_lista_srv();
	vector<Film> filtrate;
	if (tipul == anul)
	{
		filtrate = serv.sortedAn();

		for (const Film& film : filtrate)
		{
			cout << film.pretty_print() << endl;
		}
	}
	else
		if(tipul == titlul)
	{
		filtrate = serv.sortedTitlu();

		for (const Film& film : filtrate)
		{
			cout << film.pretty_print() << endl;
		}
	}



}


void Consola::adauga_wishlist()
{
	int anul;
	std::string titlu{}, gen{}, autor{}, an{};
	cout << "titlu:";
	cin >> titlu;
	cout << "gen:";
	cin >> gen;
	cout << "autor:";
	cin >> autor;
	cout << "an:";
	cin >> an;
	try {
		anul = stoi(an);
		try {
			auto nr_filme=cos.adauga_film_wishlist(titlu, gen, autor, anul);
			cout << "Numarul de filme actual din cos este: " << nr_filme << endl;
		
		}
		catch (MyException& e) {
			cout << e.what() << endl;
		}
		catch (...) {
			cout << "Filmul exista deja in lista" << endl;
		}
	}
	catch (...)
	{
		cout << "anul trebuie sa fie cifra!" << endl;

	}

}

void Consola::afiseaza_cos()
{
	vector<Film> filme = cos.get_lista_cos();
	for (const Film& film : filme)
		cout << film.pretty_print() << endl;
}

void Consola::genereaza()
{
	int nr_filme;
	cin >> nr_filme;//presupunem ca e introdus corect
	auto  filme = serv.get_lista_srv();
	auto nr = cos.genereaza_filme(filme,nr_filme);
	cout << "Numarul de filme actual din cos este: " << nr << endl;
}

void Consola::exporta()
{
	string file{};
	cout << "in ce fiser sa se exporte?" << endl;
	cin >> file;
	cos.exporta_cos(file);
}

void Consola::undo_ui()
{
	try {
		serv.undo();
	}
	catch (RepoException& e)
	{
		cout << e.getErrorMessage() << endl;;
	}
}

void Consola::menu_wish_list()
{
	show_menu_wishlist();
	int cmd_wish;
	while (true)
	{
		cout << ">>>";
		try
		{
			cin >> cmd_wish;
		}
		catch (exception esc_wish)
		{
			cout << "comanda invalida" << endl;
		}

		switch (cmd_wish)
		{
		case 1:
			cos.goleste_cos();
			cout << "numarul de filme din cos este 0" << endl;
			break;
		case 2:
			adauga_wishlist();
			break;
		case 3:
			genereaza();
			break;
		case 4:
			exporta();
			break;
		case 5:
			afiseaza_cos();
			break;
		case 0:
			show_menu();
			return;

		default:
			continue;

		}


	}


}


void Consola::filtrare_carti()
{
	int an=-1;
	std::string genul{};
	std::string tipul{}, anul{ "an" };
	cout << "gen sau an:"<<endl;
	cin >> tipul;

	vector<Film> filme = serv.get_lista_srv();
	vector<Film> filtrate;
	if (tipul==anul)
	{
		cout << "anul: ";
		cin >> an;

		filtrate = serv.an_filter(an);
		
		for (const Film& film :filtrate)
		{
				cout << film.pretty_print() << endl;
		}
	}
	else
	{
		cout << "genul: ";
		cin >> genul;
	
		filtrate = serv.gen_filter(genul);

		for (const Film& film : filtrate)
		{
			cout << film.pretty_print() << endl;
		}
	}
}



void Consola::start_consola()
{	
	int cmd;
	show_menu();
	while (true)
	{
		cout << ">>>";
		try 
		{
			cin >> cmd;
		}
		catch(exception esc)
		{
			cout << "comanda invalida"<<endl;
		}
		switch (cmd)
		{
		case 1:
			adauga_film();
			break;
		case 2:
		   afiseaza_filme();
			break;
		
		case 3:
			modifica_film();
			break;
		case 4:
			sterge_film();
			break;
		
		case 5:
			cauta_film();
			break;
		case 6:
			filtrare_carti();
			break;
		case 7:
			sortare_carti();
			break;
		case 8:
			menu_wish_list();
			break;
		case 9:
			undo_ui();
			break;
		default:
			continue;

		}

	}
}




