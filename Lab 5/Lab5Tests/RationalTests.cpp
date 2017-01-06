﻿#include "stdafx.h"
#include "../Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greatest_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}
BOOST_AUTO_TEST_CASE(Test_Minimal_Common_Denominator)
{
	BOOST_CHECK_EQUAL(MCD(2, 3), 6u);
	BOOST_CHECK_EQUAL(MCD(1, 3), 3u);
	BOOST_CHECK_EQUAL(MCD(2, 6), 6u);
}


/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)

	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}
	
	//////////////////////////////////////////////////////////////////////////
	// TODO: 1. Реализовать метод ToDouble() согласно заданию
	// Возвращает отношение числителя и знаменателя в виде числа double
	// Пример использования:
	//	CRational r(3, 5)
	//	cout << r.ToDouble(); // Должно вывести 0.6
	//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
	{
		BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
		BOOST_CHECK_EQUAL(CRational(5, 2).ToDouble(), 2.5);
		BOOST_CHECK_EQUAL(CRational(-3, 5).ToDouble(), -0.6);
	}



	//////////////////////////////////////////////////////////////////////////
	// TODO: 2. Реализовать унарный + и унарный -
	// Указание: см. материалы к лекции
	// Пример использования:
	//	const CRational r1(3, 5);
	//	CRational r2 = -r1; // r2 должно стать -3/5
	//	assert(r2.GetNumerator(), -3);
	//	assert(r2.GetDenominator(), 5);
	//	CRational r3 = +r2; // r3 также равно -3/5
	//	assert(r3.GetNumerator(), -3);
	//	assert(r3.GetDenominator(), 5);
	// Унарный минус возвращает раицональное число с противоположным знаком
	// Унарный плюс возвращает рациональное число, равное текущему
	// Реализация не должна допускать операции вроде:
	//  -someRational = someOtherRational;
	//	+someRational = someOtherRational;
	//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_unary_plus_operator)
	{
		VerifyRational(+CRational(6, 8), 3, 4);
		VerifyRational(+CRational(-6, 8), -3, 4);
		VerifyRational(+CRational(-6, -8), 3, 4);
	}

	BOOST_AUTO_TEST_CASE(has_unary_minus_operator)
	{
		VerifyRational(-CRational(6, 8), -3, 4);
		VerifyRational(-CRational(-6, 8), 3, 4);
		VerifyRational(-CRational(-6, -8), -3, 4);
	}

	//////////////////////////////////////////////////////////////////////////
	// TODO: 3. Реализовать бинарный +
	// Возвращает результат сложения двух рациональных чисел, 
	//	рационального числа с целым, целого числа с рациональным.
	//	(1/2) + (1/6) = (2/3)
	//	(1/2) + 1     = (3/2)
	//	1 + (1/2)     = (3/2)
	//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_binary_plus_operator)
	{
		CRational fraction = CRational(1, 2) + CRational(1, 3);
		VerifyRational(fraction, 5, 6);
		fraction = CRational(-1, 2) + CRational(1, 3);
		VerifyRational(fraction, -1, 6);
		fraction = CRational(1, 2) + CRational(1, 6);
		VerifyRational(fraction, 2, 3);
		fraction = CRational(1, 2) + CRational(1);
		VerifyRational(fraction, 3, 2);
		fraction = CRational(1) + CRational(1, 2) + CRational(1, 6);
		VerifyRational(fraction, 5, 3);
	}


	//////////////////////////////////////////////////////////////////////////
	// TODO: 4. Реализовать бинарный -
	// Возвращает разность двух рациональных чисел, 
	//	рационального числа и целого, либо целого числа и рационального:
	//	(1/2) - (1/6) = (1/3)
	//	(1/2) - 1     = (-1/2)
	//	1 - (1/2)     = (1/2)
	//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_binary_minus_operator)
	{
		CRational fraction = CRational(1, 2) - CRational(1, 6);
		VerifyRational(fraction, 1, 3);
		fraction = CRational(1, 2) - CRational(1);
		VerifyRational(fraction, -1, 2);
		fraction = CRational(1) - CRational(1, 2) - CRational(1, 4);
		VerifyRational(fraction, 1, 4);
	}


	//////////////////////////////////////////////////////////////////////////
	// TODO: 5. Реализовать оператор +=
	// Выполняет увеличение рационального числа на величину второго рационального,
	//	либо целого числа:
	//	(1/2) += (1/6)  → (2/3)
	//	(1/2) += 1      → (3/2)
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 6. Реализовать оператор -=
	// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
	// (1/2) -= (1/6)  → (1/3)
	// (1/2) -= 1      → (-1/2)
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 7. Реализовать оператор *
	// Возвращает результат произведения рациональных чисел, 
	//	рационального и целого, либо целого и рационального :
	//	(1/2) * (2/3) = (1/3)
	//	(1/2) * (-3)  = (-3/2)
	//	7 * (2/3)     = (14/3)
	//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_binary_multiply_operator)
	{
		CRational fraction = CRational(1, 2) * CRational(2, 3);
		std::cout << fraction.GetNumerator() << "/" << fraction.GetDenominator() << std::endl;
		VerifyRational(fraction, 1, 3);
		fraction = CRational(1, 2) * CRational(-3);
		VerifyRational(fraction, -3, 2);
		fraction = CRational(7) * CRational(2, 3);
		VerifyRational(fraction, 14, 3);
	}




	//////////////////////////////////////////////////////////////////////////
	// TODO: 8. Реализовать оператор /
	// Возвращает частное двух рациональных чисел, 
	//	рационального и целого, целого и рационального :
	//	(1/2) ⁄ (2/3) = (3/4)
	//	(1/2) ⁄ 5     = (1/10)
	//	7 ⁄ (2/3)     = (21/2)
	//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_binary_division_operator)
	{
		CRational fraction = CRational(1, 2) / CRational(2, 3);
		std::cout << fraction.GetNumerator() << "/" << fraction.GetDenominator() << std::endl;
		VerifyRational(fraction, 3, 4);
		fraction = CRational(1, 2) / CRational(5);
		VerifyRational(fraction, 1, 10);
		fraction = CRational(7) / CRational(2, 3);
		VerifyRational(fraction, 21, 2);
	}




	//////////////////////////////////////////////////////////////////////////
	// TODO: 9. Реализовать оператор *=
	// Умножает значение первого рационального числа на другое рациональное, 
	//	либо целое:
	//	(1/2) *= (2/3) → (1/3)
	//	(1/2) *= 3     → (3/2)
	//////////////////////////////////////////////////////////////////////////





	//////////////////////////////////////////////////////////////////////////
	// TODO: 10. Реализовать оператор /=
	// Делит первое рациональное число на другое рациональное, 
	//	либо целое:
	//	(1/2) /= (2/3) → (3/4)
	//	(3/4) /= (3/8) → (2/1)
	//	(1/2) /= 3     → (1/6)
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 11. Реализовать операторы == и !=
	// Проверяют равенство (и неравенство) двух рациональных чисел, 
	//	целого и рационального, рационального и целого:
	//	(1/2) == (1/2) → true
	//	(4/1) == 4     → true
	//	3 == (3/1)     → true
	//	(1/2) != (2/3) → true
	//	(1/2) != 7     → true
	//	3 != (2/3)     → true
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 12. Реализовать операторы <, >, <=, >=
	// Сравнивают два рациональных числа, рациональное с целым, 
	//	целое с рациональным:
	//	(1/2) >= (1/3) → true
	//	(1/2) <= (1/3) → false
	//	(3/1) > 2      → true
	//	(1/2) < 7      → true
	//	3 <= (7/2)     → true
	//	3 >= (8/2)     → false
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
	//	std::ostream в формате <числитель>/<знаменатель>, 
	//	например: 7/15
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
	//	std::istream в формате <числитель>/<знаменатель>, 
	//	например: 7/15
	//////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()