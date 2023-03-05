
#include "repo.h"
#include <algorithm>


 void Repo::add_film(Film& film)
{
	for (Film& filmul : lista_filme)
	{
		if (filmul.get_titlu() == film.get_titlu())
			throw RepoException("Filmul exista deja in lista!");
	}
	lista_filme.push_back(film);
	
}
const vector<Film> Repo::get_lista() const
{
	vector<Film> copie;
	copie = lista_filme;
	return copie;
}

 void Repo::delete_film(Film& film)
{
	for(int i=0;i<lista_filme.size();i++)
	{ 
		Film& filmul=lista_filme[i];
		if (film.get_titlu() == filmul.get_titlu())
		{
			lista_filme.erase(lista_filme.begin() + i);
			break;
		}
	}
}

void Repo::update_film(Film film)
{
	for (Film& filmm:lista_filme)
	{
		if (filmm.get_titlu() == film.get_titlu())
			filmm = film;
	}
}

const Film& Repo::cauta_film(const std::string& titlul){
	vector<Film>::iterator f = std::find_if(lista_filme.begin(), lista_filme.end(),
		[=](const Film& film) {
			return film.get_titlu() == titlul;
		});

	if (f != lista_filme.end())
		return (*f);
	else
		throw RepoException("Filmul cu titlul _ " + titlul +  " _ nu e in lista\n"); }




const size_t Repo::get_lungime()const noexcept
{
	return lista_filme.size();
}


