﻿/*
    Dla zadanej tablicy liczb całkowitych znajdź te pary, których różnica jest równa zadanej liczbie k.

    Przykład:
        Wejście:
        A[] = [1, 5, 2, 2, 2, 5, 5, 4]
        k = 3

        Wyjście: [2,5] oraz [1,4]
*/

#include <map>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

vector<int> GenerateRandomNumbers(int min, int max, int numbers); // Generowanie losowych liczb całkowitych
map<int, int> FindPairOfNumbers(vector<int> array, int diff); // Wyszukiwanie par
vector<int> LoadNumbersFromFile(string fileName); // Wczytywanie liczb z pliku tekstowego

int GetRandomNumber(int min, int max); // Generowanie liczby całkowitej z danego przedziału
void SaveResultsToFile(string fileName, map<int, int> array); // Zapisywanie wyszukanych par do pliku
void DoTimeMeasurements(); // Wykonywanie pomiarów czasowych wykonania algorytmu w zależności od liczby podanych danych

int main()
{
    // Zapis rezultatów wyszukiwania par liczb spełniających podany warunek ze zbioru 10 losowych liczb całkowitych z przedziału 1-20.
    SaveResultsToFile("results.txt", FindPairOfNumbers(GenerateRandomNumbers(1, 20, 10), 5));

    // Zapis rezultatów wyszukiwania par liczb spełniających podany warunek ze zbioru 50 losowych liczb całkowitych z przedziału 100-500.
    SaveResultsToFile("results2.txt", FindPairOfNumbers(GenerateRandomNumbers(100, 500, 50), 20));

    // Zapis rezultatów wyszukiwania par liczb spełniających podany warunek ze zbioru wczytanych liczb z podanego pliku tekstowego.
    SaveResultsToFile("results3.txt", FindPairOfNumbers(LoadNumbersFromFile("numbers.txt"), 3));

    // Jak wyżej, tylko dane wejściowe z treści zadania.
    SaveResultsToFile("results4.txt", FindPairOfNumbers({1, 5, 2, 2, 2, 5, 5, 4}, 3));

    // Pomiary czasowe potrzebne do wykresu
    // DoTimeMeasurements();

    return 0;
}

vector<int> LoadNumbersFromFile(string fileName)
{
    vector<int> loadedNumbers;

    ifstream file(fileName, fstream::in);

    if (file.good())
    {
        int i;
        while (!(file.eof()))
        {
            file >> i;
            loadedNumbers.push_back(i);
        }
        file.close();
    }
    else
    {
        cout << "Plik " << fileName << " nie istnieje!\n";
    }

    return loadedNumbers;
}

void SaveResultsToFile(string fileName, map<int, int> array)
{
    fstream file;
    file.open(fileName, ios::out);

    if (array.size())
    {
        for (auto const& i : array)
        {
            file << "[" << i.second << "," << i.first << "]\n";
        }
    }
    else
    {
        file << "Nie znaleziono żadnych par.";
    }

    file.close();
}

vector<int> GenerateRandomNumbers(int min, int max, int numbers)
{
    vector<int> randomNumbers;

    for (int i = 0; i < numbers; i++)
    {
        randomNumbers.push_back(GetRandomNumber(min, max));
    }

    return randomNumbers;
}

map<int, int> FindPairOfNumbers(vector<int> array, int diff)
{
    map<int, int> foundPairs;

    for (auto i : array)
    {
        for (auto x : array)
        {
            if (diff == abs(i - x) && (x - i) != diff)
            {
                foundPairs[i] = x;
            }
        }
    }

    return foundPairs;
}

int GetRandomNumber(int min, int max)
{
    static bool firstExecution = true;

    if (firstExecution)
    {
        srand((unsigned int)time(NULL));
        firstExecution = false;
    }

    return min + rand() % ((max + 1) - min);
}

void DoTimeMeasurements()
{
    DWORD time;

    fstream file;
    file.open("measurements.txt", ios::out);

    #define checkTime(elements); \
        time = GetTickCount(); \
        FindPairOfNumbers(GenerateRandomNumbers(1, 500, elements), 10); \
        file << "Czas wykonania algorytmu dla " << elements << " elementów wynosi " << (GetTickCount() - time) << " ms.\n";

    checkTime(1000);
    checkTime(5000);
    checkTime(10000);
    checkTime(50000);
    checkTime(100000);

    file.close();
}
