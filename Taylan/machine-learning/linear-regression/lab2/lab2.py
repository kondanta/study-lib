import numpy as np
import matplotlib.pyplot as plt
import csv

# This is the same code from lab1. I'll add RSS calculation and
# data training(?)
class LinearRegression:

    def fill_lists(self, csv_name):
        list1 = list()
        list2 = list()
        
        with open(csv_name, "r", newline='',
                  encoding='ISO-8859-1') as csvfile:
            row = csv.DictReader(csvfile)
            for i in row:
                list1 = np.append(list1, i['Age'])\
                               .astype(dtype=float)
                list2 = np.append(list2,
                                       i['Experience'])\
                               .astype(dtype=float)
        return list1, list2

                
    def calculate_linear_regression_coefficients(self, age_list, exp_list):
        # N for the Nth number
        n = np.size(age_list)
        # Mean value of the lists
        mean_list1, mean_list2 = np.mean(age_list),\
        np.mean(exp_list)

        # Calculating the cross-deviation
        SS_xy = 0
        SS_xx = 0
        for i in range(n):
            SS_xy += (age_list[i] - mean_list1) * \
            (exp_list[i] - mean_list2)
            SS_xx += (age_list[i] - mean_list1) ** 2

        # Calculating the coefficients.
        coef_1 = SS_xy / SS_xx
        coef_2 = mean_list2 - (coef_1 * mean_list1)

        return coef_1, coef_2

    def build_the_graph(self, age_list, exp_list, coefficients):
        # creating the data points
        plt.scatter(age_list, exp_list, color="m",
                    marker="o")

        # calculating the regression line
        regression_line = coefficients[0]*age_list + coefficients[1]

        # drawing the regression line
        plt.plot(age_list, regression_line, color="g")

        # labeling the graph
        plt.xlabel('Age')
        plt.ylabel("Experience")

        # show the graph
        plt.show()


lr = LinearRegression()

# creating the lists
csv1_x, csv1_y = lr.fill_lists("team_1.csv")
csv2_x, csv2_y = lr.fill_lists("team_2.csv")

# creating the coefficients for the linear regression line
reg_line_csv1 = lr.calculate_linear_regression_coefficients(csv1_x, csv1_y)
reg_line_csv2 = lr.calculate_linear_regression_coefficients(csv2_x, csv2_y)

# Plotting the Graphs
# Giving reverse coefs for checking the model on the new data set
lr.build_the_graph(csv1_x, csv1_y, reg_line_csv2)
lr.build_the_graph(csv2_x, csv2_y, reg_line_csv1)
