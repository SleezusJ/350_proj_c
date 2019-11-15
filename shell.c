
void type(char* filename);
int strCompare(char* str1, char* str2);

int main(){

char cmdBuffer[11]; //max cmd len + max fiename len + 1(space)
char cmdName[4];
char filename[6];
int i;
	while(1){

		//print prompt:
		syscall(0,"KSH_> ");  //printString
		//read command
		syscall(1,cmdBuffer); //readString


		//parse out command name
		for(i=0;i<4;i++){cmdName[i] = cmdBuffer[i];}
		
		//compare cmd
		if(strCompare(cmdName, "type") == 1){ //if command is type.
			
			//load file name
			for(i=0;i<6;i++){filename[i] = cmdBuffer[i+5];}
			 
			//print contents of file designated by 6 char long filename
			type(filename);
	
		}else if (strCompare(cmdName, "exec")==1){ //if command is exec.

			for(i=0;i<6;i++){filename[i] = cmdBuffer[i+5];}
		
			//try to execute program designated by 6 char long filename
			syscall(4, filename);

		}else{
			syscall(0, "Command not found!\n\r");
		}

	}

}


void type(char* filename){

	char buffer[13312]; //max file size
	int readSectors;
	int i;
	//int offset = 0x0;
	
	syscall(3,filename,buffer,&readSectors); //read file into buffer
	if(readSectors>0){
		syscall(0,buffer); //print buffer
		return;
	}else{syscall(0,"File not found!"); return;}


}




//compare string. takes: string1, string2; returns 0=F,1=T
int strCompare(char* str1, char* str2){  
	int i;
	for(i=0;i<6;i++){

		if(str1[i]==0x0 && str2[i]==0x0){break;}
		if(str1[i]=='\r' && str2[i]==0x0){break;}
		if(str1[i] != str2[i]){return 0;}
	}
	return 1;
}



