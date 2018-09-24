#define CURL_STATICLIB

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <curl/curl.h>

#ifdef _DEBUG
#pragma comment(lib, "libcurld.lib")
#else
#pragma comment(lib, "libcurl.lib")
#endif

string G_O(char *url);


using namespace std;

int main()
{
	char* plain;
	char* b64dcipher;
	int b64size = 0;
	int size = 0;
	char* u = "https://abcde.com";

	b64size = strlen(u);

	plain = new char[b64size];

	string o = G_O(plain);
	return 0;
}



string G_O(char* url)
{

	int size;
	CURL *curl;
	CURLcode res;
	string o, o2;
	char* plain;
	char* cipher;
	char* b64dcipher;
	int b64size = 0;


	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &o);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			curl_easy_cleanup(curl);
		}
	}
	int len = o.find("-->") - (o.find("<!--") + 4);
	o2 = o.substr(o.find("<!--") + 4, len);

	b64size = o2.size();

	cipher = new char[b64size];
	plain = new char[b64size];

	size = (int)(b64size * 6 / 8);

	memset(cipher, '\0', b64size + 1);
	memcpy(cipher, o2.c_str(), b64size);

	memset(plain, '\0', b64size);

	return plain;
}

size_t writer(char *data, size_t size, size_t nmemb, string *writerData)
{
	if (writerData == NULL)
	{
		return 0;
	}
	writerData->append(data, size*nmemb);
	return size * nmemb;
}