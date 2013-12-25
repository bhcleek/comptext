//======================================================================
//  comptext
//    Author: Dave Freese, W1HKJ <w1hkj@w1hkj.com>
//
//  based on the program RTTY Compare by
//    Alex Shovkoplyas, VE3NEA ve3nea@dxatlas.com
//  Original written in Pascal and distributed only for Windows OS
//
//  This program is distributed under the GPL license
//======================================================================

#include "comp_txt.h"

void comp_txt(string ref_file, string comp_file, string &results)
{
	results.clear();
	if (ref_file.empty() || comp_file.empty()) return;

	string sent = "";
	string rcvd = "";
	char ch;
	ifstream f1;
	f1.open(ref_file.c_str(), ios::binary);
	while (f1) {
		f1.get(ch);
		if (f1 && ch) sent += ch;
	}
	f1.close();

	ifstream f2;
	f2.open(comp_file.c_str(), ios::binary);
	while (f2) {
		f2.get(ch);
		if (f2 && ch) rcvd += ch;
	}
	f2.close();

	if (sent.empty() || rcvd.empty()) return;

	int error_count = Compare(sent, rcvd);

	double ber = 1.0 * error_count / (8.0 * sent.length());
	double cer = 1.0 - pow((1.0 - ber), 8.0);

	char temp[200];

	snprintf(temp, sizeof(temp), "Chars: %d, Errors: %d, CER: %5.4f, BER: %5.4f",
		(int)sent.length(), error_count, cer, ber);
	results = temp;
//	cout << temp << "\n";
}

int Compare(string sent, string rcvd)
{
	if (sent == rcvd) return 0;

	string s1 = sent;
	string s2 = rcvd;

	int distance[256];
	int sh;
	int d;
	for (int i = 0; i < 256; i++) {
		d = 0;
		sh = i;
		for (int j = 0; j < 8; j++) {
			d += sh & 0x01;
			sh /= 2;
		}
		distance[i] = d;
	}

	vector<int> Row1(s1.length() + 1, 0);
	vector<int> Row2(s1.length() + 1, 0);

	size_t s;
	size_t T, L, D;

//dynamic programming algorithm

	for (size_t i = 1; i < Row2.size(); i++)
		Row2[i] = Row2[i-1] + 1;

	for (size_t r = 0; r < s2.length(); r++) {
		Row1 = Row2;
		Row2.clear();
		for (size_t i = 0; i < s1.length() + 1; i++)
			Row2.push_back(0);
		Row2[0] = r + 1;
		for (s = 1; s < Row2.size(); s++) {
			D = Row1[s-1] + distance[(s1[s-1] ^ s2[r]) & 0xFF];
			L = Row2[s-1] + 1;
			T = Row1[s];
			Row2[s] = min(L, min(T, D));
		}
	}

	return Row2[Row2.size() - 1];
}
