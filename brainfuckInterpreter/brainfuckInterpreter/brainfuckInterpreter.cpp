#include <iostream>
#include <fstream>
#include <vector>

static std::string fileName = "morzeConverter.bf";
static char cpu[30000];

int fileOpen(std::vector<char>& acc) {
	std::ifstream bff(fileName);
	if (!bff.good()) {
		return -1;
	}
	char ch;
	while (bff) {
		bff.get(ch);
		acc.push_back(ch);
	}
	bff.close();
	return 0;
}
void intprt(std::vector<char>& acc) {
	unsigned int j = 0;
	int brc = 0;
	for (int i = 0; i < acc.size(); ++i) {
		if (acc[i] == '>')
			j++;
		if (acc[i] == '<')
			j--;
		if (acc[i] == '+')
			cpu[j]++;
		if (acc[i] == '-')
			cpu[j]--;
		if (acc[i] == '.')
			std::cout << cpu[j];
		if (acc[i] == ',')
			std::cin >> cpu[j];
		if (acc[i] == '[') {
			if (!cpu[j]) {
				++brc;
				while (brc) {
					++i;
					if (acc[i] == '[')
						++brc;
					if (acc[i] == ']')
						--brc;
				}
			}
			else
				continue;
		}
		else if (acc[i] == ']') {
			if (!cpu[j])
				continue;
			else {
				if (acc[i] == ']')
					brc++;
				while (brc) {
					--i;
					if (acc[i] == '[')
						brc--;
					if (acc[i] == ']')
						brc++;
				}
				--i;
			}
		}
	}
}
int main() {
	std::vector<char> acc;
	if (fileOpen(acc) == -1) {
		std::cout << "File problems!";
		return -1;
	}
	intprt(acc);
	return 0;
}