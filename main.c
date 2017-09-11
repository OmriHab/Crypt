#include "crypt.h"
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

int main(int argc, char* argv[]){

	int	encrypt_to_self	=	is_in_args(argc, argv, "-s", "--self"),
		use_stdin		=	is_in_args(argc, argv, "-i", "--stdin"),
		use_stdout		=	is_in_args(argc, argv, "-o", "--stdout"),
		get_help		=	is_in_args(argc, argv, "-h", "--help"),
		file_index		=	index_after_switches(argc, argv);
	char* fin, *fout;
	
/*===================Argument Handling====================*/
	/*---Help---*/
	if(get_help || argc == 1){
		print_help(argv[0]);
		return 0;
	}
	
	if(encrypt_to_self && (use_stdin || use_stdout)){
		printf("Switch: '-s' (Encrypt to self) can not be used with switch '-i'(use stdin) or switch '-o'(use stdout)\n");
		printf("For help use %s, -h\n", argv[0]);
		return 1;
	}
	
	/*---Encrypt to self---*/
	if(encrypt_to_self){
		if(file_index == argc - 1){
			encryptSelf(argv[file_index], getKey());
		}
		else{
			printf("Switch: '-s' (Encrypt to self) requires excactly one file\n");
			printf("For help use %s, -h\n", argv[0]);
		}
		return 0;
	}
	
	/*---Stdin---*/
	if(use_stdin){
		fin = NULL;	//NULL symbols stdin
	}
	else{
		fin = argv[file_index++];
	}
	
	/*---Stdout---*/
	if(use_stdout){
		fout = NULL;//NULL symbols stdout
	}
	else if(file_index == argc - 1){
		fout = argv[file_index];
	}
	else{
		printf("Missing Out-File\n");
		printf("For help use %s, -h\n", argv[0]);
		return 2;
	}
	
/*=====================Normal cases======================*/
	Key k = getKey();
	encryptFile(fin, fout, k);	
	return 0;
}
