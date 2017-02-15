//**DO NOT** CHANGE THE PROTOTYPES FOR THE FUNCTIONS GIVEN TO YOU. WE TEST EACH
//FUNCTION INDEPENDENTLY WITH OUR OWN MAIN PROGRAM.
#include "../include/map_reduce.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


//TODO need to fix this, 
//Implement map_reduce.h functions here
// Needs to check for invalid dir names
int validateargs(int argc, char** argv){

	if(argv[1]!=NULL){
	if((strcmp("-h", argv[1])==0)) {
		//printHelp();
		return 0;
	}
	if((strcmp("ana", argv[1])==0)) {
		
		if(argv[2]!=NULL){
			if(argv[2]!=NULL){
				DIR *dirN;
				if ((dirN = opendir(argv[2])) == NULL) {
    				printf("%s/n","Directory is not valid");
   				return -1;
  				}
  					if(argv[3]!=NULL){
  					return -1;
  				}
  				
  				return 1;

			}		
		}
	
	else{
			return -1;
		}	
	}
	if((strcmp("stats", argv[1])==0)) {
		if(argv[2]!=NULL){
			if(argv[2]!=NULL){
				DIR *dirN;
				if ((dirN = opendir(argv[2])) == NULL) {
    				printf("%s/n","Directory does not valid");
   				return -1;
  				}
  				if(argv[3]!=NULL){
  					return -1;
  				}
  				return 2;

			}		
		}
	else{
			return -1;
		}	
		
	}

	
	
	if((strcmp("-v",argv[1])==0)){
		if(argv[2]!=NULL){
			if(strcmp("ana",argv[2])==0){
				
				DIR *dirN;
				if ((dirN = opendir(argv[3])) == NULL) {
    				printf("%s/n","Directory does not valid");
   				return -1;
  				}
  				if(argv[4]!=NULL){
  					return -1;
  				}
				//printHelp();
				return 3;
			}
			if(strcmp("stats",argv[2])==0){
				//printf("%s\n","we here1" );
				DIR *dirN;
				if ((dirN = opendir(argv[3])) == NULL) {
    				printf("%s/n","Directory does not valid");
   				return -1;
  				}
  				if(argv[4]!=NULL){
  					return -1;
  				}
  				//printf("%s\n","we here21" );
				//printHelp();
				return 4;
			}
		}
		else{
			//printHelp();
			return -1;
		}

	}
}
	//printHelp();
	return -1;
}

int nfiles(char* dir){
	int totalFiles = 0;
	DIR *directory;

	// CHECK IF DIRECTORY IS LEGITIMATE
	if((directory = opendir(dir))==NULL){
		//printf("Could not open : %s\n",dir );
		return -1;
	}

	// CREATE DIRECT STRUCT
	struct dirent *file1;

	//LOOP THROUGH DIRECTORY INCREMENTING COUNTER EACH TIME UNTIL THE END
	while((file1 = readdir(directory))!=NULL){
		if((strcmp(file1->d_name,".")==0) || (strcmp(file1->d_name,"..")==0)){
			totalFiles = totalFiles;
		}
		else{
			totalFiles++;
		}
	}

	// CLOSE DIRECTORY
	closedir(directory);
	// RETURN TOTAL NUMBER OF FILES
	return totalFiles;

}


int map(char* dir, void* results, size_t size, int(*act)(FILE* f, void* res,char* fn)){
         //(don't print for final result)
	///printf("Here2%s\n", "test");
	int sumOfAct = 0;
	DIR *directory;

	// CHECK IF DIRECTORY IS VALID
	if((directory = opendir(dir)) == NULL){
		return -1;
	}

	// LOOP THROUGH THE DIRECTORY AND RECORD 
	struct dirent *file1;
	int counter = 0;
	//printf("Here2%s\n", "test");
	while((file1 = readdir(directory)) != NULL){
		//printf("%s\n", "Do we reach here");
		if((strcmp(file1->d_name,".")==0) || (strcmp(file1->d_name,"..")==0)) {
			//printf("Here1%s\n", "test");
		}
		else{
			//printf("%s\n", "Do we reach here1");
			FILE *fp;
			//char path[1];
			char *path1 = malloc(strlen(dir)+strlen(file1->d_name)+2);
			strcpy(path1,dir);
			strcat(path1,"/");
			strcat(path1,file1->d_name);
			//printf("we %s\n", path1);
			//printf("%s\n", "Do we reach here2");
			/*
			strcpy(path,dir);
			strcat(path,"/");
			strcat(path,file1->d_name);
			*/
			fp = fopen(path1, "r+");
			//printf("%s\n", "Do we reach here3");
			if(fp!=NULL){
				//void *incrRes = &(((int*)results)[counter * size]);
				void *incrRes = results;

				int x = counter*size;
				int n = 0;
				for(n = 0; n < x; n ++){
					incrRes++;
				}

				int *incrRes1 = (int*) incrRes;
				//int *incrRes = &(((int*)results)[counter * size]);
				//void *incrRes = &(((void*)results)[counter * size]);
				//printf("%s\n", "Do we reach here1");
				//printf("address of res: %d\n", incrRes);
				int fileBytes = (*act) (fp, incrRes1, file1->d_name);

				//Segfaults here ^^^^^
				//printf("%s\n", "Do we reach here1");
				if(fileBytes==-1){
					printf("%s\n", "File not valid");
				}
				else{


				//printf("Here%s\n", path1);
				
				
				sumOfAct += fileBytes;
				//printf("Number of bytes: %d\n", fileBytes);
				counter++;
			}
		}
		else{
			printf("Error opening file at : %s\n", path1 );
		}
		free(path1);
		fclose(fp);
		}
		//printf("%s\n", "bottom of while loop");
		//printf("This is the counter : %d\n", counter);
	}

	closedir(directory);
	return sumOfAct;
} 


int analysis(FILE* f, void* res, char* filename){
	char c;
    int n = 0;
    int numbersInALine= 0;
    int lineYouOn = 1;
    int numbersInALineDum = 0;
    int lineYouOnDum = 0;
    //int lineCounter = 0;
    struct Analysis *fin = res;
    //counter = 0;
   // printf("%s\n", filename);
    while((c = fgetc(f)) != EOF) {
    	
    	//int lineCounterDum = 0;
    	//printf("%c", c);
    	if(  c < 128 && c!= 10){
    		
        	numbersInALineDum++;
        	//printf("In here%d", numbersInALine);
        	//lineCounterDum ++;
        	

    	}
    	else{
    		lineYouOnDum++;

    		//printf("%d\n", numbersInALine);
    		if(numbersInALineDum>=numbersInALine){
    			numbersInALine = numbersInALineDum;
    			lineYouOn=lineYouOnDum;
    		}
    		numbersInALineDum = 0;
    	}
		fin->ascii[(int)c]++;
        n++;
    }
    fin->lnlen =numbersInALine;
    fin->lnno = lineYouOn;
    fin->filename = filename;
    //printf("Longes Line : %d\n", lineYouOn);
    //sprintf("Max Numbers : %d\n", numbersInALine);
    ///struct Analysis fin;
    //fin.filename = filename;
	return n;
}

struct Analysis analysis_reduce(int n, void* results){
	
	struct Analysis *dumPoint = (struct Analysis*) results;
	
	int lnlen1 = 0;
	int lnno1 = 0;
	int ascii1[128] = {0};
	char* filename ;
	int counter;

	for(counter = 0; counter < n ; counter++ ){
		/*if(lnlen1>dumPoint[counter].lnlen){
			lnlen1 = dumPoint[counter].lnlen;
			filename=
		}
		if(lnno1>dumPoint[counter].lnno){
			lnno1 = dumPoint[counter].lnno;
		}*/

		int lnlen1Dum = dumPoint[counter].lnlen;
		int lnno1Dum = dumPoint[counter].lnno;

		if(lnlen1Dum > lnlen1){
			lnlen1 = lnlen1Dum;
			lnno1 = lnno1Dum;
			filename = strdup(dumPoint[counter].filename);
		}
		int counter1;
		for(counter1 = 0; counter1 < 128; counter1++){
			//printf("%s\n","test" );
			ascii1[counter1] += dumPoint[counter].ascii[counter1];
		}

	}
	//printf("%s\n", "here");
	struct Analysis fin = {{0}, lnlen1, lnno1, filename };
	//printf("%s\n", "here");
	memcpy(fin.ascii,ascii1,sizeof(fin.ascii));

	return fin;

}


void analysis_print(struct Analysis res,int nbytes, int hist){
	printf("File: %s\n", res.filename);
	printf("Longest line length: %d\n", res.lnlen);
	printf("Longest line number: %d\n", res.lnno);
	//printf("%s\n","" );

	if(hist!= 0){
		printf("Total Bytes in directory: %d\n", nbytes);
		printf("Histogram:%s\n","" );	
		int x;
		for(x = 0; x < 128; x++){
			//printf("%d\n", res.ascii[x]);
			if(res.ascii[x] != 0){
				int b;
				printf(" %d:",x );
				for(b = 0; b < res.ascii[x]; b ++){
					printf("%s","-" );
				}
				printf("%s\n","" );

			}
		}
		

	}
	printf("%s\n","" );


}


int stats(FILE* f, void* res, char* filename){
	char c;
    int n = 0;
    int sum = 0;
    //counter = 0;
    Stats * fin = res;
    
    //int *trap = malloc(NVAL);
    //fin.histogram = (Stats.histogram) malloc(NVAL);
    // intialize everything to zero
   // printf("%s\n","reach" );
    for(int min = 1; min < NVAL; min++){
    	//printf("%s\n","seg?" );
    	fin->histogram[min] = 0;
    	//printf("%s\n", "Do we reach here1");
    }
    //printf("%s\n", "Do we reach here1");
    //printf("%s\n", filename);
    while((c = fgetc(f)) != EOF) {
    	char *numba = malloc(500);
    	int cunter = 0;
    	int val = 0;
    	numba[cunter] = c;
    		
    	while(c!=32 && c!=10 && c!=0 && c!= EOF){
    		//printf("%c\n",c );
    		numba[cunter] = c;
    		c= fgetc(f);
    		cunter++;
    		/*if(val = 0){
    		//printf("over here%d\n",fin->histogram[val] );
    	}*/
    	}
    	//printf("%d", cunter);
    	//printf(" ______________    %d\n", (int)c);
    	numba[cunter] = 0;
    	val = atoi(numba);
    	//printf("%s|%d ", numba, val);
    	sum += val;
    	fin->histogram[val] = fin->histogram[val]+1;
    	/*
    	if(val = 0){
    		printf("over here%d\n",fin->histogram[val] );
    		printf("      %c",c );
    	}*/
    	
    	if(cunter != 0){
    	n++;
    }
    	/*
    	if(c!=32 && c!=10 && c!=0 ){
        int val = c-'0';
        sum += val;
        fin.histogram[val]= fin.histogram[val]+1;
        n++;
        */
        free(numba);
    }
    //printf("adsfa\n");
  	
  	fin->sum=sum;
  	fin->n=n;
  	fin->filename=filename;
  	//printf("3242\n");
    
	//res = &fin;
	//memcpy(res, &fin, sizeof(Stats));
	//printf("%d\n", sum);
    return 0;
}
/*
typedef struct Stats {
  int histogram[NVAL]; //space to store the count for each number.
  int sum;             //the sum total of all the numbers in the file.
  int n;               //the total count of numbers the files.
  char* filename;      //the file corresponding to the struct.
                       //(don't print for final result)
} Stats;
*/
Stats stats_reduce(int n, void* results){
	int sum1=0;
	int counter;
	int n1 = 0;
	//char* filename1;
	int his1[NVAL] = {0};
	Stats *dumPoint = (Stats*) results;
	

	//LOOP THROUGH ALL THE DIFFERENT STATS
	for(counter= 0; counter < n; counter++ ){
		sum1 += dumPoint[counter].sum;
		n1 += dumPoint[counter].n;


			// COPY ALL THE VALUES FROM HISTOGRAM
		int counter1;
		for(counter1 = 1; counter1 < NVAL; counter1++){
			his1[counter1] += dumPoint[counter].histogram[counter1];
		}
	}
	// COPY ALL THE NEW VALUES FROM STATS
	Stats fin = {{0},sum1,n1,NULL};
	memcpy(fin.histogram,his1,sizeof(fin.histogram));
	
	//printf("%d\n", n1);
	//printf("%d\n", sum1);
	return fin;
}

//Print historgram if hist is non-zero

// int histogram[NVAL]
// int sum
// int n
// char * filename
void stats_print(Stats res, int hist){
	
    int sum = res.sum;
	int min_index = 1;
	int max_index = NVAL-1;
	//printf("Sum here: %d\n", sum);
	//printf("N here: %d\n", res.n);
	double mean = (double)sum/(double)res.n;
	int max = -1;
	int min = -1;

	//printf("%s\n", res.filename);

	//Find the MIN
	for(min_index=1; min_index<max_index; min_index++){
		if(res.histogram[min_index]!= 0){
			//printf("%d\n",res.histogram[min_index] );
			min = min_index;
			break;
		}
		
	}

	//Find the Max
	for(max_index=NVAL -1; min_index<max_index; max_index--){
		if(res.histogram[max_index]!= 0){
			max = max_index;
			break;
		}
		
	}

	//Find the mode

	//Create Sorted Array
	
	int *order = malloc(res.n*sizeof(int));
	int orderCount = 0;
	for(int x  = 0 ; x < NVAL; x ++){
		for(int n = 0; n <res.histogram[x]; n++){
			order[orderCount] = x;
			orderCount++;
			//printf("%d\n",x );
		}
	}
	
	if(hist!=0){
		printf("Histogram: %s\n", "");
		int x;
		for(x = 1; x < NVAL; x++){
			//printf("%d\n", res.ascii[x]);
			if(res.histogram[x] != 0){
				int b;
				printf("%d :",x );
				for(b = 0; b < res.histogram[x]; b ++){
					printf("%s","-" );
				}
				printf("%s\n","" );

			}
		}
		printf("%s\n","" );
	}
	//Find the Q1

	//Find the Q2

	int med = 0;
	// Find the Median
	if((res.n % 2) ==1 ){
		int up = (int) ((((double)res.n)/2) - 0.5);
		int down = (int) ((((double)res.n)/2) +0.5);
		int up1 = order[up];
		int down1 = order[down];
		med = (int)(up1+down1)/2;
	}
	if((res.n %2) ==0){
		med = order[res.n/2];
	}

	//printf("%d\n", order[res.n/2]);

	if(hist==0){
	printf("File: %s\n",res.filename );
	}
    printf("Count: %d\n", res.n);
    printf("Mean: %f\n", mean);
    printf("Mode: %s\n", "");
    printf("Median: %d\n", med);
    printf("Q1: %s\n", "");
    printf("Q3: %s\n", "");
    printf("Min: %d\n", min);
    printf("Max: %d\n\n", max);
}