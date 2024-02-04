class House:
    def __init__(self, amount):
        self.amount = amount
        self.position = 0


def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]
        mergeSort(left)
        mergeSort(right)
        merge(arr, left, right)


def merge(arr, left, right):
    left_pointer = right_pointer = main_pointer = 0
    while left_pointer < len(left) and right_pointer < len(right):
        if data[left[left_pointer]].amount <= data[right[right_pointer]].amount:
            arr[main_pointer] = left[left_pointer]
            left_pointer += 1
        else:
            arr[main_pointer] = right[right_pointer]
            right_pointer += 1
        main_pointer += 1
    while left_pointer < len(left):
        arr[main_pointer] = left[left_pointer]
        left_pointer += 1
        main_pointer += 1
    while right_pointer < len(right):
        arr[main_pointer] = right[right_pointer]
        right_pointer += 1
        main_pointer += 1


count = int(input())
data = [0] * count
indexes = [i for i in range(count)]
temp_counter = 0
for i in list(map(int, input().split())):
    data[temp_counter] = House(i)
    temp_counter += 1

mergeSort(indexes)

dist = 0
mode = 1
positive_position = negative_position = 0
for i in indexes:
    if mode == 1:
        dist += positive_position
        data[i].position = positive_position
        positive_position += data[i].amount
    else:
        dist += negative_position
        data[i].position = -(negative_position + data[i].amount)
        negative_position += data[i].amount
    mode *= -1
print(format(dist / count, '.7f'))
for i in data:
    print(i.position, end=' ')
