#include "cos.h"
#include <random>
int WishList::adauga_film_wishlist(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul)
{
	Film film{ titlul,genul,actorul,anul };
	cos_filme.push_back(film);
	notify();
	int size = static_cast<int>(cos_filme.size());
	return size;
	
	
}

void WishList::goleste_cos()
{
	cos_filme.clear();
	notify();

}

const vector<Film> WishList::get_lista_cos() const
{
	return cos_filme;
}

int WishList::genereaza_filme(vector<Film> lista_originala,int nr_filme)
{
	std::mt19937 mt{ std::random_device{}() };
	if (lista_originala.size() == 0)
		cout << "adauga filme mai intai fraiere!" << endl;
	std::uniform_int_distribution<> dist(0,lista_originala.size()-1);
	
	for (int i = 1; i <= nr_filme; i++)
	{
		int poz = dist(mt);
		Film film = lista_originala[poz];	
		cos_filme.push_back(film);
		
	}
	int size = static_cast<int>(cos_filme.size());
	notify();
	return size;

}

void WishList::exporta_cos(string file)
{
	ofstream myfile;
	myfile.open(file);
	for(Film& film:cos_filme)
		myfile << film.pretty_print()<<endl;
	myfile.close();
}

