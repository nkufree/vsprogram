#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// ������нṹ��
struct City {
    double x;
    double y;
};

// ����ȫ�ֱ���
const int kMaxIterations = 10000;  // ����������
const double kInitialTemperature = 1000.0;  // ��ʼ�¶�
const double kCoolingRate = 0.99;  // ��������

// ���������
vector<int> GenerateRandomSolution(int num_cities) {
    vector<int> solution(num_cities);
    for (int i = 0; i < num_cities; ++i) {
        solution[i] = i;
    }
    for (int i = 0; i < num_cities; ++i) {
        int j = rand() % num_cities;
        swap(solution[i], solution[j]);
    }
    return solution;
}

// ��������
double CalculateEnergy(const vector<City>& cities, const vector<int>& solution) {
    double energy = 0.0;
    int num_cities = cities.size();
    for (int i = 0; i < num_cities; ++i) {
        int j = (i + 1) % num_cities;
        double dx = cities[solution[i]].x - cities[solution[j]].x;
        double dy = cities[solution[i]].y - cities[solution[j]].y;
        energy += sqrt(dx * dx + dy * dy);
    }
    return energy;
}

// ���½�
void UpdateSolution(const vector<City>& cities, vector<int>& solution, double temperature) {
    int num_cities = cities.size();
    int i = rand() % num_cities;
    int j = rand() % num_cities;
    int tmp = solution[i];
    solution[i] = solution[j];
    solution[j] = tmp;
    double delta_energy = CalculateEnergy(cities, solution) - CalculateEnergy(cities, solution);
    if (delta_energy > 0 && exp(-delta_energy / temperature) < (double)rand() / RAND_MAX) {
        // �������ӽ�
        solution[j] = solution[i];
        solution[i] = tmp;
    }
}
// �����¶Ƚ��͵ĺ���
double CoolingSchedule(double initial_temperature, double cooling_rate, int iteration) {
    return initial_temperature * pow(cooling_rate, iteration);
}

// ������
int main() {
    srand(time(NULL)); // �������������
    // ��ʼ����������
    vector<City> cities = { {60, 200}, {180, 200}, {80, 180}, {140, 180}, {20, 160},
                           {100, 160}, {200, 160}, {140, 140}, {40, 120}, {100, 120},
                           {180, 100}, {60, 80}, {120, 80}, {180, 60}, {20, 40},
                           {100, 40}, {200, 40}, {20, 20}, {60, 20}, {160, 20} };

    

    // ��ʼ������
    int num_cities = cities.size();
    vector<int> solution = GenerateRandomSolution(num_cities);
    double temperature = kInitialTemperature;
    double energy = CalculateEnergy(cities, solution);

    // ����Ѱ�����Ž�
    for (int iteration = 0; iteration < kMaxIterations; ++iteration) {
        UpdateSolution(cities, solution, temperature);
        double new_energy = CalculateEnergy(cities, solution);
        if (new_energy < energy) {
            energy = new_energy;
        }
        else if (exp(-(new_energy - energy) / temperature) < (double)rand() / RAND_MAX) {
            energy = new_energy;
        }
        else {
            // �������ӽ�
            UpdateSolution(cities, solution, temperature);
        }
        temperature = CoolingSchedule(kInitialTemperature, kCoolingRate, iteration);
    }

    // ������
    cout << "����·����";
    for (int i = 0; i < num_cities; ++i) {
        cout << solution[i] << " ";
    }
    cout << endl;
    cout << "���ž��룺" << energy << endl;
    ofstream out("out.txt");
    for (int i = 0; i < cities.size(); i++)
        out << cities[solution[i]].x << endl;
    out << endl;
    for (int i = 0; i < cities.size(); i++)
        out << cities[solution[i]].y << endl;
    out.close();
    return 0;
}

// 
