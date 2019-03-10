from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans


img = Image.open("black-white-flower.jpg")

img = img.convert("1")
img = img.resize((320, 256))

xcoord = np.array([])  #320
ycoord = np.array([])  #256

for i in range(0, 320):
    for j in range(0, 256):
        if img.getpixel((i, j)) != 0:
            xcoord = np.append(xcoord, i)
            ycoord = np.append(ycoord, j)


plt.scatter(xcoord, ycoord)
plt.show()


X = np.vstack((xcoord, ycoord)).T

kmeans = KMeans(n_clusters=4).fit(X)
result = kmeans.predict(X)


c1_x = np.array([])
c2_x = np.array([])
c3_x = np.array([])
c4_x = np.array([])

c1_y = np.array([])
c2_y = np.array([])
c3_y = np.array([])
c4_y = np.array([])

i = 0
for k in result:
    if k == 1:
        c1_x = np.append(c1_x, xcoord[i])
        c1_y = np.append(c1_y, ycoord[i])
    if k == 2:
        c2_x = np.append(c2_x, xcoord[i])
        c2_y = np.append(c2_y, ycoord[i])
    if k == 3:
        c3_x = np.append(c3_x, xcoord[i])
        c3_y = np.append(c3_y, ycoord[i])
    if k == 0:
        c4_x = np.append(c4_x, xcoord[i])
        c4_y = np.append(c4_y, ycoord[i])
    i += 1


plt.scatter(c1_x, c1_y, color="red")
plt.scatter(c2_x, c2_y, color="blue")
plt.scatter(c3_x, c3_y, color="green")
plt.scatter(c4_x, c4_y, color="yellow")

plt.show()
