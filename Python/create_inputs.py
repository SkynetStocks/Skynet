import random

inputs_file=open("testing-multisets.txt","w")

for i in range(20):
    isEven=True
    for j in range(5):
        num=(int)(random.uniform(0, 100))
        if num % 2 != 0:
            isEven=False
        inputs_file.write(str(num) + ',')
    if isEven:
        inputs_file.write("1")
    else:
        inputs_file.write("0")
    if i != 99:
        inputs_file.write("\n")

inputs_file.close()
