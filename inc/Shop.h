#define _CRT_SECURE_NO_WARNINGS
#pragma once
//#include <json/json.h>
#include <string>
#include <iostream>
class Shop {
	double longitude, latitude;
	bool isOnline;
	std::string Country, Province, City, District, Shopname;
	enum OnlineShop {
		JingDong,
		Taobao,
		Amazon,
		eBuy,
		Other
	};
	void getPlace(std::string C,std::string P,std::string CI,std::string D) {
		system("python D:\\location.py");
		FILE *fp = fopen("locate.txt", "r");
		static char s[50];
		fscanf(fp, "%lf%lf", &latitude, &longitude);
		if (C.length()) Country = C;
		else Country = "China";
		if (P.length()) Province = P;
		else
		{
			fscanf(fp, "%s", s);
			Province = s;
		}
		if (D.length()) District = D;
		else
		{
			fscanf(fp, "%s", s);
			District = s;
		}
		//std::cout << Country << " " << Province << " " << City << " " << District ;
	}
public:
	Shop() {}
	Shop(std::string s, std::string C = std::string(),std::string P = std::string(), std::string CI =std::string(),std::string D = std::string()) {
		getPlace(C,P,CI, D);
		Shopname = s;
	}
	std::string getShopName() {
		return Shopname;
	}
};
