#include <iostream>
#include <math.h>

template <typename T>
class Polynomial
{
 private:
	class Coeff
	{
	 public:
		Coeff* pNext;
		T number;
		int degree;

		Coeff(T number, int degree, Coeff* pNext = nullptr)
		{
			this->number = number;
			this->pNext = pNext;
			this->degree = degree;
		}
	};
	Coeff* odds;
	int numberOfCoeff;
 public:

	int GetNumberOfCoeff()
	{
		return numberOfCoeff;
	}

	void Set(const T data, const int degreeCoeff)
	{
		if (data == 0) throw "Coefficient cannot be equal to zero";
		if (degreeCoeff < 0) throw "Degree cannot be less zero";
		Coeff* node = new Coeff(data, degreeCoeff);
		if (odds == nullptr)
		{
			odds = node;
		}
		else
		{
			Coeff* tmp = odds;
			while (tmp->pNext)
			{
				if (degreeCoeff == tmp->degree)
				{
					tmp->number = data;
					return;
				}
				tmp = tmp->pNext;
			}
			if (degreeCoeff == tmp->degree)
			{
				tmp->number = data;
				return;
			}
			tmp->pNext = node;
		}
		numberOfCoeff++;
	}

	Polynomial<T>(int degree = 0)
	{
		numberOfCoeff = 0;
		if (degree < 0) throw "Error";
		odds = nullptr;

		if (degree == 0) return;

		for (int i = 0; i <= degree; ++i)
		{
			Set(1, i);
		}
	}

	Polynomial<T>(const Polynomial<T>& obj)
	{
		numberOfCoeff = obj.numberOfCoeff;
		Coeff* tmp = obj.odds;
		while (tmp)
		{
			Set(tmp->number, tmp->degree);
			tmp = tmp->pNext;
		}
	}

	~Polynomial<T>()
	{
		delete[] odds;
	}

	void PrintPolynomial()
	{
		Coeff* tmp = odds;
		while (tmp)
		{
			if (tmp->pNext) std::cout << tmp->number << "x^" << tmp->degree << " + ";
			else std::cout << tmp->number << "x^" << tmp->degree << std::endl;
			tmp = tmp->pNext;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Polynomial<T>& obj)
	{
		obj.PrintPolynomial();
		return os;
	}

	T operator[](const int degree)
	{
		Coeff* tmp = this->odds;
		while (tmp != nullptr)
		{
			if (degree == tmp->degree)
			{
				return tmp->number;
			}
			tmp = tmp->pNext;
		}
		return 0;
	}

	Polynomial<T> operator*(const T scalar)
	{
		Polynomial<T> result(0);
		Coeff* tmp = odds;
		for (int i = 0; i < numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	friend Polynomial<T> operator*(const T scalar, const Polynomial<T>& obj)
	{
		Polynomial<T> result(0);
		Coeff* tmp = obj.odds;
		for (int i = 0; i < obj.numberOfCoeff; ++i)
		{
			result.Set(tmp->number * scalar, tmp->degree);
			tmp = tmp->pNext;
		}
		return result;
	}

	T ValueCalculation(T x)
	{
		Coeff* tmp = odds;
		T sum = 0;
		while (tmp)
		{
			sum += tmp->number * (pow(x, tmp->degree));
			tmp = tmp->pNext;
		}

		return sum;
	}

	Polynomial<T> FindIntegral()
	{
		Polynomial<T> integral(0);
		Coeff* tmp = odds;

		while (tmp)
		{
			integral.Set(tmp->number / (tmp->degree + 1), tmp->degree + 1);
			tmp = tmp->pNext;
		}

		return integral;
	}

	Polynomial<T> operator+(Polynomial<T>& obj)
	{
		Polynomial<T> sum(0);
		Coeff* tmp1 = odds;
		while (tmp1)
		{
			Coeff* tmp2 = obj.odds;
			bool found = false;
			while (tmp2 and !found)
			{
				if (tmp1->degree == tmp2->degree)
				{
					sum.Set(tmp1->number + tmp2->number, tmp1->degree);
					found = true;
				}
				tmp2 = tmp2->pNext;
			}
			if (!found)
			{
				sum.Set(tmp1->number, tmp1->degree);
			}
			tmp1 = tmp1->pNext;
		}
		Coeff* tmp2 = obj.odds;
		while (tmp2)
		{
			tmp1 = sum.odds;
			bool found = false;
			while (tmp1 and !found)
			{
				if (tmp2->degree == tmp1->degree)
				{
					found = true;
				}
				tmp1 = tmp1->pNext;
			}
			if (!found)
			{
				sum.Set(tmp2->number, tmp2->degree);
			}
			tmp2 = tmp2->pNext;
		}

		return sum;

	};

	Polynomial<T> operator-(Polynomial<T>& obj)
	{
		Polynomial<T> difference(0);
		Coeff* tmp1 = odds;
		while (tmp1)
		{
			Coeff* tmp2 = obj.odds;
			bool found = false;
			while (tmp2 and !found)
			{
				if (tmp1->degree == tmp2->degree)
				{
					if (tmp1->number - tmp2->number != 0)
					{
						difference.Set(tmp1->number - tmp2->number, tmp1->degree);
					}
					found = true;
				}
				tmp2 = tmp2->pNext;
			}
			if (!found)
			{
				difference.Set(tmp1->number * -1, tmp1->degree);
			}
			tmp1 = tmp1->pNext;
		}

		Coeff* tmp2 = obj.odds;
		while (tmp2)
		{
			tmp1 = odds;
			bool found = false;
			while (tmp1 and !found)
			{
				if (tmp2->degree == tmp1->degree)
				{
					found = true;
				}
				tmp1 = tmp1->pNext;
			}
			if (!found)
			{
				difference.Set(tmp2->number, tmp2->degree);
			}
			tmp2 = tmp2->pNext;
		}

		return difference;

	};

	Polynomial<T>& operator=(const Polynomial<T>& right)
	{
		if (this == &right)
		{
			return *this;
		}
		delete[] odds;
		numberOfCoeff = right.numberOfCoeff;
		Coeff* tmp = right.odds;
		while (tmp)
		{
			Set(tmp->number, tmp->degree);
			tmp = tmp->pNext;
		}
		return *this;
	}

	bool operator==(const Polynomial<T>& right)
	{
		if (this == &right)
		{
			return true;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			Coeff* tmp1 = odds;
			while (tmp1)
			{
				Coeff* tmp2 = right.odds;
				bool equal = false;
				while (tmp2)
				{
					if (tmp1->number == tmp2->number && tmp1->degree == tmp2->degree)
					{
						equal = true;
					}
					tmp2 = tmp2->pNext;
				}
				if (!equal)
				{
					return false;
				}
				tmp1 = tmp1->pNext;
			}
		}
		return true;
	}

	bool operator>(Polynomial<T> right)
	{
		if (this == &right)
		{
			return true;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			if (ValueCalculation(1) > right.ValueCalculation(1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	bool operator<(Polynomial<T> right)
	{
		if (this == &right)
		{
			return true;
		}
		if (numberOfCoeff != right.numberOfCoeff)
		{
			return false;
		}
		else
		{
			if (ValueCalculation(1) < right.ValueCalculation(1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};