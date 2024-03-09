#include <iostream>
using namespace std;

template <class T>
class element
{
public:
    int x;
    int y;
    T item;
    element(int i = 0, int j = 0, T t = 0)
    {
        x = i;
        y = j;
        item = t;
    }
    ~element() {}
    bool operator<(element<T> target)
    {
        if (x > target.x || (x == target.x && y >= target.y))
            return false;
        else
            return true;
    }
    bool operator>(element<T> target)
    {
        if (x < target.x || (x == target.x && y <= target.y))
            return false;
        else
            return true;
    }
    void operator=(element<T> t)
    {
        this->x = t.x;
        this->y = t.y;
        this->item = t.item;
    }
};

template <class T>
class sparseMatrix
{
private:
    int xs;
    int ys;
    int now;
    int max;
    element<T> *items;

public:
    sparseMatrix(int a, int b, int c)
    {
        xs = a;
        ys = b;
        max = c;
        now = 0;
        if (c != 0)
        {
            items = new element<T>[max];
        }
        else
        {
            items = NULL;
        }
    }
    sparseMatrix(sparseMatrix<T> const &m)
    {
        delete[] items;
        this->xs = m.xs;
        this->ys = m.ys;
        this->max = m.max;
        this->now = m.now;
        this->items = new element<T>[max];
        for (int k = 0; k < now; k++)
        {
            this->items[k] = m.items[k];
        }
    }
    ~sparseMatrix()
    {
        delete[] items;
    }
    bool get(int x, int y, T &target)
    {
        for (int k = 0; k < now; k++)
        {
            if (items[k].x == x && items[k].y == y)
            {
                target = items[k].item;
                return true;
            }
        }
        return false;
    }
    bool set(int x, int y, T target)
    {
        element<T> t(x, y, target);
        for (int k = 0; k < now; k++)
        {
            if (items[k].x == x && items[k].y == y)
            {
                items[k].item = target;
                return true;
            }
        }
        if (now < max)
        {
            int k;
            for (k = 0; k < now; k++)
            {
                if (items[k] < t && items[k + 1] > t)
                    break;
            }
            for (int j = k; j < now; j++)
            {
                items[j + 1] = items[j];
            }
            items[k] = t;
            now++;
            return true;
        }
        else
        {
            cout << "非稀疏矩阵" << endl;
            return false;
        }
    }
    void input()
    {
        int n;
        cout << "items number: ";
        cin >> n;
        for (int k = 0; k < n; k++)
        {
            int i, j;
            T t;
            cin >> i >> j >> t;
            this->set(i, j, t);
        }
    }
    void output()
    {
        for (int i = 1; i <= xs; i++)
        {
            for (int j = 1; j <= ys; j++)
            {
                T temp;
                if (this->get(i, j, temp))
                    cout << temp << " ";
                else
                    cout << 0 << " ";
            }
            cout << endl;
        }
    }
    sparseMatrix<T> operator*(sparseMatrix<T> &m)
    {
        if (this->ys == m.xs)
        {
            sparseMatrix<T> result(this->xs, m.ys, this->xs * m.ys);
            for (int i = 1; i <= result.xs; i++)
            {
                for (int j = 1; j <= result.ys; j++)
                {
                    bool isempty = 1;
                    T target = 0;
                    for (int k = 1; k <= this->ys; k++)
                    {
                        T elem1, elem2;
                        if (this->get(i, k, elem1) && m.get(k, j, elem2))
                        {
                            target += elem1 * elem2;
                            isempty = 0;
                        }
                    }
                    if (!isempty)
                    {
                        result.set(i, j, target);
                    }
                }
            }
            cout << endl;
            return result;
        }
        else
        {
            cout << "不能相乘" << endl;
            sparseMatrix<T> result(0, 0, 0);
            return result;
        }
    }
    void operator=(sparseMatrix<T> m)
    {
        delete[] items;
        this->xs = m.xs;
        this->ys = m.ys;
        this->max = m.max;
        this->now = m.now;
        this->items = new element<T>[max];
        for (int k = 0; k < now; k++)
        {
            this->items[k] = m.items[k];
        }
    }
};

int main()
{
    int i, j, k;
    cout << "行,列,最大数目" << endl;
    cin >> i >> j >> k;
    sparseMatrix<int> m(i, j, k);
    m.input();
    m.output();
    cout << "行,列,最大数目" << endl;
    cin >> i >> j >> k;
    sparseMatrix<int> m1(i, j, k);
    m1.input();
    m1.output();
    cout << "矩阵乘法" << endl;
    sparseMatrix<int> m2 = m * m1;
    m2.output();

    system("pause");
    return 0;
}
