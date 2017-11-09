// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len) : BitLen(len) //41
{
  if (len < 0)
    throw "negative length";
  MemLen = (BitLen / BITS_IN_ONE_MEM) + 1; // исправить под любой размер TELEM
  pMem = new TELEM[MemLen];
  if (pMem != NULL){
	  for (int i = 0; i < MemLen; i++){
		  pMem[i] = 0;
	  }
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL){
	for (int i=0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
	}
}

TBitField::~TBitField()
{
	delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / BITS_IN_ONE_MEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (TELEM)1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen)){
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else {
		throw "wrong findex";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen)){
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else {
		throw "wrong findex";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int a;
	if ((n > -1) && (n < BitLen)){
		a = pMem[GetMemIndex(n)] & GetMemMask(n);
		if (a > 0)
			return 1;
		else return 0;
	}
	else {
		throw "wrong findex";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen){
	MemLen = bf.MemLen;
	if (pMem != NULL){
		delete []pMem;
	}
	pMem = new TELEM[MemLen];
	}
	if (pMem != NULL) {
		for (int i = 0; i < MemLen; i++){
			pMem[i] = bf.pMem[i];
		}	
	}
  return *this;
} //33

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (MemLen != bf.MemLen){ 
		res = 0; 
	}
	else{
		if (BitLen != bf.BitLen){
			res = 0;
		}

		else{
			for (int i = 0; i < MemLen; i++){
				if (pMem[i] != bf.pMem[i]){
					res = 0;
					break;
				}
			}
			/*for (int i = 0; i < BitLen; i++){
				if (GetBit(i) != bf.GetBit(i)){
					res = 0;
					break;
				}*/
			//}
		}
	}
  return res;
} //30

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	/*int res = 0;
	if (BitLen != bf.BitLen){
		res = 1;
	}
	else{
		for (int i = 0; i < MemLen; i++){
			if (pMem[i] != bf.pMem[i]){
				res = 1;
				break;
			}
		}
	}*/
	bool res = (*this == bf);
  return !res;
} //29

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (BitLen < bf.BitLen){
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++){
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++){
		temp.pMem[i] |= bf.pMem[i];
	}
  return temp;
} //28

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min = bf.BitLen; 
	int len = BitLen;
	if (BitLen < bf.BitLen){
		min = BitLen;
		len = bf.BitLen;
	}
	
	TBitField temp(len);

	 // !!!!

	//for (int i = 0; i < MemLen; i++){
	//	temp.pMem[i] = pMem[i];
	//}
	for (int i = 0; i < temp.MemLen; i++){
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	
	
	/*int min = bf.BitLen;
	if(BitLen < bf.~TBitField){
		min = BitLen;
	}
	TBitField temp(min);
	for (int i = 0; i < temp.MemLen; i++){
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}*/
	return temp;
} //25

TBitField TBitField::operator~(void) // отрицание
{
	int pos = 0;
	int len = BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen - 1; i++)
	{
		temp.pMem[i] = ~pMem[i];
	}
	// дальше побитово
	/*for (int i = (MemLen - 1) * BITS_IN_ONE_MEM; i < BitLen; i++)
	{
		//if (temp.GetBit(i) == 1) { temp.ClrBit(i); }
		//else (temp.SetBit(i));

	}*/
	
	/*for (int i = BitLen - 1; i <= (MemLen - 1) * BITS_IN_ONE_MEM; i--)
	{
		temp.ClrBit(i);
		if (temp.GetBit(i) == 1) { pos = i; break; }
	}

	for (int i = (MemLen - 1) * BITS_IN_ONE_MEM; i < pos; i++){
		if (temp.GetBit(i) == 1) { temp.ClrBit(i); }
		else (temp.SetBit(i));
	}*/
  
	
	for (int i = BitLen - 1; i > ((MemLen - 1) * BITS_IN_ONE_MEM); i--)
	{
		
		if (GetBit(i) == 1) {
			pos = i;
			temp.ClrBit(i);
			break;
		} 
		//if (temp.GetBit(i) == 1) { temp.ClrBit(i); }
		//else (temp.SetBit(i));

	}

	for (int i = ((MemLen - 1) * BITS_IN_ONE_MEM); i < pos; i++){
		if (GetBit(i) == 0) { temp.SetBit(i); }
		else { temp.ClrBit(i); }
	}
	
	return temp;

	/*int len = BitLen;
	int i = 0;
	int pos;
	TBitField temp(len);
	do {
		temp.ClrBit(i);
		i = i + 1;
	} while ((temp.GetBit(i) != 1) || (i < len));
	pos = i;
	for (i = pos; i < BitLen; i++){
		if (temp.GetBit(i) == 1) { temp.ClrBit(i); }
		else (temp.SetBit(i));
	}
	return temp;*/
}//24

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int bl, inp;
	cout << "enter bitLen" << endl;
	cin >> bl;
	TBitField tbf(bl);
	cout << "enter bitField" << endl;
	for (int i = 0; i < tbf.BitLen; i++){
		if (inp == 0){
			tbf.ClrBit(i);
		}
		else{
			if (inp == 1){
				tbf.SetBit(i);
			}
			else { break; }
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++){
		if (bf.GetBit(i) == 0){
			ostr << 0;
		}
		else{
			ostr << 1;
		}
	}
	ostr << endl;
  return ostr;
}
