#pragma once
#include "domain.h"
template <typename ElementT>
class IteratorVectorT;
#define INITIAL_CAPACITY 5
template <typename ElementT>
class vector
{
public:

	 
	vector();

	vector(const vector& ot); //rule of 3

	~vector();//rule of 3

	
	vector& operator=(const vector& ot);//rule of 3


	vector(vector&& ot); //rule of 5 

	vector& operator=(vector&& ot); //rule of 5 

	void swapp(int poz1, int poz2);

	void add(const ElementT& el);

	ElementT& get(int poz) const;

	void set(int poz, const ElementT& el);

	int size() const noexcept;

	friend class IteratorVectorT<ElementT>;
	//functii care creaza iteratori
	IteratorVectorT<ElementT> begin();
	IteratorVectorT<ElementT> end();


private:
	int lg;//numar elemente
	int cap;//capacitate
	ElementT* elems;//elemente

	void ensureCapacity();
};


template<typename ElementT>
vector<ElementT>::vector() :elems{ new ElementT[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}


template<typename ElementT>
vector<ElementT>::vector(const vector<ElementT>& ot) {
	elems = new ElementT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
}


template<typename ElementT>
vector<ElementT>& vector<ElementT>::operator=(const vector<ElementT>& ot) {
	if (this == &ot) {
		return *this;//s-a facut l=l;
	}
	delete[] elems;
	elems = new ElementT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}


template<typename ElementT>
vector<ElementT>::~vector() {
	delete[] elems;
}


template<typename ElementT>
vector<ElementT>::vector(vector&& ot) {

	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

template<typename ElementT>
vector<ElementT>& vector<ElementT>::operator=(vector<ElementT>&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename ElementT>
void vector<ElementT>::add(const ElementT& el) {
	ensureCapacity();//daca e nevoie mai alocam memorie
	elems[lg++] = el;
}

template<typename ElementT>
ElementT& vector<ElementT>::get(int poz) const {
	return elems[poz];
}

template<typename ElementT>
void vector<ElementT>::set(int poz, const ElementT& el) {
	elems[poz] = el;
}

template<typename ElementT>
int vector<ElementT>::size() const noexcept {
	return lg;
}

template<typename ElementT>
void vector<ElementT>::ensureCapacity() {
	if (lg < cap) {
		return; //mai avem loc
	}
	cap *= 2;
	ElementT* aux = new ElementT[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}
template<typename ElementT>
void vector<ElementT>::swapp(int poz1, int poz2)
{
	Film aux;
	aux = this->elems[poz1];
	this->elems[poz1] = this->elems[poz2];
	this->elems[poz2] = aux;
}

template<typename ElementT>
IteratorVectorT<ElementT> vector<ElementT>::begin()
{
	return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> vector<ElementT>::end()
{
	return IteratorVectorT<ElementT>(*this, lg);
}

template<typename ElementT>
class IteratorVectorT {
private:
	const vector<ElementT>& v;
	int poz = 0;
public:
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept;
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept;
	bool valid()const;
	ElementT& element() const;
	void next();
	ElementT& operator*();
	IteratorVectorT& operator++();
	bool operator==(const IteratorVectorT& ot)noexcept;
	bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const vector<ElementT>& v) noexcept :v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const vector<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const {
	return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
	poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
	return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
	return !(*this == ot);
}
