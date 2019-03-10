from sklearn.linear_model import LinearRegression
import numpy as np
import matplotlib.pyplot as plt
import csv


def create_lists(name):
    """
    Creates respective X and y values for testing
    """
    zeroes = []
    x1 = []
    x2 = []
    x3 = []
    y = []
    with open(name, 'r', newline='', encoding='ISO-8859-1') as csvfile:
        rows = csv.DictReader(csvfile)
        for i in rows:
            zeroes = np.append(zeroes, '0').astype(dtype=float)
            x1 = np.append(x1, i["Power"]).astype(dtype=float)
            x2 = np.append(x2, i["Age"]).astype(dtype=float)
            x3 = np.append(x3, i["Experience"]).astype(dtype=float)
            y = np.append(y, i["Salary"]).astype(dtype=float)
    csvfile.close()
    X = np.array([zeroes, x1, x2, x3])
    return X, y


def do_calculation():
    X, y = create_lists('team.csv')
    X = np.transpose(X)

    reg = LinearRegression()
    reg.fit(X, y)  # training
    predictions = reg.predict(X)  # predictions from training
    err = calculate_error(predictions, y)
    plot(predictions, err)


def calculate_error(predictions, y):
    """
    Calculating the error margin
    """
    error = []
    for i, pred in enumerate(predictions):
        error.append(pred - y[i])
    return error


def plot(predictions, errors):
    """
    Plot predicted Y values against each X's error margin
    """
    plt.scatter(predictions, errors, c='b')
    plt.hlines(0, 0, 20000)
    plt.show()


do_calculation()
