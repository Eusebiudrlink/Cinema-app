#include "service.h"


void Srv::srv_add(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul)
{
	Film film{ titlul,genul,actorul,anul };
	valid.valideaza(film);
	repository.add_film(film);
	undoActions.push_back(std::make_unique<UndoAdauga>(repository, film));
	
}

const  vector<Film> Srv::get_lista_srv()const
{
	return repository.get_lista();
}

void Srv::srv_delete(const std::string& titlul)
{
	    Film film = repository.cauta_film(titlul);
		repository.delete_film(film);

		undoActions.push_back(std::make_unique<UndoSterge>(repository, film));
}

void Srv::srv_update(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul)
{
	Film filmtoDel = repository.cauta_film(titlul);
	Film filmtoAdd{ titlul,genul,actorul,anul };
	repository.update_film(filmtoAdd);
	undoActions.push_back(std::make_unique<UndoUpdate>(repository, filmtoAdd,filmtoDel));
	
}

Film Srv::srv_cauta_film(std::string titlul)
{
	const Film film = repository.cauta_film(titlul);
	return film;

}


vector<Film> Srv::filter(std::function<bool(const Film&)> fct)
{
	vector<Film> filme = repository.get_lista();
	vector<Film> filtrata;
	copy_if(filme.begin(), filme.end(), back_inserter(filtrata), fct);
	return filtrata;
}

vector<Film> Srv::an_filter(int an) {
	return filter([an](const Film& o) noexcept {
		return o.get_an() == an;
		});
}
vector<Film> Srv::gen_filter(string gen) {
	return filter([gen](const Film& o) noexcept {
		return o.get_gen() == gen;
		});
}

vector<Film> Srv::sortedAn() {
	auto sorted = repository.get_lista();
	sort(sorted.begin(), sorted.end(), cmpAn);
	return sorted;
}

vector<Film> Srv::sortedTitlu() {
	auto sorted = repository.get_lista();
	sort(sorted.begin(), sorted.end(), cmpTitlu);
	return sorted;
}



void Srv::undo()
{
	if (undoActions.empty()) {
		throw RepoException{ "Nu mai exista operatii pentru undo!!" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
