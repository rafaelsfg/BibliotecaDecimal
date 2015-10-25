/*
 * decimal.h
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
 *	21/02/2014
 *
 *  Define a classe decimal, que representa números com precisão arbitrária.
 */

#ifndef _DECIMAL_H_
#define _DECIMAL_H_

#include "mpfr.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

// Define a classe decimal
class decimal
{
	private:
		mpfr_t num;	// define o decimal
		static unsigned int precisao;	// precisão do decimal

	public:
		char *get_str(void) const;	// Retorna uma string contendo o valor de 'num'

		////////
		static unsigned int GetPrecisao(void);	// Retorna a precisão
		static void SetPrecisao(unsigned int);	// Ajusta a precisão
		static decimal Pi(void); // Retorna o número Pi
		static decimal E(void); // Retorna o número de Euler
		static decimal SetStr(const char*); // Converte uma string para decimal

		//// Operações
		decimal& operator= ( const decimal& );
		decimal& operator= ( const double& );
		decimal& operator+ ( const decimal& );
		decimal& operator+ ( const double& );
		decimal& operator- ( const decimal& );
		decimal& operator- ( const double& );
		decimal& operator* ( const decimal& );
		decimal& operator* ( const double& );
		decimal& operator/ ( const decimal& );
		decimal& operator/ ( const double& );
		decimal& operator- ( void );
		decimal& operator+= ( const decimal& );
		decimal& operator+= ( const double& );
		decimal& operator-= ( const decimal& );
		decimal& operator-= ( const double& );
		decimal& operator*= ( const decimal& );
		decimal& operator*= ( const double& );
		decimal& operator/= ( const decimal& );
		decimal& operator/= ( const double& );

		//// Comparações
		bool operator== ( const decimal& );
		bool operator== ( const double& );
		bool operator!= ( const decimal& );
		bool operator!= ( const double& );
		bool operator<  ( const decimal& );
		bool operator< ( const double& );
		bool operator>  ( const decimal& );
		bool operator> ( const double& );
		bool operator>= ( const decimal& );
		bool operator>= ( const double& );
		bool operator<= ( const decimal& );
		bool operator<= ( const double& );
		friend bool ehnumero(decimal);

		//// Funções matemáticas
		friend decimal pow(decimal, decimal);
		friend decimal sqrt(decimal);
		friend decimal abs(decimal);
		friend decimal log(decimal);
		friend decimal log10(decimal);
		friend decimal exp(decimal);
		friend decimal fmod(decimal, decimal);
		friend decimal sin(decimal);
		friend decimal cos(decimal);
		friend decimal tan(decimal);
		friend decimal asin(decimal);
		friend decimal acos(decimal);
		friend decimal atan(decimal);

		//// Imprime na tela o valor do decimal
		friend std::ostream& operator<<( std::ostream&, const decimal& );

		////
		decimal();
		decimal(const decimal&);
		decimal(const double&);
		virtual ~decimal();
};

#endif /* _DECIMAL_H_ */
