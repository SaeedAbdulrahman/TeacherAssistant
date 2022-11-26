#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double** weightedSum(int studentsnum, int gradesnum, double **grades, const double *weights){
    double** weightedGrades = grades;
    double sum = 0;
    for(int r = 0; r < studentsnum; r++){
        sum = 0;
        int c = 0;
        while(c < gradesnum){
            sum += weightedGrades[r][c] * (weights[c]/100);
            c++;
        }
        weightedGrades[r][c] = sum;
    }
    return weightedGrades;
}

double getAverage(int studentsnum, int gradesnum, double **grades) {
    double sum = 0;
    double average;
    for (int i = 0; i < studentsnum; i++) {
        sum += grades[i][gradesnum];
    }
    average = double(sum) / studentsnum;
    return average;
}

double** getGrades(int studentsnum, int gradesnum){
    double** grades;
    grades = new double* [studentsnum];
    for(int k=0; k<studentsnum;k++){
        grades[k] = new double[gradesnum+1];
    }
    cout << "\nEnter the grades of each student OUT OF 100: " << endl;
    int i = 0;
    while(i < studentsnum){
        cout << "Student " << i+1 << endl;
        int j = 0;
        while(j < gradesnum){
            double input;
            cout << "Grade " << j+1 << ": ";
            cin >> input;
            if(input < 0){
                cout << "\nPlease do not enter negative numbers!\n";
                continue;
            }else if(input > 100){
                cout << "\nPlease do not enter numbers greater than 100!\n";
                continue;
            }
            grades[i][j] = input;
            j++;
        }
        i++;
    }
    return grades;
}

double* weightGrades(int gradesnum){
    double *gradesweights;
    gradesweights = new double[gradesnum];
    cout<<"\nEnter the weights of each grade!";
    double weightsums = 0;
    while(abs(weightsums-100) > 0.1){
        weightsums = 0;
        cout<<"\nThe total weights should add up to 100!\n";
        int i = 0;
        while(i<gradesnum){
            double weight;
            cout << "Weight of Grade " << i+1 << ": ";
            cin >> weight;
            if(weight < 0 || weight > 100){
                cout << "\nThe grade's weight should be between 0-100\n";
                continue;
            }
            gradesweights[i] = weight;
            i++;
            weightsums += weight;
        }
    }
    return gradesweights;
}

char *letterGrade(int studentsnum, int gradesnum, double **weightedGrades) {
    char *letterGrades;
    letterGrades = new char[studentsnum];
    for(int i = 0; i<studentsnum; i++){
        double grade = weightedGrades[i][gradesnum];
        if(grade >= 90){
            letterGrades[i] = 'A';
        }else if(grade >= 80){
            letterGrades[i] = 'B';
        }else if(grade >= 70){
            letterGrades[i] = 'C';
        }else if(grade >= 60){
            letterGrades[i] = 'D';
        }else{
            letterGrades[i] = 'F';
        }
    }
    return letterGrades;
}

double getDeviation(int studentsnum, int gradesnum, double **weightedGrades, double average) {
    double x = 0;
    for(int i = 0; i<studentsnum; i++){
        double grade = weightedGrades[i][gradesnum];
        x += pow((grade - average),2);
    }
    return sqrt(x/(studentsnum-1));
}

int main()
{
    cout<<"Teacher Assistant Program\n";
    cout<<"-------------------------\n";
    string teacher,course;
    cout<<"\nTeacher Name: ";
    getline(cin, teacher);
    cout<<"Course Name: ";
    getline(cin, course);
    int studentsnum;
    cout<<"\nEnter the number of students in your class: ";
    cin>>studentsnum;
    while(studentsnum<=0){
        cout<<"\nPlease enter a non-zero number!";
        cout<<"\nEnter the number of students in your class: ";
        cin>>studentsnum;
    }
    int gradesnum;
    cout<<"Enter the number of grades for each student (maximum 20): ";
    cin>>gradesnum;
    while(gradesnum<=0 || gradesnum>20){
        if(gradesnum>20){cout<<"\nMaximum grades are 20!";}
        else{cout<<"\nPlease enter a non-zero number!";}
        cout<<"\nEnter the number of grades for each student (maximum 20): ";
        cin>>gradesnum;
    }
    double* gradesweights = weightGrades(gradesnum);
    double** grades = getGrades(studentsnum, gradesnum);
    double** weightedGrades = weightedSum(studentsnum, gradesnum, grades, gradesweights);
    char* letterGrades = letterGrade(studentsnum,gradesnum, weightedGrades);
    double average = getAverage(studentsnum, gradesnum, weightedGrades);
    double deviation = getDeviation(studentsnum, gradesnum, weightedGrades, average);
    cout << "\n----------------";
    cout << "\nInstructor - " << teacher;
    cout << "\nCourse - " << course;
    cout << "\n----------------";
    cout << "\nClass Average: " << average;
    cout << "\nStandard Deviation: " << deviation;
    cout << "\nVariance: " << pow(deviation, 2);
    cout << "\n----------------";
    cout << "\nWEIGHT DISTRIBUTION";
    cout << "\n----------------";
    for(int e = 0; e < gradesnum; e++){
        cout << "\nGrade " << e+1 << " - weighs " << gradesweights[e] << "%";
    }
    cout << "\n----------------";
    cout << "\nSTUDENTS GRADES";
    cout << "\n----------------";
    for(int student = 0; student < studentsnum; student++){
        cout << "\nStudent no. " << student+1;
        for(int cols = 0; cols <= gradesnum; cols++){
            if(cols==gradesnum){
                cout << "\nWeighted Sum - " << weightedGrades[student][cols] << " | Letter Grade - " << letterGrades[student];
            }else{
                cout << "\n\tGrade " << cols+1 << " : ";
                cout << weightedGrades[student][cols];}
        }
        cout << "\n";
    }
    return 0;
}
