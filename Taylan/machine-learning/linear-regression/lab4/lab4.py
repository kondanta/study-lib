from sklearn.linear_model import LinearRegression
from sklearn.model_selection import LeaveOneOut
from sklearn import metrics
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
    X, y = create_lists('teams_comb.csv')
    X = np.transpose(X)

    reg = LinearRegression()
    reg.fit(X, y)  # training with all data
    predictions = reg.predict(X)  # predictions from training
    err = calculate_error(predictions, y)

    print_mse_for_all_data(err)  # just in case

    test_pred, test_err = leave_one_out(X, y)
    plot(predictions, err, test_pred, test_err)


def calculate_error(predictions, y):
    """
    Calculating the error margin
    """
    error = []
    for i, pred in enumerate(predictions):
        error.append(pred - y[i])
    return error


def plot(predictions, errors, test_pred, test_err):
    """
    Plot predicted Y values against each X's error margin
    """
    plt.scatter(predictions, errors, c='b')
    plt.scatter(test_pred, test_err, c='r')
    plt.hlines(0, 0, 40000)
    plt.show()


def leave_one_out(X, y):
    ytest, ypred = loo_training(X, y)
    err = []
    for i in range(len(ytest)):
        err.append(ypred[i] - ytest[i])
    print_mean_square_error(ytest, ypred)
    return ypred, err


def loo_training(X, y):
    ytests = []
    ypredictions = []
    loo = LeaveOneOut()

    for train_index, test_index in loo.split(X):
        # one row at a time
        X_train, X_test = X[train_index], X[test_index]
        y_train, y_test = y[train_index], y[test_index]

        model = LinearRegression()
        model.fit(X=X_train, y=y_train)
        y_pred = model.predict(X_test)

        ytests += list(y_test)
        ypredictions += list(y_pred)

    return ytests, ypredictions


def print_mean_square_error(ytests, ypred):
    rr = metrics.r2_score(ytests, ypred)
    ms_error = metrics.mean_squared_error(ytests, ypred)
    print("Leave One Out Cross Validation")
    print("R^2: {:.5f}% MSE: {:.5f}".format(rr*100, ms_error))


def print_mse_for_all_data(errors):
    error = np.square(errors)
    error = np.mean(error)

    print("MSE for all data: {:.5}". format(error))


do_calculation()
