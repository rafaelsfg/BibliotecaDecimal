/*
 * exemplo.cpp
 *
 * Copyright 2014 Rafael Andrade <rafaelsandrade@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


// Exibe exemplos de utilização da biblioteca decimal

#include <iostream>
#include "decimal.cpp"


int main()
{
	decimal::SetPrecisao(50); // Define a precisão para 50 dígitos

	decimal d1 = 1.0;

	// Divisão
	d1 = d1 / 7.0;

	std::cout << "1 / 7 = " << d1 << "\n";

	// Raiz quadrada de 2
	d1 = 2.0;
	std::cout << "\nRaiz de 2 = " << sqrt(d1) << "\n";

	// Número Pi
	decimal pi = decimal::Pi();
	std::cout << "\nPi = " << pi << "\n";

	// Cosseno de pi / 4
	std::cout << "\ncos(pi / 4) = " << cos(pi / 4.0) << "\n";

	return 0;
}

