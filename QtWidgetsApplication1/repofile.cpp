#include "repofile.h"

void RepoFilmeFile::load_from_file()
{
	ifstream fin(fName);
	if (!fin.is_open())
		throw RepoException("Fisierul nu a putut fi deschis\n");
	while (!fin.eof())
	{
		string titlu,autor,gen;
		int an;
		fin >> titlu;
		if (fin.eof())break;
		fin >> gen;
		fin >> autor;
		fin >> an;

		Film film{ titlu,gen,autor,an};
		Repo::add_film(film);
	}
	fin.close();
}

void RepoFilmeFile::write_to_file()
{
	ofstream fout(fName);
	if (!fout.is_open()) {
		throw RepoException("Error open file!");
	}
	for (auto& film : get_lista())
	{
		fout << film.get_titlu() << endl;
		fout << film.get_gen() << endl;
		fout << film.get_actor() << endl;
		fout << film.get_an() << endl;

	}
	
	fout.close();

}
