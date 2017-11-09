// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp < 0) { throw "wrong mp value"; }
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField temp(this->BitField);
	return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int res = 1;
	if ((Elem >= 0) & (Elem < MaxPower)){
		if (BitField.GetBit(Elem) != 1){ res = 0; }
	}
	else { throw "wrong findex"; }
    return res;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (!IsMember(Elem)){ BitField.SetBit(Elem); }
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (IsMember(Elem)){ BitField.ClrBit(Elem); }

}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res = 1;
	if (MaxPower != s.MaxPower){ res = 0; }
	else{
		if (BitField != s.BitField){ res = 0; }
	}
    return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	bool res = (*this == s);
	return !res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res(BitField | s.BitField);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	if (!IsMember(Elem)) { res.InsElem(Elem); }
	return res;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	if (IsMember(Elem)) { res.DelElem(Elem); }
	return res;

}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(BitField & s.BitField);
	return res;

}

TSet TSet::operator~(void) // дополнение
{
	TSet res(~BitField);
	return res;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{ 
	ostr << s.BitField;
	return ostr;
}
