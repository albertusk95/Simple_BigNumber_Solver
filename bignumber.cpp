#include "bignumber.h"

// variabel global
int jmlh_op_kali = 0, jmlh_op_plus = 0, jmlh_op_min = 0;
int jmlh_op_plus_detail = 0, jmlh_op_min_detail = 0;

// konstruktor: menset nilai bn_a dan bn_b menjadi bna dan bnb secara berurutan
BigNumber::BigNumber (string bna, string bnb, int _max_length) {
	// alokasi buffer bn_a dan bn_b untuk menyimpan string input
	bn_a = new char[bna.length()+1];
	bn_b = new char[bnb.length()+1];

	// memasukkan string input ke dalam setiap buffer
	for (int i = 0; i <= bna.length(); i++) {
		bn_a[i] = bna[i];
	}
	for (int i = 0; i <= bnb.length(); i++) {
		bn_b[i] = bnb[i];
	}

	// inisialisasi atribut max_length, is_min_a, dan is_min_b
	max_length = _max_length;
	is_min_a = 0;
	is_min_b = 0;
}

// destruktor
BigNumber::~BigNumber() {
	delete[] bn_a;
	delete[] bn_b;
}

// GETTER
int BigNumber::panjangBNA(const BigNumber& BN) {
	return strlen(BN.bn_a);
}
int BigNumber::panjangBNB(const BigNumber& BN) {
	return strlen(BN.bn_b);
}

// method
void BigNumber::printab() {
	cout <<"a: ";
	for (int i = 0; i <= strlen(bn_a); i++) {
		if (bn_a[i] == '\0') {
			cout << "nul" << endl;
		} else {
			cout << bn_a[i];
		}
	}
	cout <<"b: ";
	for (int i = 0; i <= strlen(bn_b); i++) {
		if (bn_b[i] == '\0') {
			cout << "nul" << endl;
		} else {
			cout << bn_b[i];
		}
	}
	//cout << endl;
}

void BigNumber::addZero() {
	// menambahkan angka 0 sebanyak max_length - bn.length() di depan string bn
	// I.S: string input terdefinisi yaitu bn_a dan bn_b
	// F.S: string input bn_a dan bn_b sudah memiliki karakter tambahan yaitu 0 di depannya sesuai definisi prosedur

	// untuk big number A
	char* temp = new char[max_length+1];
	int j = 0;

	for (int i = 0; i <= max_length; i++) {
		if (i < max_length - strlen(bn_a)) {
			temp[i] = '0';
		} else {
			temp[i] = bn_a[j];
			j++;
		}
	}
	// menghapus buffer milik bn_a yang lama
	delete[] bn_a;
	// menggantinya dengan buffer milik temp_a
	bn_a = new char[max_length+1];
	for (int i = 0; i <= max_length; i++) {
		bn_a[i] = temp[i];
	}
	// menghapus buffer sementara temp_a
	delete[] temp;

	// untuk big number B
	temp = new char[max_length+1];
	j = 0;

	for (int i = 0; i <= max_length; i++) {
		if (i < max_length - strlen(bn_b)) {
			temp[i] = '0';
		} else {
			temp[i] = bn_b[j];
			j++;
		}
	}
	// menghapus buffer milik bn_a yang lama
	delete[] bn_b;
	// menggantinya dengan buffer milik temp_a
	bn_b = new char[max_length+1];
	for (int i = 0; i <= max_length; i++) {
		bn_b[i] = temp[i];
	}
	// menghapus buffer sementara temp_a
	delete[] temp;
}
	
void countpowten(string* result, string yangmaudipow, int pjgchar) {
	char* buff_temp;
	buff_temp = new char[yangmaudipow.length() + pjgchar + 1];
	for (int j = 0; j < yangmaudipow.length() + pjgchar; j++) {
		if (j < yangmaudipow.length()) {
			buff_temp[j] = yangmaudipow[j];
		} else {
			buff_temp[j] = '0';
		}
	}
	buff_temp[yangmaudipow.length() + pjgchar] = '\0';

	*result = string(buff_temp);		// menyimpan hasil yangmaudipow x 10^(pjgchar)
	delete[] buff_temp;
}

void BigNumber::startRecPlus(const BigNumber& BIN, string* buff_add_str) {	
	// BRUTE FORCE
	vector<int> v_add;
	int ch_int_a, ch_int_b;
	int saved_value = 0;

	for (int i = strlen(BIN.bn_a)-1; i >= 0; i--) {
		//ch_int_a = atoi(BIN.bn_a[i]);
		ch_int_a = BIN.bn_a[i] - '0';

		//ch_int_b = atoi(BIN.bn_b[i]);
		ch_int_b = BIN.bn_b[i] - '0';

		if (ch_int_a + ch_int_b >= 10) {
			if (saved_value == 1) {
				jmlh_op_plus_detail = jmlh_op_plus_detail + 2;
				jmlh_op_min_detail++;
				v_add.push_back(ch_int_a + ch_int_b - 9); 
			} else {
				saved_value = 1;
				jmlh_op_plus_detail++;
				jmlh_op_min_detail++;
				v_add.push_back(ch_int_a + ch_int_b - 10); 
			}
		} else {
			if (saved_value == 1) {
				saved_value = 0;
				jmlh_op_plus_detail = jmlh_op_plus_detail + 2;
				jmlh_op_min_detail++;
				if (ch_int_a + ch_int_b + 1 >= 10) {
					saved_value = 1;
					v_add.push_back(ch_int_a + ch_int_b - 9);
				} else {
					v_add.push_back(ch_int_a + ch_int_b + 1);
				}
			} else {
				saved_value = 0;
				jmlh_op_plus_detail++;
				v_add.push_back(ch_int_a + ch_int_b);
			}
		}
	}

	if (saved_value == 1) {
		jmlh_op_plus_detail++;
		v_add.push_back(1);
	}
	reverse(v_add.begin(), v_add.end());

	// memindahkan hasil penjumlahan di dalam vektor ke dalam buffer char*
	char* buff_add = new char[v_add.size() + 1];
	for (int i = 0; i < v_add.size(); i++) {
		buff_add[i] = v_add[i] + '0';
	}
	buff_add[v_add.size()] = '\0';

	// konversi char* ke string
	*buff_add_str = string(buff_add);

	// dealokasi memori dari vektor
	vector<int>().swap(v_add);
}

void BigNumber::startRecMinus(const BigNumber& BIN, string* buff_minus_str, char* maxchar) {
	// BRUTE FORCE
	vector<int> v_minus;
	int ch_int_1, ch_int_2;
	int temp_ch_int_1, temp_ch_int_2;
	int borrowed_value = 0;
	int status = 0;
	char maxbn;

	// mencari nilai yang paling besar di antara 2 big number
	for (int i = 0; i < strlen(BIN.bn_a); i++) {
		temp_ch_int_1 = BIN.bn_a[i] - '0';
		temp_ch_int_2 = BIN.bn_b[i] - '0';
		
		if (temp_ch_int_1 > temp_ch_int_2) {
			maxbn = 'a';
			break;
		} else if (temp_ch_int_1 < temp_ch_int_2) {
			maxbn = 'b';
			break;
		}
	}

	*maxchar = maxbn;

	for (int i = strlen(BIN.bn_a)-1; i >= 0; i--) {
		
		if (maxbn == 'a') {
			ch_int_1 = BIN.bn_a[i] - '0';
			ch_int_2 = BIN.bn_b[i] - '0';
		} else {
			ch_int_1 = BIN.bn_b[i] - '0';
			ch_int_2 = BIN.bn_a[i] - '0';
		}

		if (ch_int_1 < ch_int_2) {
			if (borrowed_value == 1) {
				jmlh_op_min_detail = jmlh_op_min_detail + 2;
				jmlh_op_plus_detail++;
				v_minus.push_back(ch_int_1 + 9 - ch_int_2);
			} else {
				borrowed_value = 1;
				jmlh_op_plus_detail++;
				jmlh_op_min_detail++;
				v_minus.push_back(ch_int_1 + 10 - ch_int_2);
			}
		} else {
			if (borrowed_value == 1) {
				if (ch_int_1 - 1 < ch_int_2) {
					borrowed_value = 1;
					jmlh_op_min_detail = jmlh_op_min_detail + 2;
					jmlh_op_plus_detail++;
					v_minus.push_back(ch_int_1 + 9 - ch_int_2);
				} else {
					borrowed_value = 0;
					jmlh_op_min_detail = jmlh_op_min_detail + 2;
					v_minus.push_back(ch_int_1 - 1 - ch_int_2);
				}
			} else {
				borrowed_value = 0;
				jmlh_op_min_detail++;
				v_minus.push_back(ch_int_1 - ch_int_2);
			}
		}
	}

	reverse(v_minus.begin(), v_minus.end());

	// memindahkan hasil penjumlahan di dalam vektor ke dalam buffer char*
	char* buff_minus = new char[v_minus.size() + 1];
	for (int i = 0; i < v_minus.size(); i++) {
		buff_minus[i] = v_minus[i] + '0';
	}
	buff_minus[v_minus.size()] = '\0';

	// konversi char* ke string
	*buff_minus_str = string(buff_minus);

	// dealokasi memori dari vektor
	vector<int>().swap(v_minus);
}

void countupluswminusv(string* result, string nilai_u, string nilai_v, string nilai_w, int pjgchar, int* isnegative) {
	// GOAL: pow(10, pjgchar/2) * (u + w - v)
	string buff_add_str;
	int maxl;
	int result_ml;

	// memanggil prosedur plus untuk menjumlahkan nilai_u dan nilai_w
	if (nilai_u.length() > nilai_w.length()) {
		maxl = nilai_u.length();
	} else if (nilai_u.length() < nilai_w.length()) {
		maxl = nilai_w.length();
	} else {
		maxl = nilai_u.length();
	}
	
	makepowoftwo(&result_ml, maxl);
	maxl = result_ml;

	BigNumber BNUPLUSW(nilai_u, nilai_w, maxl);
	BNUPLUSW.addZero();

	BNUPLUSW.startRecPlus(BNUPLUSW, &buff_add_str);		// buff_add_str akan menyimpan hasil penjumlahan u dan w

	// memanggil prosedur minus untuk (u+w) - v, nilai (u+w) disimpan di buff_add_str
	if (buff_add_str.length() > nilai_v.length()) {
		maxl = buff_add_str.length();
	} else if (buff_add_str.length() < nilai_v.length()) {
		maxl = nilai_v.length();
	} else {
		maxl = buff_add_str.length();
	}

	makepowoftwo(&result_ml, maxl);
	maxl = result_ml;

	BigNumber BNUWMINV(buff_add_str, nilai_v, maxl);
	BNUWMINV.addZero();

	string buff_minus_str_uwv;
	char maxchar;

	if (*isnegative == 0) {
		// jika nilai v positif
		BNUWMINV.startRecMinus(BNUWMINV, &buff_minus_str_uwv, &maxchar);	// buff_minus_str_uwv akan menyimpan hasil pengurangan (u+w) - v
		if (maxchar == 'b') {
			*isnegative = 1;
		}
	} else {
		// jika nilia v negatif maka (u+w)-v menjadi (u+w)+v dan hasilnya pasti positif
		BNUWMINV.startRecPlus(BNUWMINV, &buff_minus_str_uwv);
		*isnegative = 0;
	}

	// menambahkan angka 0 di belakang buff_minus_str_uwv sebanyak m/2
	string hasiluwvpowten;
	countpowten(&hasiluwvpowten, buff_minus_str_uwv, pjgchar/2);

	*result = hasiluwvpowten;
}

void countuwv(string* result, string nilai_u_times_ten, string nilai_upluswminv, string nilai_w) {

	int maxl;
	int result_ml;

	if (nilai_u_times_ten.length() > nilai_upluswminv.length()) {
		maxl = nilai_u_times_ten.length();
	} else if (nilai_u_times_ten.length() < nilai_upluswminv.length()) {
		maxl = nilai_upluswminv.length();
	} else {
		maxl = nilai_u_times_ten.length();
	}

	makepowoftwo(&result_ml, maxl);
	maxl = result_ml;

	string buff_add_str;
	BigNumber BNUW(nilai_u_times_ten, nilai_upluswminv, maxl);
	BNUW.addZero();

	BNUW.startRecPlus(BNUW, &buff_add_str);		// buff_add_str akan menyimpan hasil penjumlahan nilai_u_timesten dan nilai_upluswminv

	string buff_add_uwv;

	if (buff_add_str.length() > nilai_w.length()) {
		maxl = buff_add_str.length();
	} else if (buff_add_str.length() < nilai_w.length()) {
		maxl = nilai_w.length();
	} else {
		maxl = buff_add_str.length();
	}

	makepowoftwo(&result_ml, maxl);
	maxl = result_ml;

	BigNumber BNUWV(buff_add_str, nilai_w, maxl);
	BNUWV.addZero();

	BNUWV.startRecPlus(BNUWV, &buff_add_uwv);	// buff_add_uwv akan menyimpan hasil penjumlahan buff_add_str dan nilai_w

	// mengembalikan nilai
	*result = buff_add_uwv;
}

void BigNumber::startRecTimes(const BigNumber& BIN, string* buff_times_str, string* buff_times_str_v, string* buff_times_str_w, int* isNegative) {
	
	// KAMUS
	char* temp_bn_p;
	char* temp_bn_q;
	char* temp_bn_r;
	char* temp_bn_s;

	string temp_bn_p_str;
	string temp_bn_q_str;
	string temp_bn_r_str;
	string temp_bn_s_str;
	string buff_times, buff_times_v, buff_times_w;

	stringstream convert, convert_v, convert_w;
	stringstream convu, convv, convw;

	int counter = 0;
	int u, v, w;
	int m;
	int ismin;
	int buff_u_int, buff_uwv_int, buff_ab_int;
	int final_u, final_v, final_w, final_final;

	int n = strlen(BIN.bn_a);

	// mendapatkan nilai p, q, r, dan s
		
	// p adalah digit terdepan dari BIN.bn_a sebanyak n/2 digit dan harus dibuat menjadi bertipe string
	temp_bn_p = new char[(n/2)+1];
	for (int i = 0; i < n/2; i++) {
		temp_bn_p[counter] = BIN.bn_a[i];
		counter++;
	}
	temp_bn_p[counter] = '\0';
	temp_bn_p_str = string(temp_bn_p);

	// q adalah digit sisa dari BIN.bn_a dan harus dibuat menjadi bertipe string
	counter = 0;
	temp_bn_q = new char[(n/2)+1];
	for (int i = n/2; i < n; i++) {
		temp_bn_q[counter] = BIN.bn_a[i];
		counter++;
	}
	temp_bn_q[counter] = '\0';
	temp_bn_q_str = string(temp_bn_q);

	// r adalah digit terdepan dari BIN.bn_b sebanyak n/2 digit dan harus dibuat menjadi bertipe string
	counter = 0;
	temp_bn_r = new char[(n/2)+1];
	for (int i = 0; i < n/2; i++) {
		temp_bn_r[counter] = BIN.bn_b[i];
		counter++;
	}
	temp_bn_r[counter] = '\0';
	temp_bn_r_str = string(temp_bn_r);

	// s adalah digit sisa dari BIN.bn_b dan harus dibuat menjadi bertipe string
	counter = 0;
	temp_bn_s = new char[(n/2)+1];
	for (int i = n/2; i < n; i++) {
		temp_bn_s[counter] = BIN.bn_b[i];
		counter++;
	}
	temp_bn_s[counter] = '\0';
	temp_bn_s_str = string(temp_bn_s);

	int maxl;

	// mencari nilai u = p x r
	if (strlen(temp_bn_p) == 1 && strlen(temp_bn_r) == 1) { 
		// basis
		u = (temp_bn_p[0] - '0') * (temp_bn_r[0] - '0');
		jmlh_op_kali++;
		// mengembalikan nilai
		convert << u;
		*buff_times_str = convert.str();
		final_u = u;
	} else {
		// rekursif
		if (temp_bn_p_str.length() > temp_bn_r_str.length()) {
			maxl = temp_bn_p_str.length();
		} else if (temp_bn_p_str.length() < temp_bn_r_str.length()) {
			maxl = temp_bn_r_str.length();
		} else {
			maxl = temp_bn_p_str.length();
		}

		BigNumber BNR(temp_bn_p_str, temp_bn_r_str, maxl);

		// memanggil dirinya sendiri 
		BNR.startRecTimes(BNR, &buff_times, &buff_times_v, &buff_times_w, &ismin);

		m = strlen(temp_bn_p);

		// menghitung u x 10^(n)
		// menambahkan angka 0 di belakang buff_times sebanyak m digit
		string buffer_u_times_ten;
		countpowten(&buffer_u_times_ten, buff_times, m);	// hasil buff_times x 10^(n) akan disimpan di buffer_u_times_ten

		// menghitung (10^(n/2) x (u + w - v))
		// hasil (u + w - v) x 10^(n/2) akan disimpan di buffer_upluswminv
		string buffer_upluswminv;
		countupluswminusv(&buffer_upluswminv, buff_times, buff_times_v, buff_times_w, m, &ismin);
		jmlh_op_min++;

		// menghitung a x b = buffer_u_times_ten + buffer_upluswminv + buff_times_w
		// hasilnya akan disimpan di buffer_uwv
		string buffer_uwv;
		countuwv(&buffer_uwv, buffer_u_times_ten, buffer_upluswminv, buff_times_w);

		jmlh_op_plus = jmlh_op_plus + 3;
		// mengembalikan nilai
		*buff_times_str = buffer_uwv;
	}

	// mencari nilai v = (q-p) * (s-r)
	// menghitung (q-p) dengan memanggil prosedur pengurangan
	if (temp_bn_p_str.length() > temp_bn_q_str.length()) {
		maxl = temp_bn_p_str.length();
	} else if (temp_bn_p_str.length() < temp_bn_q_str.length()) {
		maxl = temp_bn_q_str.length();
	} else {
		maxl = temp_bn_p_str.length();
	}

	BigNumber BNQ(temp_bn_q_str, temp_bn_p_str, maxl);

	string buff_minus_str_qp;
	char maxcharqp;
	BNQ.startRecMinus(BNQ, &buff_minus_str_qp, &maxcharqp);
	jmlh_op_min++;

	// menghitung (s-r) dengan memanggil prosedur pengurangan
	if (temp_bn_s_str.length() > temp_bn_r_str.length()) {
		maxl = temp_bn_s_str.length();
	} else if (temp_bn_s_str.length() < temp_bn_r_str.length()) {
		maxl = temp_bn_r_str.length();
	} else {
		maxl = temp_bn_s_str.length();
	}

	BigNumber BNS(temp_bn_s_str, temp_bn_r_str, maxl);

	string buff_minus_str_sr;
	char maxcharsr;
	BNS.startRecMinus(BNS, &buff_minus_str_sr, &maxcharsr);
	jmlh_op_min++;

	// menghitung v = (q-p) * (s-r) dengan (q-p) dan (s-r) adalah 2 objek baru
	int isneg = 0;
	if ((maxcharqp == 'b' && maxcharsr == 'a') ||  (maxcharqp == 'a' && maxcharsr == 'b')) {
		// berarti salah satu big number nya negatif
		isneg = 1;
	} else {
		isneg = 0;
	}

	if (buff_minus_str_qp.length() == 1 && buff_minus_str_sr.length() == 1) {
		v = atoi(buff_minus_str_qp.c_str()) * atoi(buff_minus_str_sr.c_str());
		jmlh_op_kali++;
		// mengembalikan nilai
		convert_v << v;
		*buff_times_str_v = convert_v.str();
		*isNegative = isneg;
		final_v = v;
	} else {
		if (buff_minus_str_qp.length() > buff_minus_str_sr.length()) {
			maxl = buff_minus_str_qp.length();
		} else if (buff_minus_str_qp.length() < buff_minus_str_sr.length()) {
			maxl = buff_minus_str_sr.length();
		} else {
			maxl = buff_minus_str_qp.length();
		}

		BigNumber BNQS(buff_minus_str_qp, buff_minus_str_sr, maxl);

		// memanggil dirinya sendiri
		ismin = isneg;
		BNQS.startRecTimes(BNQS, &buff_times, &buff_times_v, &buff_times_w, &ismin);
		
		m = buff_minus_str_qp.length();

		*isNegative = isneg;

		// menghitung u x 10^(n)
		// menambahkan angka 0 di belakang buff_times sebanyak m digit
		string buffer_u_times_ten;
		countpowten(&buffer_u_times_ten, buff_times, m);	// hasil buff_times x 10^(n) akan disimpan di buffer_u_times_ten

		// menghitung (10^(n/2) x (u + w - v))
		string buffer_upluswminv;
		countupluswminusv(&buffer_upluswminv, buff_times, buff_times_v, buff_times_w, m, &ismin);
		jmlh_op_min++;

		// menghitung a x b
		string buffer_uwv;
		countuwv(&buffer_uwv, buffer_u_times_ten, buffer_upluswminv, buff_times_w);

		jmlh_op_plus = jmlh_op_plus + 3;
		*buff_times_str_v = buffer_uwv;
		//*isNegative = ismin;
		ismin = 0;
	}

	// mencari w = q x s
	if (strlen(temp_bn_q) == 1 && strlen(temp_bn_s) == 1) { 
		// basis
		w = (temp_bn_q[0] - '0') * (temp_bn_s[0] - '0');
		jmlh_op_kali++;
		// mengembalikan nilai
		convert_w << w;
		*buff_times_str_w = convert_w.str();
		final_w = w;
	} else {
		if (temp_bn_q_str.length() > temp_bn_s_str.length()) {
			maxl = temp_bn_q_str.length();
		} else if (temp_bn_q_str.length() < temp_bn_s_str.length()) {
			maxl = temp_bn_s_str.length();
		} else {
			maxl = temp_bn_q_str.length();
		}

		BigNumber BNW(temp_bn_q_str, temp_bn_s_str, maxl);

		// memanggil dirinya sendiri
		BNW.startRecTimes(BNW, &buff_times, &buff_times_v, &buff_times_w, &ismin);

		m = strlen(temp_bn_q);	

		// menghitung u x 10^(n)
		string buffer_u_times_ten;
		countpowten(&buffer_u_times_ten, buff_times, m);	// hasil buff_times x 10^(n) akan disimpan di buffer_u_times_ten

		// menghitung(10^(n/2) x (u + w - v))
		string buffer_upluswminv;
		countupluswminusv(&buffer_upluswminv, buff_times, buff_times_v, buff_times_w, m, &ismin);
		jmlh_op_min++;

		// menghitung a x b
		string buffer_uwv;
		countuwv(&buffer_uwv, buffer_u_times_ten, buffer_upluswminv, buff_times_w);

		jmlh_op_plus = jmlh_op_plus + 3;
		*buff_times_str_w = buffer_uwv;
	}
}

void makepowoftwo(int* result, int maxlength) {
	int k = 1, status = 0;
	while (pow(2, k) <= maxlength) {
		if (pow(2, k) == maxlength) {
			status = 1;
			*result = pow(2, k);
			break;
		}
		k++;
	}	
	if (status == 0) { *result = pow(2, k); }
}

void eliminatezero(string* final_res, string yangdieliminasi) {
	int found = 0, i = 0, pos, start_loc;
	while (found == 0 && i < yangdieliminasi.length()) {
		if (yangdieliminasi[i] != '0') {
			found = 1;
			pos = i;
			start_loc = i;
		} else {
			i++;
		}
	}
	if (found == 1) {
		char* temp_final = new char[yangdieliminasi.length() - pos + 1];
		for (int j = 0; j < yangdieliminasi.length() - pos; j++) {
			temp_final[j] = yangdieliminasi[start_loc];
			start_loc++;
		}
		temp_final[yangdieliminasi.length()-pos] = '\0';
		*final_res = string(temp_final);
		delete[] temp_final;
	} else {
		*final_res = "0";
	}
}

/*
max_length = 5
bn_a = 123\0

buffer temp_a[5+1] = 0 0 0 0 0 0
*/

/*
a x b = (p x 10^(n/2) + q) x (r x 10^(n/2) + s)
u = p x r
v = (q - p) x (s - r) = qs - qr - ps + pr 
w = q x s

a x b = (p x r x 10^(n) + p x s x 10^(n/2) + q x r x 10^(n/2) + q x s)
a x b = (u x 10^(n)) + 10^(n/2) x (pxs+qxr) + (w)
pxs + qxr = u + w - v 
a x b = (u x 10^(n)) + (10^(n/2) x (u + w - v)) + (w)

a = 125 -> 0125
b = 200 -> 0200
//b dijadikan 0002 (2 angka 0 terakhir dihilangkan)



root(a, b):
a x b = (p x 10^(n/2) + q) x (r x 10^(n/2) + s) -> n = 4 -> p = r = n/2 digit paling awal -> q = s = sisa digitnya
a x b = (01 x 10^2 + 25) x (02 x 10^2 + 00) 
hitung u = p x r = 01 x 02 -> misal diganti dengan 0011 x 0022 -> p = 00, q = 11, r = 00, s = 22
	root(p, r):
	p x r = (p1 x 10^(n/2) + q1) x (r1 x 10^(n/2) + s1) -> n = 2 -> p1 = r1 = n/2 digit paling awal -> q1 = s1 = sisa digitnya
	p x r = (0 x 10^1 + 1) + (0 x 10^1 + 2)



	fungsiTime(00112345, 00222345, final_u, final_v, final_w)
	fungsiTime(0011, 0022, final_u, final_v, final_w)
	fungsiTime(00, 00, final_u, final_v, final_w)
		basis -> final_u = 0, final_v = 0, final_w = 0 send them
		final_final_u = 0
		final_u = final_final_u = 0
	fungsiTime(11, 22, final_u, final_v, final_w)
		basis -> final_u = 2, final_v = 0, final_w = 2 send them
		final_final_v = 242
		final_v = final_final_v = 242
	fungsiTime(11, 22, final_u, final_v, final_w)
		basis -> final_u = 2, final_v = 0, final_w = 2 send them
		final_final_w = 242
		final_w = final_final_w = 242
	final_final = 242

	bna = 1234567899999999
	bnb = 0002345678999999
	
	p = 12345678
	q = 99999999
	r = 00023456
	s = 78999999

	u = 12345678 x 00023456
	v = (99999999 - 12345678) * (78999999 - 00023456)
	w = 99999999 x 78999999

	bna = 00112345 
	bnb = 00222345

	call fungsiTime (bna, bnb, final_u, final_v, final_w)
	akan dipecah menjadi (0011 x 10^(8/2) + 2345) + (0022 x 10^(8/2) + 2345)
	berusaha mendapatkan bentuk a x b = (u x 10^(8)) + (10^(8/2) x (u + w - v)) + (w)
	dengan u = 0011 x 0022
	dengan v = (2345 - 0011) x (2345 - 0022)
	dengan w = 2345 x 2345
	mendapatkan p = 0011, q = 2345, r = 0022, s = 2345

	1) menghitung u = 0011 x 0022 -> n = 4
		n > 1, maka call fungsiTime (0011, 0022, &final_u, &final_v, &final_w) -> ke 1.x
		akan dipecah menjadi (00 x 10^(4/2) + 11) + (00 x 10^(4/2) + 22)
		berusaha mendapatkan bentuk a x b = (u x 10^(4)) + (10^(4/2) x (u + w - v)) + (w)
		dengan u = 00 x 00
		dengan v = (11 - 00) x (22 - 00)
		dengan w = 11 x 22
		mendapatkan p = 00, q = 11, r = 00, s = 22
		1.x) final_final = (final_u x 10^(4)) + (10^(4/2) x (final_u + final_w - final_v)) + (final_w)
			  jadi u = 0011 x 0022 = final_final [DONE]
				send final_final -> *final_u = final_final_u

		1.1) menghitung u = 00 x 00 -> n = 2
				1.1.a) n > 1, maka call fungsiTime (00, 00, &final_u, &final_v, &final_w) -> ke 1.1.c
				akan dipecah menjadi (0 x 10^(2/2) + 0) + (0 x 10^(2/2) + 0)
				1.1.b) berusaha mendapatkan bentuk a x b = (u x 10^(2)) + (10^(2/2) x (u + w - v)) + (w)
				dengan u = 0 x 0
				dengan v = (0 - 0) x (0 - 0)
				dengan w = 0 x 0
				mendapatkan p = 0, q = 0, r = 0, s = 0
				1.1.c) final_final_u = (final_u x 10^(2)) + (10^(2/2) x (final_u + final_w - final_v)) + (final_w)
						jadi u = 00 x 00 = final_final [DONE]
						send final_final_u -> *final_u = final_final_u 

				1.1.2) menghitung u = 0 x 0 -> n = 1
						n = 1, maka basis
						u = 0
						final_u = 0;
				1.1.3) menghitung v = (0 - 0) x (0 - 0) = 0 x 0 -> n = 1
						n = 1, maka basis 
						v = 0
						final_v = 0;
				1.1.4) menghitung w = 0 x 0 -> n = 1
						n = 1, maka basis 
						w = 0
						final_w = 0
				1.1.5) menghitung final_final untuk 1.1.b
						send final_u, final_v, final_w 
		1.2) menghitung v = (11 - 00) x (22 - 00) = 11 x 22 -> n = 2
				1.2.a) n > 1, maka call fungsiTime (11, 22, &final_u, &final_v, &final_w) -> ke 1.2.c
				akan dipecah menjadi (1 x 10^(2/2) + 1) + (2 x 10^(2/2) + 2)
				1.2.b) berusaha mendapatkan bentuk a x b = (u x 10^(2)) + (10^(2/2) x (u + w - v)) + (w)
				dengan u = 1 x 2
				dengan v = (1 - 1) x (2 - 2)
				dengan w = 1 x 2
				mendapatkan p = 1, q = 1, r = 2, s = 2
				1.2.c) final_final_v = (final_u x 10^(2)) + (10^(2/2) x (final_u + final_w - final_v)) + (final_w)
						jadi v = 11 x 22 = final_final [DONE]
						send final_final_v -> *final_v = final_final_v 

				1.2.2) menghitung u = 1 x 2 -> n = 1
						n = 1, maka basis
						u = 2
						final_u = 2;
				1.2.3) menghitung v = (1 - 1) x (2 - 2) = 0 x 0 -> n = 1
						n = 1, maka basis 
						v = 0
						final_v = 0;
				1.2.4) menghitung w = 1 x 2 -> n = 1
						n = 1, maka basis 
						w = 2
						final_w = 2
				1.2.5) menghitung final_final untuk 1.2.b
						send final_u, final_v, final_w 
		1.3) menghitung w = (11 - 00) x (22 - 00) = 11 x 22 -> n = 2
				1.3.a) n > 1, maka call fungsiTime (11, 22, &final_u, &final_v, &final_w) -> ke 1.3.c
				akan dipecah menjadi (1 x 10^(2/2) + 1) + (2 x 10^(2/2) + 2)
				1.3.b) berusaha mendapatkan bentuk a x b = (u x 10^(2)) + (10^(2/2) x (u + w - v)) + (w)
				dengan u = 1 x 2
				dengan v = (1 - 1) x (2 - 2)
				dengan w = 1 x 2
				mendapatkan p = 1, q = 1, r = 2, s = 2
				1.3.c) final_final_w = (final_u x 10^(2)) + (10^(2/2) x (final_u + final_w - final_v)) + (final_w)
						jadi w = 11 x 22 = final_final [DONE]
						send final_final_w -> *final_w = final_final_w 

				1.3.2) menghitung u = 1 x 2 -> n = 1
						n = 1, maka basis
						u = 2
						final_u = 2;
				1.3.3) menghitung v = (1 - 1) x (2 - 2) = 0 x 0 -> n = 1
						n = 1, maka basis 
						v = 0
						final_v = 0;
				1.3.4) menghitung w = 1 x 2 -> n = 1
						n = 1, maka basis 
						w = 2
						final_w = 2
				1.3.5) menghitung final_final untuk 1.3.b
						send final_u, final_v, final_w 






	p x r = (00 x 10^2 + 11) + (00 x 10^2 + 22)

	hitung u = p1 x r1 = 0 x 0 = 0 (BASIS) -> diganti 00 x 00 
		// seandainya jika digit u masih lebih dari 1
		hitung u = p2 x r2 = basis
		hitung v = (q2-p2) x (s2-r2) = basis
		hitung w = q2 x s2 = basis
		final p1 x r1 = .....
	hitung v = (q1-p1) x (s1-r1) = 1 x 2 = 2 (BASIS)
		// seandainya jika digit u masih lebih dari 1
		hitung u = p2 x r2 = basis
		hitung v = (q2-p2) x (s2-r2) = basis
		hitung w = q2 x s2 = basis
		final p1 x r1 = .....
	hitung w = q1 x s1 = 1 x 2 = 2 (BASIS)
		// seandainya jika digit u masih lebih dari 1
		hitung u = p2 x r2 = basis
		hitung v = (q2-p2) x (s2-r2) = basis
		hitung w = q2 x s2 = basis
		final p1 x r1 = .....

	maka final p x r = u diganti finalu, dst
	final p x r = (u x 10^(n)) + (10^(n/2) x (u + w - v)) + (w) = (0 x 10^2) + ((10^1) x (0 + 2 - 2)) + 2 = 2 (result)
hitung v = (q-p)x(s-r) = (25-01) x (00-02) = 24 x -02
	root(q-p, s-r):
	(q-p) x (s-r) = (p1 x 10^(n/2) + q1) x (r1 x 10^(n/2) + s1) -> n = 2 
	(q-p) x (s-r) = (2 x 10^1 + 4) x (0 x 10^1 + 2)
	hitung u = p1 x r1 = 2 x 0 = 0 (BASIS)
	hitung v = (q1-p1) x (s1-r1) = 2 x 2 = 4 (BASIS)
	hitung w = 4 x 2 = 8 (BASIS)
	final (q-p) x (s-r) = (u x 10^(n)) + (10^(n/2) x (u + w - v)) + (w) = 0 + 40 + 8 = 48 (result)
hitung w = q x s = 25 x 00
	root(q, s):
	q x s = (2 x 10^1 + 5) + (0 x 10^1 + 0)
	hitung u = p1 x r1 = 2 x 0 = 0 (BASIS)
	hitung v = (q1-p1) x (s1-r1) = 3 x 0 = 0 (BASIS)
	hitung w = 5 x 0 = 0 (BASIS)
	final q x s = 0 + 0 + 0 = 0 (result)
final a x b = 2x10^4 + 10^2 x (50) + 0 = 25000 (result)

final_final = 2*10^4 + 10^2 * -46 + 0 = -4600 + 20000 = 15400
*/

/*
/////////
10 digit
Nilai a: 0000005637827899
Nilai b: 0000009274622778

p = 00000056
q = 37827899
r = 00000092
s = 74622778

u = p x r = 00000056 * 00000092 = 0000000000005152 [OK]
v = (37827899 - 00000056) * (74622778 - 00000092) = 2822815250246298 [OK]
w = 37827899 * 74622778 = 00000000000000002822822909283422 [OK]

/////////
30 digit
Nilai a: 00273648673337468392839489399899
Nilai b: 00474644487392384827384758673828

p = 0027364867333746
q = 8392839489399899
r = 0047464448739238
s = 4827384758673828

u = pxr = 0027364867333746 * 0047464448739238 = 0000000000000000000000000000000000001298858342818635460271725548 [OK]
v = (8392839489399899 - 0027364867333746) * (4827384758673828 - 0047464448739238) = 39986302048256393193238082932270 [OK]
w = 8392839489399899 * 4827384758673828 = 0000000000000000000000000000000040515465433124905246802797143372 [OK]

/////////
50 digit

Nilai a: 0000000000000092345728373849583920453394094059039059403940490003
Nilai b: 0000000000000039283938495802020002920299999929383782640283748372

p = 00000000000000923457283738495839 
q = 20453394094059039059403940490003
r = 00000000000000392839384958020200
s = 02920299999929383782640283748372

u = p x r = 0000000000000000000000000000362770391378834654137933707377947800 [OK]
v = (20453394094059039059403940490003 - 00000000000000923457283738495839) * (02920299999929383782640283748372 - 00000000000000392839384958020200)
v = 00000000000000000000000000000000000000000000000000000000000000000059730046771425538771025467532107859080342389657883649794388208 [OK]
w = 20453394094059039059403940490003 * 02920299999929383782640283748372
w = 00000000000000000000000000000000000000000000000000000000000000000059730046771436270442087317643340225953522433524352343233525116 [OK]

/////////
100 digit [OK]

Nilai a: 00000000000000000000000000001757755800556448216268483935782833328354948606456863995235148761243621828767243643155277207753059873
Nilai b: 00000000000000000000000000002556336359923278344523651110596756264362191603759719363210877793821379735354100624396258002895837015

p = 0000000000000000000000000000175775580055644821626848393578283332 
q = 8354948606456863995235148761243621828767243643155277207753059873
r = 0000000000000000000000000000255633635992327834452365111059675626
s = 4362191603759719363210877793821379735354100624396258002895837015

u = 0000000000000000000000000000175775580055644821626848393578283332 * 0000000000000000000000000000255633635992327834452365111059675626
u = 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044934150648284988727624233556064721552127421987315230963508289842465832

v = (8354948606456863995235148761243621828767243643155277207753059873 - 0000000000000000000000000000175775580055644821626848393578283332)
dikali (4362191603759719363210877793821379735354100624396258002895837015 - 0000000000000000000000000000255633635992327834452365111059675626)
v = 8354948606456863995235148761067846248711598821528428814174776541 * 4362191603759719363210877793565746099361772789943892891836161389
v = 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000036445886660930099936684817464908523084880890070863374662871012902349288503178244970282298159605226844808448597811474072287175449

w = 8354948606456863995235148761243621828767243643155277207753059873 * 4362191603759719363210877793821379735354100624396258002895837015
w = 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000036445886660930099936684817467811095735143218967671071954302188053347875942828009446036493497037809591100975881952389759744599095

 4 493 415 064 828 498 872 762 423 355 606 472 184 238 468 701 354 812 064 427 801 899 007 676 252 914 610 944 703 987 
 029 787 418 057 658 197 417 941 644 118 715 311 727 301 082 833 347 875 942 828 009 446 036 493 497 037 809 591 100 
 975 881 952 389 759 744 599 095

*/

// list to do 
// hilangkan 0 di depan hasil final 
// tambahin - utk pengurangan jika hslnya minus 
// hilangkan komentar debugging