#include <iostream>
#include <windows.h>

#define WITH_MANUAL_MODE true
#define MIN -10
#define MAX -1

using namespace std;

template <typename T> class VECTOR
{
private:
    int lenght;
    T* array;
public:
    VECTOR()
    {
        lenght = 0;
        array = nullptr;
    }
    VECTOR(int settable_lenght)
    {
        if (settable_lenght > 0)
        {
            lenght = settable_lenght;
            array = new T[lenght];
        }
        else
        {
            lenght = 0;
            array = nullptr;
        }
    }
    VECTOR(VECTOR const& src_object)
    {
        lenght = src_object.lenght;
        if (lenght > 0)
        {
            array = new T[lenght];
            for (int i = 0; i < lenght; i++)
            {
                array[i] = src_object.array[i];
            }
        }
        else
        {
            array = nullptr;
        }
    }
    ~VECTOR()
    {
	    if (lenght > 0)
	    {
            delete[]array;
	    }
    }
    void set_number_manual(int settable_lenght, int index)
    {
	    if (array == nullptr)
	    {
            delete[]array;
	    }
        lenght = settable_lenght;
        array = new T[lenght];
        for (int i = 0; i < lenght; i++)
        {
            cout << "A[" << index + 1 << "][" << i + 1 << "] = ";
            cin >> array[i];
        }
    }
    void set_number_random(int settable_lenght)
    {
        if (array == nullptr)
        {
            delete[]array;
        }
        lenght = settable_lenght;
        array = new T[lenght];
        for (int i = 0; i < lenght; i++)
        {
            array[i] = (MAX - MIN) * (T)rand() / RAND_MAX + MIN;
        }
    }
    void set_number_coefficient(int settable_lenght, int index, double first_coefficient, double second_coefficient)
    {
	    if (array == nullptr)
	    {
            delete[]array;
	    }
        lenght = settable_lenght;
        array = new T[lenght];
        for (int i = 0; i < lenght; i++)
        {
            array[i] = first_coefficient * (index + 1) * powf(sin(i + 1 + second_coefficient), 2);
        }
    }
    void output()
    {
        if (lenght > 0)
        {
            for (int i = 0; i < lenght; i++)
            {
                cout << array[i] << "   ";
            }
        }
        else
        {
            cout << "[Ошибка]: Вектор пуст." << endl;
        }
    }
    int get_lenght() const { return lenght; }
    const T operator [] (int index)const
    {
	    if ((index >= 0) && (index < lenght))
	    {
            return array[index];
	    }
        else
        {
            cout << "[Ошибка]: Неверно указан индекс элемента." << endl;
            exit(1);
        }
    }
    T & operator [] (int index)
    {
        if ((index >= 0) && (index < lenght))
        {
            return array[index];
        }
        else
        {
            cout << "[Ошибка]: Неверно указан индекс элемента." << endl;
            exit(1);
        }
    }
    VECTOR & operator = (VECTOR& src_object)
    {
        if (this != &src_object)
        {
            if (lenght > 0)
            {
                delete[]array;
            }
            lenght = src_object.lenght;
            array = new T[lenght];
            for (int i = 0; i < lenght; i++)
            {
                array[i] = src_object[i];
            }
        }
        return *this;
    }
};

template <typename T> class MATRIX
{
private:
    int strings;
    VECTOR<T>* array;
public:
    MATRIX()
    {
        strings = 0;
        array = nullptr;
    }
    MATRIX (bool mode)
    {
        cout << "Введите кол-во строк: ";
        cin >> strings;
        while (strings < 0)
        {
            cout << "[Ошибка]: Кол-во строк не может быть меньше нуля. Введите кол-во строк: ";
            cin >> strings;
        }
        if (strings > 0)
        {
            int columns = 0;
            cout << "Введите кол-во колонок: ";
            cin >> columns;
            array = new VECTOR<T>[strings];
            for (int i = 0; i < strings; i++)
            {
                array[i].set_number_manual(columns, i);
            }
        }
        else
        {
            strings = 0;
            array = nullptr;
        }
    }
    MATRIX(int settable_strings, int settable_columns)
    {
	    if (settable_strings > 0 && settable_columns > 0)
	    {
            strings = settable_strings;
            array = new VECTOR<T>[strings];
            for (int i = 0; i < strings; i++)
            {
                array[i].set_number_random(settable_columns);
            }
	    }
        else
        {
            strings = 0;
            array = nullptr;
        }
    }
    MATRIX(int settable_strings, int settable_columns, double first_coefficient, double second_coefficient)
    {
        if (settable_strings > 0 && settable_columns > 0)
        {
            strings = settable_strings;
            array = new VECTOR<T>[strings];
            for (int i = 0; i < strings; i++)
            {
                array[i].set_number_coefficient(settable_columns, i, first_coefficient, second_coefficient);
            }
        }
        else
        {
            strings = 0;
            array = nullptr;
        }
    }
    MATRIX(MATRIX const& src_object)
    {
        strings = src_object.strings;
        array = new VECTOR<T>[strings];
        for (int i = 0; i < strings; i++)
        {
            array[i] = src_object[i];
        }
    }
    ~MATRIX()
    {
	    if (strings > 0)
	    {
            delete[]array;
	    }
    }
    int get_strings() const { return strings; }
	void output()
    {
        if (strings > 0)
        {
            for (int i = 0; i < strings; i++)
            {
                array[i].output();
                cout << endl;
            }
        }
        else
        {
            cout << "[Ошибка]: Матрица пуста." << endl;
        }
    }
    T parameter()
    {
        T parameter = 0.0;
        T avg = 0.0;
        int i = 0;
    	int j = 0;
        for (i = 0; i < strings; i++)
        {
            for (j = 0; j < array[i].get_lenght(); j++)
            {
                avg += array[i][j];
            }
        }
        avg /= strings * array[i].get_lenght();
        for (i = 0; i < strings; i++)
        {
            for (j = 0; j < array[i].get_lenght(); j++)
            {
                if (array[i][j] > avg)
                {
                    parameter += array[i][j];
                }
            }
        }
        return parameter;
    }
    void processing()
    {
        double avg_global = 0.0;
        double avg_string = 0.0;
        int i = 0;
        int j = 0;
        for (i = 0; i < strings; i++)
        {
	        for (j = 0; j < array[i].get_lenght(); j++)
	        {
                avg_global += array[i][j];
	        }
        }
        avg_global /= strings * array[i].get_lenght();
        for (i = 0; i < strings; i++)
        {
	        for (j = 0; j < array[i].get_lenght(); j++)
	        {
                avg_string = array[i][j];
	        }
            avg_string /= array[i].get_lenght();
            if (avg_string > avg_global)
            {
	            for (j = 0; j < array[i].get_lenght(); j++)
	            {
                    array[i][j] -= avg_global;
	            }
            }
            avg_string = 0.0;
        }
    }
    const VECTOR<T> operator [] (int index)const
    {
        if ((index >= 0) && (index < strings))
        {
            return array[index];
        }
        else
        {
            cout << "[Ошибка]: Неверно указан индекс элемента." << endl;
            exit(1);
        }
    }
    VECTOR<T>& operator [] (int index)
    {
        if ((index >= 0) && (index < strings))
        {
            return array[index];
        }
        else
        {
            cout << "[Ошибка]: Неверно указан индекс элемента." << endl;
            exit(1);
        }
    }
    double composition(int string) const
    {
        double composition = 1.0;
        int i = string;
        for (int j = 0; j < array[i].get_lenght(); j++)
        {
	        if (array[i][j] != 0)
	        {
                composition *= array[i][j];
	        }
        }
        return composition;
    }
};

//template <typename T> VECTOR<T> generate_vector(const MATRIX<T>& src_object)
//{
//    T composition = 0.0;
//    T max_composition = 0.0;
//    int max_composition_string_index = 0;
//    int lenght = src_object.get_strings();
//    int i = 0;
//	for (i = 0; i < lenght; i++)
//    {
//        composition = src_object.composition(i);
//        if (composition > max_composition)
//        {
//            max_composition = composition;
//            max_composition_string_index = i;
//        }
//    }
//    T* generated_vector = new T[lenght];
//    for (i = 0; i < lenght; i++)
//    {
//        generated_vector[i] = src_object[max_composition_string_index][i];
//    }
//    return *generated_vector;
//}

//template <typename T> VECTOR<T> generate_vector(const MATRIX<T>& src_object)
//{
//    T composition = 0.0;
//    T max_composition = 0.0;
//    int max_composition_string_index = 0;
//    int length = src_object.get_strings();
//    for (int i = 0; i < length; i++)
//    {
//        composition = src_object.composition(i);
//        if (composition > max_composition)
//        {
//            max_composition = composition;
//            max_composition_string_index = i;
//        }
//    }
//    VECTOR<T> generated_vector(src_object[max_composition_string_index].get_lenght());
//    for (int i = 0; i < length; i++)
//    {
//        generated_vector[i] = src_object[max_composition_string_index][i];
//    }
//    return generated_vector;
//}

template <typename T> VECTOR<T> generate_vector(const MATRIX<T>& src_object)
{
    T max_composition = 0.0;
    int max_composition_string_index = 0;
    int length = src_object.get_strings();
    for (int i = 0; i < length; i++)
    {
        T composition = src_object.composition(i);
        if (composition != 0 && (max_composition == 0 || composition > max_composition))
        {
            max_composition = composition;
            max_composition_string_index = i;
        }
    }
    return src_object[max_composition_string_index];
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(nullptr));
    MATRIX<double> A(6, 8, 17.2, -1.1);
    double A_parameter = A.parameter();
    cout << "Матрица A:" << endl;
    A.output();
    cout << "Параметр для A: " << A_parameter << endl;
    cout << endl;
    if (A_parameter > 0)
    {
        A.processing();
        cout << "Преобразованная матрица A:" << endl;
        A.output();
        VECTOR<double> VA = generate_vector(A);
        cout << "Сформированный вектор:" << endl;
        VA.output();
    }
    cout << endl;
    cout << endl;
    MATRIX<double> B(5, 7, 5.9, 2.4);
    double B_parameter = B.parameter();
    cout << "Матрица B:" << endl;
    B.output();
    cout << "Параметр для B: " << B_parameter << endl;
    if (B_parameter < 0)
    {
        B.processing();
        cout << "Преобразованная матрица B:" << endl;
        B.output();
        VECTOR<double> VB = generate_vector(A);
        cout << "Сформированный вектор:" << endl;
        VB.output();
    }
    cout << endl;
    MATRIX<double> C(4, 6, 12.3, -3.9);
    double C_parameter = C.parameter();
    cout << "Матрица C:" << endl;
	C.output();
    cout << "Параметр для C: " << C_parameter << endl;
    if (C_parameter < 0)
    {
        C.processing();
        cout << "Преобразованная матрица C:" << endl;
        C.output();
        VECTOR<double> VC = generate_vector(A);
        cout << "Сформированный вектор:" << endl;
        VC.output();
    }
    return 0;
}