350_proj_c

Questions:

Do we need to build any of our own functions outside of Main?  Anything that I can do to make that work?
  
fseek(floppy,512*2,SEEK_SET);

If the second argument is always going to be 512x2; wouldn't we just set it to 1024 instead of doing the math in the argument?  Just preference?



int dirindex=i;

	//fill the name field with 00s first
  
	for (i=0; i<6; i++)
	
    dir[dirindex+i]=0x00;
	
  //copy the name over
	
  for (i=0; i<6; i++)
	
  {
	
  if(argv[1][i]==0)
	
  break;
	
  dir[dirindex+i]=argv[1][i];
	
  }

If dirindex = i; and you're adding dirindex with i; couldn't you just multiply i and save the use of a variable or am I missing the reuse of this variable somewhere else?
