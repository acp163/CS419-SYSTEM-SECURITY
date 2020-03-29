#include <stdio.h>
#include <string.h>
#include "ed2.c"
#include <stdlib.h>




main()
{

char ch[2];

char *UNAME=getenv("USER");
printf("Welcome %s to secure file system: Group members ?,acp163,???\n", UNAME);
printf("Change User (Y/N):");
scanf("%s",&ch);
if(ch[0]=='Y')
{
printf("Provide Username:");
scanf("%s",UNAME);
}
ch[0]='c';
while(ch[0]!='x')
{
printf("\n\n\nSecure File system for Alice\n\n");
printf("Hello %s\n", UNAME);
printf("Create New File:(c)\n");
printf("Edit Exiting FIle:(e)\n");
printf("List all files from secure system(l)--To be implemented\n");
printf("Delete File(d)--To be implemented\n");
printf("Rename File(r)--To be implemented\n");
printf("Exit system(x)--To be implemented\n");
printf("Select Option:");

//ch=getc(stdin);
scanf("%s",&ch);
switch (ch[0])
{
    case 'c':
      printf("Selected Option:%c",ch[0]);
ed2();
system ("clear");
printf("\n\n\nSecure File system for Alice\n\n");
getc(stdin);
printf("\n\n\nSecure File system for Alice\n\n");

	break;
    case 'e':
      //printf("Selected Option:%c",ch);
      break;
    case 'x':
      //printf("Exiting....:%c",ch);
      break;
    default:
      printf("Selected  Invalid Option:%c",ch[0]);
}
}
}


