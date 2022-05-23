/*
# 4-去除C程序中的注释
## 描述
C程序的注释用\/\\*...\\*\/来表示。请写一个程序，将输入的C程序源代码中的注释去掉，输出去掉注释之后的源代码。
注意：
[1] 用于测试的C代码保证符合语法，不使用C++的//注释语法。
[2] C语言不允许出现嵌套注释。具体来说，对于\/\\*\/\\*\\*\/"\\*\/"，如果不允许嵌套注释，那么它表示字符串"\\*\/"；如果允许嵌套注释，它表示一个引号"。
[3] 字符串中出现的注释符\/\\*属于字符串的一部分，注释中出现的双引号"属于注释的一部分。

## 输入
符合语法的C代码文本文件。代码每行不超过200个字符。

## 输出
去掉注释后的C代码。要求只能去掉注释，不可以做其他的修改，比如调整缩进，去除注释之外的换行符等。

## 样例1
### 输入
\/\\*Hash Search: 
Hash function: division method; 
handling collisions: open addressing's linear probing. 
In this exercise, M is the basic area's length, all keys are non negative integers.\\*\/

#define M 11

int hash(int key)
{
	return key % M;
}

void init_hash(int* hashtable)
{
	int i;
	for(i = 0; i < M; ++i)
	{
		hashtable[i] = -1;
	}
}

\/\\*return value: 
1:found, *position is the key's index; 
0:not found, *position is where to insert the key; 
-1:overflow. \\*\/
int search_hash(int* hashtable, int key, int* position)
{
	int i, h = hash(key);
	for(i = 0; i < M; ++i)
	{
		if(key == hashtable[h])
		{
			*position = h;
			return 1;
		}
		if(-1 == hashtable[h])
		{
			*position = h;
			return 0;
		}
		h = (h+1) % M;
	}
	*position = -1;
	return -1;
}

\/\\*return value: 1:inserted, 0:overflow\\*\/
int insert_hash(int* hashtable, int key)
{
	int position, result;
	result = search_hash(hashtable, key, &position);
	if(-1 == result)
		return 0;
	hashtable[position] = key;
	return 1;
}

void main()
{
	int hashtable[M];
	init_hash(hashtable);
	srand(time(NULL));
	int i, j, key;
	for(i = 0; i < 8; ++i) 	\/\\*make a hash table with 8 elements\\*\/
	{
		key = rand() % 50;
		insert_hash(hashtable, key);
		printf("Insert %d\n", key);
		for(j = 0; j < M; ++j)
			printf("%3d", hashtable[j]);
		printf("\n");
	}

	printf("Please input the key to search:\n");
	scanf("%d", &key);
	i = search_hash(hashtable, key, &j);
	if(1 == i)
		printf("Found!Its index is %d\n", j);
	else
		printf("Not found!\n");
}

### 输出


#define M 11

int hash(int key)
{
	return key % M;
}

void init_hash(int* hashtable)
{
	int i;
	for(i = 0; i < M; ++i)
	{
		hashtable[i] = -1;
	}
}


int search_hash(int* hashtable, int key, int* position)
{
	int i, h = hash(key);
	for(i = 0; i < M; ++i)
	{
		if(key == hashtable[h])
		{
			*position = h;
			return 1;
		}
		if(-1 == hashtable[h])
		{
			*position = h;
			return 0;
		}
		h = (h+1) % M;
	}
	*position = -1;
	return -1;
}


int insert_hash(int* hashtable, int key)
{
	int position, result;
	result = search_hash(hashtable, key, &position);
	if(-1 == result)
		return 0;
	hashtable[position] = key;
	return 1;
}

void main()
{
	int hashtable[M];
	init_hash(hashtable);
	srand(time(NULL));
	int i, j, key;
	for(i = 0; i < 8; ++i) 	
	{
		key = rand() % 50;
		insert_hash(hashtable, key);
		printf("Insert %d\n", key);
		for(j = 0; j < M; ++j)
			printf("%3d", hashtable[j]);
		printf("\n");
	}

	printf("Please input the key to search:\n");
	scanf("%d", &key);
	i = search_hash(hashtable, key, &j);
	if(1 == i)
		printf("Found!Its index is %d\n", j);
	else
		printf("Not found!\n");
}

*/

#include <stdio.h>

typedef enum {
    NORMAL,
    COMMENTARY,
    STRING
} State;

int main() {
    char c;
    State s = NORMAL;
    while ((c=getchar()) != EOF) {
        switch (s) {
            case NORMAL:
                if (c == '/') {
                    if ((c=getchar()) == '*')
                        s = COMMENTARY;
                    else {
                        putchar('/');
                        putchar(c);
                    }
                }
                else {
                    if (c == '"')
                        s = STRING;
                    putchar(c);
                }
                break;
            case COMMENTARY:
                if (c == '*' && getchar() == '/')
                    s = NORMAL;
                break;
            case STRING:
                if (c == '"')
                    s = NORMAL;
                putchar(c);
                break;
        }
    }
}