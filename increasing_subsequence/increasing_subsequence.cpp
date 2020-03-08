// increasing_subsequence.cpp.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>  
#define SIZE 10000
using namespace std;



char* copyArr(string target, int size)
{
	char* result = new char[size];
	for ( int i = 0; i < size; i++ )
	{
		result[i] = target[i];
	}
	return result;
}

int main()
{
	string result;
	string input;

	char* arr;
	int* pointer;
	int* countArr;
	
	int max, max_index, index, size, k;

	while ( getline(cin, input) )
	{
		
		if ( input.size() == 0 )
		{

			break;
		}

		size = input.size();
		for ( int i = 0; i < input.size(); i++ )
		{
			if ( input[i] == ' ' )
			{
				size = i;
				break;
			}
		}
		if(size == 0) break;

		arr = copyArr(input, size);
		
		pointer = new int[size];
		countArr = new int[size];
		max_index = 0;
		for ( int i = 0; i < size; i++ )
		{
			pointer[i] = -1;
			countArr[i] = 1;
			for ( int j = 0; j < i; j++ )
			{
				if ( arr[i] > arr[j] && countArr[i] < countArr[j] + 1 )
				{
					countArr[i] = countArr[j] + 1;
					pointer[i] = j;
					if ( countArr[i] > countArr[max_index] ) max_index = i;
					
				}
			}
		}
		index = max_index;
		while ( index != -1 )
		{
		
			result = arr[index] + result;
			index = pointer[index];
		}

		cout << result << endl;

		result = "";
		input = "";
	}
	
	return 0;
}

