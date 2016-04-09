#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <chrono>

using namespace std;

extern int jmlh_op_kali, jmlh_op_plus, jmlh_op_min;
extern int jmlh_op_plus_detail, jmlh_op_min_detail;

class BigNumber {
public:
	// konstruktor: menset nilai bn_a dan bn_b menjadi bna dan bnb secara berurutan
	BigNumber (string bna, string bnb, int _max_length);

	// destruktor
	~BigNumber();

	// GETTER
	int panjangBNA(const BigNumber& BN);
	int panjangBNB(const BigNumber& BN);

	// method
	void printab();
	void addZero();
	void startRecPlus(const BigNumber& BIN, string* buff_add_str);
	void startRecMinus(const BigNumber& BIN, string* buff_minus_str, char* maxchar);
	void startRecTimes(const BigNumber& BIN, string* buff_times_str, string* buff_times_str_v, string* buff_times_str_w, int* isNegative);

private:
	char* bn_a;
	char* bn_b;
	int max_length;
	int is_min_a, is_min_b;
};

void countpowten(string* result, string yangmaudipow, int pjgchar);
void countupluswminusv(string* result, string nilai_u, string nilai_v, string nilai_w, int pjgchar, int* isnegative);
void countuwv(string* result, string nilai_u_times_ten, string nilai_upluswminv, string nilai_w);
void makepowoftwo(int* result, int maxlength);
void eliminatezero(string* final_res, string yangdieliminasi);