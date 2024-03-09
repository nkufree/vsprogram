#include <iostream>
#include <chrono>
#include <omp.h>
#include <random>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <unistd.h>

using namespace std;

#define TOTAL_S 9
#define TOTAL_M 2

bool isMultiThread = false;
//��׼ʱ�䣬��i9-13900HXΪ��׼
double baseLineSingle1[TOTAL_S] = { 9.4968,9.96625,7.47495,17.2032,16.4162,16.9425,15.4485,90.559,1726.54 };
double baseLineSingle2[TOTAL_S] = { 2309.6,4046.47 };
double baseLineMulti[TOTAL_M] = { 236.686,673.989 };

//���ڴ洢����ʱ��
double testSingle1[TOTAL_S] = {  };
double testSingle2[TOTAL_M] = {  };
double testMulti[TOTAL_M] = {  };

//������
void progressBar(int i,int taskNum,int total, int current)
{
    int p = current * 100.0 / total;
    cout << "\r" << "[" << i << "/" << taskNum << " " << p << "%] [";
    
    for (int j = 0; j < 25; j++)
    {
        if (j < p / 4 && j != 24)
            cout << "=";
        else if (j - 1 < p / 4)
            cout << ">";
        else
            cout << " ";
    }
    cout << "]";
    fflush(stdout);
    return;
}

//˳���ȡ����
double testReadData()
{
    int* arr = new int[10000000];
    srand((unsigned)time(NULL));
    
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i)
    {
        int val = arr[i];
        val++;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    return duration.count();
}

//˳��д������
double testWriteData()
{
    int* arr = new int[10000000];
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i)
    {
        arr[i] = i;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    return duration.count();
}

//�����ȡ����
double testRandomReadData()
{
    int* arr = new int[10000000];
    int* arr2 = new int[10000000];
    srand((unsigned)time(NULL));

    for (int i = 0; i < 10000000; i++)
    {
        arr[i] = rand();
        arr2[i] = rand() % 10000000;
    }


    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i)
    {
        int val = arr[arr2[i]];
        val++;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    delete[] arr2;
    return duration.count();
}


//���д������
double testRandomWriteData()
{
    int* arr = new int[10000000];
    int* arr2 = new int[10000000];
    srand((unsigned)time(NULL));

    for (int i = 0; i < 10000000; i++)
    {
        arr[i] = rand() + i;
        arr2[i] = (rand() + i) % 10000000;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i)
    {
        arr[arr2[i]] = arr2[i];
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    delete[] arr2;
    return duration.count();
}

//���㵥���ȸ������ӷ�
double testCalculateFloat()
{
    float* arr = new float[10000000];
    default_random_engine e1(time(NULL));
    uniform_real_distribution<float> u1(-1.0e38, 1.0e38);
    for (int i = 0; i < 10000000; i++)
        arr[i] = u1(e1);
    auto start = std::chrono::high_resolution_clock::now();
    float sum = 0;
    for (int i = 0; i < 10000000; ++i)
        sum += arr[i];
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    return duration.count();
}

//����˫���ȸ������ӷ�
double testCalculateDouble()
{
    double* arr = new double[10000000];
    default_random_engine e1(time(NULL));
    uniform_real_distribution<double> u1(-1.0e300, 1.0e300);
    for (int i = 0; i < 10000000; i++)
        arr[i] = u1(e1);
    auto start = std::chrono::high_resolution_clock::now();
    double sum = 0;
    for (int i = 0; i < 10000000; ++i)
        sum += arr[i];
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    return duration.count();
}

//����switch
double testSwitch()
{
    int i, j, k = 1, l = 2, m = 3, n = 4, o = 5;
    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 10000000; i++) {
        j = i % 10;
        switch (j) {
        case 0:
            k++;
            break;
        case 1:
            l++;
            break;
        case 3:
            m++;
            break;
        case 4:
            n++;
            break;
        case 5:
            o++;
            break;
        case 6:
            k--;
            break;
        case 7:
            l--;
            break;
        case 8:
            m--;
            break;
        case 9:
            n--;
            break;
        case 2:
            o--;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    //cout << k << l << m << n << o << endl;
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

//��������
double testCalcPrime()
{
    int max = 10000000;
    int* isPrime = new int[max+10];

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 2; i <= max; ++i) 
        isPrime[i] = 1;
    for (int i = 2; i <= max; ++i)
    {
        if (isPrime[i])
            for (int j = i * 2; j <= max; j += i)
                isPrime[j] = 0;	
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] isPrime;
    return duration.count();
}

//��������
double testSort()
{
    int max = 20000000;
    int* arr = new int[max];
    
    srand((unsigned)time(NULL));

    for (int i = 0; i < max; i++)
        arr[i] = rand();

    auto start = std::chrono::high_resolution_clock::now();

    sort(arr, arr + max);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    delete[] arr;
    return duration.count();
}

//�������˻�
double testMultiThreads(int num)
{
    int** arr = new int* [1000];
    for (int i = 0; i < 1000; i++)
        arr[i] = new int[1000];

    int** arr2 = new int* [1000];
    for (int i = 0; i < 1000; i++)
        arr2[i] = new int[1000];

    int** arr3 = new int* [1000];
    for (int i = 0; i < 1000; i++)
        arr3[i] = new int[1000];

    srand((unsigned)time(NULL));

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            arr[i][j] = rand();
            arr2[i][j] = rand();
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(num)
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int k = 0; k < 1000; k++)
            {
                arr3[i][j] += arr[j][k] * arr2[k][j];
            }
        }

    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    for (int i = 0; i < 1000; i++)
    {
        delete[] arr[i];
        delete[] arr2[i];
        delete[] arr3[i];
    }
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    return duration.count();

}


//�����˹��Ԫ
double testGaussEliminate(int num)
{
    int n = 2000;
    float** A = new float*[n];
    for (int i = 0; i < n; i++)
        A[i] = new float[n];
    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand();

    auto start = std::chrono::high_resolution_clock::now();
    int i, j, k;
    float tmp;
#pragma omp parallel num_threads(num),private(i,j,k,tmp)
    for (k = 1; k < n; k++) {
#pragma omp single
        {
            tmp = A[k][k];
            for (j = k + 1; j < n; j++) {
                A[k][j] = A[k][j] / tmp;
            }
            A[k][k] = 1.0;
        }
#pragma omp for
        for (i = k + 1; i < n; i++) {
            tmp = A[i][k];
            for (j = k + 1; j < n; j++) {
                A[i][j] = A[i][j] - tmp * A[k][j];
            }
            A[i][k] = 0.0;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    return duration.count();
}


double helpTestSingle(double (*s)())
{
    int warmup = 2;
    int iterations = 2;
    double duration = 0;
    for (int i = 0; i < warmup + iterations; i++)
    {
        double temp = s();
        if (i >= warmup)
            duration += temp;
    }
    duration /= iterations;
    return duration;
}

double helpTestMulti(double (*m)(int), int t)
{
    int warmup = 2;
    int iterations = 2;
    double duration = 0;
    for (int i = 0; i < warmup + iterations; i++)
    {
        double temp = m(t);
        if (i >= warmup)
            duration += temp;
    }
    duration /= iterations;
    return duration;
}


int main(int argc, char* argv[])
{
    int num_threads = 8;
    //��������
    
    int o;
    const char* optstring = "mt:";
    
    while ((o = getopt(argc, argv, optstring)) != -1)
    {
        switch (o)
        {
        case 'm':
            isMultiThread = true;
            break;
        case 't':
            num_threads = atoi(optarg);
            break;
        default:
            return -1;
        }
    }

    double(*s[])() = { testReadData,testWriteData,testRandomReadData,
                        testRandomWriteData,testCalculateFloat,testCalculateDouble,
                        testSwitch,testCalcPrime,testSort };
    double(*m[])(int) = { testMultiThreads,testGaussEliminate };
    cout << "���̲߳���" << endl;
    double totalTime = 0;
    for (int i = 0; i < TOTAL_S; i++)
        totalTime += baseLineSingle1[i];
    for (int i = 0; i < TOTAL_M; i++)
        totalTime += baseLineSingle2[i];
    double currentTime = 0;
    progressBar(0, TOTAL_S+ TOTAL_M, totalTime, currentTime);
    for (int i = 0; i < TOTAL_S; i++)
    {
        testSingle1[i] = helpTestSingle(s[i]);
        currentTime += baseLineSingle1[i];
        progressBar(i + 1, TOTAL_S + TOTAL_M, totalTime, currentTime);
    }
        
    for (int i = 0; i < TOTAL_M; i++)
    {
        testSingle2[i] = helpTestMulti(m[i],1);
        currentTime += baseLineSingle2[i];
        progressBar(i + TOTAL_S + 1, TOTAL_S + TOTAL_M, totalTime, currentTime);
    }

    //���̲߳���
    cout << endl;
    cout << "˳���ȡ����ʱ�䣺" << testSingle1[0] << "ms" << endl
        << "˳��д������ʱ�䣺" << testSingle1[1] << "ms" << endl
        << "�����ȡ����ʱ�䣺" << testSingle1[2] << "ms" << endl
        << "���д������ʱ�䣺" << testSingle1[3] << "ms" << endl
        << "���㵥���ȸ������ӷ�ʱ�䣺" << testSingle1[4] << "ms" << endl
        << "����˫���ȸ������ӷ�ʱ�䣺" << testSingle1[5] << "ms" << endl
        << "����switchʱ�䣺" << testSingle1[6] << "ms" << endl 
        << "��������ʱ�䣺" << testSingle1[7] << "ms" << endl
        << "��������ʱ�䣺" << testSingle1[8] << "ms" << endl
        << "�������˻�ʱ�䣺" << testSingle2[0] << "ms" << endl
        << "�����˹��Ԫʱ�䣺" << testSingle2[1] << "ms" << endl << endl;
    //���̲߳���
    if (isMultiThread)
    {
        cout << "���̲߳���" << endl
             << "�߳�����Ϊ��" << num_threads << endl;
        totalTime = 0;
        for (int i = 0; i < TOTAL_M; i++)
            totalTime += baseLineMulti[i];
        currentTime = 0;
        progressBar(0, TOTAL_M, totalTime,0);
        for (int i = 0; i < TOTAL_M; i++)
        {
            testMulti[i] = helpTestMulti(m[i], num_threads);
            currentTime += baseLineMulti[i];
            progressBar(i + 1, TOTAL_M, totalTime, currentTime);
        }

        cout << endl;
        cout << "���̼߳������˻�ʱ�䣺" << testMulti[0] << "ms" << endl
            << "���̼߳����˹��Ԫʱ�䣺" << testMulti[1] << "ms" << endl;
    }

    //�ּܷ���
    //�����ּܷ��㣺�ܳɼ�=��ͣ���׼ʱ��/����ʱ��*Ȩ�أ�
    //����ּܷ��㣺�ܳɼ�=��ͣ����߳�ʱ��/���߳�ʱ��*���̲߳��Ի�׼ʱ��/���̲߳���ʱ��*Ȩ�أ�
    double singleScore = 0;
    double temp1 = 0;
    double temp2 = 0;
    double temp3 = 0;
    for (int i = 0; i < TOTAL_S - 1; i++)
        temp1 += baseLineSingle1[i] / testSingle1[i];
    temp1 /= (TOTAL_S - 1);
    temp2 += baseLineSingle1[TOTAL_S - 1] / testSingle1[TOTAL_S - 1];
    for (int i = 0; i < TOTAL_M; i++)
        temp3 += baseLineSingle2[i] / testSingle2[i];
    temp3 /= TOTAL_M;
    singleScore = (temp1 * 0.2 + temp2 * 0.2 + temp3 * 0.6) * 100.0;

    double multiScore = 0;
    if (isMultiThread)
    {
        for (int i = 0; i < TOTAL_M; i++)
            multiScore += testSingle2[i] / testMulti[i] * baseLineSingle2[i] / testSingle2[i];
        multiScore /= TOTAL_M;
        multiScore *= 100;
    }

    cout<< endl << endl << "���Խ���" << endl;
    cout << "�����ֵĻ�׼Ϊi9-13900HX�����˻�׼����Ϊ100��" << endl;
    cout << "���ĵ�������Ϊ" << int(singleScore) << endl;
    if (isMultiThread)
        cout << "���Ķ������Ϊ" << int(multiScore) << endl << endl;

    system("pause");
    return 0;
}