#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <functional>
#include <set>

int n;
char* input;
char* output;
std::map<std::string, int> urls;
std::map<std::string, int> domains;

int parseToInt(char* val) {
	std::string str(val);
	int n = str.size();
	int res = 0;
	for (int i = 0; i < n; ++i) {
		res *= 10;
		if (int(str[i]) >= int('0') && int(str[i]) <= int('9'))
			res += (int(str[i]) - int('0'));
		else
			return -1;
	}
	return res;
}

int execute(int argc, char* argv[]) {
	n = -2;
	if (!(argc == 3 || argc == 5))
		return -1;

	if (argc == 3) {
		input = argv[1];
		output = argv[2];
	}

	if (argc == 5) {
		std::string argv1(argv[1]);
		if (argv1 == "-n") {
			n = parseToInt(argv[2]);
		}
		if (n == -1)
			return -1;
		input = argv[3];
		output = argv[4];
	}

	freopen(input, "r", stdin);
	freopen(output, "w", stdout);
	return 0;
}

bool isUrl(std::string str) {
	if (str.find("http://") != std::string::npos || str.find("https://") != std::string::npos)
		return 1;
	return 0;
}

std::string cropHttp(std::string str) {
	if (str.find("http://") != std::string::npos)
		str.erase(0, 7);
	else if (str.find("https://") != std::string::npos)
		str.erase(0, 8);
	return str;
}

bool isUrlSymbol(char c) {
	if (int(c) >= int('a') && int(c) <= int('z'))
		return 1;
	else if (int(c) >= int('A') && int(c) <= int('Z'))
		return 1;
	else if (int(c) == int('.') || int(c) == int('/') || int(c) == int(',') || int(c) == int('+') || int(c) == int('_'))
		return 1;
	return 0;
}

std::string cropParameters(std::string str) {
	std::string result = "";
	int n = str.size();
	for (int i = 0; i < n; ++i) {
		if (!isUrlSymbol(str[i]))
			break;
		result += str[i];
	}
	return result;
}

std::string findDomain(std::string str) {
	std::string result = "";
	int n = str.size();
	for (int i = 0; i < n; ++i) {
		if (str[i]=='/')
			break;
		result += str[i];
	}
	return result;
}

std::string findPath(std::string str) {
	std::string domain=findDomain(str);
	str.erase(0,domain.size());
	if (str == "")
		str = '/';
	return str;
}

int findUrls() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::string buf;
		std::string dom;
		std::stringstream ss(line);		
		while (ss >> buf)
			if (isUrl(buf)) {
				buf=cropParameters(cropHttp(buf));
				dom = findDomain(buf);
				if (urls.find(buf) == urls.end())
					urls.insert(std::pair<std::string, int>(buf, 1));
				else
					urls[buf] += 1;
				if (domains.find(dom) == domains.end())
					domains.insert(std::pair<std::string, int>(dom, 1));
				else
					domains[dom] += 1;
			}
	}
	return 0;
}


typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;

Comparator cmp = [](std::pair<std::string, int> a, std::pair<std::string, int> b)
{
	return a.second != b.second ? a.second > b.second : a.first < b.first;
};

Comparator cmpPaths = [](std::pair<std::string, int> a, std::pair<std::string, int> b)
{
	return a.second != b.second ? a.second > b.second : findPath(a.first) < findPath(b.first);
};

int main(int argc, char* argv[]) {
	int start=execute(argc,argv);
	if (start == -1)
		return 0;
	
	findUrls();
	std::cout << "total urls " << urls.size() << ", domains " << domains.size() << ", paths " << urls.size() << "\n";

	std::set<std::pair<std::string, int>, Comparator> setOfDomains(
		domains.begin(), domains.end(), cmp);
	std::set<std::pair<std::string, int>, Comparator> setOfUrls(
		urls.begin(), urls.end(), cmpPaths);

	if (n == -2)
		n = std::max(setOfDomains.size(), setOfUrls.size());
	else
		if (n <= 0)
			return 0;

	int i = 0;

	std::cout << "\ntop domains\n";
	for (std::pair<std::string, int> element : setOfDomains) 
	{
		std::cout << element.second << " " << element.first << '\n';
		++i;
		if (i >= n)
			break;
	}

	std::cout << "\ntop paths\n";

	i = 0;
	for (std::pair<std::string, int> element : setOfUrls)
	{
		std::cout << element.second << " " << findPath(element.first) << '\n';
		++i;
		if (i >= n)
			break;
	}

	return 0;
}