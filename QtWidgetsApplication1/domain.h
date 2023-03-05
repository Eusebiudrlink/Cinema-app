#pragma once
#include <iostream>
#include <string>

//titlu,gen,an,actor
class Film{
private:
	std::string titlu;
	std::string gen;
	std::string actor;
	int an;

public:
	Film() = default;
	Film(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul);
	
	Film(const Film& copie);
	~Film();

	const std::string& get_titlu() const noexcept;

	const std::string& get_gen() const noexcept;

	const std::string& get_actor() const  noexcept;
	
	const int get_an() const noexcept;

	const std::string pretty_print() const;



	

	void set_titlu(std::string& titlul);

	void set_gen(std::string& genul);

	void set_actor(std::string& actorul);

	void set_an(int anul);



};
bool cmpAn(const Film& o1, const Film& o2) noexcept;

bool cmpTitlu(const Film& o1, const Film& o2) noexcept;