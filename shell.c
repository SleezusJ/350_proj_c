
void type(char* filename);
int strCompare(char* str1, char* str2);
void getcmdName(char* cmdbuffer, char* cmdName, int* spaceIndex);
void getfileName(char* cmdbuffer, char* filename, int spaceIndex);

int main(){

char cmdBuffer[20]; 
char* cmdName;  //[4]
char filename[6];  //[6]
int spi; //index of SPACE in command buffer(used to differentiate between cmd & filename)
int i;


	while(1){

		//print prompt:
		syscall(0,"KSH_> ");  //printString
		//read command
		syscall(1,cmdBuffer); //readString


		//parse out command name
		//for(i=0;i<4;i++){cmdName[i] = cmdBuffer[i];}
		//cmdName[4]=0x0;  //add NULL terminator
		getcmdName(cmdBuffer, cmdName, &spi);

		//syscall(0,"command buffer: \r\n");
		//syscall(0,cmdBuffer); 

		syscall(0,"cmdName: \r\n");
		syscall(0,cmdName); syscall(0,"\r\n");

		//parse out filename
		for(i=0;i<6;i++){filename[i] = cmdBuffer[i+5];}	
		filename[6]=0x0;
		//getfileName(cmdBuffer, filename, &spi);		
		
		syscall(0,"file name: \r\n");
		syscall(0,filename); syscall(0,"\r\n");
		


		//compare cmd
		if(strCompare(cmdName, "type") == 1){ //if command is type.
			
			//load file name
			//for(i=0;i<6;i++){filename[i] = cmdBuffer[i+5];}
			 
			//print contents of file designated by 6 char long filename
			type(filename);
	
		}else if (strCompare("exec", cmdName)==1){ //if command is exec.

			//for(i=0;i<6;i++){filename[i] = cmdBuffer[i+5];}
		
			//try to execute program designated by 6 char long filename
			syscall(4, filename);

		}else{
			syscall(0, "Command not found!\r\n");
			
		}


	}

}


void type(char* filename){

	char buffer[13312]; //max file size
	int readSectors;
	int i;
	
	syscall(3,filename,buffer,&readSectors); //read file into buffer
	if(readSectors>0){
		syscall(0,buffer); //print buffer
		syscall(0,"\r\n");//-----------
		return;
	}else{syscall(0,"File not found!\r\n"); return;}


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

//takes incoming command buffer, empty buffer to write command to, and int address to write index of SPACE to.
//
void getcmdName(char* cmdbuffer, char* cmdName, int* spaceIndex){

	int i = 0;
	while(cmdbuffer[i]!=0x20){
		*cmdName = cmdbuffer[i];
		i++;
		cmdName++;
	}
	*cmdName = 0x0; //NULL terminate string
	*spaceIndex = *spaceIndex+i; //reference to location of SPACE in cmdbuffer
	return;
}

void getfileName(char* cmdbuffer, char* filename, int* spaceIndex){
	
	int i = *spaceIndex + 1; //location of first element after space
	while(cmdbuffer[i] != 0xa){ //
		*filename = cmdbuffer[i];
		i++;			
		filename++;	
	}
	*filename = 0x0; //null terminate string
	return;
}







