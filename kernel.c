/* kernel.c -program to serve as OS kernel for comp350
 *-----------------------------------------------------
 *Authors: Kyle Snow, Tom Foley, Shane Driskell
 *
 *last modified: 10/26/19 @ 11:32
 *
 */

void printChar(char c);
void printString(char* chars);
char* readString(char* line);
void readSector(char* buffer, int sector);
void handleInterrupt21(int ax, int bx, int cx, int dx);
void readFile(char* buffer, char* message, int &sectorRead);
int strCompare(char* str1, char* str2, int offset);

int main(){
/*
	char buffer[13312]; //this is the maximum size of a file
	int sectorsRead;
	makeInterrupt21();
	interrupt(0x21, 3, "messag", buffer, &sectorsRead); //read the file into buffer
	if (sectorsRead>0)
		interrupt(0x21, 0, buffer, 0, 0); //print out the file
	else
		interrupt(0x21, 0, "messag not found\r\n", 0, 0); //no sectors read? then print an error/
*/	 
	while(1);/*boucle infini*/

}

/*
void readFile(char* buffer, char* filename, int &sectorsRead){
	char dir[512];
	//read sector 2 into a buffer	
	readSector(dir,2); 
	int fileEntry;
	//iterate over every file entry in sector
	for(fileEntry=0;fileEntry<512;fileEntry+=32){ 
		// string compare using fileEntry as an offset.
		if(stringCompare(filename, dir, fileEntry) == 0){
			sectorsRead = 0;
			return;
		}

		//load the file sector by sector into buffer.


	}

	
}
	
*/

//compare string. takes: string1, string2, offset value; returns 0=F,1=T
int strCompare(char* str1, char* str2, int offset){  
	int i;
	for(i=0;i<6;i++){
		if(str1[i]==0x0 && str2[i+offset]==0x0){break;}
		if(str1[i]=='\r' && str2[i+offset]==0x0){break;}
		if(str1[i] != str2[i+offset]){return 0;}
	}
	return 1;
}





void printChar(char c){
	interrupt(0x10,0xe*256+c,0,0,0);
}

void printString(char* chars){  

	while(*chars != 0x0){ //while element is NOT NULL, iterate.
		interrupt(0x10,0xe*256+*chars,0,0,0); //interrupt to print char
		chars++;
	}
 
}

char* readString(char* line){
	char new; //define a new character container
	do{

		new = interrupt(0x16,0,0,0,0); // interrupt to get character
		
		if(new == 0x08 && *line !=  0){//---------------------
			interrupt(0x10,0xe*256+0x08,0,0,0);//print bkspc
			line--; //step back in array
			interrupt(0x10,0xe*256+' ',0,0,0);//print space over bkspc 
			interrupt(0x10,0xe*256+0x08,0,0,0);//second backspace??
				
		}
		else{
		*line = new;
		interrupt(0x10,0xe*256+*line,0,0,0);
		line++;
		}

	}while(new != 0xd);


	*line = 0xa; //line return
	line++;
	*line = 0xd;
	line++;
	*line = 0x0; //append NULL
	interrupt(0x10,0xe*256+0xa,0,0,0);
	interrupt(0x10,0xe*256+0xd,0,0,0);

	return line;
}

// takes two parameters: predefined character array of >= 512 bytes to store result, and sector number to read	
void readSector(char* buffer, int sector){
	int AH = 2; //read
	int AL = 1; //number of sectors to read
	//pass buffer to BX
	int CH = 0;//trackNum
	int CL = sector + 1; //relative Sector
	int DH = 0; //head number
	int DL = 0x80; //device number

	interrupt(0x13,AH*256+AL,buffer,CH*256+CL,DH*256+DL);

}


void handleInterrupt21(int ax, int bx, int cx, int dx){
	//printString("Hello World! I am comming at you live from the interrupt!");
	if(ax == 0){ //print string
		printString(bx);
	}else if(ax == 1){ //read string
		readString(bx);
	}else if(ax == 2){ //read sector
		readSector(bx,cx);
	}else{
		printString("ERROR");
	}
}






