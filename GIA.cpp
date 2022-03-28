#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
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
bool IsPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
int main(int argc, char** argv){
	std::string senARGS;
	for(int i = 1; i<argc;i++){
		senARGS = senARGS + " " + argv[i];
	}
	std::cout << "arguments are" << senARGS<< std::endl;
	std::cout << fs::current_path() << " is path" <<std::endl; 
	

struct stat info;
	const char* pathname = "./.git";
if( stat( pathname, &info ) != 0 ){
    printf( "cannot access (unhide it or run as admin) %s\n", pathname );}
else if( info.st_mode & S_IFDIR ){  // S_ISDIR() doesn't exist on win
    printf( "%s is a directory\n", pathname );}
else{
    printf( "%s is not a directory please make sure this is a git repo\n", pathname );
}
	return 0;
}
