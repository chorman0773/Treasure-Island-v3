#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

#include <Text.hpp>
#include <Errors.hpp>
#include <Curl.hpp>
#include <IOWrapper.hpp>

using namespace std::string_literals;


void quit() {
	throw exit_program();
}

void help(Terminal& t,char* name) {
	/*
	printf(NORMAL);
	printf("Usage:\n");
	printf("\t%s fetch <packagename>\n", name);
	printf("\t%s help\n", name);
	*/
	t.print(Color::Reset)
	.print("Usage"s,endline)
	.print(tab,name," fetch <packagename>"s,endline)
	.print(tab,name," help"s,endline);
}


void helpFetch(Terminal& t,char* name) {
	t.print(Color::Reset)
	.print("Usage (fetch)"s,endline)
	.print(tab,name,"fetch <packagename>",endline);
}
/*
size_t writeFile(void* ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}
*/

void startDownload(const char* url,const char* resultName) {
	/*CURL *curl;
	FILE *fp;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		fp = fopen(resultName, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}*/

	FileOutputStream strm(resultName);
	Curl target(strm);
	target.setURL(url);
	target.fetch();
}


int main(int argc, char** argv) {
	Terminal t;
	Version current(1,1);
	CurlGlobal instance;
	try{
		/*
		printf(GREEN);
		printf("Lightning Creations Unified Package Manager\n");
		printf(NORMAL);
		printf("by InfernoDeity and Rdrpenguin\n");
		printf("Version 1.0\n");
		*/
		t.print(foreground<Color::GREEN>,background<Color::DARK_RED>)
		.print("Lighting Creations Unified Package Manager",endline)
		.print(Color::Reset)
		.print("by InfernoDeity and Rdrpenguin",endline)
		.print("Version ",current,endline);
		
		
		if(argc == 1) {
			/*
			printf(RED);
			printf("ERROR! Not enough arguments!\n");
			*/
			t.print(foreground<Color::RED>,"ERROR! Not enough arguments!"s,endline);
			help(t,argv[0]);
			t.print("Press any key to exit>"s,endline).wait();
			return 0;
		}
		
		if(strcmp("fetch", argv[1]) == 0) {
			if(argc == 2) {
				t.print(foreground<Color::RED>,"ERROR! Not enough arguments!"s,endline);
				helpFetch(t,argv[0]);
				t.print("Press any key to exit>"s,endline).wait();
				return 0;
			}
			t.print("Fetching "s, argv[2],"...",endline);
			startDownload(argv[2], "./download");
			t.print("Download Complete"s,endline);
		} else if(strcmp("help", argv[1]) == 0) {
			help(t,argv[0]);
		}
		t.print("Press any key to exit>",endline).wait().clear();
	}catch(exit_program e){
		return e.getCode();
	}
	
	return 0;
}
