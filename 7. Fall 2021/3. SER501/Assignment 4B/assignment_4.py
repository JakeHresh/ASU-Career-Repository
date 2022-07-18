# -*- coding: utf-8 -*-
"""
SER501 Assignment 4 scaffolding code
created by: Xiangyu Guo
#ToDo
author:
"""
import numpy as np


# ============================== Counting Pond ================================


def visitAdjacentSquare(i, j, waterIndices, m, n):
    if i < 0 or j < 0 or i > m - 1 or j > n - 1:
        return
    if waterIndices[i][j][0] == -1 or waterIndices[i][j][1]:
        return
    waterIndices[i][j][1] = True
    visitAdjacentSquare(i + 1, j - 1, waterIndices, m, n)
    visitAdjacentSquare(i, j - 1, waterIndices, m, n)
    visitAdjacentSquare(i - 1, j - 1, waterIndices, m, n)
    visitAdjacentSquare(i - 1, j, waterIndices, m, n)
    visitAdjacentSquare(i - 1, j + 1, waterIndices, m, n)
    visitAdjacentSquare(i, j + 1, waterIndices, m, n)
    visitAdjacentSquare(i + 1, j + 1, waterIndices, m, n)
    visitAdjacentSquare(i + 1, j, waterIndices, m, n)


def count_ponds(G):
    m = len(G)
    n = len(G[0])
    pondCount = 0
    waterIndices = []
    for i in range(m):
        col = []
        for j in range(n):
            if G[i][j] == "#":
                col.append([1, False])
            else:
                col.append([-1, False])
        waterIndices.append(col)
    for i in range(m):
        for j in range(n):
            if waterIndices[i][j][0] == 1 and not waterIndices[i][j][1]:
                visitAdjacentSquare(i, j, waterIndices, m, n)
                pondCount = pondCount + 1
    return pondCount

# ======================== Longest Ordered Subsequence ========================


def longest_ordered_subsequence(L):
    n = len(L)
    sortedArray = np.sort(L)
    rows = n + 1
    cols = n + 1
    table = []
    for i in range(rows):
        col = []
        for j in range(cols):
            col.append(0)
        table.append(col)
    for i in range(1, rows):
        for j in range(1, cols):
            if L[i - 1] == sortedArray[j - 1]:
                table[i][j] = 1 + table[i - 1][j - 1]
            else:
                table[i][j] = max(table[i - 1][j], table[i][j - 1])
    return table[n][n]


# =============================== Supermarket =================================


def supermarket(Items):
    n = len(Items)
    time = 0
    for i in range(n):
        if Items[i][1] > time:
            time = Items[i][1]
    rows = time + 1
    cols = n + 1
    table = []
    for i in range(rows):
        col = []
        for j in range(cols):
            col.append([0, i])
        table.append(col)
    for j in range(1, cols):
        for i in range(1, rows):
            if table[i][j][1] <= i:
                if (Items[j - 1][0] +
                        table[i - table[i][j][1]][j - 1][0]
                        > table[i][j - 1][0]):
                    table[i][j][0] = (Items[j - 1][0] +
                                      table[i - table[i][j][1]][j - 1][0])
                else:
                    table[i][j][0] = table[i][j - 1][0]
            else:
                table[i][j][0] = table[i][j - 1][0]
    return table[rows - 1][cols - 1][0]

# =============================== Unit tests ==================================


def test_suite():

    if count_ponds(["#--------##-",
                    "-###-----###",
                    "----##---##-",
                    "---------##-",
                    "---------#--",
                    "--#------#--",
                    "-#-#-----##-",
                    "#-#-#-----#-",
                    "-#-#------#-",
                    "--#-------#-"]) == 3:
        print('passed')
    else:
        print('failed')

    if longest_ordered_subsequence([1, 7, 3, 5, 9, 4, 8]) == 4:
        print('passed')
    else:
        print('failed')

    # if supermarket([(50, 2), (10, 1), (20, 2), (30, 1)]) == 80:
    #     print('passed')
    # else:
    #     print('failed')

    # ToDo More test cases


if __name__ == '__main__':
    test_suite()
