/**************
 * Shira Fisher
 * Computer Science Student
 **************/

#define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define MAX_WORKERS_PER_PROJECT 4
#define JOIN_COMPANY_OPTION 1
#define OPEN_PROJECT_OPTION 2
#define JOIN_PROJECT_OPTION 3
#define PROJECTS_IN_WORK_OPTION 4
#define PEOPLE_IN_PROJECT_OPTION 5
#define WORK_ON_PROJECT_OPTION 6
#define LEAVE_COMPANY_OPTION 7
#define EXIT_OPTION 8
#define INITIAL_PROJECT_COUNT 0
#define INITIAL_WORKERS_COUNT 0
#define WORKERS_OBJECT 1
#define PROJECTS_OBJECT 2
#define PROJECTS_PER_WORKER_OBJECT 3
#define EXIT_CODE 1

// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

typedef enum
{
    False,
    True
} Bool;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

void clearInputBuffer(void);
char *getChars(Bool indClear);
Bool isStringEmpty(const char *name);
Bool isObjectEmpty(int objectCount, int objectNumber);
Bool isWorkerNameExists(Worker *workers[], int workerCount, char *name);
Bool isProjectNameExists(Project *projects[], int projectCount, char *name);
Bool isFeatureExists(FeatureNode *head, const char *featureName);
Bool isWorkerPartOfProject(Worker currentWorker, const char *projectName);
Bool displayAndSelectWorker(Worker *workers[], int workerCount, int *workerNumber, int optionNumber);
Bool displayAndSelectProject(Project *projects[], int projectCount, int *projectNumber, int optionNumber);
Bool displayAndSelectFeatures(Project currentProject, FeatureNode **beforeFeature,FeatureNode **currentFeature);
void joinCompany(Worker *workers[], int *workerCount);
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount);
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void addWorkerToProject(Worker *worker, Project *project);
void displayAllProjects(Project *projects[], int projectCount);
void displayAllWorkers(Worker *workers[], int workerCount);
void workOnProject(Worker *workers[], int workerCount, int projectCount);
void addFeatureToProject(Project *project);
void removeFeatureFromProject(Project *project);
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount);
void freeProject(Project *projects[], Project *currentProject, int *projectCount);
void freeFeatures(FeatureNode *currentFeature);
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void exitProgram(void);