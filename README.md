# Company Management System

## Overview
This project is a Company Management System implemented in C.<br>
It allows you to manage company operations including adding and removing workers, opening and working on projects, and presenting details about projects and workers.

## Features
- **Add Workers**: Add new workers to the company.
- **Open Projects**: Create and open new projects for the company.
- **Join Workers to Projects**: Join workers to existing projects in the company.
- **Present Projects Details**: Display details about projects including their workers and features.
- **Present Workers Details**: Display details about workers, including their projects.
- **Work on Projects**: Add/Remove features to/from existing projects in the company.
- **Remove Workers**: Remove workers from the company.

## How to Use
1. Run the program.
2. Select action from the presented options (enter a number).
3. Enter compatiables details (if needed).
5. Continue selecting actions until exiting.

## Technologies Used
- **Language:** C
- **Concepts:** Dynamic Memory, Structs, Pointers, Arrays

## Setup and Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/Fisher-Shira/Company-Management-System.git
2. Navigate to the project directory:
   ```bash
    cd Company-Management-System
3. Compile the project:
   ```bash
    gcc -o company_management company_management.c
4. Run the executable:
   ```bash
    ./company_management

## Project Structure
company_management.c – The main file containing the project logic.<br>
company_management.h - File contains declarations and definitions used throughout the project.<br>
