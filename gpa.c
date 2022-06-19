#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char letter_grade[2];
	double credit;
} course;

double letter_grade_convert(char *letter_grade) {
	double grade = 0.00;
	if (strcmp(letter_grade, "AA") == 0) {
		grade = 4.00;
	}
	else if (strcmp(letter_grade, "BA") == 0) {
		grade = 3.50;
	}
	else if (strcmp(letter_grade, "BB") == 0) {
		grade = 3.00;
	}
	else if (strcmp(letter_grade, "CB") == 0) {
		grade = 2.50;
	}
	else if (strcmp(letter_grade, "CC") == 0) {
		grade = 2.00;
	}
	else if (strcmp(letter_grade, "DC") == 0) {
		grade = 1.50;
	}
	else if (strcmp(letter_grade, "DD") == 0) {
		grade = 1.00;
	}
	else if ((strcmp(letter_grade, "FF") == 0) || (strcmp(letter_grade, "VF") == 0)) {
		grade = 0.00;
	}
	else {
		return -1;
	}
	return grade;
}

course *get_info(int n_course) {
	course *course_array = malloc(n_course * sizeof(course));
	for (int i = 0; i < n_course; i++) {
		printf("Enter the credit and letter grade of %d. course\n", i + 1);
		scanf("%lf %s", &course_array[i].credit, course_array[i].letter_grade);
		if (letter_grade_convert(course_array[i].letter_grade) == -1) {
			printf("Undefined letter grade. Try again.\n");
			exit(1);
		}
	}
	return course_array;
}

double t_gpa(course *course_array, int n_course) {
	double total_credits = 0.00, total = 0.00;
	for (int i = 0; i < n_course; i++) {
		total_credits += course_array[i].credit;
		double converted_letter = letter_grade_convert(course_array[i].letter_grade);
		total += course_array[i].credit * converted_letter;
	}
	return total / total_credits;
}

double c_gpa(double current_credit, double current_gpa, int n_course, course *course_array) {
	double total_credits = 0.00, total = 0.00;
	double exist_total = current_credit * current_gpa;
	for (int i = 0; i < n_course; i++) {
		total_credits += course_array[i].credit;
		double converted_letter = letter_grade_convert(course_array[i].letter_grade);
		total += course_array[i].credit * converted_letter;
	}
	total += exist_total;
	total_credits += current_credit;
	return total / total_credits;
}

int main() {
	while (1) {
		int choice, n_course;
		double current_gpa, current_credit;
		printf("Which task would you like to perform?\n");
		printf("1 to calculate term grade point average.\n");
		printf("2 to calculate cumulative grade point average.\n");
		printf("-1 to exit.\n");
		printf("Choose: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1: 
				printf("Enter number of courses: ");
				scanf("%d", &n_course);
				course *course_array = get_info(n_course);
				double average = t_gpa(course_array, n_course);
				printf("## Term grade point average is: %.2lf\n", average);
				printf("\n");
				free(course_array);
				course_array = NULL;
				break;
			case 2:
				printf("Enter your current credits: ");
				scanf("%lf", &current_credit);
				printf("Enter your current gpa: ");
				scanf("%lf", &current_gpa);
				printf("Enter number of courses: ");
				scanf("%d", &n_course);
				course *course_array2 = get_info(n_course);
				double average_new = c_gpa(current_credit, current_gpa, n_course, course_array2);
				printf("## Cumulative grade point average is: %.2lf\n", average_new);
				printf("\n");
				free(course_array2);
				course_array2 = NULL;
				break;
			case -1: 
				return EXIT_SUCCESS;
			default:
				printf("Invalid operation. Try again.\n");
				printf("\n");
				break;
		}
	}
	return EXIT_FAILURE;
}
