


int main(){
char* cmdBuffer;
	while(1){
		//print prompt:
		syscall(0,"KSH_> ");  //printString
		//read command
		syscall(1,cmdBuffer); //readString
		//try to execute
		syscall(4,cmdBuffer);

		syscall(0,"Command not found!\r\n"); //if we get to this point, the command did not run.
	}

	return 0;
}
