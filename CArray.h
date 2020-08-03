//
//  CArray.h
//  test
//
//  Created by Roman Semenov on 28/07/2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#pragma once

template <typename TData>
class CArray
{
public:// Interface
  using Iterator = TData*;
  
  // Конструктор по умолчанию
  CArray();
  
  // Копирующий конструктор
  CArray(
      const CArray & _array
    );
  
  // Деструктор
  ~CArray();
  
  // Добавить элемент в конец массива
  void push_back(
      const TData & _value
    );
  
  // Добавить элемент в массив по заданному индексу
  void insert(
      unsigned int  _index,
      const TData & _value
    );
  
  // Удалить элемент массива по заданному индексу
  void erase(
      unsigned int _index
    );
  
  // Удалить элемнты массива в диапозоне
  Iterator erase (
      Iterator _first,
      Iterator _last
    );
  
  // Очистить массив
  void clear();
  
  // Получить размер массива
  unsigned int size() const;
  
  // Итератор начала массива
  Iterator begin();
  
  // Итератор конца массива
  Iterator end();
  
  // Получить элемент массива по заданному индексу
  TData & operator[](
      unsigned int _index
    );
  
  // Вывести содержимое массива
  void print();
protected: // Metods
  // Выделить память для буфера до mCapacity
  void reallocate();
protected: // Attributes
  // Кол-во элементов в массиве
  unsigned int mSize = 0;
  // Обьем массива
  unsigned int mCapacity = 1;
  // Буфер данных
  TData* mBuffer = nullptr;
};

template<typename TData>
CArray<TData>::CArray()
{
  mBuffer = new TData[mCapacity];
}

template<typename TData>
CArray<TData>::CArray(
    const CArray<TData> & _array
  )
{
  mSize = _array.mSize;
  mCapacity = _array.mCapacity;
  mBuffer = new TData[mCapacity];
  
  for (unsigned int i = 0; i < mSize; ++i)
    mBuffer[i] = _array.mBuffer[i];
}

template<typename TData>
CArray<TData>::~CArray()
{
  delete[] mBuffer;
}

template<typename TData>
void CArray<TData>::push_back(
    const TData & _value
  )
{
  if (mCapacity == mSize)
  {
    mCapacity <<= 1;
    reallocate();
  }
  
  mBuffer [mSize++] = _value;
}

template<typename TData>
void CArray<TData>::insert(
    unsigned int  _index,
    const TData & _value
  )
{
  if (mCapacity == mSize)
  {
    mCapacity <<= 1;
    reallocate();
  }
  
  CArray::Iterator it = &mBuffer[_index];
  memmove(it + 1, it, (mSize - _index) * sizeof(TData));
  ++mSize;
  mBuffer [_index] = _value;
}

template<typename TData>
void CArray<TData>::erase(
    unsigned int _index
  )
{
  CArray::Iterator it = &mBuffer[_index];
  (*it).~TData();
  memmove(it, it + 1, (mSize - _index - 1) * sizeof(TData));
  --mSize;
}

template<typename TData>
void CArray<TData>::clear()
{
  mSize = 0;
}

template<typename TData>
unsigned int CArray<TData>::size() const
{
  return mSize;
}

template<typename TData>
TData & CArray<TData>::operator[](
    unsigned int _index
  )
{
  return mBuffer[_index];
}

template <typename TData>
void CArray<TData>::reallocate()
{
		TData* arr = new TData[mCapacity];
		memcpy(arr, mBuffer, mSize * sizeof(TData));
		delete [] mBuffer;
		mBuffer = arr;
}

template<typename TData>
typename CArray<TData>::Iterator CArray<TData>::begin()
{
  return mBuffer;
}

template<typename TData>
typename CArray<TData>::Iterator CArray<TData>::end()
{
  return mBuffer + mSize;
}

template<typename TData>
typename CArray<TData>::Iterator CArray<TData>::erase (
    typename CArray<TData>::Iterator _first,
    typename CArray<TData>::Iterator _last
  )
{
  if (_first == _last)
    return _first;
  
  for (CArray<TData>::Iterator it = _first; it != _last; ++it)
    (*it).~TData();

  memmove(_first, _last, (mSize - (_last - mBuffer)) *  sizeof(TData));
  mSize -= _last - _first;
  return _first;
}

template<typename TData>
void CArray<TData>::print()
{
  for (int i = 0; i < mSize; ++i)
    std::cout << mBuffer[i] << ' ';
  
  std::cout << "\n";
}
