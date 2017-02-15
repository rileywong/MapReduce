#include "../include/map_reduce.h"
#include "map_reduce.c"
//Space to store the results for analysis map
struct Analysis analysis_space[NFILES];
//Space to store the results for stats map
Stats stats_space[NFILES];

//Sample Map function action: Print file contents to stdout and returns the number bytes in the file.
int cat(FILE* f, void* res, char* filename) {
    char c;
    int n = 0;
    printf("%s\n", filename);
    while((c = fgetc(f)) != EOF) {
        printf("%c", c);
        n++;
    }
    printf("\n");
    return n;
}

int sucOrFail(int x){
    if(x==0){
        printf("%s\n", "success");
        return EXIT_SUCCESS;
    }
    else{
        printf("%s\n", "fail");
        return EXIT_FAILURE;
    }
}

void printHelp(){
    printf("Usage:  ./mapreduce [h|v] FUNC DIR\n\tFUNC\tWhich operation you would like to run on the data:\n\t\tana - Analysis of various text files in a directory.\n\t\t\tstats - Calculates stats on files which contain only numbers.\n\tDIR\tThe directory in which the files are located.\n\n\n\tOptions:\n\t-h\tPrints this help munu\n\t-v\tPrints the map function's results, stating the file it's from.");
            
}
int main(int argc, char** argv) {
    //printf("Welcome to CSE 320!\n");
    //printf("%s\n","TEST NUMBER OF FILES SRC " );
    //int appd = nfiles("src");
    //printf("\nWE HERE%i\n", appd);

    int sucOrFail = 0;
    
    sucOrFail = validateargs(argc,argv);
    if(sucOrFail == -1){
        printHelp();
        //printf("%d\n", sucOrFail);
        return EXIT_FAILURE;
    }
    if(sucOrFail == 0){
        printHelp();
        //printf("%d\n", sucOrFail);
        return EXIT_FAILURE;
    }
    if(sucOrFail == 1){
         //printf("%d\n", sucOrFail);
        int v = map(argv[2], analysis_space, sizeof(struct Analysis), analysis);
        int n = nfiles(argv[2]);
       // int i = 0;
        //printf("RUNNING WHILE LOOP: ...");
        struct Analysis fin = analysis_reduce(n,analysis_space);
        analysis_print(fin,v,1);
         return EXIT_SUCCESS;
    }  
    if(sucOrFail == 2){
        
        // Running -v stats analyses
        //printf("%d\n", sucOrFail);
        map(argv[2], stats_space, sizeof(Stats), stats);
        
        //Fails here^^^ FIX THIS SHIT I SWEAR TO GOD
        
        int n = nfiles(argv[2]);
      //  int i = 0;
        //printf("RUNNING WHILE LOOP: ...");
        
        Stats fin= stats_reduce(n,stats_space);
        stats_print(fin,1);
        return EXIT_SUCCESS;
    }
    if(sucOrFail == 3){
        //printf("%d\n", sucOrFail);
        int v = map(argv[3], analysis_space, sizeof(struct Analysis), analysis);
        int n = nfiles(argv[3]);
        int i = 0;
        //printf("RUNNING WHILE LOOP: ...");
        while(i < n) {
            struct Analysis current = analysis_space[i];;
            //printf("%d\n", current.histogram[1]);
            analysis_print(current,v , 0);
            i++;
        }
        struct Analysis fin = analysis_reduce(n,analysis_space);
        analysis_print(fin,v,1);
         return EXIT_SUCCESS;
    }
    if(sucOrFail == 4){
        
        // Running -v stats analyses
        //printf("%d\n", sucOrFail);
        map(argv[3], stats_space, sizeof(Stats), stats);
        
        //Fails here^^^ FIX THIS SHIT I SWEAR TO GOD
        
        int n = nfiles(argv[3]);
        int i = 0;
        //printf("RUNNING WHILE LOOP: ...");
        while(i < n) {
            Stats current = stats_space[i];;
            //printf("%d\n", current.histogram[1]);
            stats_print(current, 0);
            i++;
        }
        Stats fin= stats_reduce(n,stats_space);
        stats_print(fin,1);
        return EXIT_SUCCESS;
    }


    //printf("%s\n", "asdfsd");
    /*
    int mapp = 0;
    mapp = map(argv[2], analysis_space, sizeof(analysis_space), cat);
    printf("mapp = %d\n", mapp);  
    mapp = map(argv[2], analysis_space, sizeof(analysis_space), stats);
    printf("mapp = %d\n", mapp);  

    
    
    if(sucOrFail==0){
        return EXIT_SUCCESS;
    }
    else{
        return EXIT_FAILURE;
    }
    */
    return EXIT_SUCCESS;
}