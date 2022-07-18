# -*- coding: utf-8 -*-

from numpy import asarray
import numpy

# The first comment has been replaced.

ENERGY_LEVEL = [100, 113, 110, 85, 105, 102, 86, 63,
                81, 101, 94, 106, 101, 79, 94, 90, 97]


# The brute force method to solve first problem
def find_significant_energy_increase_brute(A):
    ELC = []
    for y in range(1, len(A)):
        ELC.append(A[y] - A[y - 1])
    maxSum = -100000
    startDex = 0
    endDex = 0
    for x, value in enumerate(ELC):
        currentSum = 0
        for y in range(x, len(ELC)):
            currentSum += ELC[y]
            if currentSum > maxSum:
                maxSum = currentSum
                startDex = x
                endDex = y
    print(maxSum)
    return((startDex, endDex + 1))


# The recursive method to solve first problem
def find_significant_energy_increase_recursive(A):
    ELC = []
    for y in range(1, len(A)):
        ELC.append(A[y] - A[y - 1])
    maximum = find_max_subarray(ELC, 0, len(ELC) - 1)
    print(maximum[0])
    # This method also utilizes the iterative method as a helper
    return find_significant_energy_increase_iterative(A)


def find_max_subarray(A, startDex, endDex):
    if endDex <= startDex:
        return (A[startDex], startDex, endDex)
    midDex = (startDex + endDex) // 2
    sumLeft = find_max_subarray(A, startDex, midDex)
    sumRight = find_max_subarray(A, midDex + 1, endDex)
    sumCross = find_max_crossing_subarray(A, startDex, endDex, midDex)
    if sumLeft[0] > sumRight[0] and sumLeft[0] > sumCross[0]:
        return sumLeft
    elif sumRight[0] > sumLeft[0] and sumRight[0] > sumCross[0]:
        return sumRight
    else:
        return sumCross


def find_max_crossing_subarray(A, startDex, endDex, midDex):
    lms = -100000
    currentSum = 0
    for x in range(midDex, startDex - 1, -1):
        currentSum += A[x]
        if currentSum > lms:
            lms = currentSum
    rms = -100000
    currentSum = 0
    for y in range(midDex + 1, endDex + 1):
        currentSum += A[y]
        if currentSum > rms:
            rms = currentSum
    if lms + rms > lms and lms + rms > rms:
        return (lms + rms, startDex, endDex)
    elif lms > lms + rms and lms > rms:
        return (lms, startDex, midDex)
    else:
        return (rms, midDex + 1, endDex)


# The iterative method to solve first problem
def find_significant_energy_increase_iterative(A):
    ELC = []
    for y in range(1, len(A)):
        ELC.append(A[y] - A[y - 1])
    maxSum = -100000
    startDex = 0
    endDex = 0
    currentSum = 0
    for x in range(0, len(ELC)):
        if currentSum <= 0:
            currentStart = x
            currentSum = ELC[x]
        else:
            currentSum += ELC[x]
        if currentSum > maxSum:
            maxSum = currentSum
            startDex = currentStart
            endDex = x
    print(maxSum)
    return (startDex, endDex + 1)


# The Strassen Algorithm to do the matrix multiplication
def square_matrix_multiply_strassens(A, B):

    """
    Return the product AB of matrix multiplication.
    Assume len(A) is a power of 2
    """

    A = asarray(A)

    B = asarray(B)

    assert A.shape == B.shape

    assert A.shape == A.T.shape

    assert (len(A) & (len(A) - 1)) == 0, "A is not a power of 2"

    # trivial case
    if len(A) == 1:
        return A * B
    a_00, a_01, a_10, a_11 = split_matrix(A)
    b_00, b_01, b_10, b_11 = split_matrix(B)

    m1 = square_matrix_multiply_strassens(a_00 + a_11, b_00 + b_11)
    m2 = square_matrix_multiply_strassens(a_10 + a_11, b_00)
    m3 = square_matrix_multiply_strassens(a_00, b_01 - b_11)
    m4 = square_matrix_multiply_strassens(a_11, b_10 - b_00)
    m5 = square_matrix_multiply_strassens(a_00 + a_01, b_11)
    m6 = square_matrix_multiply_strassens(a_10 - a_00, b_00 + b_01)
    m7 = square_matrix_multiply_strassens(a_01 - a_11, b_10 + b_11)

    c_00 = m1 + m4 - m5 + m7
    c_01 = m3 + m5
    c_10 = m2 + m4
    c_11 = m1 + m3 - m2 + m6

    c = numpy.vstack((numpy.hstack((c_00, c_01)), numpy.hstack((c_10, c_11))))
    return c


# split matrix into 4 quadrants
def split_matrix(m):
    r, c = m.shape
    rDiv, cDiv = r//2, c//2
    return m[:rDiv, :cDiv], m[:rDiv, cDiv:], m[rDiv:, :cDiv], m[rDiv:, cDiv:]


# Calculate the power of a matrix in O(k)
def power_of_matrix_navie(A, k):
    """
    Return A^k.
    time complexity = O(k)
    """
    if k == 0:
        return numpy.identity(len(A))
    if k == 1:
        return A
    multipliedByMatrix = A
    for x in range(0, k - 1):
        A = square_matrix_multiply_strassens(A, multipliedByMatrix)
    print(A)
    return A


# Calculate the power of a matrix in O(log k)
def power_of_matrix_divide_and_conquer(A, k):
    """
    Return A^k.
    time complexity = O(log k)
    """
    if k == 0:
        return numpy.identity(len(A))
    if k == 1:
        return A
    splitK = k//2
    m = square_matrix_multiply_strassens(
        power_of_matrix_divide_and_conquer(A, splitK),
        power_of_matrix_divide_and_conquer(A, splitK))
    if k % 2 == 1:
        m = square_matrix_multiply_strassens(m, A)
    print(m)
    return m


def test():

    assert(find_significant_energy_increase_brute(ENERGY_LEVEL) == (7, 11))
    assert(find_significant_energy_increase_recursive(ENERGY_LEVEL) == (7, 11))
    assert(find_significant_energy_increase_iterative(ENERGY_LEVEL) == (7, 11))
    assert((square_matrix_multiply_strassens(
        [[0, 1], [1, 1]], [[0, 1], [1, 1]]) == asarray(
        [[1, 1], [1, 2]])).all())
    assert((power_of_matrix_navie(
        [[0, 1], [1, 1]], 3) == asarray([[1, 2], [2, 3]])).all())
    assert((power_of_matrix_divide_and_conquer(
        [[0, 1], [1, 1]], 3) == asarray([[1, 2], [2, 3]])).all())


if __name__ == '__main__':
    test()
