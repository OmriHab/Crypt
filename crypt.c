#include "crypt.h"

/*-----------------Encrypt File-----------------*/
void encryptFile(const char* inPath, const char* outPath, Key k){
	if(inPath == outPath && inPath != NULL){
		encryptSelf(inPath, k);
		return;
	}
	FILE* fin = (inPath ? fopen(inPath, "r") : stdin);		//If inPath is null, use stdin
	if(!fin){fprintf(stderr,"Error opening file: %s\n", inPath);exit(1);}
	FILE* fout = (outPath ? fopen(outPath, "w") : stdout);	//If outPath is null, print to stdout
	if(!fout){fprintf(stderr,"Error opening file: %s\n", outPath);fclose(fin);exit(1);}
	int n_read = 0;
	Key to_encrypt = 0;
	int i = 0;
	
	while(!feof(fin)){
		n_read = fread(&to_encrypt, 1, sizeof(Key), fin);
		to_encrypt^=k;
		k = scrambleKey(k);	//Makes it harder to break, because every to_encrypt is encrypted with a different key
		fwrite(&to_encrypt, n_read, 1, fout);
	}
	
	if(fin != stdin)
		fclose(fin);
	if(fout != stdout)
		fclose(fout);
}
/*-----------------Encrypt Self-----------------*/
void encryptSelf(const char* inPath, Key k){
	/*Encrypt file to tmp file*/
	encryptFile(inPath, TMP_PATH, k);
	/*Copy from tmp to self and remove tmp file*/
	FILE* fout = fopen(inPath, "w");
	if(!fout){fprintf(stderr,"Error opening file: %s\n", inPath);exit(1);}
	FILE* tmp = fopen(TMP_PATH, "r");
	if(!fout){fprintf(stderr,"Error opening tmp file\n");fclose(fout);exit(1);}
	char c;
	while((c=fgetc(tmp)) != EOF){
		fputc(c, fout);
	}
	
	fclose(fout);
	if(remove(TMP_PATH) != 0){
		printf("Unable to remove tmp file, remove manually\n");
		fclose(tmp);
	}
}

/*-----------------Get Key-----------------*/
Key getKey(){
	char code[100];
	int i = 0, j;
	Key k = 0;
	printf("Enter encryption code: ");
	while(1){
		if(i == 100){
			break;
		}
		code[i] = getch();
		if(code[i] == '\b' || code[i] == 127){	//If entered backspace, erase last char
			i--;
			printf("\b \b");
			continue;
		}
		else if(code[i] == '\n'){
			code[i++] = 0;
			break;
		}
		else{
			putchar('*');
		}
		i++;
	}
	for(j = 0; j < i; j++){
		k += code[j]*25127;
		k *= 457;
		k += 99821;
	}
	putchar('\n');
	return k;
}

Key scrambleKey(Key k){
	k ^= 13378008135;
	k ^= 80081351337;
	return k;
}

/*----------------getch---------------*/
/* reads from keypress, doesn't echo */
int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


/*Returns if argument is in argv, gets long and short argument, ex.:'-h' '--help'*/
/*----For only checking for one argument enter ""(Empty string) at arg_long-----*/
int is_in_args(int argc, const char* argv[], char* arg_short, char* arg_long){
	int i;
	for(i = 0; i < argc; i++){
		if(!strcmp(argv[i], arg_short) || !strcmp(argv[i], arg_long))
			return TRUE;
	}
	return FALSE;
}

/*Returns index after switches in argv. Switch is an argument that starts with a '-'*/
int index_after_switches(int argc, const char* argv[]){
	int i;
	for(i = 1; i < argc; i++){
		if(argv[i][0] != '-')
			return i;
	}
	return -1;	//If all are switches
}

void print_help(const char* prog_name){
	printf("Usage:%s [-ios] [File To Encrypt/Decrept] [OutFile]\n\n", prog_name);
	printf("To use stdin as in-file use switch '-i' or '--stdin'.\n"
	        "To use stdout as outfile use switch '-o' or '--stdout'.\n");
	printf("To encrypt on to self use option '-s' or '--self'. File will be overwriten with the encrypted data\n");
}










