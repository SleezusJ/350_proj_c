
void type(char* filename);

int main(){
char* cmdBuffer;
char* cmdName;
int i;
	while(1){
		//print prompt:
		syscall(0,"KSH_> ");  //printString
		//read command
		syscall(1,cmdBuffer); //readString
		//------------------------------------
		cmdName[10]; //change size if necessary
		for(i=0;i<10;i++){cmdName[i] = cmdBuffer[i];}
		
		if(syscall(42,"type",cmdName,0) == 1){
			//run type func.
			//test
			syscall(0,cmdName);
		}

		//try to execute
		syscall(4,cmdBuffer);

		syscall(0,"Command not found!\n\r"); //if we get to this point, the command did not run.
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


