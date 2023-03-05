#include "domain.h"
#include <string>
using namespace std;


Film::Film(const std::string& titlul, const std::string& genul, const std::string& actorul, int anul) : titlu{ titlul }, gen{ genul }, actor{ actorul }, an{ anul }{
}
Film::Film(const Film& copie) : titlu{ copie.titlu }, gen{ copie.gen }, actor{ copie.actor }, an{ copie.an }{
	
}
Film:: ~Film() {
}
const std::string& Film ::get_titlu() const noexcept {
	return this->titlu;
}
const std::string& Film::get_gen() const noexcept {
	return this->gen;
}
const std::string& Film::get_actor() const noexcept {
	return this->actor;
}
const int Film::get_an() const noexcept {
	return this->an;
}

const std::string Film::pretty_print() const
{
	std::string an = to_string(this->an);
	return this->titlu + " " + this->gen + " " + this->actor + " " + an;
}





void Film::set_titlu(std::string& titlul)
{
	this->titlu = titlul;
}

void Film::set_gen(std::string& genul)
{
	this->gen = genul;
}

void Film::set_actor(std::string& actorul)
{
	this->actor = actorul;
}

void Film::set_an(int anul)
{
	this->an = anul;
}

bool cmpAn(const Film& o1, const Film& o2) noexcept {
	return o1.get_an() < o2.get_an();
}
bool cmpTitlu(const Film& o1, const Film& o2) noexcept {
	return o1.get_titlu() < o2.get_titlu();
}


