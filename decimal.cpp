/*
 * decimal.cpp
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
 */


#include "decimal.h"

// Variável estática que armazena a precisão do decimal
unsigned int decimal::precisao = (unsigned int)(mpfr_get_default_prec() / 3.5);

// Retorna a precisão
unsigned int decimal::GetPrecisao(void)
{
	return precisao;
}

// Ajusta a precisão
void decimal::SetPrecisao(unsigned int p)
{
	if((int)(p * 3.5) < MPFR_PREC_MIN || (int)(p * 3.5) > MPFR_PREC_MAX)
	{
		std:: cout << "\n\nErro: Precisão informada é inválida\n\n";
	}
	else
	{
		precisao = p;
		mpfr_set_default_prec((int)(p * 3.5));
	}
}

// Retorna o número Pi
decimal decimal::Pi(void)
{
	decimal d;
	mpfr_const_pi(d.num, MPFR_RNDN);
	mpfr_free_cache();
	return d;
}

// Retorna o número de Euler
decimal decimal::E(void)
{
	decimal d;
	mpfr_t um;
	mpfr_init_set_d(um, 1.0, MPFR_RNDN);
	mpfr_exp(d.num, um, MPFR_RNDN);
	mpfr_clear(um);
	return d;
}

// Converte string para decimal
decimal decimal::SetStr(const char* str)
{
	decimal r;
	mpfr_set_str(r.num, str, 10, MPFR_RNDN);
	return r;
}

// Retorna uma string contendo o valor de 'num'
char *decimal::get_str(void) const
{
	char *temp = new char[precisao + 4];
	if (!temp)
	{
		std:: cout << "\n\nErro1 'get_str': falha na alocação de memória\n\n";
		exit(1);
	}

	mpfr_snprintf (temp, precisao + 4, "%.*RNG\n\n", precisao, num);

	int i = 0;
	do
	{
		if (temp[i] == '.') temp[i] = ',';
	} while (temp[i++] != '\0');

	return temp;
}

//// Imprime na tela o valor do decimal
std::ostream& operator<< ( std::ostream& out, const decimal& d)
{
	char *temp = new char[decimal::precisao + 10];
	if (!temp)
	{
		std:: cout << "\n\nErro '<<': falha na alocação de memória\n\n";
		exit(1);
	}

	mpfr_snprintf (temp, decimal::precisao + 10,"%.*RNG", decimal::precisao, d.num);

	int i = 0;
	while (1)
	{
		if (temp[i] == '.')
		{
			temp[i] = ',';
			break;
		}
		if (temp[i] == '\0') break;
		i++;
	}

	out << temp;

	delete temp;
	return out;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////// Operações ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Adição entre dois decimais
decimal& decimal::operator+ ( const decimal& d1 )
{
	decimal *d3 = new decimal;
	mpfr_add(d3->num, this->num, d1.num, MPFR_RNDN);
	return *d3;
}

// Adição entre um decimal e um double
decimal& decimal::operator+ ( const double& i )
{
	decimal *d3 = new decimal;
	mpfr_add_d(d3->num, this->num, i, MPFR_RNDN);
	return *d3;
}

// Subtração entre dois decimais
decimal& decimal::operator- ( const decimal& d1 )
{
	decimal *d3 = new decimal;
	mpfr_sub(d3->num, this->num, d1.num, MPFR_RNDN);
	return *d3;
}

// Subtração entre um decimal e um double
decimal& decimal::operator- ( const double& i )
{
	decimal *d3 = new decimal;
	mpfr_sub_d(d3->num, this->num, i, MPFR_RNDN);
	return *d3;
}

// Multiplicação entre dois decimais
decimal& decimal::operator* ( const decimal& d1 )
{
	decimal *d3 = new decimal;
	mpfr_mul(d3->num, this->num, d1.num, MPFR_RNDN);
	return *d3;
}

// Multiplicação entre um decimal e um double
decimal& decimal::operator* ( const double& i )
{
	decimal *d3 = new decimal;
	mpfr_mul_d(d3->num, this->num, i, MPFR_RNDN);
	return *d3;
}

// Divisão entre dois decimais
decimal& decimal::operator/ ( const decimal& d1 )
{
	decimal *d3 = new decimal;
	mpfr_div(d3->num, this->num, d1.num, MPFR_RNDN);
	return *d3;
}

// Divisão entre um decimal e um double
decimal& decimal::operator/ ( const double& i )
{
	decimal *d3 = new decimal;
	mpfr_div_d(d3->num, this->num, i, MPFR_RNDN);
	return *d3;
}

// Retorna a negação de decimal
decimal& decimal::operator- ( void )
{
	decimal *d3 = new decimal;
	mpfr_neg(d3->num, this->num, MPFR_RNDN);
	return *d3;
}

// Variável decimal recebe o valor de um decimal
decimal& decimal::operator= ( const decimal& d1 )
{
	mpfr_set(this->num, d1.num, MPFR_RNDN);
	return *this;
}

// Variável decimal recebe o valor de um double
decimal& decimal::operator= ( const double& i )
{
	mpfr_set_d(this->num, i, MPFR_RNDN);
	return *this;
}

// dX = dX + d1
decimal& decimal::operator+= ( const decimal& d1 )
{
	mpfr_add(this->num, this->num, d1.num, MPFR_RNDN);
	return *this;
}

// dX = dX + i
decimal& decimal::operator+= ( const double& i )
{
	mpfr_add_d(this->num, this->num, i, MPFR_RNDN);
	return *this;
}

// dX = dX - d1
decimal& decimal::operator-= ( const decimal& d1 )
{
	mpfr_sub(this->num, this->num, d1.num, MPFR_RNDN);
	return *this;
}

// dX = dX - i
decimal& decimal::operator-= ( const double& i )
{
	mpfr_sub_d(this->num, this->num, i, MPFR_RNDN);
	return *this;
}

// dX = dX * d1
decimal& decimal::operator*= ( const decimal& d1 )
{
	mpfr_mul(this->num, this->num, d1.num, MPFR_RNDN);
	return *this;
}

// dX = dX * i
decimal& decimal::operator*= ( const double& i )
{
	mpfr_mul_d(this->num, this->num, i, MPFR_RNDN);
	return *this;
}

// dX = dX / d1
decimal& decimal::operator/= ( const decimal& d1 )
{
	mpfr_div(this->num, this->num, d1.num, MPFR_RNDN);
	return *this;
}

// dX = dX / i
decimal& decimal::operator/= ( const double& i )
{
	mpfr_div_d(this->num, this->num, i, MPFR_RNDN);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////// Comparações //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Compara dois decimais e retorna 1 se iguais, e 0 do contrário
bool decimal::operator== ( const decimal& d1 )
{
	return mpfr_equal_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se iguais, e 0 do contrário
bool decimal::operator== ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) == 0) return 1;
	return 0;
}

// Compara dois decimais e retorna 1 se diferentes, e 0 do contrário
bool decimal::operator!= ( const decimal& d1 )
{
	return !mpfr_equal_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se diferentes, e 0 do contrário
bool decimal::operator!= ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) != 0) return 1;
	return 0;
}

// Compara dois decimais e retorna 1 se dX < d1, e 0 do contrário
bool decimal::operator< ( const decimal& d1 )
{
	return mpfr_less_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se dX < i, e 0 do contrário
bool decimal::operator< ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) < 0) return 1;
	return 0;
}

// Compara dois decimais e retorna 1 se dX > d1, e 0 do contrário
bool decimal::operator> ( const decimal& d1 )
{
	return mpfr_greater_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se dX > i, e 0 do contrário
bool decimal::operator> ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) > 0) return 1;
	return 0;
}

// Compara dois decimais e retorna 1 se dX >= d1, e 0 do contrário
bool decimal::operator>= ( const decimal& d1 )
{
	return mpfr_greaterequal_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se dX >= i, e 0 do contrário
bool decimal::operator>= ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) >= 0) return 1;
	return 0;
}

// Compara dois decimais e retorna 1 se dX <= d1, e 0 do contrário
bool decimal::operator<= ( const decimal& d1 )
{
	return mpfr_lessequal_p (this->num, d1.num);
}

// Compara um decimal com um double e retorna 1 se dX <= i, e 0 do contrário
bool decimal::operator<= ( const double& i )
{
	if (mpfr_cmp_d (this->num, i) <= 0) return 1;
	return 0;
}

// Retorna 1 se d for um decimal, do contrário retorna 0
bool ehnumero(decimal d)
{
	return mpfr_number_p (d.num);
}

//////////////////////////////////////////////////////////////////////////
/////////////////////// Funções matemáticas //////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Retorna d1 ^ d2
decimal pow(decimal d1, decimal d2)
{
	decimal r;
	mpfr_pow(r.num, d1.num, d2.num, MPFR_RNDN);
	return r;
}

// Retorna a raiz quadrada de d
decimal sqrt(decimal d)
{
	decimal r;
	mpfr_sqrt(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o valor absoluto de d
decimal abs(decimal d)
{
	decimal r;
	mpfr_abs(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o logarítmo natural (ln) de d
decimal log(decimal d)
{
	decimal r;
	mpfr_log(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o logarítmo de d na base 10
decimal log10(decimal d)
{
	decimal r;
	mpfr_log10(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna e ^ d
decimal exp(decimal d)
{
	decimal r;
	mpfr_exp(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o resto da divisão entre d1 e d2
decimal fmod(decimal d1, decimal d2)
{
	decimal r;
	mpfr_fmod(r.num, d1.num, d2.num, MPFR_RNDN);
	return r;
}

// Retorna o seno de d
decimal sin(decimal d)
{
	decimal r;
	mpfr_sin(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o cosseno de d
decimal cos(decimal d)
{
	decimal r;
	mpfr_cos(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna a tangente de d
decimal tan(decimal d)
{
	decimal r;
	mpfr_tan(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o arco seno de d
decimal asin(decimal d)
{
	decimal r;
	mpfr_asin(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o arco cosseno de d
decimal acos(decimal d)
{
	decimal r;
	mpfr_acos(r.num, d.num, MPFR_RNDN);
	return r;
}

// Retorna o arco tangente de d
decimal atan(decimal d)
{
	decimal r;
	mpfr_atan(r.num, d.num, MPFR_RNDN);
	return r;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

decimal::decimal()
{
	mpfr_init(num);
}

decimal::decimal(const decimal& obj)
{
	mpfr_init_set(num, obj.num, MPFR_RNDN);
}

decimal::decimal(const double& obj)
{
	mpfr_init_set_d(num, obj, MPFR_RNDN);
}

decimal::~decimal()
{
	mpfr_clear(num);
}

