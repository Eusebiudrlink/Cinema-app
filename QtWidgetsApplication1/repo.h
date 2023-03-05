#pragma once

#include <vector>
#include "domain.h"
#include "observer.h"


using namespace std;

class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class Repo {
public:
	Repo()= default;
	Repo(const Repo& ot) = delete;
	virtual ~Repo() = default;

	virtual void add_film(Film& film);

	const vector<Film> get_lista() const;

	virtual void delete_film(Film& film);

	virtual void update_film(Film film);

	const Film& cauta_film(const std::string& titlul);
	
	const  size_t get_lungime()const noexcept;


private:
	vector<Film> lista_filme;

};