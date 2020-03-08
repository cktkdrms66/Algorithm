// merge_slides.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

string** extra_m;
int extra_k;


//string manager function
string intToString(int n)
{
	stringstream s;
	s << n;
	return s.str();
}

string* StringSplit(string strTarget, string strTok, int size)
{
	int     nCutPos;
	int     nIndex = 0;
	string* strResult = new string[size];

	while ( (nCutPos = strTarget.find_first_of(strTok) < strTarget.find_first_of(9) ? strTarget.find_first_of(strTok) : strTarget.find_first_of(9)) != strTarget.npos )
	{
		if ( nCutPos > 0 )
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}
		strTarget = strTarget.substr(nCutPos + 1);
	}

	if ( strTarget.length() > 0 )
	{
		strResult[nIndex++] = strTarget.substr(0, nCutPos);
	}

	return strResult;
}

int* copyArr(string* target, int size)
{
	int* result = new int[size];
	for ( int i = 0; i < size; i++ )
	{
		result[i] = atoi(target[i].c_str());
	}
	return result;
}



//initialize the matrix
int** m_set(int size)
{
	int** result = new int*[size];
	for ( int i = 0; i < size; i++ )
	{
		result[i] = new int[size];
		for ( int j = 0; j < size; j++ )
		{
			result[i][j] = 0;
		}
	}

	return result;
}


//calculation function
int min_cal(int a, int b, int k)
{
	if ( a == 0 )
	{
		extra_k = k;
		return b;
	}
	else
	{
		if ( a < b )
		{
			extra_k = k;
			return a;
		}
		else
		{
			extra_k = k;
			return b;
		}
	}
}

int all_cal(int* arr, int start, int finish)
{
	int result = 0;
	if ( start == finish ) return 0;
	for ( int i = start; i <= finish; i++ )
	{
		result += arr[i];
	}
	return result;
}

int size_cal(string input)
{
	int result = 1;

	for ( int i = 0; i < input.size(); i++ )
	{
		if ( input[i] == ' ' || input[i] == 9)
		{
			result++;
		}
	}

	return result;
}


//EXTRA
//extra function
string extra_fun(int* arr, string** m, int i, int k, int j)
{
	string result;

	if ( k == -1 )
	{
		result = intToString(arr[i]);
	}
	else
	{
		result = "(" + m[i][k] + "," + m[k + 1][j] + ")";

	}
	return result;
}

//extra print
string extra_print(int size)
{
	string result;
	if ( size == 1 )
	{
		result = "";
	}
	else
	{
		result = extra_m[0][size - 1];
		
	}
	return result;

}

//extra matrix initialize
string** extra_m_set(int size)
{
	string** result = new string*[size];
	for ( int i = 0; i < size; i++ )
	{
		result[i] = new string[size];
		for ( int j = 0; j < size; j++ )
		{
			result[i][j] = "";
		}
	}

	return result;

}








//cost calculation function
//this is main algorithm 
//fill the min_cost_matrix
int cost_cal(int* arr, int** m, int size)
{
	int finish = size;
	int j, min, all;

	for ( int n = 0; n < size; n++ )
	{
		j = n;
		
		for ( int i = 0; i < finish; i++ )
		{
			extra_k = -1;
			min = 0;
			m[i][j] = all_cal(arr, i, j);
			for ( int k = i; k < j; k++ )
			{
				min = min_cal(min, m[i][k] + m[k + 1][j], k);
				
			}
			extra_m[i][j] = extra_fun(arr, extra_m, i, extra_k, j);
			m[i][j] += min;
			j++;
		}
		finish--;
		
	}

	return m[0][size - 1];
}

int err_fun(string input)
{
	string str_arr = "0123456789 ";
	char tab = 9;
	int count, space_count, i, j;

	str_arr += tab;
	//input size zero
	if ( input.size() == 0 )
	{
		return -1;
	}


	//In index 1 to last -1, There are no numbers or spaces, or
	//there exist a series of spaces
	space_count = 0;
	for ( i = 1; i < input.size() -1; i++ )
	{
		count = 0;
		
		for ( j = 0; j < str_arr.size(); j++ )
		{
			if ( input[i] == str_arr[j] )
			{
				space_count = 0;
				count = 1;
				break;
			}
			if ( input[i] == ' ' || input[i] == 9 )
			{
				space_count++;
				count = 1;
				break;
			}
			
		}
		if ( count == 0 ) return -1;
		if ( space_count == 2 ) return -1;
	}

	//In first or last case, there are no numbers. this must be number not space 
	count = 0;
	for ( j = 0; j < str_arr.size() -2; j++ )
	{
		if ( input[0] == str_arr[j] || input[i] == str_arr[j] )
		{
			if ( input.size() == 1 ) count++;
			count++;
		}

	}
	if ( count != 2 ) return -1;

	
}

int main()
{
	string input;
	string* str_arr;
	
	int size;
	int* int_arr;
	int** m;

	while ( getline(cin, input) )
	{
		
		if ( err_fun(input) == -1 ) break;


		size = size_cal(input);
		str_arr = StringSplit(input, " ", size);
		int_arr = copyArr(str_arr, size);
		m = m_set(size);
		extra_m = extra_m_set(size);
		cout << cost_cal(int_arr, m, size) << " ";
		cout << extra_print(size) << endl;


		input = "";

	}
    return 0;
}

