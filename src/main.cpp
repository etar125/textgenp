#include <iostream>
#include <string>
#include <random>
#include <fstream>
#define VERSION "v1.0-7924"
#define uchar unsigned char

using namespace std;
random_device gen;
// distro(gen);
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
uniform_int_distribution<uchar> full(0, alphabet.size());
uniform_int_distribution<uchar> steam(0, 35);
uniform_int_distribution<uchar> password(1, 32);

string genpassword() {
	string res = "";
	for(uchar i = password(gen); i > 0; i--)
		res += alphabet[full(gen)];
	return res;
} string gensteamkey() {
	string res = "";
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			res += alphabet[steam(gen)];
		} res += "-";
	} res = res.substr(0, res.size() - 1);
	return res;
}

long index = 0;

/*bool starts(string what, string with) {
	for(int i = 0; i < what.size() && i < with.size(); i++)
		if(what[i] != with[i]) return false;
	return true;
} */ string format(string str) {
	string res = "";
	string tmp = "";
	bool n = false;
	for(int i = 0; i < str.size(); i++) {
		tmp = str.substr(i, 1);
		if (tmp == "/" && !n) n = true;
		else if(tmp == "@" && !n) {
			i++;
			tmp = str.substr(i, 1);
			if(tmp == "i") res += to_string(index);
			else if(tmp == "n") res += "\n";
			else if(tmp == "t") res += "\t";
			else if(tmp == "k") res += gensteamkey();
			else if(tmp == "p") res += genpassword();
		} else { res += tmp; n = false; }
	} return res;
}

int main(int argc, char *argv[]) {
	string arg;
	string start, base, end;
	string output = "textgenp_output.txt";
	long count = 0;
	for(int i = 0; i < argc; i++) {
		arg = argv[i];
		if(arg == "-h" || arg == "--help") {
			cout << "textgenp " << VERSION << endl;
			cout << "Использование: textgenp [ПАРАМЕТР]...\n\n"
				 << "\t-h, --help                 Выводит эту справку\n\n"
				 << "\t-b, --base <текст>         Основной текст\n"
				 << "\t-s, --start <текст>        Начальный текст\n"
				 << "\t-e, --end <текст>          Конечный текст\n"
				 << "\t-c, --count <число>        Число итераций\n\n"
				 << "\t-o, --output-file <файл>   Выходной файл\n"
				 << "\t                           (По умолчанию \"textgenp_output.txt\")\n\n"
				 << "В тексте вы можете использовать переменные.\n"
				 << "@i - индекс\n@n - новая строка\n@t - таб\n@k - ключ steam\n@p - пароль\n"
				 << "Чтобы вывести символ @ или /, поставьте перед ним /\n\n"
				 << "Пример: ./textgenp -s \"[@i]@t///@n@n\" -e \"[@i]@tpassword: @p@n\" -b \"[@i]@t@k@n\" -c 15 -o test.txt\n"
				 << endl;
			return 0;
		} else if(arg == "-b" || arg == "--base") {
			i++; if(i < argc) {
				base = argv[i];
			}
		} else if(arg == "-s" || arg == "--start") {
			i++; if(i < argc) {
				start = argv[i];
			}
		} else if(arg == "-e" || arg == "--end") {
			i++; if(i < argc) {
				end = argv[i];
			}
		} else if(arg == "-o" || arg == "--output-file") {
			i++; if(i < argc) {
				output = argv[i];
			}
		} else if(arg == "-c" || arg == "--count") {
			i++; if(i < argc) {
				arg = argv[i];
				count = stol(arg);
			}
		} 
	}
	ofstream file(output);
	file << format(start);
	while(count > 0) {
		file << format(base);
		count--; index++;
	}
	file << format(end);
	return 0;
}
