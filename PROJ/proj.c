#include <stdio.h>
#include <string.h>
#include "ed2/ed2.c"
#include "hashvalue.c"
//#include "write_repository.c"
//#include "checksum.c"
#include <stdlib.h>

void load_file(char *new_filename, char *full_command);
char* call_checksum(char *file);
void create_repository(char *filename,char* vchksum);
char* read_repository(char *vfilename);
char* read_repository_filename();
int save_file(char *new_filename) ;
//char* save_file(char *new_filename) ;

int key=0;
//char *name,*chksum,*dt,*tm;
char *name,*dt,*tm;
//char *name="News-File.txt";
unsigned chksum;


int main()
{

 char ch[2];
 char *UNAME=getenv("USER");
 printf("Project SYSTEM SECURITY: Group members jp1476, acp163, asp209, cyk17, ttm30, sss309\n");
	do {
		printf("Username: %s \n", UNAME);
		printf("Change User (Y/N):");
		scanf("%s",&ch);
		if(ch[0]=='Y' || ch[0]=='y') {
			printf("Provide Username:");
			scanf("%s",UNAME);
			printf("Changed Username: %s \n", UNAME);
		}
		if (strcmp(UNAME,"Alice")!=0 && strcmp(UNAME, "Bob")!=0) {
			printf("%s cannot read the file system content \n", UNAME);
		}
	} while (strcmp(UNAME,"Alice")!=0 && strcmp(UNAME, "Bob")!=0);
 key=3;
 printf("Key Value: %d \n", key);
 ch[0]='c';
 while(ch[0]!='x')
	{
	//printf("\n\n\nSecure File system for user Alice\n\n");
	printf("Username: %s\n", UNAME);
	printf("Create New File:(c)\n");
	printf("Edit Exiting FIle:(e)\n");
	printf("List all files from secure system(l)--To be implemented\n");
	printf("Delete File(d)\n");
	printf("Rename File(r)--To be implemented\n");
	printf("Exit system(x)--To be implemented\n");
	printf("Select Option:");
	scanf("%s",&ch);
	//char* name="News-File.txt";
	//char* name;
	char* repository_name=".//.SYSSEC//.security_metadata.dat";
	
	switch (ch[0])
	{
		case 'c':
			printf("Selected Option:%c",ch[0]);
			printf("\n\nBasic ed editor commands:\na: to append text to file.\n.<ret>w filename: To save.\nq: to quit\n");
			char vname[]="";
			name=vname;
			ed2(vname);
		if(strlen(name)>0)
		{
			//char fullpath[1024];
				//strcat(fullpath,".//.SYSSEC//");
				//strcat(fullpath,name);
			//name=fullpath;
			char* chksum = call_checksum(name);
			printf("\n\nThe checksum is %#x\n",  chksum);
			create_repository(repository_name, chksum);
		}
			break;
		case 'l':
			printf("Selected Option:%c\n",ch[0]);
			char *vfilelist=  read_repository_filename();
			printf("\n\nFile list:  %s\n",  vfilelist);
			break;

	case 'd':
	  printf("Selected Option:%c\n",ch[0]);
	  printf("Enter filename to delete:");
	  char file2remove[256];
	  char file2removepath[512] = "./.SYSSEC/";
	  scanf("%s",file2remove);
	  strcat(file2removepath, file2remove);
	  if (remove(file2removepath) == 0) {
	    printf("Deleted [%s] successfully.\n\n", file2remove);
	  } else {
	    printf("ERROR: unable to delete [%s].\n\n");
	  }

	  
	  break;
	
		case 'e':
			printf("Selected Option:%c",ch[0]);
												printf("\n\nBasic ed editor commands:\na: to append text to file.\n.<ret>w filename: To save.\nq: to quit\n");
			printf("Enter File Name to edit:");
		

		char v2name[100];
		 scanf("%s",v2name);
		name=(char *) malloc(strlen(v2name));
		strcpy(name,v2name);
	
		char *v21chksum =read_repository( name);
		if(strcmp(v21chksum,"NOTFOUND")==0)
		printf("File not exits in system.\n");
		else
		{char* v3chksum = call_checksum(name);
		char c2[100];
		sprintf (c2, "%s", v3chksum);
		//size_t num=strlen(v2chksum);
		//printf("\n\nGot v2chksum= %s size %d, c2=%s size %d...compare%d\n",v2chksum,strlen(v2chksum),c2,strlen(c2),strncmp(v2chksum,c2,num));
		//if(strncmp(v2chksum,c2,num)==0){
		//if(strcmp(v2chksum,c2)==0){
		if(strcmp(v21chksum,v3chksum)==0){
			printf("File %s not tampered",name);
			char path[1024]="";
			strcat(path,".//.SYSSEC//");
			char *vname=strcat(path,name);
			ed2(vname);
		}
		else
			printf("File %s tampered. Not secure system file",name);
		}
		break;
		case 'x':
		//printf("Exiting....:%c",ch);
		break;
		default:
		printf("Selected  Invalid Option:%c",ch[0]);
	}
	}
}




char* read_repository(char *vfilename){
	FILE *file;
	char* filename=".//.SYSSEC//.security_metadata.dat";
	file = fopen(filename, "r");
	size_t num=strlen(vfilename);
	//printf("Finding %s length %d\n",vfilename,num);
	char lfilename[100];
	char lchkpt[100];
	char line[256];
	char *delimiter = ":";
	char *token;

	while(fgets(line, 256, file) != NULL) {
		token = strtok(line, delimiter);
		//printf("%s\n", token);
		strcpy(lfilename,token);
		token = strtok(NULL, delimiter);
		//printf("%s\n", token);
		strcpy(lchkpt,token);
	//printf("Got %s size %d, %s size %d...compare%d\n",lfilename,strlen(lfilename),lchkpt,strlen(lchkpt),strncmp(vfilename,lfilename,num));
				if(strncmp(vfilename,lfilename,num)==0)
			{
			//printf("match found %s",lfilename);
			char *ptr=lchkpt;
			return ptr;
			}
	}

 fclose(file);
 char* ptr="NOTFOUND";
 return(ptr);

}

char* read_repository_filename(){
	FILE *file;
	char* filename=".//.SYSSEC//.security_metadata.dat";
	file = fopen(filename, "r");
	char lfilename[4096]="";
	char line[256]="";
	char *delimiter = ":";
	char *token;

	while(fgets(line, 256, file) != NULL) {
		token = strtok(line, delimiter);
		//printf("%s\n", token);
		strcat(lfilename,token);
		strcat(lfilename,":");
		token = strtok(NULL, delimiter);
	}
	char *ptr2=lfilename;
	printf("File list %s",lfilename);
	fclose(file);
return(ptr2);


}
//=============================================

void create_repository(char *filename,char* vchksum){
	FILE *fp;
fp = fopen(filename, "a");
if(fp==NULL)
{
//fclose(fp);
	fp=fopen(filename,"w+");
	fprintf(fp,"Filename:Checksum:\n");
	fprintf(fp,"%s:%s:\n",name,vchksum);
	fclose(fp);
	printf("\n %sfile created",filename);
}
else
{
	fprintf(fp,"%s:%s:\n",name,vchksum);
	fclose(fp);
	printf("\n %sfile appened",filename);

}

}




//char* save_file(char *new_filename) {
int  save_file(char *new_filename) {
	if (new_filename) strlcpy(filename, new_filename, string_capacity);
	if (strlen(filename) == 0) {
		ed2__error(error__no_current_filename);
		return -1;
	}
	char path[1024];
	 strcat(path,".//.SYSSEC//");

	FILE *f = fopen(strcat(path,filename), "wb");
	if (f == NULL) {
		if (errno == EACCES) {  // A permission error has its own error string.
			char err_str[string_capacity];
			snprintf(err_str, string_capacity, "%s: permission denied", filename);
			ed2__error(err_str);
		} else {
			ed2__error(error__bad_write);  // Other write errors get a generic string.
		}
		return -1;  // -1 --> indicate error
	}

	int nbytes_written = 0;
	int was_error = 0;
	array__for(char **, line, lines, i) {
//--------------------------------------------------
char * newline = *line;
//char *buf;
char *buf=(char *) malloc(strlen(*line)+1);
strcpy(buf,newline);
char *buf2=(char *) malloc(strlen(*line)+1);
int i=0;
//int key=3;
char ch=buf[i];
while(ch!='\0')
 {
								if(ch >= 'a' && ch <= 'z'){
												ch = ch + key;
												if(ch > 'z'){
																ch = ch - 'z' + 'a' - 1;
												}
												buf2[i] = ch;
								}
								else if(ch >= 'A' && ch <= 'Z'){
												ch = ch + key;
												if(ch > 'Z'){
																ch = ch - 'Z' + 'A' - 1;
												}
												buf2[i] = ch;
								}
								else
												buf2[i] = ch;
//printf("changed:%c ",ch);
i++;
	ch=buf[i];
				 }
									buf2[i]='\0';
//--------------------------------------------------
		int nbytes_this_line = 0;
		if (i) nbytes_this_line += fwrite("\n", 1, 1, f);  // 1, 1 = size, nitems
		size_t len = strlen(*line);
		//nbytes_this_line += fwrite(*line,  // buffer
		// nbytes_this_line += fwrite(newline,  // buffer
		nbytes_this_line += fwrite(buf2,  // buffer
															 1,      // size
															 len,    // nitems
															 f);     // stream
		if (nbytes_this_line < len + (i ? 1 : 0)) was_error = 1;
		nbytes_written += nbytes_this_line;
	}

	if (was_error) {
		ed2__error(error__bad_write);
		return -1;  // -1 --> indicate error
	}

	is_modified = 0;
	fclose(f);
	printf("%d\n", nbytes_written);  // Report how many bytes we wrote.
//  return nbytes_written;
		 //   char *ptr=filename;
				printf("File name: .//.SYSSEC//.%s",filename);
//name=(char *) malloc(strlen(filename)+1);
//strcpy(filename,name);
name=filename;
	printf("  Bytes Written %d\n", nbytes_written);  // Report how many bytes we wrote.
	return nbytes_written;

}



 void load_file(char *new_filename, char *full_command) {
	if (is_modified && strcmp(last_command, full_command) != 0) {
		ed2__error(error__file_modified);
		return;
	}

	if (new_filename) strlcpy(filename, new_filename, string_capacity);
	if (strlen(filename) == 0) {
		ed2__error(error__no_current_filename);
		return;
	}

	FILE *f = fopen(filename, "rb");

	if (f == NULL) {
		if (errno == ENOENT) {
			printf("%s: No such file or directory\n", filename);
			setup_for_new_file();
			return;
		}
		// Otherwise, the file exists but we couldn't open it.
		goto bad_read;
	}

	struct stat file_stats;
	int is_err = fstat(fileno(f), &file_stats);
	if (is_err) goto bad_read;

	size_t buffer_size = file_stats.st_size;
	char * buf2 = malloc(buffer_size + 1);  // + 1 for the final null character.
	char * buffer = malloc(buffer_size + 1);  // + 1 for the final null character.

	//int num_read = fread(buffer,       // buffer ptr
	int num_read = fread(buf2,       // buffer ptr
											 1,            // item size
											 buffer_size,  // num items
											 f);           // stream
	//buffer[buffer_size] = '\0';        // Manually add a final null character.
	buf2[buffer_size] = '\0';        // Manually add a final null character.
//-------------------------------------------------------------------------
int i=0;
//int key=3;
char ch=buf2[i];
while(ch!='\0')
 {
								if(ch >= 'a' && ch <= 'z'){
												ch = ch - key;
												 if(ch < 'a'){
												 ch = ch + 'z' - 'a' + 1;

											}
												buffer[i] = ch;
								}
								else if(ch >= 'A' && ch <= 'Z'){
												ch = ch - key;
								 if(ch < 'A'){
									 ch = ch + 'Z' - 'A' + 1;

									}
												buffer[i] = ch;
								}
								else
												buffer[i] = ch;
//printf("changed:%c ",ch);
i++;
 ch=buf2[i];
			}
														buffer[i]='\0';
//----------------------------------------
	if (num_read < buffer_size) goto bad_read;

	fclose(f);
	break_into_lines(buffer);
	free(buffer);
	printf("%zd\n", buffer_size);  // Report how many bytes we read.
	return;

bad_read:
	// It feels disingenuous to me to let the user edit anything when the file may
	// exist but we can't read it. So we report an error and flat-out exit.
	printf("%s\n", error__bad_read);
	exit(1);
}

