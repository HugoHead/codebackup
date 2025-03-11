#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>

#define DEFAULT_ROUNDS 3
#define DEFAULT_DURATION 60
#define DEFAULT_INTERVAL 30
#define DEFAULT_RECOVERY 15
#define DEFAULT_CYCLE 1.0
#define DEFAULT_BREATH_COUNT 30
#define DEFAULT_BREATHS_PER_HOLD 3
#define DEFAULT_COMMENTARY_FILE "commentary.txt"
#define DATA_DIR "./data/"

// Global variables
int rounds = DEFAULT_ROUNDS;
int duration = DEFAULT_DURATION;
int interval = DEFAULT_INTERVAL;
int recovery = DEFAULT_RECOVERY;
double cycle = DEFAULT_CYCLE;
int breathCount = DEFAULT_BREATH_COUNT;
int breathsPerHold = DEFAULT_BREATHS_PER_HOLD;
bool descriptiveMode = false;
bool commentary = true;
bool reflect = true;
bool holotropic = false;
bool sessionIncomplete = false;
char outputFile[256] = "";
char commentaryFile[256] = DEFAULT_COMMENTARY_FILE;

// Function prototypes
void handle_interrupt(int sig);
void parse_args(int argc, char *argv[]);
void start_session();
void record_data(const char *message);
void display_commentary();
void wait_time(double seconds);

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_interrupt); // Handle Ctrl+C
    parse_args(argc, argv);
    start_session();
    return 0;
}

void handle_interrupt(int sig) {
    printf("\nSession interrupted. Saving progress...\n");
    record_data("SESSION INCOMPLETE\n");
    exit(1);
}

void parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--rounds") == 0) rounds = atoi(argv[++i]);
        else if (strcmp(argv[i], "--duration") == 0) duration = atoi(argv[++i]);
        else if (strcmp(argv[i], "--interval") == 0) interval = atoi(argv[++i]);
        else if (strcmp(argv[i], "--recovery") == 0) recovery = atoi(argv[++i]);
        else if (strcmp(argv[i], "--cycle") == 0) cycle = atof(argv[++i]);
        else if (strcmp(argv[i], "--breathCount") == 0) breathCount = atoi(argv[++i]);
        else if (strcmp(argv[i], "--commentaryFile") == 0) strcpy(commentaryFile, argv[++i]);
        else if (strcmp(argv[i], "--outputFile") == 0) strcpy(outputFile, argv[++i]);
        else if (strcmp(argv[i], "--holotropic") == 0) holotropic = true;
        else if (strcmp(argv[i], "--reflect") == 0) reflect = true;
    }
}

void start_session() {
    if (strlen(outputFile) == 0) {
        snprintf(outputFile, sizeof(outputFile), "%sbreath_session_%ld.txt", DATA_DIR, time(NULL));
    }
    
    FILE *file = fopen(outputFile, "w");
    if (!file) {
        perror("Error opening output file");
        exit(1);
    }
    fclose(file);
    
    if (reflect) {
        int mood;
        printf("Rate your mood 1-10: ");
        scanf("%d", &mood);
        char moodEntry[50];
        snprintf(moodEntry, sizeof(moodEntry), "Mood Before: %d\n", mood);
        record_data(moodEntry);
    }
    
    for (int r = 0; r < rounds; r++) {
        printf("\nRound %d\n", r + 1);
        for (int b = 0; b < breathCount; b++) {
            printf("IN\n");
            wait_time(cycle);
            printf("OUT\n");
            wait_time(cycle);
            if (rand() % 5 == 0) display_commentary();
        }
        
        printf("Hold your breath\n");
        wait_time(duration + (r * interval));
        
        printf("Recovery breath\n");
        wait_time(recovery);
    }
    
    if (reflect) {
        int mood;
        printf("Rate your mood after session 1-10: ");
        scanf("%d", &mood);
        char moodEntry[50];
        snprintf(moodEntry, sizeof(moodEntry), "Mood After: %d\n", mood);
        record_data(moodEntry);
    }
    
    printf("Session complete!\n");
}

void record_data(const char *message) {
    FILE *file = fopen(outputFile, "a");
    if (file) {
        fprintf(file, "%s", message);
        fclose(file);
    }
}

void display_commentary() {
    FILE *file = fopen(commentaryFile, "r");
    if (!file) return;
    char line[256];
    int lines = 0;
    while (fgets(line, sizeof(line), file)) lines++;
    rewind(file);
    int randomLine = rand() % lines;
    for (int i = 0; i <= randomLine; i++) fgets(line, sizeof(line), file);
    fclose(file);
    printf("%s\n", line);
}

void wait_time(double seconds) {
    usleep((int)(seconds * 1000000));
}
