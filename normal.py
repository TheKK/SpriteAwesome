from PIL import Image
import numpy as np
import math


def Ry(Ty, n):
    R = np.array([[np.cos(Ty), 0, np.sin(Ty)],
                 [0, 1, 0],
                 [-np.sin(Ty), 0, np.cos(Ty)]])
    return np.dot(R, n)


def Rx(Tx, n):
    R = np.array([[1, 0, 0],
                  [0, np.cos(Tx), -np.sin(Tx)],
                  [0, np.sin(Tx), np.cos(Tx)]])
    return np.dot(R, n)


def normalizeNormal(a):
    t = []
    for i in range(len(a)):
        t.append((a[i] * 128 + 128 + 0.5).astype(int))
    return t


def calcNormal(u, d, l, r):
    result = []
    for i in range(len(l)):
        if u[i][0] == 0 and u[i][2] == 255:
            result.append((-1, -1, -1))
        else:
            theta = math.acos(l[i][0] / 255)
            ln = Ry(theta, np.array([-1, 0, 0]))
            theta = -math.acos(r[i][0] / 255)
            rn = Ry(theta, np.array([1, 0, 0]))
            theta = -math.acos(u[i][0] / 255)
            un = Rx(theta, np.array([0, -1, 0]))
            theta = math.acos(d[i][0] / 255)
            dn = Rx(theta, np.array([0, 1, 0]))
            result.append(ln + rn + un + dn)

    for i in range(len(result)):
        result[i] = result[i] / np.linalg.norm(result[i])

    return result


def main():
    upImg = Image.open("data/blue-up.png", "r")
    downImg = Image.open("data/blue-down.png", "r")
    leftImg = Image.open("data/blue-left.png", "r")
    rightImg = Image.open("data/blue-right.png", "r")
    normImg = Image.new("RGB", (upImg.size[0], upImg.size[1]))

    up = upImg.getdata()
    down = downImg.getdata()
    left = leftImg.getdata()
    right = rightImg.getdata()

    n = calcNormal(up, down, left, right)
    n = normalizeNormal(n)

    for j in range(upImg.size[1]):
        for i in range(upImg.size[0]):
            normImg.putpixel((i, j),
                             tuple(n[i + upImg.size[0] * j]))

    normImg.save("output/normal.png")


if __name__ == '__main__':
    main()
