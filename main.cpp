#include <iostream>
#include "Polynomial.cpp"

int main()
{
	try
	{
		bool exit = false;
		const int SIZE = 9;
		Polynomial polynomials[SIZE];

		while (!exit)
		{
			int choose;
			bool right_choose = false;

			std::cout << "\n" << "\033[35;40m\033[1m" << "Menu:\n"
														 "1 - List of polynomials\n"
														 "2 - Create polynomial\n"
														 "3 - Get coefficient\n"
														 "4 - Set coefficient\n"
														 "5 - Polynomial addition and subtraction operators\n"
														 "6 - Operator of multiplication of a polynomial by a scalar\n"
														 "7 - Calculation of polynomial value at a given value of x.\n"
														 "8 - Find the integral of a polynomial.\n"
														 "9 - Reset polymonial\n"
														 "10 - Exit\n"
														 "Enter a number:" << "\033[0m";

			while (!right_choose)
			{
				fflush(stdin);
				std::cin >> choose;
				if (choose > 11 || choose < 1)
				{
					std::cout << "\033[31;40m\033[1m" << "Incorrect number! Enter a number from 1 to 9: " << "\033[0m";
				}
				else
				{
					right_choose = true;
				}
			}

			switch (choose)
			{
			case 1:
			{
				std::cout << "\n" << "\033[33;40m\033[1m" << "List of polynomials:" << "\033[0m\n\n";
				for (int i = 0; i < SIZE; ++i)
				{
					std::cout << "\033[37;40m\033[1m" << i << ".\n" << "\033[0m";
					std::cout << polynomials[i];
				}
				std::cout << "\n\n";
			}
				break;
			case 2:
			{
				int indexPolynomial;

				std::cout << "\033[35;40m\033[1m" << "in which cell (0-8) to write?\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> indexPolynomial;
				if (indexPolynomial < 0 || indexPolynomial > 9) throw "Invalid index";

				int element;
				int degree;
				bool enter = true;
				polynomials[indexPolynomial] = Polynomial();

				while (enter)
				{
					std::cout << "\033[35;40m\033[1m" << "Enter coefficient " << "\033[0m\n";
					fflush(stdin);
					std::cin >> element;
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore();
						enter = false;
					}
					else
					{
						std::cout << "\033[35;40m\033[1m" << "Enter degree " << "\033[0m\n";
						fflush(stdin);
						std::cin >> degree;
						if (std::cin.fail())
						{
							std::cin.clear();
							std::cin.ignore();
							enter = false;
						}
						else
						{
							polynomials[indexPolynomial].Set(element, degree);
						}
					}
				}
				break;
			}
			case 3:
			{
				int degree;
				int indexPolynomial;

				std::cout << "\033[35;40m\033[1m" << "in which cell (0-8) to read?\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> indexPolynomial;

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Enter the degree at which to read the coefficient\n"
						  << "\033[0m\n";
				fflush(stdin);
				std::cin >> degree;

				int coeff = polynomials[indexPolynomial][degree];

				std::cout << "\033[37;40m\033[1m" << "coefficient with degree " << degree << ": " << coeff
						  << "\033[0m\n\n";

			}
				break;
			case 4:
			{
				int degree;
				int indexPolynomial;
				int coeff;

				std::cout << "\033[35;40m\033[1m" << "In which cell (0-8) to write?\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> indexPolynomial;

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Enter the degree at which to change the coefficient\n"
						  << "\033[0m\n";
				fflush(stdin);
				std::cin >> degree;

				if (degree < 1) throw "Invalid degree";

				std::cout << "\033[35;40m\033[1m" << "Enter the coefficient\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> coeff;

				polynomials[indexPolynomial].Set(coeff, degree);
				std::cout << polynomials[indexPolynomial];

				break;
			}
			case 5:
			{
				int first;
				int second;
				int third;
				int choose;

				std::cout << "\033[35;40m\033[1m" << "1. adding\n"
													 "2. subtraction\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> choose;
				if (choose < 1 || choose > 2) throw "Invalid number";

				if (choose == 1)
				{
					std::cout << "\033[35;40m\033[1m" << "First polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> first;

					if (first < 0 || first > 9) throw "Invalid number";

					std::cout << "\033[35;40m\033[1m" << "Second polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> second;

					if (second < 0 || second > 9) throw "Invalid number";

					std::cout << "\033[35;40m\033[1m" << "Third polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> third;

					if (third < 0 || third > 9) throw "Invalid number";

					polynomials[third] = polynomials[first] + polynomials[second];

					if (polynomials[third].GetNumberOfCoeff() == 0)
					{
						std::cout << "\033[35;40m\033[1m" << "Polymonial is Empty\n" << "\033[0m\n";
					}
					else
					{
						std::cout << polynomials[first];
						std::cout << "\033[35;40m\033[1m" << "+++++++\n" << "\033[0m\n";
						std::cout << polynomials[second];
						std::cout << "\033[35;40m\033[1m" << "=======\n" << "\033[0m\n";
						std::cout << polynomials[third];
					}
					break;
				}
				else if (choose == 2)
				{
					std::cout << "\033[35;40m\033[1m" << "First polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> first;

					if (first < 0 || first > 9) throw "Invalid number";

					std::cout << "\033[35;40m\033[1m" << "Second polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> second;

					if (second < 0 || second > 9) throw "Invalid number";

					std::cout << "\033[35;40m\033[1m" << "Third polynomial (0-8):" << "\033[0m\n";

					fflush(stdin);
					std::cin >> third;

					if (third < 0 || third > 9) throw "Invalid number";

					polynomials[third] = polynomials[third] = polynomials[first] - polynomials[second];
					if (polynomials[third].GetNumberOfCoeff() == 0)
					{
						std::cout << "\033[35;40m\033[1m" << "Polymonial is Empty\n" << "\033[0m\n";
					}
					else
					{
						std::cout << polynomials[first];
						std::cout << "--------\n";
						std::cout << polynomials[second];
						std::cout << "=======\n";
						std::cout << polynomials[third];
					}
					break;
				}
				else throw "Invalid number";
			}
			case 6:
			{
				int choose;
				int factor;

				std::cout << "\033[35;40m\033[1m" << "Polynomial (0-8):" << "\033[0m\n";

				fflush(stdin);
				std::cin >> choose;

				std::cout << "\033[35;40m\033[1m" << "Factor:" << "\033[0m\n";

				fflush(stdin);
				std::cin >> factor;

				if (polynomials[choose].GetNumberOfCoeff() == 0)
				{
					std::cout << "\033[35;40m\033[1m" << "Polymonial is Empty\n" << "\033[0m\n";
				}
				else
				{
					std::cout << polynomials[choose];
					std::cout << "\033[35;40m\033[1m" << "*******\n" << factor << "\n=======" << "\033[0m\n\n";
					polynomials[choose] = polynomials[choose] * factor;
					std::cout << polynomials[choose];
				}
				break;
			}
			case 7:
			{
				int choose;
				int x;

				std::cout << "\033[35;40m\033[1m" << "Polynomial (0-8):" << "\033[0m\n";

				fflush(stdin);
				std::cin >> choose;

				std::cout << "\033[35;40m\033[1m" << "x:" << "\033[0m\n";

				fflush(stdin);
				std::cin >> x;

				std::cout << "\033[37;40m\033[1m" << "Value:" << polynomials[choose].ValueCalculation(x) << "\033[0m\n\n";
				break;
			}
			case 8:
			{
				int first;
				int second;

				std::cout << "\033[35;40m\033[1m" << "Enter the polynomial from which to take the integral (0-8)"
						  << "\033[0m\n";
				fflush(stdin);
				std::cin >> first;

				std::cout << "\033[35;40m\033[1m" << "Enter the polynomial where to write the integral (0-8)"
						  << "\033[0m\n";
				fflush(stdin);
				std::cin >> second;

				polynomials[second] = polynomials[first].FindIntegral();
				std::cout << polynomials[first];
				std::cout << polynomials[second];
				break;
			}
			case 9:
			{
				int indexPolynomial;

				std::cout << "\033[35;40m\033[1m" << "Which cell (0-8) to reset?\n" << "\033[0m\n";
				fflush(stdin);
				std::cin >> indexPolynomial;

				if (indexPolynomial < 0 || indexPolynomial > 10) throw "Invalid index";

				std::cout << "\033[35;40m\033[1m" << "Polynom cleared" << "\033[0m";
				polynomials[indexPolynomial] = Polynomial(0);
				break;
			}
			case 10:
			{
				exit = true;
				break;
			}
			}
		}
	}
	catch (const char* e)
	{
		std::cout << "\033[31;40m\033[1m" << (e) << "\033[0m\n";
	}
}
