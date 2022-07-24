#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//������ת��Ϊʮ�����ƺ���ʵ��
string bin_hex(string str)
{
	string hex = "";//�����洢������ɵ�ʮ��������
	int temp = 0;//�����洢ÿ����λ����������ʮ����ֵ
	while (str.size() % 4 != 0)//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
	{
		str = "0" + str;//���λ��0ֱ������Ϊ4�ı�������
	}
	for (int i = 0; i < str.size(); i += 4) 
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;                 //�жϳ�4λ����������ʮ���ƴ�СΪ����
		if (temp < 10) //���õ���ֵС��10ʱ������ֱ����0-9������
		{
			hex += to_string(temp);
		}
		else //���õ���ֵ����10ʱ����Ҫ����A-F��ת��
		{
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
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

//������ת��Ϊʮ���Ƶĺ���ʵ��
int bin_dec(string str) 
{
	int dec = 0;
	for (int i = 0; i < str.size(); i++) 
	{
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
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

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
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

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
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

string fill(string str)//�����ݽ������ 
{
	string res = "";

	//δ����ǰ
	//for (int i = 0; i < str.size() ; i ++) //���Ƚ�����ֵת��Ϊ16�����ַ���
	//{
	//	res += DecToHex((int)str[i]);
	//}
	
	//����ѭ��չ������
	int j = 0;
	for ( j = 0; j < str.size()-1; j+=2) //���Ƚ�����ֵת��Ϊ16�����ַ���
	{
		res += (dec_hex((int)str[j]) + dec_hex((int)str[j + 1]));
	}
	res += dec_hex((int)str[j]);

	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
	while (res.size() % 128 != 112)
	{
		res += "0";//��0���������
	}
	string res_len = dec_hex(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) 
	{
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LS(string str, int len) //ʵ��ѭ������lenλ����
{
	string res = hex_bin(str);
	res = res.substr(len) + res.substr(0, len);
	return bin_hex(res);
}

string XOR(string str1, string str2) //ʵ��������
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";
	//ʹ��ѭ��չ������
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

string AND(string str1, string str2) //ʵ�������
{   
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";
	//ʹ��ѭ��չ������
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

string OR(string str1, string str2) //ʵ�ֻ����
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	string res = "";

	//ʹ��ѭ��չ������
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

string NOT(string str)//ʵ�ַǲ���
{
	string res1 = hex_bin(str);
	string res = "";
	//ʹ��ѭ��չ������
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

char one_xor(char str1, char str2) //ʵ�ֵ����ص�������
 {
	return str1 == str2 ? '0' : '1';
 }

char one_and(char str1, char str2) //ʵ�ֵ����ص������
{
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string modmeth(string str1, string str2) //mod 2^32����ĺ���ʵ��
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

string P1(string str) //ʵ���û�����P1��X��
{
	return XOR(XOR(str, LS(str, 15)), LS(str, 23));
}

string P0(string str) //ʵ���û�����P0��X��
{
	return XOR(XOR(str, LS(str, 9)), LS(str, 17));
}

string T(int j)//����Tj����ֵ�ĺ���ʵ��
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

string FF(string str1, string str2, string str3, int j) //ʵ�ֲ�������FF����
{
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else 
	{
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j)//ʵ�ֲ�������GG����
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
string extension(string str)//��Ϣ��չ����
{
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) //���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
	{
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LS(res.substr((i - 3) * 8, 8), 15))), LS(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}

	for (int i = 0; i < 64; i++)//���ݹ�ʽ����64λW'ֵ
	{
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	
	return res;
}

string compress(string str1, string str2) //��Ϣѹ������
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

string iteration(string str) //����ѹ������ʵ��
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

int main() //������
{
	
	string str = "welcome to the sdu";
	
	cout << "������ϢΪ�ַ���: " + str << endl;
	cout << endl;
	string fillnum = fill(str);
	string result = iteration(fillnum);
	cout << "�Ӵ�ֵ��";
	for (int i = 0; i < 8; i++) 
	{
		cout << result.substr(i * 8, 8) << "  ";
	}
	cout << endl;

	
}

