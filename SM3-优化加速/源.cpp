#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//二进制转换为十六进制函数实现
string bin_hex(string str)
{
	string hex = "";//用来存储最后生成的十六进制数
	int temp = 0;//用来存储每次四位二进制数的十进制值
	while (str.size() % 4 != 0)//因为每四位二进制数就能够成为一个十六进制数，所以将二进制数长度转换为4的倍数
	{
		str = "0" + str;//最高位添0直到长度为4的倍数即可
	}
	for (int i = 0; i < str.size(); i += 4) 
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;                 //判断出4位二进制数的十进制大小为多少
		if (temp < 10) //当得到的值小于10时，可以直接用0-9来代替
		{
			hex += to_string(temp);
		}
		else //当得到的值大于10时，需要进行A-F的转换
		{
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//十六进制转换为二进制函数实现
string hex_bin(string str)
{
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			bin += table[str[i] - 'A' + 10];
		}
		else
		{
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

//二进制转换为十进制的函数实现
int bin_dec(string str) 
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++) 
	{
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//十进制转换为二进制的函数实现
string dec_bin(int str) 
{
	string bin = "";
	while (str >= 1)
	{
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//十六进制转换为十进制的函数实现
int hex_dec(string str) 
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else
		{
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//十进制转换为十六进制的函数实现
string dec_hex(int str) 
{
	string hex = "";
	int temp = 0;
	while (str >= 1) 
	{
		temp = str % 16;
		if (temp < 10 && temp >= 0) 
		{
			hex = to_string(temp) + hex;
		}
		else 
		{
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}

string fill(string str)//对数据进行填充 
{
	string res = "";

	//未加速前
	//for (int i = 0; i < str.size() ; i ++) //首先将输入值转换为16进制字符串
	//{
	//	res += DecToHex((int)str[i]);
	//}
	
	//进行循环展开加速
	int j = 0;
	for ( j = 0; j < str.size()-1; j+=2) //首先将输入值转换为16进制字符串
	{
		res += (dec_hex((int)str[j]) + dec_hex((int)str[j + 1]));
	}
	res += dec_hex((int)str[j]);

	int res_length = res.size() * 4;//记录的长度为2进制下的长度
	res += "8";//在获得的数据后面添1，在16进制下相当于是添加8
	while (res.size() % 128 != 112)
	{
		res += "0";//“0”数据填充
	}
	string res_len = dec_hex(res_length);//用于记录数据长度的字符串
	while (res_len.size() != 16) 
	{
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LS(string str, int len) //实现循环左移len位功能
{
	string res = hex_bin(str);
	res = res.substr(len) + res.substr(0, len);
	return bin_hex(res);
}

string XOR(string str1, string str2) //实现异或操作
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";
	//使用循环展开加速
	for (int i = 0; i < res1.size()-1; i+=2) 
	{
		if (res1[i] == res2[i]) 
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
		if (res1[i+1] == res2[i+1])
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
	}
	return bin_hex(res);
}

string AND(string str1, string str2) //实现与操作
{   
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";
	//使用循环展开加速
	for (int i = 0; i < res1.size()-1; i+=2)
	{
		if (res1[i] == '1' && res2[i] == '1') 
		{
			res += "1";
		}
		else 
		{
			res += "0";
		}
		if (res1[i+1] == '1' && res2[i+1] == '1')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
	}
	return bin_hex(res);
}

string OR(string str1, string str2) //实现或操作
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";

	//使用循环展开加速
	for (int i = 0; i < res1.size()-1; i+=2) 
	{
		if (res1[i] == '0' && res2[i] == '0') 
		{
			res += "0";
		}
		else
		{
			res += "1";
		}
		if (res1[i+1] == '0' && res2[i+1] == '0')
		{
			res += "0";
		}
		else 
		{
			res += "1";
		}
	}
	return bin_hex(res);
}

string NOT(string str)//实现非操作
{
	string res1 = hex_bin(str);
	string res = "";
	//使用循环展开加速
	for (int i = 0; i < res1.size()-1; i+=2)
	{
		if (res1[i] == '0')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
		if (res1[i+1] == '0')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
	}
	return bin_hex(res);
}

char one_xor(char str1, char str2) //实现单比特的异或操作
 {
	return str1 == str2 ? '0' : '1';
 }

char one_and(char str1, char str2) //实现单比特的与操作
{
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string modmeth(string str1, string str2) //mod 2^32运算的函数实现
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) 
	{
		res = one_xor(one_xor(res1[i], res2[i]), temp) + res;
		if (one_and(res1[i], res2[i]) == '1') 
		{
			temp = '1';
		}
		else 
		{
			if (one_xor(res1[i], res2[i]) == '1')
			{
				temp = one_and('1', temp);
			}
			else
			{
				temp = '0';
			}
		}
	}
	return bin_hex(res);
}

string P1(string str) //实现置换功能P1（X）
{
	return XOR(XOR(str, LS(str, 15)), LS(str, 23));
}

string P0(string str) //实现置换功能P0（X）
{
	return XOR(XOR(str, LS(str, 9)), LS(str, 17));
}

string T(int j)//返回Tj常量值的函数实现
{
	if (0 <= j && j <= 15)
	{
		return "79CC4519";
	}
	else 
	{
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) //实现布尔函数FF功能
{
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else 
	{
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j)//实现布尔函数GG功能
{
	if (0 <= j && j <= 15) 
	{
		return XOR(XOR(str1, str2), str3);
	}
	else 
	{
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str)//消息扩展函数
{
	string res = str;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i++) //根据公式生成第17位到第68位的W值
	{
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LS(res.substr((i - 3) * 8, 8), 15))), LS(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}

	for (int i = 0; i < 64; i++)//根据公式生成64位W'值
	{
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	
	return res;
}

string compress(string str1, string str2) //消息压缩函数
{
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = LS(modmeth(modmeth(LS(A, 12), E), LS(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LS(A, 12));
		TT1 = modmeth(modmeth(modmeth(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = modmeth(modmeth(modmeth(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LS(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LS(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	return res;
}

string iteration(string str) //迭代压缩函数实现
{
	int num = str.size() / 128;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string d = "", extensionb = "", compressb = "";
	for (int i = 0; i < num; i++) 
	{
		d = str.substr(i * 128, 128);
		extensionb = extension(d);
		compressb = compress(extensionb, V);
		V = XOR(V, compressb);
	}
	return V;
}

int main() //主函数
{
	
	string str = "welcome to the sdu";
	
	cout << "输入消息为字符串: " + str << endl;
	cout << endl;
	string fillnum = fill(str);
	string result = iteration(fillnum);
	cout << "杂凑值：";
	for (int i = 0; i < 8; i++) 
	{
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;

	
}

