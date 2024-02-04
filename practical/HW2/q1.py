def search_max(cuts, n):
    res = 0
    for i in range(n):
        if cuts[i + 1] - cuts[i] > res:
            res = cuts[i + 1] - cuts[i]
    return res


line_one = input().split()
line_two = input().split()

length = int(line_one[0])
cut_count = int(line_one[1])
save = list(map(int, line_two))  # can be implemented normally

cuts = [0] * (cut_count + 2)
cuts[1] = length
controller = 2
ans = length

for i in save:
    cuts[controller] = i
    for j in range(controller, 0, -1):
        if cuts[j] < cuts[j - 1]:
            cuts[j], cuts[j - 1] = cuts[j - 1], cuts[j]
        else:
            if (ans == cuts[j + 1] - cuts[j - 1]):
                ans = search_max(cuts, controller)
            break
    print(ans)
    controller += 1
