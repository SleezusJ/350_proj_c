
void type(char* filename);
int strCompare(char* str1, char* str2);

int main(){

char* cmdBuffer;
char cmdName[4];
char filename[6];
int i;
	while(1){
		//print prompt:
		syscall(0,"KSH_> ");  //printString
		//read command
		syscall(1,cmdBuffer); //readString
		//------------------------------------

		//parse out command name
		for(i=0;i<4;i++){cmdName[i] = cmdBuffer[i];}
		
		//compare cmd
		if(strCompare(cmdName, "type") == 1){
			
			//load file name
			for(i=0;i<6;i++){
				filename[i] = cmdBuffer[i+5];	
			}
			//run type func with file name as a param.
			syscall(0,"this is the filename:\r\n");
			syscall(0,filename);
	
		}else{
			syscall(0,"ERROR! This is what is registering: \r\n");
			syscall(0,cmdName); //-----------TEST
			//try to execute
			//syscall(4,cmdBuffer);

			syscall(0,"Command not found!\n\r"); //if we get to this point, the command did not run.
		}
	}

}


void type(char* filename){

	char buffer[13312];
	int readSectors;
	int i;
	int offset = 0x0;
	
	syscall(3,filename,buffer,&readSectors); //read in file
	if(readSectors>0){
		syscall(0,buffer); //print buffer
	}else{syscall(0,"File not found!");}


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



