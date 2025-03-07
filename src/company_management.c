/**************
 * Shira Fisher
 * Computer Science Student
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "company_management.h"

int main()
{
    Worker allWorkers[MAX_WORKERS];
    Project allProjects[MAX_PROJECTS];
    int workerSelection = 0, workerCount = 0, projectCount = 0;
    while(workerSelection != EXIT_OPTION)
    {
        printf("\nWelcome!\n"
               "Please select the desired option:\n"
               "1. Join the company\n"
               "2. Open a new project\n"
               "3. Join an existing project\n"
               "4. See what projects are in work\n"
               "5. See which people are in what projects\n"
               "6. Work on existing project (features)\n"
               "7. Leave the company\n"
               "8. Exit\n\n"
               "Enter your choice: ");
        scanf(" %d", &workerSelection);
        switch (workerSelection)
        {
            case JOIN_COMPANY_OPTION:
                joinCompany((Worker **) allWorkers, &workerCount);
                break;
            case OPEN_PROJECT_OPTION:
                openNewProject((Worker **) allWorkers, workerCount, (Project **) allProjects, &projectCount);
                break;
            case JOIN_PROJECT_OPTION:
                workerJoinsProject((Worker **) allWorkers, workerCount, (Project **) allProjects, projectCount);
                break;
            case PROJECTS_IN_WORK_OPTION:
                displayAllProjects((Project **) allProjects, projectCount);
                break;
            case PEOPLE_IN_PROJECT_OPTION:
                displayAllWorkers((Worker **) allWorkers, workerCount);
                break;
            case WORK_ON_PROJECT_OPTION:
                workOnProject((Worker **) allWorkers, workerCount, projectCount);
                break;
            case LEAVE_COMPANY_OPTION:
                leaveCompany((Worker **) allWorkers, &workerCount, (Project **) allProjects, &projectCount);
                break;
            case EXIT_OPTION:
                freeAllAllocations((Worker **) allWorkers, workerCount, (Project **) allProjects, projectCount);
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void clearInputBuffer(void)
{
    // Clear input buffer
    char ch;
    while(True)
    {
        scanf("%c", &ch);
        if (ch == '\n' || ch == EOF)
            return;
    }
}

char *getChars(Bool indClear)
{
    // Get user input char by char, returns the full string
    char ch;
    int sizeChars = 0;
    char *headNamePointer, *namePointer = (char *) malloc(sizeof(char));
    if(namePointer == NULL)
        exit(EXIT_CODE);
    headNamePointer = namePointer;
    if(indClear)
        clearInputBuffer();
    // Get char after char and add it to the full string
    scanf("%c", &ch);
    while( ch != '\n')
    {
        sizeChars += 1;
        namePointer = (char *) realloc(headNamePointer,sizeChars*sizeof(char));
        if(namePointer == NULL)
            exit(EXIT_CODE);
        headNamePointer = namePointer;
        namePointer[sizeChars - 1] = ch;
        scanf("%c", &ch);
    }
    // Add '\0' to the end of the string
    sizeChars += 1;
    namePointer = (char *) realloc(headNamePointer,sizeChars*sizeof(char));
    if(namePointer == NULL)
        exit(EXIT_CODE);
    headNamePointer = namePointer;
    namePointer[sizeChars - 1] = '\0';
    return headNamePointer;
}

Bool isStringEmpty(const char *name)
{
    return name == NULL ? True : False;
}

Bool isObjectEmpty(int objectCount, int objectNumber)
{
    // check if objectCount is 0 and present message
    if(!objectCount)
    {
        if(objectNumber == WORKERS_OBJECT)
            printf("There are no workers in the company yet, please join the company first.\n");
        else if(objectNumber == PROJECTS_OBJECT)
            printf("There are no projects in the company yet, please create a project first.\n");
        else if(objectNumber == PROJECTS_PER_WORKER_OBJECT)
            printf("This worker is not involved in any projects.\n");
        return True;
    }
    return False;
}

Bool isWorkerNameExists(Worker *workers[], int workerCount, char *name)
{
    // Check if worker name already taken
    for (int i = 0; i < workerCount; i++)
    {
        if(strcmp(name, workers[i]->name) == 0)
            return True;
    }
    return False;
}

Bool isProjectNameExists(Project *projects[], int projectCount, char *name)
{
    // Check if project name already taken
    for (int i = 0; i < projectCount; i++)
    {
        if(strcmp(name, projects[i]->name) == 0)
            return True;
    }
    return False;
}

Bool isFeatureExists(FeatureNode *head, const char *featureName)
{
    // Check if feature name already taken
    while(head)
        if(strcmp(featureName, head->feature) == 0)
            return True;
        else
            head = head->next;
    return False;
}

Bool isWorkerPartOfProject(Worker currentWorker, const char *projectName)
{
    // Check if project name in worker projects
    for(int i = 0; i < currentWorker.projectCount; i++)
        if(currentWorker.projects[i]->name == projectName)
        {
            printf("The worker is already part of the project '%s'.\n", projectName);
            return True;
        }
    return False;
}

Bool displayAndSelectWorker(Worker **workers, int workerCount, int *workerNumber, int optionNumber)
{
    // Return False selection out of range, else True
    // Put user selection into workerNumber
    int SelectedWorker;
    // Display workers list
    printf(optionNumber == JOIN_PROJECT_OPTION ? "Select a worker to join a project:\n" :
       optionNumber == WORK_ON_PROJECT_OPTION ? "Select a worker:\n" :
        optionNumber == LEAVE_COMPANY_OPTION ? "Select a worker to leave the company:\n" :
        "Who are you? Choose a number:\n");
    for (int i = 0; i < workerCount; i++)
        printf("%d. %s\n", i + 1, workers[i]->name);
    printf(optionNumber == OPEN_PROJECT_OPTION ?
        "Enter your choice: " : "Enter the worker's number: ");
    scanf("%d", &SelectedWorker);
    // Selection out of range
    if(SelectedWorker < 1 || SelectedWorker > workerCount)
    {
        printf("Invalid worker selection.\n\n");
        return False;
    }
    *workerNumber = SelectedWorker - 1;
    return True;
}

Bool displayAndSelectProject(Project *projects[], int projectCount, int *projectNumber, int optionNumber)
{
    // Return False if selection out of range, else True
    // Put user selection into projectNumber
    int SelectedProject;
    // Display projects list
    if(optionNumber == WORK_ON_PROJECT_OPTION)
    {
        printf("Select a project:\n");
        for (int i = 0; i < projectCount; i++)
            printf("%d. %s\n", i + 1, projects[i]->name);
        printf("Enter the project number: ");
    }
    else
    {
        printf("Select a project to join:\n");
        for (int i = 0; i < projectCount; i++)
            printf("%d. %s (Workers: %d)\n", i + 1, projects[i]->name, projects[i]->workerCount);
        printf("Enter the project's number: ");
    }
    scanf("%d", &SelectedProject);
    // Selection out of range
    if(SelectedProject < 1 || SelectedProject > projectCount)
    {
        printf("Invalid project selection.\n\n");
        return False;
    }
    *projectNumber = SelectedProject - 1;
    return True;
}

Bool displayAndSelectFeatures(Project currentProject, FeatureNode **beforeFeature,FeatureNode **currentFeature)
{

    // Return False if no features or if selection out of range, else True
    // Put user selection into currentFeature
    int currentFeaturesNumber = 1, selectedFeature;
    FeatureNode *feature;
    if (!currentProject.features)
    {
        printf("There are no features to remove.\n");
        return False;
    }
    else
    {
        // Display features list
        printf("Select a feature to remove:\n");
        feature = (FeatureNode *) currentProject.features;
        while(feature)
        {
            printf("%d. %s\n", currentFeaturesNumber, feature->feature);
            feature = feature->next;
            currentFeaturesNumber++;
        }
        printf("Enter your choice:\n");
        scanf("%d", &selectedFeature);
        // Selection out of range
        if (selectedFeature < 1 || selectedFeature >= currentFeaturesNumber) {
            printf("Invalid feature selection.\n\n");
            return False;
        }
        // find the selected feature
        if (selectedFeature == 1)
        {
            *beforeFeature = NULL;
            *currentFeature = currentProject.features;
        }
        else
        {
            currentFeaturesNumber = 1;
            feature = currentProject.features;
            while(currentFeaturesNumber != selectedFeature - 1)
            {
                feature = feature->next;
                currentFeaturesNumber ++;
            }
            *beforeFeature = feature;
            *currentFeature = feature->next;
        }
        return True;
    }
}

void addWorkerToProject(Worker *worker, Project *project)
{
    // Add new project to the worker
    if(worker->projectCount == 0)
    {
        Project **newProjectPointer = (Project **) malloc(sizeof(Project *));
        if(newProjectPointer == NULL)
            exit(EXIT_CODE);
        worker->projects = newProjectPointer;
    }
    else
    {
        Project **newProjectsPointer = (Project **) realloc(worker->projects,
                                                            (worker->projectCount + 1) * sizeof(Project *));
        if(newProjectsPointer == NULL)
            exit(EXIT_CODE);
        worker->projects = newProjectsPointer;
    }
    worker->projects[worker->projectCount] = project;
    worker->projectCount ++;
    //Add new worker to the project
    if(project->workerCount == 0)
    {
        Worker **newWorkerPointer = (Worker **) malloc(sizeof(Worker *));
        if(newWorkerPointer == NULL)
            exit(EXIT_CODE);
        project->workers = newWorkerPointer;
    }
    else
    {
        Worker **newWorkersPointer = (Worker **) realloc(project->workers,
                                                           (project->workerCount + 1) * sizeof(Worker *));
        if(newWorkersPointer == NULL)
            exit(EXIT_CODE);
        project->workers = newWorkersPointer;
    }
    project->workers[project->workerCount] = worker;
    project->workerCount ++;
}

void joinCompany(Worker *workers[], int *workerCount)
{
    // Get worker name, check if empty or exists
    // Add the worker to the array of all workers
    char *workerName;
    if(*workerCount == MAX_WORKERS)
        printf("You have reached to the maximum number of workers.\n");
    else
    {
        printf("Enter the name of the new worker: ");
        workerName = getChars(True);
        if(isStringEmpty(workerName))
        {
            free(workerName);
            workerName = NULL;
        }
        else if(isWorkerNameExists(workers, *workerCount, workerName))
        {
            free(workerName);
            workerName = NULL;
            printf("A worker with this name already exists.\n");
        }
        else
        {
            // Initialize and add worker
            Worker *newWorker = (Worker *) malloc(sizeof(Worker));
            newWorker->name = workerName;
            newWorker->projects = NULL;
            newWorker->projectCount = INITIAL_PROJECT_COUNT;
            workers[*workerCount] = newWorker;
            *workerCount += 1;
        }
    }
}

void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount)
{
    // Get project name and worker name, check if empty or exists
    // Add the project to the array of all project
    int workerNumber;
    char *projectName;
    Worker *currentWorker;
    if(*projectCount == MAX_PROJECTS)
        printf("You have reached to the maximum number of projects.\n");
    else
    {
        if(!isObjectEmpty(workerCount, WORKERS_OBJECT) &&
           displayAndSelectWorker(workers, workerCount, &workerNumber, OPEN_PROJECT_OPTION))
        {
            currentWorker = workers[workerNumber];
            printf("Enter the name of the new project: ");
            projectName = getChars(True);
            if(isStringEmpty(projectName))
            {
                free(projectName);
                projectName = NULL;
            }
            else if(isProjectNameExists(projects, *projectCount, projectName))
            {
                free(projectName);
                projectName = NULL;
                printf("A project with this name already exists.\n");
            }
            else
            {
                // Initialize and add project
                Project *newProject = (Project *) malloc(sizeof(Project));
                newProject->name = projectName;
                newProject->workers = NULL;
                newProject->workerCount = INITIAL_WORKERS_COUNT;
                newProject->features = NULL;
                addWorkerToProject(currentWorker, newProject);
                projects[*projectCount] = newProject;
                *projectCount += 1;
            }
        }
    }
}

void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    // joins worker to project if the option is valid
    int workerNumber, projectNumber;
    if(!isObjectEmpty(workerCount, WORKERS_OBJECT) &&
        !isObjectEmpty(projectCount, PROJECTS_OBJECT) &&
        displayAndSelectWorker(workers, workerCount, &workerNumber, JOIN_PROJECT_OPTION) &&
        displayAndSelectProject(projects, projectCount, &projectNumber, JOIN_PROJECT_OPTION) &&
        !isWorkerPartOfProject(*workers[workerNumber], projects[projectNumber]->name))
    {
        if(projects[projectNumber]->workerCount == MAX_WORKERS_PER_PROJECT)
            printf("Project is full.\n");
        else
            addWorkerToProject(workers[workerNumber], projects[projectNumber]);
    }

}

void displayAllProjects(Project *projects[], int projectCount) {
    // Display all projects information
    FeatureNode *currentFeatures;
    if (!projectCount)
        printf("There are no projects to display.\n");
    else
    {
        for (int i = 0; i < projectCount; i++)
        {
            printf("Project: %s\n", projects[i]->name);
            printf("  Workers in this project:\n");
            if (!projects[i]->workerCount)
                printf("    No workers\n");
            else
                for (int j = 0; j < projects[i]->workerCount; j++)
                    printf("    - %s\n", projects[i]->workers[j]->name);
            printf("  Features of the project:\n");
            if (!projects[i]->features)
                printf("    No features\n");
            else
            {
                currentFeatures = (FeatureNode *) projects[i]->features;
                while (currentFeatures)
                {
                    printf("    - %s\n", currentFeatures->feature);
                    currentFeatures = currentFeatures->next;
                }
            }
            printf("\n");
        }
    }
}

void displayAllWorkers(Worker *workers[], int workerCount)
{
    // Display all workers information
    if(!workerCount)
        printf("There are no workers to display.\n");
    else
    {
        for (int i = 0; i < workerCount; i++)
        {
            printf("Worker: %s\n", workers[i]->name);
            if (!workers[i]->projectCount)
                printf("  Not involved in any projects.\n");
            else
            {
                printf("  Projects this worker is involved in:\n");
                for (int j = 0; j < workers[i]->projectCount; j++)
                    printf("    - %s\n", workers[i]->projects[j]->name);
            }
            printf("\n");
        }
    }
}

void workOnProject(Worker *workers[], int workerCount, int projectCount)
{
    // Add or remove feature from selected project
    char *addOrRemove;
    int workerNumber, projectNumber;
    // call selection worker project
    if(!isObjectEmpty(workerCount, WORKERS_OBJECT) &&
        !isObjectEmpty(projectCount, PROJECTS_OBJECT) &&
        displayAndSelectWorker(workers, workerCount, &workerNumber, WORK_ON_PROJECT_OPTION) &&
        !isObjectEmpty(workers[workerNumber]->projectCount, PROJECTS_PER_WORKER_OBJECT) &&
        displayAndSelectProject(workers[workerNumber]->projects, workers[workerNumber]->projectCount,
                                &projectNumber, WORK_ON_PROJECT_OPTION))
    {
        printf("Do you want to add or remove a feature? (add/remove): ");
        addOrRemove = getChars(True);
        if(!strcmp(addOrRemove, "add"))
            addFeatureToProject(workers[workerNumber]->projects[projectNumber]);
        else if(!strcmp(addOrRemove, "remove"))
            removeFeatureFromProject(workers[workerNumber]->projects[projectNumber]);
        else
            printf("Invalid choice\n");
        free(addOrRemove);
        addOrRemove = NULL;
    }
}

void addFeatureToProject(Project *project)
{
    // Add feature to the current project
    char *featureName;
    FeatureNode *lastFeature;
    printf("Enter the new feature: ");
    featureName = getChars(False);
    lastFeature = (FeatureNode *) project->features;
    if(isStringEmpty(featureName))
    {
        free(featureName);
        featureName = NULL;
    }
    else if(isFeatureExists(lastFeature, featureName))
    {
        free(featureName);
        featureName = NULL;
        printf("This feature already exists in th project.\n");
    }
    else
    {
        while(lastFeature && lastFeature->next)
            lastFeature = lastFeature->next;
        FeatureNode *newFeature = malloc(sizeof(FeatureNode)); //VALGRIND - invalid write
        newFeature->feature = featureName;
        newFeature->next = NULL;
        if(lastFeature == NULL)
            project->features = newFeature;
        else
            lastFeature->next = newFeature;
    }
}

void removeFeatureFromProject(Project *project)
{
    // Remove feature from the current project
    FeatureNode *beforeFeature, *currentFeature;
    if(displayAndSelectFeatures(*project, &beforeFeature, &currentFeature))
    {
        // new head
        if(beforeFeature == NULL)
            project->features = currentFeature->next;
        else
            beforeFeature->next = currentFeature->next;
        free(currentFeature->feature);
        free(currentFeature);
        currentFeature = NULL;
    }
}

void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount)
{
    // Remove worker from the projects and delete project if he is the only 1 in it
    int workerNumber;
    Bool isAfterWorker = False;
    Worker *currentWorker;
    Project *currentProject;
    if(!isObjectEmpty(*workerCount, WORKERS_OBJECT) &&
        displayAndSelectWorker(workers, *workerCount, &workerNumber, LEAVE_COMPANY_OPTION))
    {
        currentWorker = workers[workerNumber];
        // Remove worker from projects
        for(int i = 0; i < currentWorker->projectCount; i++)
        {
            currentProject = currentWorker->projects[i];
            for(int j = 0; j < currentProject->workerCount; j++)
            {
                if (strcmp(currentWorker->name, currentProject->workers[j]->name) == 0)
                {
                    isAfterWorker = True;
                }
                else if (isAfterWorker)
                    currentProject->workers[j - 1] = currentProject->workers[j];
            }
            currentProject->workerCount -= 1;
            // no more workers on project
            if(currentProject->workerCount == 0)
                freeProject(projects, currentProject, projectCount);
            // reallocate memory of the project
            else
            {
                Worker **newWorkersPointer = (Worker **) realloc(currentProject->workers,
                                                                 (currentProject->workerCount) * sizeof(Worker *));
                if(newWorkersPointer == NULL)
                    exit(EXIT_CODE);
                currentProject->workers = newWorkersPointer;
            }
        }
        // delete worker
        isAfterWorker = False;
        for(int i = 0; i < *workerCount; i++)
        {
            if (strcmp(currentWorker->name, workers[i]->name) == 0)
                isAfterWorker = True;
            else if (isAfterWorker)
                workers[i - 1] = workers[i];
        }
        free(currentWorker->name);
        free(currentWorker->projects);
        free(currentWorker);
        currentWorker = NULL;
        *workerCount -= 1;
    }
}

void freeProject(Project *projects[], Project *currentProject, int *projectCount)
{
    // free all project allocations
    int isAfterProject = 0;
    for(int i = 0; i < *projectCount; i++)
    {
        if (strcmp(currentProject->name, projects[i]->name) == 0)
        {
            isAfterProject -= 1;
        }
        else if (isAfterProject)
        {
            projects[i - 1] = projects[i];
        }
    }
    free(currentProject->name);
    free(currentProject->workers);
    freeFeatures(currentProject->features);
    free(currentProject);
    currentProject = NULL;
    *projectCount -= 1;
}

void freeFeatures(FeatureNode *currentFeature)
{
    // Free all features allocations (from the given feature)
    if(currentFeature != NULL)
    {
        freeFeatures(currentFeature->next);
        free(currentFeature->feature);
        free(currentFeature);
    }
}

void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    // Free workers allocations
    for(int i = 0; i < workerCount; i++)
    {
        free(workers[i]->name);
        free(workers[i]->projects);
        free(workers[i]);
        workers[i] = NULL;
    }
    // Free projects allocations
    for(int i = 0; i < projectCount; i++)
    {
        free(projects[i]->name);
        free(projects[i]->workers);
        freeFeatures(projects[i]->features);
        free(projects[i]);
        projects[i] = NULL;
    }
}

void exitProgram(void)
{
    printf("Exiting...");
}