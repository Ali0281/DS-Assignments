def count_m(n):
    counter = 0
    i = 2
    while True:
        temp = i * i * i
        if (temp > n): break
        counter += n // temp
        i += 1
    return counter


def binary_search(target):
    start = 8
    end = target * 8 + 1
    while start <= end:
        mid = start + (end - start) // 2
        if count_m(mid) < target:
            start = mid + 1
        else:
            if count_m(mid) == target:
                while count_m(mid - 1) == target:
                    mid -= 1
                return mid
            else:
                end = mid - 1
    return -1


m = int(input())
print(binary_search(m))
