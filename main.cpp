#include <algorithm>
#include <clocale>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr int kMinElementsForTask2 = 5;
constexpr int kMinElementsForTask7 = 3;
constexpr int kMiddleElementsCount = 5;

// Вспомогательные функции для проверки ввода

int InputInt(string prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            return x;
        }
        cout << "Ошибка ввода. Попробуйте снова.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string InputUpperWord(string prompt) {
    string word;
    while (true) {
        cout << prompt;
        word.clear();
        if (cin >> word) {
            bool ok = !word.empty();
            for (char c : word) {
                if (c < 'A' || c > 'Z') ok = false;
            }
            if (ok) return word;
        }
        cout << "Ошибка: слово должно состоять только из заглавных A-Z.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Задание 1.5. Заполнение и доступ к элементам. Обратные итераторы
void Task1() {
    cout << "Задание 1.5. Заполнение и доступ к элементам. Обратные итераторы.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов (делится на 3): ");
        if (n > 0 && n % 3 == 0) break;
        cout << "Число должно быть положительным и делиться на 3.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    list<int> L(temp.begin(), temp.end());

    cout << "\nИсходный список: ";
    for (auto it = L.begin(); it != L.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    int third = n / 3;

    cout << "Первая треть (прямой порядок): ";
    int count = 0;
    for (auto it = L.begin(); it != L.end() && count < third; ++it) {
        cout << *it << " ";
        count++;
    }
    cout << "\n";

    cout << "Вторая треть (обратный порядок): ";
    count = 0;
    int skip = 0;
    for (auto rit = L.rbegin(); rit != L.rend(); ++rit) {
        if (skip < third) {
            skip++;
            continue;
        }
        if (count < third) {
            cout << *rit << " ";
            count++;
        }
        else break;
    }
    cout << "\n";

    cout << "Третья треть (обратный порядок): ";
    count = 0;
    for (auto rit = L.rbegin(); rit != L.rend() && count < third; ++rit) {
        cout << *rit << " ";
        count++;
    }
    cout << "\n";
}

// Задание 2.2 Вставка элементов
void Task2() {
    cout << "Задание 2.2 Вставка элементов.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов (нечётное, >= 5): ");
        if (n >= kMinElementsForTask2 && n % 2 != 0) break;
        cout << "Число должно быть нечётным и не меньше 5.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    deque<int> D(temp.begin(), temp.end());

    cout << "\nИсходный дек: ";
    for (auto it = D.begin(); it != D.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    int mid = n / 2;
    int start = mid - 2;
    vector<int> mid_elements;

    auto it = D.begin();
    for (int i = 0; i < start; i++) ++it;
    for (int i = 0; i < kMiddleElementsCount; i++) {
        mid_elements.push_back(*it);
        ++it;
    }

    D.insert(D.begin(), mid_elements.begin(), mid_elements.end());

    cout << "Дек после вставки: ";
    for (auto it = D.begin(); it != D.end(); ++it)
        cout << *it << " ";
    cout << "\n";
}

// Задание 3.8. Удаление элементов
void Task3() {
    cout << " Задание 3.8. Удаление элементов.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов (> 0): ");
        if (n > 0) break;
        cout << "Число должно быть положительным.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    vector<int> V(temp.begin(), temp.end());

    cout << "\nИсходный вектор: ";
    for (auto it = V.begin(); it != V.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    for (auto it = V.begin(); it != V.end(); ++it) {
        it = V.erase(it);
        if (it == V.end()) break;
    }

    cout << "Вектор после удаления: ";
    if (V.empty()) cout << "(пустой)";
    else
        for (auto it = V.begin(); it != V.end(); ++it)
            cout << *it << " ";
    cout << "\n";
}

// Задание 4.1 Итераторы и алгоритмы
void Task4() {
    cout << "Задание 4.1 Итераторы и алгоритмы.\n\n";

    int k;
    while (true) {
        k = InputInt("Введите целое число K (> 0): ");
        if (k > 0) break;
        cout << "K должно быть больше 0.\n\n";
    }

    string name1, name2;
    cout << "Введите имя исходного файла: ";
    cin >> name1;
    cout << "Введите имя выходного файла: ";
    cin >> name2;

    ifstream fin(name1);
    if (!fin) {
        cout << "Не удалось открыть файл " << name1 << "\n";
        return;
    }

    ofstream fout(name2);
    if (!fout) {
        cout << "Не удалось открыть файл " << name2 << "\n";
        return;
    }

    istream_iterator<string> in_begin(fin);
    istream_iterator<string> in_end;
    ostream_iterator<string> out_iter(fout, "\n");

    auto is_too_long = [k](const string& w) {
        return w.length() > static_cast<size_t>(k);
        };

    remove_copy_if(in_begin, in_end, out_iter, is_too_long);

    cout << "\nГотово! Слова длиной не более " << k
        << " записаны в файл " << name2 << "\n";

    fin.close();
    fout.close();
}

void Task5() {
    cout << "Задание 5.4. Алгоритмы поиска.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов списка (> 0): ");
        if (n > 0) break;
        cout << "Количество элементов должно быть положительным.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    list<int> L(temp.begin(), temp.end());

    cout << "\nИсходный список: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    auto isNegative = [](int x) { return x < 0; };

    list<int>::iterator first_neg = find_if(L.begin(), L.end(), isNegative);

    if (first_neg == L.end()) {
        cout << "Отрицательных элементов нет. Список не изменен.\n";
    }
    else {
        list<int>::iterator after_first = first_neg;
        ++after_first;

        list<int>::iterator second_neg =
            find_if(after_first, L.end(), isNegative);

        list<int>::iterator finish = L.end();
        if (second_neg != L.end()) finish = second_neg;

        L.erase(after_first, finish);

        if (second_neg == L.end())
            cout << "Отрицательный элемент один: всё после него удалено.\n";
        else
            cout << "Элементы между первым и вторым отрицательными удалены.\n";
    }

    cout << "Список после обработки: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it)
        cout << *it << " ";
    cout << "\n";
}

// Задание 6.4. Базовые модифицирующие алгоритмы. Итераторы вставки
void Task6() {
    cout << "Задание 6.4. Базовые модифицирующие алгоритмы. Итераторы вставки. "
        << "Итераторы вставки.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите N (> 0): ");
        if (n > 0) break;
        cout << "N должно быть больше 0.\n\n";
    }

    int size;
    while (true) {
        size = InputInt("Введите количество элементов дека (>= 0): ");
        if (size >= 0) break;
        cout << "Размер не может быть отрицательным.\n\n";
    }

    vector<int> temp(size);
    for (int i = 0; i < size; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    deque<int> D(temp.begin(), temp.end());

    cout << "\nИсходный дек: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    int counter = n;
    auto generator = [&counter]() {
        int value = counter;
        counter--;
        return value;
        };

    generate_n(front_inserter(D), n, generator);

    counter = n;

    generate_n(back_inserter(D), n, generator);

    cout << "Дек после вставки: ";
    for (deque<int>::iterator it = D.begin(); it != D.end(); ++it)
        cout << *it << " ";
    cout << "\n";
}

// Задание 7.1. Сортировка и слияние
void Task7() {
    cout << "Задание 7.1. Сортировка и слияние.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов (нечётное, >= 3): ");
        if (n >= kMinElementsForTask7 && n % 2 != 0) break;
        cout << "Число должно быть нечётным и не меньше 3.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    vector<int> V(temp.begin(), temp.end());

    cout << "\nИсходный вектор: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    vector<int>::iterator center = V.begin() + n / 2;

    nth_element(V.begin(), center, V.end());

    int left = *max_element(V.begin(), center);

    int middle = *center;

    int right = *min_element(center + 1, V.end());

    cout << "Вектор после nth_element: ";
    for (vector<int>::iterator it = V.begin(); it != V.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    cout << "Три средних элемента по возрастанию: "
        << left << " " << middle << " " << right << "\n";
}

// Задание 8.1. Численные алгоритмы
void Task8() {
    cout << "Задание 8.1. Численные алгоритмы.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество элементов списка (> 0): ");
        if (n > 0) break;
        cout << "Количество элементов должно быть положительным.\n\n";
    }

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        temp[i] = InputInt("Введите элемент " + to_string(i + 1) + ": ");

    list<int> L(temp.begin(), temp.end());

    cout << "\nИсходный список: ";
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it)
        cout << *it << " ";
    cout << "\n\n";

    vector<double> V;

    adjacent_difference(L.begin(), L.end(), back_inserter(V),
        [](int current, int previous) {
            return (current + previous) / 2.0;
        });

    V.erase(V.begin());

    cout << fixed << setprecision(1);
    cout << "Вектор средних значений: ";
    if (V.empty()) cout << "(пустой)";
    else
        for (vector<double>::iterator it = V.begin(); it != V.end(); ++it)
            cout << *it << " ";
    cout << "\n";
    cout.unsetf(ios::fixed);
}

// Задание 9.2. Множества
void Task9() {
    cout << "Задание 9.2. Множества.\n\n";

    int n0;
    while (true) {
        n0 = InputInt("Введите размер вектора V0 (> 0): ");
        if (n0 > 0) break;
        cout << "Размер должен быть положительным.\n\n";
    }

    vector<int> temp0(n0);
    for (int i = 0; i < n0; i++)
        temp0[i] = InputInt("Введите элемент V0[" + to_string(i + 1) + "]: ");

    vector<int> V0(temp0.begin(), temp0.end());

    multiset<int> base(V0.begin(), V0.end());

    cout << "\nВектор V0: ";
    for (vector<int>::iterator it = V0.begin(); it != V0.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    int n;
    while (true) {
        n = InputInt("Введите количество векторов N (> 0): ");
        if (n > 0) break;
        cout << "N должно быть больше 0.\n\n";
    }

    int count = 0;

    for (int i = 1; i <= n; i++) {
        cout << "\n--- Вектор V" << i << " ---\n";

        int size;
        while (true) {
            size = InputInt("Введите размер (не меньше " +
                to_string(n0) + "): ");
            if (size >= n0) break;
            cout << "Размер должен быть не меньше размера V0.\n\n";
        }

        vector<int> temp(size);
        for (int j = 0; j < size; j++)
            temp[j] = InputInt("Введите элемент " + to_string(j + 1) + ": ");

        vector<int> Vi(temp.begin(), temp.end());

        multiset<int> current(Vi.begin(), Vi.end());

        cout << "Вектор V" << i << ": ";
        for (vector<int>::iterator it = Vi.begin(); it != Vi.end(); ++it)
            cout << *it << " ";
        cout << "\n";

        bool ok = includes(base.begin(), base.end(),
            current.begin(), current.end());

        cout << "Содержит все элементы V0: " << (ok ? "да" : "нет") << "\n";
        if (ok) count++;
    }

    cout << "\nКоличество подходящих векторов: " << count << "\n";
}

// Задание 10.4. Отображения
void Task10() {
    cout << "Задание 10.4. Отображения.\n\n";

    int n;
    while (true) {
        n = InputInt("Введите количество слов (> 0): ");
        if (n > 0) break;
        cout << "Количество слов должно быть положительным.\n\n";
    }

    vector<string> temp(n);
    int index = 0;
    for (string& word : temp) {
        word = InputUpperWord("Введите слово " + to_string(index + 1) +
            " (заглавными буквами): ");
        index++;
    }

    vector<string> V(temp.begin(), temp.end());

    cout << "\nИсходный вектор: ";
    for (const string& word : V)
        cout << word << " ";
    cout << "\n\n";

    vector<string> reversed(V.rbegin(), V.rend());

    multimap<char, string> M;
    for (const string& word : reversed) {
        M.insert(make_pair(word.back(), word));
    }

    cout << "Мультиотображение M (ключ - слово):\n";
    for (const auto& item : M) {
        cout << item.first << " - " << item.second << "\n";
    }
}
// Менюшка
void ShowMenu() {
    cout << "\nЛабораторная работа. Контейнеры и алгоритмы STL.\n\n";
    cout << "1.  Задание 1  (list, обратные итераторы)\n";
    cout << "2.  Задание 2  (deque, вставка)\n";
    cout << "3.  Задание 3  (vector, удаление)\n";
    cout << "4.  Задание 4  (файлы, remove_copy_if)\n";
    cout << "5.  Задание 5  (find_if, удаление диапазона)\n";
    cout << "6.  Задание 6  (generate_n, итераторы вставки)\n";
    cout << "7.  Задание 7  (nth_element, max_element, min_element)\n";
    cout << "8.  Задание 8  (adjacent_difference, средние пары)\n";
    cout << "9.  Задание 9  (multiset, includes)\n";
    cout << "10. Задание 10 (multimap, группировка слов)\n";
    cout << "0.  Выход\n";
}

int main() {
    setlocale(LC_ALL, "RUS");

    int choice;
    do {
        ShowMenu();
        choice = InputInt("Выберите номер задачи (0-10): ");
        cout << "\n";

        switch (choice) {
        case 1: Task1(); break;
        case 2: Task2(); break;
        case 3: Task3(); break;
        case 4: Task4(); break;
        case 5: Task5(); break;
        case 6: Task6(); break;
        case 7: Task7(); break;
        case 8: Task8(); break;
        case 9: Task9(); break;
        case 10: Task10(); break;
        case 0: cout << "До свидания!\n"; break;
        default: cout << "Неверный выбор.\n";
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (choice != 0);

    return 0;
}
