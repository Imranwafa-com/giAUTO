/* still in progress */
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <errno.h> 
#include <limits.h>
#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __cplusplus >= 201703L && __has_include(<filesystem>)
#    include <filesystem>
     namespace fs = std::filesystem;
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
     namespace fs = std::experimental::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
     namespace fs = boost::filesystem;
#  endif
#endif
int time_mult;
bool isNumber(char number[]){
    int i = 0;
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++){
        if (!isdigit(number[i]))
            return false;}
    return true;}
bool isempty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();}
int callfailed(){
  std::cout << "[ \x1B[91mFAILED\033[0m ] ";
  return 0;}
int callok(){
  std::cout << "[ \x1B[92mOK\033[0m ] ";
  return 0;}
int callend(int arg){
  std::cout << "\n\n\x1B[31mError:\033[0m " <<arg << " has crashed this program\nfix it and try again "<< std::endl;
  exit(arg);
  return arg;}
void cheGIT(){
struct stat info;
	const char* pathname = "./.git";
if( stat( pathname, &info ) != 0 ){
    callfailed();printf( "%s is not a directory please make sure this is a git repo", pathname );callend(1);}
else if( info.st_mode & S_IFDIR ){
    callok();printf( "%s exists this is a git repo\n\n", pathname );}
else{
    callfailed();printf( "%s is not a directory please make sure this is a git repo\n", pathname );
    callend(1);}}
int main(int argc, char** argv){
	std::string senARGS;
	for(int i = 1; i<argc;i++){
		senARGS = senARGS + " " + argv[i];}
  std::cout << "Remember the syntax for the arguments\n"<<argv[0] <<" <time> <sec/min/hour> <pull/push/both> <git args(if any)>"<< std::endl;
	std::cout << "your arguments are " << argv[0]<<senARGS<< std::endl<<std::endl;
  if(argc > 3){
    callok();std::cout << "Arguments count Met" <<std::endl<<std::endl;
    }else{callfailed();printf("You have less than 2 additional arguments");callend(1);}
  if (isNumber(argv[1])){
    callok();std::cout << "<time> is number " <<std::endl<<std::endl;}else{
      callfailed();printf("<time> is not a number");
    callend(1);}
    if(std::string(argv[3]) == "both"){
    callok();std::cout << "<pull/push/both> is defined" <<std::endl<<std::endl;}else if(std::string(argv[3]) == "pull"){
    callok();std::cout << "<pull/push/both> is defined" <<std::endl<<std::endl;}else if(std::string(argv[3]) == "push"){
    callok();std::cout << "<pull/push/both> is defined" <<std::endl<<std::endl;}else{
      callfailed();printf("<pull/push/both> is not defined");
    callend(1);
    }
    if(argc > 4){
      std::string senARG2;
	for(int i = 3; i<argc;i++){
		senARG2 = senARG2 + " " + argv[i];}
    callok();std::cout << "Additional Arguments:" <<senARG2 <<std::endl <<std::endl;
    }
	callok();std::cout << fs::current_path() << " is the path" <<std::endl<<std::endl; 
	cheGIT();
  callok();std::cout << "Terminal Instance Accessible" <<std::endl<<std::endl;
  std::system("git --version > tmp"); 
  std::ifstream file("tmp");
  if(isempty(file)){
    callfailed();printf( "git is not installed please install it first\n" );
    callend(1);}
  else{
     callok();std::cout << "Git Installed" <<std::endl<<std::endl;}
  file.close();
#ifdef _WIN32
    std::system("del tmp");
#else
    std::system("rm tmp");
#endif
  // const char* _UNIXcommand;
  // strcpy(_UNIXcommand,"sleep ");
  // strcat(_UNIXcommand,std::string(argv[1]));
  // std::cout << "Next in " << argv[1] << " sec"<<std::endl;
char *p;
    int num;
    errno = 0;
    long conv = strtol(argv[1], &p, 10);
    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        callfailed();printf("<time> is not a number");
    callend(1);
    } else {
        num = conv;
        printf("%d\n", num);}
  std::cout << "Next in " << num << " sec"<<std::endl;
  bool start = true;
  while(start){
  time_t t;
  struct tm * tt;
  time (&t);
  tt = localtime(&t);
  std::cout << "Done at " << asctime(tt) << std::endl;
  std::cout << "Next in " << argv[1] << "sec"<<std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(num));
  std::cout << " \x1B[31mError:\033[0m command in process not finished"<<std::endl;
  }
	return 0;
}
