import numpy as np
import matplotlib.pyplot as plt
import csv

class LinearRegression:
    def __init__(self):
        self.list1 = np.array([])
        self.list2 = np.array([])

    def fill_lists(self):
        with open("team.csv", "r", newline='',
                  encoding='ISO-8859-1') as csvfile:
            row = csv.DictReader(csvfile)
            for i in row:
                self.list1 = np.append(self.list1, i['Age'])\
                               .astype(dtype=float)
                self.list2 = np.append(self.list2,
                                       i['Experience'])\
                               .astype(dtype=float)


    def calculate_linear_regression_coefficients(self):
        # N for the Nth number
        n = np.size(self.list1)
        # Mean value of the lists
        mean_list1, mean_list2 = np.mean(self.list1),
        np.mean(self.list2)

        # Calculating the cross-deviation
        SS_xy = 0
        SS_xx = 0
        for i in range(n):
            SS_xy += (self.list1[i] - mean_list1) * \
            (self.list2[i] - mean_list2)
            SS_xx += (self.list1[i] - mean_list1) ** 2

        # Calculating the coefficients.
        coef_1 = SS_xy/ SS_xx
        coef_2 = mean_list2 - (coef_1 * mean_list1)

        return coef_1, coef_2

    def build_the_graph(self):
        # creating the data points
        plt.scatter(self.list1, self.list2, color="m",
                    marker="o")

        # calculating the regression line
        coefs = self.calculate_linear_regression_coefficients()
        regression_line = coefs[0]*self.list1 + coefs[1]

        # drawing the regression line
        plt.plot(self.list1, regression_line, color="g")

        # labeling the graph
        plt.xlabel('Age')
        plt.ylabel("Experience")

        # show the graph
        plt.show()


lr = LinearRegression()

lr.fill_lists()
lr.calculate_linear_regression_coefficients()
lr.build_the_graph()
