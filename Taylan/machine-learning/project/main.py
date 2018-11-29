from sklearn.linear_model import LinearRegression, Ridge
from sklearn.model_selection import LeaveOneOut, train_test_split
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import make_pipeline
from sklearn import metrics
import numpy as np
import matplotlib.pyplot as plt
import csv

def create_lists(name):
    """Creating the X y values for testing"""
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    x5 = []
    y = []
    with open(name, 'r', newline='', encoding='ISO-8859-1') as csvfile:
        rows = csv.DictReader(csvfile)
        for j, i in enumerate(rows):
            if j >= 100:
                break
            x1 = np.append(x1, i['x1']).astype(dtype=float)
            x2 = np.append(x2, i['x2']).astype(dtype=float)
            x3 = np.append(x3, i['x3']).astype(dtype=float)
            x4 = np.append(x4, i['x4']).astype(dtype=float)
            x5 = np.append(x5, i['x5']).astype(dtype=float)
            y = np.append(y, i['Y']).astype(dtype=float)
        
    csvfile.close()
    X = np.array([x1, x2, x3, x4, x5])
    return X, y

def create_actual_data_lists(name):
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    x5 = []
    with open(name, 'r', newline='', encoding='ISO-8859-1') as csvfile:
        rows = csv.DictReader(csvfile)
        for j, i in enumerate(rows):
            if j >= 100:
                x1 = np.append(x1, i['x1']).astype(dtype=float)
                x2 = np.append(x2, i['x2']).astype(dtype=float)
                x3 = np.append(x3, i['x3']).astype(dtype=float)
                x4 = np.append(x4, i['x4']).astype(dtype=float)
                x5 = np.append(x5, i['x5']).astype(dtype=float)
    csvfile.close()
    X = np.array([x1,x2,x3,x4,x5])
    return X

def calculate_error(predictions, y):
    """
    Calculating the error margin
    """
    error = []
    for i, pred in enumerate(predictions):
        error.append(pred - y[i])
    return error


X, y = create_lists("project-data.csv")
X = np.transpose(X)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)

# clf = LinearRegression(n_jobs=-1)

# clf.fit(X_train, y_train)
# pr = clf.predict(X_test)
# err = calculate_error(pr, y)

# accuracy = clf.score(X_test, y_test)
# accr2 = clf.score(X_train, y_train)

# PredListt = create_actual_data_lists("project-data.csv")
# PredListt = np.transpose(PredListt)

# pred_set = clf.predict(PredListt)
# pred_err = calculate_error(pred_set, y)


# print(pred_set, accuracy, accr2)

# plt.scatter(pr, err, c='b')
# plt.scatter(pred_set, pred_err, c='r')
# plt.show()

# model = LinearRegression()

# def do_calculation():
#     X, y = create_lists('project-data.csv')
# #    X = np.transpose(X)

#     md = make_pipeline(PolynomialFeatures(degree=3), Ridge())
#     md.fit(X,y)
#     y_p = md.predict(X)
#     print(y_p)

#     model.fit(X, y)  # training with all data
#     predictions = model.predict(X)  # predictions from training
#     err = calculate_error(predictions, y)

#     print_mse_for_all_data(err)  # just in case

#     test_pred, test_err = leave_one_out(X, y)

#     pred_list = create_actual_data_lists('project-data.csv')
   
#     pr = predict_values(pred_list, y)
#     print(pr[0])
    
#     plot(predictions, err, test_pred, test_err)
    


# def predict_values(pred_list, y):
#     pred_list = np.transpose(pred_list)
#     pred_set = model.predict(pred_list)
#     pred_err = calculate_error(pred_set, y)

#     return pred_set, pred_err

# def calculate_error(predictions, y):
#     """
#     Calculating the error margin
#     """
#     error = []
#     for i, pred in enumerate(predictions):
#         error.append(pred - y[i])
#     return error


# def plot(predictions, errors, test_pred, test_err):
#     """
#     Plot predicted Y values against each X's error margin
#     """
#     plt.scatter(predictions, errors, c='b')
#     plt.scatter(test_pred, test_err, c='r')
#     plt.hlines(0, 0, 40000)
#     plt.show()


# def leave_one_out(X, y):
#     ytest, ypred = loo_training(X, y)
#     err = []
#     for i in range(len(ytest)):
#         err.append(ypred[i] - ytest[i])
#     print_mean_square_error(ytest, ypred)
#     return ypred, err


# def loo_training(X, y):
#     ytests = []
#     ypredictions = []
#     loo = LeaveOneOut()

#     for train_index, test_index in loo.split(X):
#         # one row at a time
#         X_train, X_test = X[train_index], X[test_index]
#         y_train, y_test = y[train_index], y[test_index]

#         #model = LinearRegression()
#         model.fit(X=X_train, y=y_train)
#         y_pred = model.predict(X_test)

#         ytests += list(y_test)
#         ypredictions += list(y_pred)
#         print("Test confidence: {0}, \
#         Train confidence: {1} " .format(model.score(X_test, y_test),
#                                         model.score(X_train, y_train)))

#     return ytests, ypredictions


# def print_mean_square_error(ytests, ypred):
#     rr = metrics.r2_score(ytests, ypred)
#     ms_error = metrics.mean_squared_error(ytests, ypred)
#     print("Leave One Out Cross Validation")
#     print("R^2: {:.5f}% MSE: {:.5f}".format(rr*100, ms_error))


# def print_mse_for_all_data(errors):
#     error = np.square(errors)
#     error = np.mean(error)

#     print("MSE for all data: {:.5}". format(error))


# do_calculation()

poly_req = PolynomialFeatures(degree=4)
regressor = LinearRegression()

x_poly = poly_req.fit_transform(X)
regressor.fit(x_poly, y)

y_pred = regressor.predict(poly_req.fit_transform(X_test))

print("Accurracy: ", regressor.score(poly_req.fit_transform(X_test), y_test))

pred_list = create_actual_data_lists("project-data.csv")
pred_list = np.transpose(pred_list)

print("pred:",regressor.predict(poly_req.fit_transform(pred_list)))


