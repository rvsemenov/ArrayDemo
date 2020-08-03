//
//  main.cpp
//  test
//
//  Created by Roman Semenov on 28/07/2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#include <iostream>
#include "CArray.h"

void testIntArray()
{
// 1.1. добавление в цикле 20 случайных чисел в диапазоне от 0 до 100.
  const int size = 20;
  CArray<int> array;
  for (unsigned int i = 0; i < size; ++i)
  {
    int rnd = rand() % 100;
    array.push_back(rnd);
  }
  array.print();

// 1.2. упорядочивание получившегося набора чисел по возрастанию.
  std::sort(array.begin(), array.end());
  array.print();

// 1.3. удаление каждого 2 элемента.
  bool removeFlag = false;
  CArray<int>::Iterator iter = std::remove_if(array.begin(), array.end(), [&removeFlag] (const int& i)
  {
    removeFlag = !removeFlag;
    return removeFlag;
  });
  array.erase(iter, array.end());
  array.print();
  
// 1.4. вставка 10 случайных чисел в диапазоне от 0 до 100 на случайные позиции.
  for (unsigned int i = 0; i < 10; ++i)
  {
    int rnd = rand() % 100;
    int index = rand() % array.size();
    array.insert(index, rnd);
  }
  array.print();

// 1.5. очистка контейнера.
  array.clear();
  array.print();
}

void testStringArray()
{
  CArray<std::string> dictionary;
  dictionary.push_back("hello");
  dictionary.push_back("world");
  dictionary.push_back("git");
  dictionary.push_back("c++");
  dictionary.push_back("g5");
  dictionary.push_back("work");
  dictionary.push_back("developer");
  
// 2.1. добавление в цикле 15 случайно выбранных слов, состоящих из латинских букв в нижнем регистре.
  CArray<std::string> array;
  for (int i = 0; i < 15; ++i)
  {
    const std::string& randWord = dictionary[rand() % dictionary.size()];
    array.push_back(randWord);
  }
  array.print();

// 2.2. упорядочивание получившегося набора слов по возрастанию.
  std::sort(array.begin(), array.end());
  array.print();

// 2.3. удаление каждого слова, включающего в себя любую из букв a, b, c, d, e.
  CArray<std::string>::Iterator iter = std::remove_if(array.begin(), array.end(), [] (const std::string& _str) {
    return std::string::npos != _str.find_first_of("abcde");
  });
  array.erase(iter, array.end());
  array.print();
 
// 2.4. вставка 3 новых случайно выбранных слов на случайные позиции.
  for (int i = 0; i < 3; ++i)
  {
    const std::string& randWord = dictionary[rand() % dictionary.size()];
    int index = rand() % array.size();
    array.insert(index, randWord);
  }
  array.print();
}

int main(int argc, const char * argv[])
{

  testIntArray();
  testStringArray();
  
  return 0;
}
