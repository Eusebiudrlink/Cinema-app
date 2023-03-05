#pragma once

#include "domain.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Film film;
	Repo& rep;

public:
	UndoAdauga(Repo& rep, Film film) :rep{ rep }, film{  film }{}
	void doUndo() override{
		rep.delete_film(film);
	}
};

class UndoSterge : public ActiuneUndo {
	Film film;
	Repo& rep;

public:
	UndoSterge(Repo& rep, Film& film) : rep{ rep }, film{ film }{}
	void doUndo() override {
		rep.add_film(film);
	}

};

class UndoUpdate : public ActiuneUndo {
	Film filmtoAdd;
	Film filmtoDel;
	Repo& rep;

public:
	UndoUpdate(Repo& rep, Film& filmtoAdd, Film& filmtoDel) : rep{ rep }, filmtoAdd{ filmtoAdd }, filmtoDel{ filmtoDel }{}
	void doUndo()override {
		rep.delete_film(filmtoAdd);
		rep.add_film(filmtoDel);
	}


};