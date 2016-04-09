#include "bignumber.h"

int main() {
	
	int max_length;
	int start_s, stop_s, start_add, stop_add, start_min, stop_min;
	int temp_op_plus_detail, temp_op_min_detail;
	string bn_a, bn_b;
	double time_in_seconds, time_in_seconds_plus, time_in_seconds_min;

	cout << "Nilai a: ";
	// mendapatkan string big number a
	while (getline(cin, bn_a)) { break; }

	cout << "Nilai b: ";
	// mendapatkan string big number b
	while (getline(cin, bn_b)) { break; }

	// mencari panjang string terbesar antara bn_a dan bn_b
	if (bn_a.length() > bn_b.length()) { max_length = bn_a.length(); } 
	else if (bn_a.length() < bn_b.length()) { max_length = bn_b.length(); } 
	else { max_length = bn_a.length(); }

	// membuat max_length menjadi bilangan pangkat 2 -> 2^k
	int result_ml;
	makepowoftwo(&result_ml, max_length);
	max_length = result_ml;

	// menghidupkan objek BN dengan parameter berupa big number a dan b dan max_length
	BigNumber BN(bn_a, bn_b, max_length);

	// menambahkan karakter 0 di depan string input yang lebih kecil dari pada max_length
	BN.addZero();

	// PERKALIAN - memulai proses rekursif
	int isNegative;
	int final_u_int, final_v_int, final_w_int, final_uvw_int;
	int panjangbna, panjangbnb;

	string buff_times_str, buff_times_str_v, buff_times_str_w;

	// memulai penghitungan waktu eksekusi operasi perkalian
	const auto start_time = std::chrono::steady_clock::now();
	BN.startRecTimes(BN, &buff_times_str, &buff_times_str_v, &buff_times_str_w, &isNegative);

	panjangbna = BN.panjangBNA(BN);

	// menghitung buff_times_str * 10^(panjangbna) dan disimpan di result_times_ten
	string result_times_ten;
	countpowten(&result_times_ten, buff_times_str, panjangbna);

	// menghitung (u+w-v)*10^(n/2) dan disimpan di result_upluswminv
	string result_upluswminv;
	countupluswminusv(&result_upluswminv, buff_times_str, buff_times_str_v, buff_times_str_w, panjangbna, &isNegative);

	// menghitung result_times_ten + result_upluswminv + buff_times_str_w
	string result_final;
	countuwv(&result_final, result_times_ten, result_upluswminv, buff_times_str_w);

	// menghilangkan semua angka 0 di depan bilangan utama
	string final_times;
	eliminatezero(&final_times, result_final);

	// menghentikan penghitungan waktu operasi perkalian
	time_in_seconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time).count() / 1000000.0;

	jmlh_op_plus = jmlh_op_plus + 3;
	jmlh_op_min++;
	cout << endl;
	cout << "a x b = " << final_times << endl;
	cout << "banyak operasi kali = " << jmlh_op_kali << endl;
	cout << "banyak operasi plus = " << jmlh_op_plus << endl;
	cout << "banyak operasi minus = " << jmlh_op_min << endl;
	cout << "waktu eksekusi perkalian = " << time_in_seconds << "microseconds" << endl << endl;

	// PENJUMLAHAN 
	jmlh_op_plus_detail = 0;
	jmlh_op_min_detail = 0;
	string buff_add_str;
	// memulai penghitungan waktu eksekusi operasi penjumlahan
	const auto start_time_plus = std::chrono::steady_clock::now();
	BN.startRecPlus(BN, &buff_add_str);
	
	// menghilangkan semua angka 0 di depan bilangan utama
	string final_plus;
	eliminatezero(&final_plus, buff_add_str);

	// menghentikan penghitungan waktu operasi penjumlahan
	time_in_seconds_plus = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time_plus).count() / 1000000.0;
	
	cout << "a + b = " << final_plus << endl;
	cout << "banyak operasi kali = " << "0" << endl;
	cout << "banyak operasi plus = " << jmlh_op_plus_detail << endl;
	cout << "banyak operasi minus = " << jmlh_op_min_detail << endl;
	cout << "waktu eksekusi penjumlahan = " << time_in_seconds_plus << "microseconds" << endl << endl;

	// PENGURANGAN
	jmlh_op_plus_detail = 0;
	jmlh_op_min_detail = 0;
	string buff_minus_str;
	char maxchar;
	// memulai penghitungan waktu eksekusi operasi pengurangan
	const auto start_time_minus = std::chrono::steady_clock::now();
	BN.startRecMinus(BN, &buff_minus_str, &maxchar);

	// menghilangkan semua angka 0 di depan bilangan utama
	string final_minus;
	eliminatezero(&final_minus, buff_minus_str);

	// menghentikan penghitungan waktu operasi penjumlahan
	time_in_seconds_min = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time_minus).count() / 1000000.0;


	if (maxchar == 'b') { cout << "a - b = " << "-" << final_minus << endl; } 
	else { cout << "a - b = " << final_minus << endl; }
	cout << "banyak operasi kali = " << "0" << endl;
	cout << "banyak operasi plus = " << jmlh_op_plus_detail << endl;
	cout << "banyak operasi minus = " << jmlh_op_min_detail << endl;
	cout << "waktu eksekusi pengurangan = " << time_in_seconds_min << "microseconds" << endl;

	return 0;
}

